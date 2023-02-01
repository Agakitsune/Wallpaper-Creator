/*
** EPITECH PROJECT, 2023
** Wallpaper-Creator
** File description:
** VideoException
*/

#pragma once

#include <string>
#include <exception>

namespace wcreator::error {
    class VideoException : public std::exception {
        std::string __msg;

        public:
            VideoException(const std::string &msg) : __msg(msg) {}
            ~VideoException() = default;

            virtual const char *what() const noexcept {
                return __msg.c_str();
            }

    };
}
