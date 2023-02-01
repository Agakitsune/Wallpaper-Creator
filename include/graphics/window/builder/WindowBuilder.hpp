/*
** EPITECH PROJECT, 2023
** Wallpaper-Creator
** File description:
** WindowBuilder
*/

#pragma once

#include "Context.hpp"
#include "utils/Builder.hpp"
#include "graphics/window/Window.hpp"

#include "utils/Types.hpp"
#include "utils/Vector.hpp"

namespace wcreator::builder {
    class WindowBuilder : public utils::Builder<Window> {
        XWindow __parentWindow = Context::getRootWindow();
        int __x = 0;
        int __y = 0;
        unsigned int __width;
        unsigned int __height;
        XScreen &__screen = Context::getDefaultScreen();
        int __depth = DefaultDepthOfScreen(&__screen);

        utils::Vector<bool> __anchored = false;
        utils::Vector<bool> __resized = false;

        public:
            WindowBuilder() = default;
            ~WindowBuilder() = default;

            WindowBuilder &setParentWindow(const XWindow &Parentwindow);

            WindowBuilder &setPosition(const int &x, const int &y);
            WindowBuilder &setX(const int &x);
            WindowBuilder &setY(const int &y);

            WindowBuilder &setDimension(const unsigned int &width, const unsigned int &height);
            WindowBuilder &setWidth(const unsigned int &width);
            WindowBuilder &setHeight(const unsigned int &height);

            WindowBuilder &setScreen(const XScreen &screen);

            WindowBuilder &setDepth(const int &depth);

            virtual std::unique_ptr<Window> build() const override;

        private:
            void __setAnchored() const;
            void __setResized() const;

    };
}
