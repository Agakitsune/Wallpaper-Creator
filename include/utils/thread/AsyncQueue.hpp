/*
** EPITECH PROJECT, 2023
** Wallpaper-Creator
** File description:
** AsyncQueue
*/

#pragma once

#include <queue>
#include <mutex>

template<typename T>
class AsyncQueue : public std::queue<T> {
    using std::queue<T>::queue;
    std::mutex __lock;

    public:
        bool poll(T &value) {
            std::lock_guard<std::mutex> lock(__lock);
            if (std::queue<T>::empty())
                return false;
            value = std::move(std::queue<T>::front());
            std::queue<T>::pop();
            return true;
        }

        T pop() {
            std::lock_guard<std::mutex> lock(__lock);
            T value = std::move(std::queue<T>::front());
            std::queue<T>::pop();
            return value;
        }

        void push(const T &value) {
            std::lock_guard<std::mutex> lock(__lock);
            std::queue<T>::push(value);
        }

        T &front() {
            std::lock_guard<std::mutex> lock(__lock);
            return std::queue<T>::front();
        }

        T &back() {
            std::lock_guard<std::mutex> lock(__lock);
            return std::queue<T>::back();
        }

        bool empty() {
            std::lock_guard<std::mutex> lock(__lock);
            return std::queue<T>::empty();
        }

        void clear() {
            std::lock_guard<std::mutex> lock(__lock);
            std::queue<T>::clear();
        }

        size_t size() {
            std::lock_guard<std::mutex> lock(__lock);
            return std::queue<T>::size();
        }
};
