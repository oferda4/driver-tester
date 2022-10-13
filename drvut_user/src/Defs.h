#pragma once

#include <winsock2.h>
#include <Windows.h>

#include <vector>
#include <concepts>
#include <string>

#define NO_COPY(cls)             \
    cls(const cls&) = delete;    \
    cls& operator=(const cls&) = delete

#define NO_MOVE(cls)        \
    cls(cls&&) = delete;    \
    cls& operator=(cls&&) = delete
