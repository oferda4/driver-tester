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
