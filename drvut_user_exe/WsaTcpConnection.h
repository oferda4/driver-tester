#pragma once

#include "Defs.h"

#include "WsaSocketHandle.h"
#include "Buffer.h"

class WsaTcpConnection {
public:
    explicit WsaTcpConnection(WsaSocketHandleGuard socket);

    Buffer recv(uint32_t size);
    uint32_t send(const Buffer& data);

private:
    WsaSocketHandleGuard m_socket;
};
