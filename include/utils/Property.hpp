/*
** EPITECH PROJECT, 2023
** Wallpaper-Creator
** File description:
** Property
*/

#pragma once

#include <concepts>
#include <functional>

namespace wcreator::utils {
    template<typename T>
    class Property {
        T &__data;

        std::function<void()> __callback;

        public:
            Property(T &data) : __data(data) {};
            ~Property() = default;

            std::function<void()> &callback() { return __callback; }

            template<typename U>
            requires std::convertible_to<U, T>
            Property &operator=(const U &value) {
                __data = value;
                if (__callback)
                    __callback();
                return *this;
            }

            template<typename U>
            requires std::convertible_to<U, T>
            Property &operator=(U &&value) {
                __data = value;
                if (__callback)
                    __callback();
                return *this;
            }

            operator T&() { return __data; }
            operator T() const { return __data; }

    };
}
