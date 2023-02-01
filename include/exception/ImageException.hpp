/*
** EPITECH PROJECT, 2023
** Wallpaper-Creator
** File description:
** ImageException
*/

#pragma once

#include <string>
#include <exception>

namespace wcreator::error {
    class ImageException : public std::exception {
        std::string __msg;

        public:
            ImageException(const std::string &msg) : __msg(msg) {}
            ~ImageException() = default;

            virtual const char *what() const noexcept {
                return __msg.c_str();
            }

    };
}
