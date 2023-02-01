/*
** EPITECH PROJECT, 2023
** Wallpaper-Creator
** File description:
** Window
*/

#pragma once

#include <X11/Xlib.h>

#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/videoio.hpp>
#include <opencv4/opencv2/highgui.hpp>

#include "Context.hpp"
#include "graphics/Drawable.hpp"
#include "graphics/Pixmap.hpp"

#include "utils/Vector.hpp"
#include "utils/Property.hpp"

#include "utils/Types.hpp"

namespace wcreator {
    class Window : public Drawable<XWindow> {
        int __x;
        int __y;
        unsigned int __width;
        unsigned int __height;
        int __depth;

        Pixmap *__pixmap;

        public:
            Window(const XWindow &Xwindow);
            virtual ~Window() override;

            utils::Property<int> x();
            utils::Property<int> y();
            utils::Property<unsigned int> width();
            utils::Property<unsigned int> height();

            const int &x() const;
            const int &y() const;
            const unsigned int &width() const;
            const unsigned int &height() const;

            const int &depth() const;

            void raise() const;
            void lower() const;

            void display() const;
            void hide() const;

            void drawFrame(const cv::Mat &frame);
            void drawPixmap(const Pixmap &pixmap);

        private:
            void __refresh() const;

    };
}
