/*
** EPITECH PROJECT, 2023
** Wallpaper-Creator
** File description:
** Builder
*/

#pragma once

#include <memory>

namespace wcreator::utils {
    template<typename T>
    class Builder {
        public:
            Builder() = default;
            virtual ~Builder() = default;

            virtual std::unique_ptr<T> build() const = 0;

    };
}
