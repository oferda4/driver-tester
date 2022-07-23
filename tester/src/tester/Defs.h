#pragma once

#include <windows.h>
#include <string>

#include "Exceptions.h"

#define NOCOPY(className)                 \
    className(const className&) = delete; \
    className& operator=(const className&) = delete
#define MOVEABLE(className)                    \
    className(className&&) noexcept = default; \
    className& operator=(className&&) noexcept = default
#define NOMOVE(className)                    \
    className(className&&) noexcept = delete; \
    className& operator=(className&&) noexcept = delete

#ifndef CL_CODE
#define CTL_CODE(DeviceType, Function, Method, Access) ( \
    ((DeviceType) << 16) | ((Access) << 14) | ((Function) << 2) | (Method))
#endif
