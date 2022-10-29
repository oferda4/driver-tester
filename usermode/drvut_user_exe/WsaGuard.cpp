#include "WsaGuard.h"

#include "WinExceptions.h"

namespace {
void cleanup();
}

WsaGuard::WsaGuard() {
    WSADATA wsaData{};
    int err = WSAStartup(VERSION, &wsaData);
    if (err) {
        throw WsaException(err);
    }

    if (wsaData.wVersion != VERSION) {
        cleanup();
        throw BadWsaVersion();
    }
}

WsaGuard::~WsaGuard() {
    cleanup();
}

namespace {
void cleanup() {
    (void)WSACleanup();
}
}
