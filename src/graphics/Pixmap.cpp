/*
** EPITECH PROJECT, 2023
** Wallpaper-Creator
** File description:
** Pixmap
*/

#include <iostream>

#include <X11/Xproto.h>
#include <cstring>

#include "graphics/Pixmap.hpp"
#include "graphics/window/Window.hpp"

#include <Imlib2.h>

wcreator::Pixmap::Pixmap(Window &window) :
Drawable(XCreatePixmap(&Context::getDisplay(), window.getHandle(), window.width(), window.height(), window.depth())) {
    __depth = window.depth();
    __width = window.width();
    __height = window.height();
    __image = imlib_create_image(window.width(), window.height());

    imlib_context_set_display(&Context::getDisplay());
    imlib_context_set_visual(&Context::getDefaultVisual());
    imlib_context_set_colormap(Context::getDefaultColormap());
    // __context = XCreateGC(&Context::getDisplay(), __internal, 0, nullptr);
}

wcreator::Pixmap::Pixmap(const cv::Mat &frame) :
Drawable(XCreatePixmap(&Context::getDisplay(), Context::getRootWindow(), frame.cols, frame.rows, 24)) {
    __width = frame.cols;
    __height = frame.rows;
    __depth = 24;
    __image = imlib_create_image_using_data(frame.cols, frame.rows, (DATA32*)frame.data);
    // __context = XCreateGC(&Context::getDisplay(), __internal, 0, nullptr);
    __draw();
}

wcreator::Pixmap::Pixmap(Window &window, const cv::Mat &frame) :
Pixmap(window) {
    // __image.depth() = window.depth();
    drawFrame(frame);
}

wcreator::Pixmap::~Pixmap() {
    XFreePixmap(&Context::getDisplay(), __internal);
    // XFreeGC(&Context::getDisplay(), __context);
}

void wcreator::Pixmap::drawFrame(const cv::Mat &frame) {
    // Updating the image data
    // __image.update(frame);
    // Drawing the image
    // __draw();

    // Using Imlib
    // Imlib_Image img = imlib_create_image_using_data(frame.cols, frame.rows,  (DATA32 *)frame.data);
    //---
    // if (!__image)
    // imlib_free_image();
        // imlib_image_put_back_data((DATA32 *)frame.data);
    // else
    if (!__image)
        __image = imlib_create_image_using_data(frame.cols, frame.rows, (DATA32 *)frame.data);
    imlib_context_set_image(__image);
    auto ptr = imlib_image_get_data();
    std::memcpy(ptr, frame.data, frame.cols * frame.rows * 4);
    // imlib_image_put_back_data(ptr);
    // Rendering the image
    __draw();
}

int &wcreator::Pixmap::depth() {
    return __depth;
}

unsigned int &wcreator::Pixmap::width() {
    return __width;
}

unsigned int &wcreator::Pixmap::height() {
    return __height;
}

void wcreator::Pixmap::__draw() {
    // GC __context = XCreateGC(&Context::getDisplay(), __internal, 0, nullptr);
    // Drawing the image
    // std::cout << "Pixmap: " << __internal << std::endl;
    // std::cout << "Context: " << XGContextFromGC(__context) << std::endl;
    // XPutImage(&Context::getDisplay(), __internal, __context, __image.getHandle(), 0, 0, 0, 0, __image.width(), __image.height());
    // XFreeGC(&Context::getDisplay(), __context);
    // Set Display, Visual and Colormap

    // Set Drawable
    imlib_context_set_drawable(__internal);
    // Render the Image
    imlib_render_image_on_drawable(0, 0);
    // imlib_free_image();
}

const wcreator::XPixmap wcreator::Pixmap::INVALID_PIXMAP = 0;
