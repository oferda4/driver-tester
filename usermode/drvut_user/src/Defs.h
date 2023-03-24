#pragma once

// clang-format off
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
// clang-format on

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "onecore.lib")

#include <concepts>
#include <string>
#include <vector>

#define NO_COPY(cls)                                                                               \
    cls(const cls&) = delete;                                                                      \
    cls& operator=(const cls&) = delete

#define NO_MOVE(cls)                                                                               \
    cls(cls&&) = delete;                                                                           \
    cls& operator=(cls&&) = delete
