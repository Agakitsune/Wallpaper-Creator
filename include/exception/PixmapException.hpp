/*
** EPITECH PROJECT, 2023
** Wallpaper-Creator
** File description:
** PixmapException
*/

#pragma once

#include <string>
#include <exception>

namespace wcreator::error {
    class PixmapException : public std::exception {
        std::string __msg;

        public:
            PixmapException(const std::string &msg) : __msg(msg) {}
            ~PixmapException() = default;

            virtual const char *what() const noexcept {
                return __msg.c_str();
            }

    };
}
