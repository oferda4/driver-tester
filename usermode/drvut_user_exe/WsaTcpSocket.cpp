#include "WsaTcpSocket.h"

#include <iostream>

int WsaTcpSocketApi::close(SOCKET socket) {
    std::cout << "close" << std::endl;
    return ::closesocket(socket);
}

SOCKET WsaTcpSocketApi::create(int af, int type, int protocol) {
    std::cout << "create" << std::endl;
    return ::socket(af, type, protocol);
}

int WsaTcpSocketApi::bind(SOCKET socket, const sockaddr* addr, int addrlen) {
    std::cout << "bind" << std::endl;
    
    int res = ::bind(socket, reinterpret_cast<sockaddr*>(&addr), addrlen);

    std::cout << "res: " << res << std::endl;
    std::cout << "gle: " << WSAGetLastError() << std::endl;

    return res;
}

int WsaTcpSocketApi::listen(SOCKET socket, int backlog) {
    std::cout << "listen" << std::endl;
    return ::listen(socket, backlog);
}

SOCKET WsaTcpSocketApi::accept(SOCKET socket, sockaddr* addr, int* addrlen) {
    std::cout << "accept" << std::endl;
    return ::accept(socket, addr, addrlen);
}

int WsaTcpSocketApi::recv(SOCKET socket, char* buf, int len, int flags) {
    std::cout << "recv" << std::endl;
    return ::recv(socket, buf, len, flags);
}

int WsaTcpSocketApi::send(SOCKET socket, const char* buf, int len, int flags) {
    std::cout << "send" << std::endl;
    return ::send(socket, buf, len, flags);
}
