/*
** EPITECH PROJECT, 2023
** Wallpaper-Creator
** File description:
** Drawable
*/

#pragma once

#include <concepts>

namespace wcreator {

    template<typename T>
    requires std::is_default_constructible_v<T>
    class Drawable {
        protected:
            T __internal;

        public:
            Drawable(const T &Drawable) : __internal(Drawable) {}
            virtual ~Drawable() = 0;

            T getHandle() const {
                return __internal;
            }
    };

    template<typename T>
    Drawable<T>::~Drawable() = default;
}
