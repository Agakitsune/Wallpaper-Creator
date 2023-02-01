#include <iostream>
#include <memory>

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/Xutil.h>
#include <X11/extensions/Xrandr.h>

#include <vector>

#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/videoio.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/core/hal/interface.h>

#include <Imlib2.h>

#include "Context.hpp"
#include "graphics/window/builder/WindowBuilder.hpp"
#include "graphics/window/Window.hpp"
#include "graphics/Pixmap.hpp"
#include "graphics/Video.hpp"
#include "graphics/Drawable.hpp"

int main2(int argc, char *argv[]) {
    Display *dpy = XOpenDisplay(NULL);
    if (dpy == nullptr) {
        std::cerr << "Failed to open display" << std::endl;
        exit(1);
    }
    auto res = XRRGetScreenResourcesCurrent(dpy, DefaultRootWindow(dpy));

    std::cout << res->noutput << std::endl;
    std::cout << res->ncrtc << std::endl;
    std::vector<m_crct_t> m_crtcs;
    std::vector<m_output_t> m_outputs;
    for (int i = 0; i < res->ncrtc; ++i) {
        m_crct_t __kek;
        __kek.info = XRRGetCrtcInfo(dpy, res, res->crtcs[i]);
        __kek.xid = res->crtcs[i];
        __kek.index = i;
        m_crtcs.push_back(__kek);
        std::cout << i << ": " << "outputs: " << __kek.info->noutput << " - output: " << __kek.info->outputs << std::endl;
        for (size_t i = 0; i < __kek.info->noutput; ++i) {
            std::cout << __kek.info->outputs[i] << ", " << std::endl;
        }
        std::cout << "\t<" << __kek.info->x << "x" << __kek.info->y << ">" << std::endl;
        std::cout << "\t<" << __kek.info->width << "x" << __kek.info->height << ">" << std::endl;
    }
    for (int i = 0; i < res->noutput; ++i) {
        m_output_t __kek;
        __kek.info = XRRGetOutputInfo(dpy, res, res->outputs[i]);
        if (__kek.info->connection != RR_Connected)
            continue;
        __kek.xid = res->outputs[i];
        __kek.index = i;
        std::cout << __kek.info->name << "(" << __kek.xid << "): " << "crtc: " << __kek.info->ncrtc << std::endl;
        for (size_t i = 0; i < __kek.info->ncrtc; ++i) {
            std::cout << "Crtc: " << __kek.info->crtcs[i] << " - ";
            auto test = XRRGetCrtcInfo(dpy, res, __kek.info->crtcs[i]);
            std::cout << test << std::endl;
            if (!test)
                continue;
            std::cout << test->x << "x" << test->y << std::endl;
            std::cout << test->width << "x" << test->height << std::endl;
        }
        for (auto &yes : m_crtcs) {
            // std::cout << "i: " << i << std::endl;
            // std::cout << "cmp xid: " << yes.xid << " == " << res->outputs[i] << std::endl;
            // std::cout << "cmp index: " << yes.index << " == " << i << std::endl;
            if (yes.xid == res->outputs[i] || yes.index == i) {
                __kek.crct = &yes;
                m_outputs.push_back(__kek);
                break;
            }
        }
    }
    for (auto &output : m_outputs) {
        if (output.info->connection == RR_Connected) {
            std::cout << output.info->name << ": " << std::endl;
            std::cout << "\t<" << output.crct->info->x << "x" << output.crct->info->y << ">" << std::endl;
            std::cout << "\t<" << output.crct->info->width << "x" << output.crct->info->height << ">" << std::endl;
        }
    }
    // std::string filename;
    // //---
    // if (dpy == NULL) {
    //     std::cerr << "Failed to open display" << std::endl;
    //     exit(1);
    // }
    // //---
    // if (argc < 2) {
    //     std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
    //     exit(1);
    // }
    // filename = argv[1];
    // //---
    // display(dpy, filename);
    // //---
    XCloseDisplay(dpy);
    return 0;
}

int main(int argc, char *argv[]) {
    wcreator::Context::getContext();
    auto win = wcreator::builder::WindowBuilder().setWidth(1920).setHeight(1080).build();
    std::string filename;
    //---
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
        exit(1);
    }
    filename = argv[1];
    wcreator::Video capture(filename);
    // ---
    while (true) {
        // std::cout << "Pending: " << XPending(&wcreator::Context::getDisplay()) << std::endl;
        auto frame = capture.getFrame();
        if (frame.empty())
            break;
        win->drawFrame(frame);
        win->display();
        frame.release();
    }
}

