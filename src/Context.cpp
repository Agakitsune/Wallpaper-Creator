/*
** EPITECH PROJECT, 2023
** Wallpaper-Creator
** File description:
** Context
*/

#include <array>
#include <iostream>

#include <X11/Xproto.h>

#include "Context.hpp"

using namespace wcreator;

const std::array<std::string, 17> __XErrorCode = {
    "BadAccess",
    "BadAlloc",
    "BadAtom",
    "BadColor",
    "BadCursor",
    "BadDrawable",
    "BadFont",
    "BadGC",
    "BadIDChoice",
    "BadImplementation",
    "BadLength",
    "BadMatch",
    "BadName",
    "BadPixmap",
    "BadRequest",
    "BadValue",
    "BadWindow"
};

const std::array<std::string, 128> __XMajorOpCode = {
    "",
    "X_CreateWindow",
    "X_ChangeWindowAttributes",
    "X_GetWindowAttributes",
    "X_DestroyWindow",
    "X_DestroySubwindows",
    "X_ChangeSaveSet",
    "X_ReparentWindow",
    "X_MapWindow",
    "X_MapSubwindows",
    "X_UnmapWindow",
    "X_UnmapSubwindows",
    "X_ConfigureWindow",
    "X_CirculateWindow",
    "X_GetGeometry",
    "X_QueryTree",
    "X_InternAtom",
    "X_GetAtomName",
    "X_ChangeProperty",
    "X_DeleteProperty",
    "X_GetProperty",
    "X_ListProperties",
    "X_SetSelectionOwner",
    "X_GetSelectionOwner",
    "X_ConvertSelection",
    "X_SendEvent",
    "X_GrabPointer",
    "X_UngrabPointer",
    "X_GrabButton",
    "X_UngrabButton",
    "X_ChangeActivePointerG",
    "X_GrabKeyboard",
    "X_UngrabKeyboard",
    "X_GrabKey",
    "X_UngrabKey",
    "X_AllowEvents",
    "X_GrabServer",
    "X_UngrabServer",
    "X_QueryPointer",
    "X_GetMotionEvents",
    "X_TranslateCoords",
    "X_WarpPointer",
    "X_SetInputFocus",
    "X_GetInputFocus",
    "X_QueryKeymap",
    "X_OpenFont",
    "X_CloseFont",
    "X_QueryFont",
    "X_QueryTextExtents",
    "X_ListFonts",
    "X_ListFontsWithInfo",
    "X_SetFontPath",
    "X_GetFontPath",
    "X_CreatePixmap",
    "X_FreePixmap",
    "X_CreateGC",
    "X_ChangeGC",
    "X_CopyGC",
    "X_SetDashes",
    "X_SetClipRectangles",
    "X_FreeGC",
    "X_ClearArea",
    "X_CopyArea",
    "X_CopyPlane",
    "X_PolyPoint",
    "X_PolyLine",
    "X_PolySegment",
    "X_PolyRectangle",
    "X_PolyArc",
    "X_FillPoly",
    "X_PolyFillRectangle",
    "X_PolyFillArc",
    "X_PutImage",
    "X_GetImage",
    "X_PolyText8",
    "X_PolyText16",
    "X_ImageText8",
    "X_ImageText16",
    "X_CreateColormap",
    "X_FreeColormap",
    "X_CopyColormapAndFree",
    "X_InstallColormap",
    "X_UninstallColormap",
    "X_ListInstalledColorma",
    "X_AllocColor",
    "X_AllocNamedColor",
    "X_AllocColorCells",
    "X_AllocColorPlanes",
    "X_FreeColors",
    "X_StoreColors",
    "X_StoreNamedColor",
    "X_QueryColors",
    "X_LookupColor",
    "X_CreateCursor",
    "X_CreateGlyphCursor",
    "X_FreeCursor",
    "X_RecolorCursor",
    "X_QueryBestSize",
    "X_QueryExtension",
    "X_ListExtensions",
    "X_ChangeKeyboardMapping",
    "X_GetKeyboardMapping",
    "X_ChangeKeyboardControl",
    "X_GetKeyboardControl",
    "X_Bell",
    "X_ChangePointerControl",
    "X_GetPointerControl",
    "X_SetScreenSaver",
    "X_GetScreenSaver",
    "X_ChangeHosts",
    "X_ListHosts",
    "X_SetAccessControl",
    "X_SetCloseDownMode",
    "X_KillClient",
    "X_RotateProperties",
    "X_ForceScreenSaver",
    "X_SetPointerMapping",
    "X_GetPointerMapping",
    "X_SetModifierMapping",
    "X_GetModifierMapping",
    "X_NoOperation",
};

int Context::__handler(Display *display, XErrorEvent *event) {
    static int errorCount = 5;
    std::cerr << "X Error: " << __XErrorCode[event->error_code] << std::endl;
    std::cerr << "\tMajor opcode: " << __XMajorOpCode[event->request_code] << " " << std::to_string(event->request_code) << std::endl;
    std::cerr << "\tMinor opcode: " << std::to_string(event->minor_code) << std::endl;
    std::cerr << "\tResource ID: " << event->resourceid << std::endl;
    std::cerr << "\tSerial: " << event->serial << std::endl;
    if (--errorCount == 0)
        exit(1);
    return 0;
}

Context::Context(const std::string &name) {
    if (name.empty())
        __display = XOpenDisplay(nullptr);
    else
        __display = XOpenDisplay(name.c_str());
    if (__display == nullptr)
        throw error::ContextException("Failed to open display");
    // XSetErrorHandler(&Context::__handler);
}

Context::~Context() {
    XCloseDisplay(__display);
}

Context &Context::getContext(const std::string &name) {
    if (__instance == nullptr)
        __instance = new Context(name);
    return *__instance;
}

Context &Context::modifyContext(const std::string &name) {
    if (__instance != nullptr) {
        delete __instance;
        __instance = nullptr;
    }
    return getContext(name);
}

XDisplay &Context::getDisplay() {
    if (__instance == nullptr)
        throw error::ContextException("Context not initialized");
    auto ptr = __instance->__display;
    return *__instance->__display;
}

XWindow &Context::getRootWindow() {
    return DefaultRootWindow(__instance->__display);
}

XScreen &Context::getDefaultScreen() {
    auto ptr = XDefaultScreenOfDisplay(__instance->__display);
    if (ptr)
        return *ptr;
    throw error::ContextException("Failed to get default screen");
}

XScreen &Context::getScreen(const size_t &screen) {
    auto ptr = XScreenOfDisplay(__instance->__display, screen);
    if (ptr)
        return *ptr;
    throw error::ContextException("Failed to get screen " + std::to_string(screen));
}

XVisual &Context::getDefaultVisual() {
    auto ptr = DefaultVisualOfScreen(&Context::getDefaultScreen());
    if (ptr)
        return *ptr;
    throw error::ContextException("Failed to get default visual");
}

XColormap &Context::getDefaultColormap() {
    return DefaultColormapOfScreen(&Context::getDefaultScreen());
}

Context *Context::__instance = nullptr;
