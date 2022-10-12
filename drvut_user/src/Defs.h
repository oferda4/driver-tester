#pragma once

#include <Windows.h>

#include <winsock.h>

#include <vector>
#include <concepts>
#include <string>

#define NO_COPY(cls)             \
    cls(const cls&) = delete;    \
    cls& operator=(const cls&) = delete
