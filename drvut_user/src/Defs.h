#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

// note: include order is important
#include <WinSock2.h>
#include <Windows.h>

#pragma comment(lib, "ws2_32.lib")

#include <vector>
#include <concepts>
#include <string>

#define NO_COPY(cls)             \
    cls(const cls&) = delete;    \
    cls& operator=(const cls&) = delete

#define NO_MOVE(cls)        \
    cls(cls&&) = delete;    \
    cls& operator=(cls&&) = delete
