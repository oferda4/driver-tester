#pragma once

#include "Defs.h"

struct WsaException : std::exception {
    WsaException(int code = WSAGetLastError()) 
        : std::exception("WinSock Exception", code) {
        // left blank intentionally
    }
};

struct Win32Exception : std::exception {
    Win32Exception(int code = GetLastError())
        : std::exception("Win32 Exception", code) {
        // left blank intentionally
    }
};
