/*
** EPITECH PROJECT, 2023
** Wallpaper-Creator
** File description:
** Vector
*/

#pragma once

#include <array>
#include <concepts>

namespace wcreator::utils {
    template<typename T>
    requires std::is_arithmetic_v<T>
    class Vector {
        std::array<T, 2> __data;

        public:
            Vector() = default;
            Vector(const T &value) {
                __data.fill(value);
            }

            Vector(const T &x, const T &y) {
                __data[0] = x;
                __data[1] = y;
            }

            ~Vector() = default;

            T &x() { return __data[0]; }
            T &y() { return __data[1];}
            const T &x() const { return __data[0]; }
            const T &y() const { return __data[1]; }

            void fill(const T &value) {
                __data.fill(value);
            }

    };
}
