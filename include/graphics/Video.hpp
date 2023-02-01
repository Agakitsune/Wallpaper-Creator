/*
** EPITECH PROJECT, 2023
** Wallpaper-Creator
** File description:
** Video
*/

#pragma once

#include <string>
#include <queue>
#include <filesystem>
#include <thread>

#include "utils/thread/AsyncQueue.hpp"

#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/videoio.hpp>
#include <opencv4/opencv2/highgui.hpp>

namespace wcreator {
    class Video {
        cv::VideoCapture __video;

        AsyncQueue<cv::Mat> __frameCache;
        size_t __cacheSize = 64;

        size_t __pos = 0;

        std::thread __cacheLoader;
        std::mutex __lock;

        std::atomic<bool> __isRunning = true;
        std::atomic<bool> __isLoaded = false;

        unsigned int __framerate;

        public:
            Video(const std::string &file);
            ~Video();

            Video &setCacheSize(const size_t &size);

            void loadVideo(const std::string &file);

            cv::Mat getFrame();

            const unsigned int &getFramerate() const;

        private:
            void __loadFrame();

    };
}
