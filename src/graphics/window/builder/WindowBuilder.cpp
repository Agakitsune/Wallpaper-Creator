/*
** EPITECH PROJECT, 2023
** Wallpaper-Creator
** File description:
** WindowBuilder
*/

#include "graphics/window/builder/WindowBuilder.hpp"

using namespace wcreator::builder;

WindowBuilder &WindowBuilder::setParentWindow(const XWindow &parentwindow) {
    __parentWindow = parentwindow;
    return *this;
}

WindowBuilder &WindowBuilder::setPosition(const int &x, const int &y) {
    return setX(x).setY(y);
}

WindowBuilder &WindowBuilder::setX(const int &x) {
    __x = x;
    __anchored.x() = true;
    return *this;
}

WindowBuilder &WindowBuilder::setY(const int &y) {
    __y = y;
    __anchored.y() = true;
    return *this;
}

WindowBuilder &WindowBuilder::setDimension(const unsigned int &width, const unsigned int &height) {
    return setWidth(width).setHeight(height);
}

WindowBuilder &WindowBuilder::setWidth(const unsigned int &width) {
    __width = width;
    __resized.x() = true;
    return *this;
}

WindowBuilder &WindowBuilder::setHeight(const unsigned int &height) {
    __height = height;
    __resized.y() = true;
    return *this;
}

WindowBuilder &WindowBuilder::setScreen(const wcreator::XScreen &screen) {
    __screen = screen;
    return *this;
}

WindowBuilder &WindowBuilder::setDepth(const int &depth) {
    __depth = depth;
    return *this;
}

std::unique_ptr<wcreator::Window> WindowBuilder::build() const {
    XSetWindowAttributes attr;
    attr.override_redirect = true;
    XWindow window = XCreateWindow(
        &Context::getDisplay(),
        __parentWindow,
        __x,
        __y,
        __width,
        __height,
        0,
        __depth,
        InputOutput,
        CopyFromParent,
        CWOverrideRedirect,
        &attr
    );
    return std::move(std::make_unique<Window>(window));
}

void WindowBuilder::__setAnchored() const {

}

void WindowBuilder::__setResized() const {

}

