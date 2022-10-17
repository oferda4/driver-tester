#pragma once

#include "Defs.h"

#include "TcpSocket.h"
#include "WinExceptions.h"

class WsaTcpSocketApi {
public:
    using ExceptionType = WsaException;

    int close(SOCKET socket);

    SOCKET create(int af, int type, int protocol);
    int bind(SOCKET socket, const sockaddr* addr, int addrlen);
    int listen(SOCKET socket, int backlog);
    SOCKET accept(SOCKET socket, sockaddr* addr, int* addrlen);

    int recv(SOCKET socket, char* buf, int len, int flags);
    int send(SOCKET socket, const char* buf, int len, int flags);
};

using WsaTcpSocketServer = TcpSocketServer<WsaTcpSocketApi>;
