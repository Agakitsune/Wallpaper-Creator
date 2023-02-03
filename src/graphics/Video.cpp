/*
** EPITECH PROJECT, 2023
** Wallpaper-Creator
** File description:
** Video
*/

#include <iostream>

#include "graphics/Video.hpp"
#include "exception/VideoException.hpp"

using namespace wcreator;

Video::Video(const std::string &file) : __video(file) {
    if (!std::filesystem::exists(file))
        throw error::VideoException(file + ": no such file or directory");
    if (!__video.isOpened())
        throw error::VideoException(file + ": failed to open video file");
    // Starts to load the cache
    __cacheLoader = std::thread(&Video::__loadFrame, this);
    while (!__isLoaded) {}
    std::cout << "Frame count: " << __video.get(cv::CAP_PROP_FRAME_COUNT) << std::endl;
    // std::cout << "Framerate: " << __video.get(cv::CAP_PROP_FPS) << std::endl;
    __framerate = __video.get(cv::CAP_PROP_FPS);
}

Video::~Video() {
    // Wait for the cache loader to finish
    __isRunning = false;
    if (__cacheLoader.joinable())
        __cacheLoader.join();
    // Release all the frames and the capture
    while (!__frameCache.empty()) {
        __frameCache.front().release();
        __frameCache.pop();
    }
    __video.release();
}

Video &Video::setCacheSize(const size_t &size) {
    __cacheSize = size;
    return *this;
}

void Video::loadVideo(const std::string &file) {
    if (!std::filesystem::exists(file))
        throw error::VideoException(file + ": no such file or directory");
    __video.open(file);
    if (!__video.isOpened())
        throw error::VideoException(file + ": failed to open video file");
}

cv::Mat Video::getFrame() {
    // Lock the cache
    cv::Mat frame;
    cv::Mat tmp;
    // Poll the frame
    while (!__frameCache.poll(tmp))
        std::this_thread::sleep_for(std::chrono::milliseconds(1 / __framerate));
    // std::cout << "polling frame "  << std::endl;
    // Getting the frame in the cache and convert to rgba
    cv::cvtColor(tmp, frame, cv::COLOR_BGR2BGRA);
    return frame;
}

const unsigned int &Video::getFramerate() const {
    return __framerate;
}

void Video::__loadFrame() {
    const float factor = 0.5;
    //---
    while (__isRunning) {
        if (__pos >= __video.get(cv::CAP_PROP_FRAME_COUNT)) {
            __video.set(cv::CAP_PROP_POS_FRAMES, 0);
            __pos = 0;
        }
        while (__frameCache.size() < __cacheSize) {
            ++__pos;
            cv::Mat frame;
            __video >> frame;
            if (frame.empty()) {
                std::cerr << "frame is empty, skipping..." << std::endl;
                break;
                // throw error::VideoException("Failed to get frame");
            }
            // std::cout << "pushing frame " << __pos << std::endl;
            __frameCache.push(frame);
        }
        __isLoaded = true;

        const float dt = (__cacheSize * (1.0f / __framerate) - (__cacheSize * factor)) * 1000;
        // std::cout << "Delta:" << dt << std::endl;
        // std::this_thread::sleep_for(std::chrono::milliseconds((int64_t)dt));
    }
}
