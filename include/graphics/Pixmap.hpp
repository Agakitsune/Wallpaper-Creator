/*
** EPITECH PROJECT, 2023
** Wallpaper-Creator
** File description:
** Pixmap
*/

#pragma once

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <Imlib2.h>

#include "Context.hpp"
#include "graphics/Drawable.hpp"
#include "graphics/image/Image.hpp"

#include "utils/Types.hpp"

#include "Video.hpp"

#include "exception/PixmapException.hpp"

namespace wcreator {
    class Window;

    class Pixmap : public Drawable<XPixmap> {
        // Image __image;
        // GC __context;
        Imlib_Image __image;

        unsigned int __width;
        unsigned int __height;

        int __depth;

        public:
            Pixmap(Window &window);
            Pixmap(const cv::Mat &frame);
            Pixmap(Window &window, const cv::Mat &frame);
            virtual ~Pixmap() override;

            void drawFrame(const cv::Mat &frame);

            int &depth();
            unsigned int &width();
            unsigned int &height();

            static const XPixmap INVALID_PIXMAP;

        private:
            void __draw();

    };
}
