/*
** EPITECH PROJECT, 2023
** Wallpaper-Creator
** File description:
** Context
*/

#pragma once

#include <X11/Xlib.h>
#include <string>

#include "utils/Types.hpp"

namespace wcreator {
    class Context {
        static Context *__instance;
        XDisplay *__display;

        Context(const std::string &name);

        static int __handler(Display *display, XErrorEvent *event);

        public:
            Context(const Context &other) = delete;
            ~Context();

            Context &operator=(const Context &other) = delete;

            static Context &getContext(const std::string &name = "");
            static Context &modifyContext(const std::string &name = "");

            static XWindow &getRootWindow();

            static XDisplay &getDisplay();

            static XScreen &getDefaultScreen();
            static XScreen &getScreen(const size_t &screen);

            static XVisual &getDefaultVisual();

            static XColormap &getDefaultColormap();
    };

    namespace error {

        class ContextException : public std::exception {
            public:
                ContextException(const std::string &message) : __message(message) {}
                ~ContextException() override = default;

                const char *what() const noexcept override {
                    return __message.c_str();
                }

            private:
                std::string __message;
        };
    }
}
