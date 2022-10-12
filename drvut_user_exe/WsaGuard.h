#pragma once

#include "Defs.h"

struct BadWsaVersion : std::exception {
    // left blank intentionally
};

class WsaGuard final {
public:
    WsaGuard();
    ~WsaGuard();

    NO_COPY(WsaGuard);
    NO_MOVE(WsaGuard);

private:
    static constexpr uint16_t VERSION = MAKEWORD(2, 2);
};
