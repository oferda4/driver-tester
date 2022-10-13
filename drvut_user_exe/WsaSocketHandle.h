#pragma once

#include "Handle.h"

class WsaSocketHandleTraits {
public:
    using Type = SOCKET;
    void close(SOCKET socket);
};

using WsaSocketHandleGuard = HandleGuard<WsaSocketHandleTraits>;
