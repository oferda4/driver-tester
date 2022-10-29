#include "WsaTcpSocket.h"

int WsaTcpSocketApi::close(SOCKET socket) {
    return ::closesocket(socket);
}

SOCKET WsaTcpSocketApi::create(int af, int type, int protocol) {
    return ::socket(af, type, protocol);
}

int WsaTcpSocketApi::bind(SOCKET socket, const sockaddr* addr, int addrlen) {
    return ::bind(socket, reinterpret_cast<sockaddr*>(&addr), addrlen);
}

int WsaTcpSocketApi::listen(SOCKET socket, int backlog) {
    return ::listen(socket, backlog);
}

SOCKET WsaTcpSocketApi::accept(SOCKET socket, sockaddr* addr, int* addrlen) {
    return ::accept(socket, addr, addrlen);
}

int WsaTcpSocketApi::recv(SOCKET socket, char* buf, int len, int flags) {
    return ::recv(socket, buf, len, flags);
}

int WsaTcpSocketApi::send(SOCKET socket, const char* buf, int len, int flags) {
    return ::send(socket, buf, len, flags);
}
