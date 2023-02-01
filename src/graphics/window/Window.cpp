/*
** EPITECH PROJECT, 2023
** Wallpaper-Creator
** File description:
** Window
*/

#include <iostream>

#include "graphics/window/Window.hpp"

wcreator::Window::Window(const XWindow &XWindow) : Drawable(XWindow) {
    XWindowAttributes attr;

    XGetWindowAttributes(&Context::getDisplay(), getHandle(), &attr);
    __x = attr.x;
    __y = attr.y;
    __width = attr.width;
    __height = attr.height;
    __depth = attr.depth;
    __pixmap = new Pixmap(*this);
}

wcreator::Window::~Window() {
    XDestroyWindow(&Context::getDisplay(), getHandle());
    delete __pixmap;
}

wcreator::utils::Property<int> wcreator::Window::x() {
    utils::Property<int> property = __x;
    property.callback() = [this] { __refresh(); };
    return std::move(property);
}

wcreator::utils::Property<int> wcreator::Window::y() {
    utils::Property<int> property = __y;
    property.callback() = [this] { __refresh(); };
    return std::move(property);
}

wcreator::utils::Property<unsigned int> wcreator::Window::width() {
    utils::Property<unsigned int> property = __width;
    property.callback() = [this] { __refresh(); };
    return std::move(property);
}

wcreator::utils::Property<unsigned int> wcreator::Window::height() {
    utils::Property<unsigned int> property = __height;
    property.callback() = [this] { __refresh(); };
    return std::move(property);
}


const int &wcreator::Window::x() const {
    return __x;
}

const int &wcreator::Window::y() const {
    return __y;
}

const unsigned int &wcreator::Window::width() const {
    return __width;
}

const unsigned int &wcreator::Window::height() const {
    return __height;
}

const int &wcreator::Window::depth() const {
    return __depth;
}

void raise() const {
    XRaiseWindow(&Context::getDisplay(), getHandle());
}

void lower() const {
    XLowerWindow(&Context::getDisplay(), getHandle());
}

void wcreator::Window::display() const {
    XMapWindow(&Context::getDisplay(), getHandle());
}

void wcreator::Window::hide() const {
    XUnmapWindow(&Context::getDisplay(), getHandle());
}

void wcreator::Window::drawFrame(const cv::Mat &frame) {
    __pixmap->drawFrame(frame);
    // If the depth of the pixmap is different from the depth of the window
    // if (__pixmap->depth() != depth()) {
    //     __pixmap->depth() = depth();
    //     // __pixmap->depth(false) = depth();
    //     std::cout << "Pixmap depth: " << __pixmap->depth() << std::endl;
    //     std::cout << "Window depth: " << depth() << std::endl;
    //     std::cout << "Pixmap intern depth: " << __pixmap->depth(false) << std::endl;
    // }
    // std::cout << "Pixmap depth: " << __pixmap->depth() << std::endl;
    // std::cout << "Window depth: " << depth() << std::endl;
    // std::cout << "Pixmap handle: " << __pixmap->getHandle() << std::endl;
    // std::cout << "Window handle: " << getHandle() << std::endl;
    // std::cout << "Pixmap width: " << __pixmap->width() << std::endl;
    // std::cout << "Window width: " << width() << std::endl;
    // std::cout << "Pixmap height: " << __pixmap->height() << std::endl;
    // std::cout << "Window height: " << height() << std::endl;
    // Drawing the pixmap on the window
    XClearWindow(&Context::getDisplay(), getHandle());
    XSetWindowBackgroundPixmap(&Context::getDisplay(), getHandle(), __pixmap->getHandle());
}

void wcreator::Window::drawPixmap(const Pixmap &pixmap) {
    XSetWindowBackgroundPixmap(&Context::getDisplay(), getHandle(), pixmap.getHandle());
}

void wcreator::Window::__refresh() const {
    XMoveResizeWindow(&Context::getDisplay(), getHandle(), __x, __y, __width, __height);
}
