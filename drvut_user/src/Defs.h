#pragma once

#include <Windows.h>

#include <winsock.h>

#include <vector>
#include <concepts>
#include <string>

#define NO_COPY(cls)             \
    cls(const cls&) = delete;    \
    cls& operator=(const cls&) = delete

#define NO_MOVE(cls)        \
    cls(cls&&) = delete;    \
    cls& operator=(cls&&) = delete
