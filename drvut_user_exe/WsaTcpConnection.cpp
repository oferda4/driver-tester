#include "WsaTcpConnection.h"

#include "WinExceptions.h"

WsaTcpConnection::WsaTcpConnection(WsaSocketHandleGuard socket) 
    : m_socket(std::move(socket)) {
    // left blank intentionally
}

Buffer WsaTcpConnection::recv(uint32_t size) {
    Buffer buffer(size);
    WSABUF dataBuf{ size, reinterpret_cast<char*>(buffer.data()) };
    DWORD bytesReceived = 0;
    DWORD flags = 0;

    if (WSARecv(*m_socket,
                &dataBuf,
                1,
                &bytesReceived,
                &flags,
                nullptr,
                nullptr) == SOCKET_ERROR) {
        throw WsaException();
    }

    buffer.resize(bytesReceived);
    return buffer;
}

uint32_t WsaTcpConnection::send(const Buffer& data) {
    WSABUF dataBuf { 
        data.size(), 
        // the const cast is ok as this api shouldn't change the buffer
        reinterpret_cast<char*>(const_cast<Buffer&>(data).data()) 
    };
    DWORD bytesSent = 0;

    if (WSASend(*m_socket, 
                &dataBuf, 
                1, 
                &bytesSent, 
                0, 
                nullptr, 
                nullptr) == SOCKET_ERROR) {
        throw WsaException();
    }

    return bytesSent;
}