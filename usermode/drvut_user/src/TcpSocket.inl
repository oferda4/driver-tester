#pragma once

#include "TcpSocket.h"

#include "CastUtils.h"

namespace impl {
template <typename Api>
SocketGuard<Api> createTcpSocket(Api& api);
inline sockaddr_in createSocketAddress(const std::string& ip, uint16_t port);
inline long getIpAddrees(const std::string& ip);
}

template<PosixSocketApi TcpSocketApi>
void SocketHandleTraits<TcpSocketApi>::close(SOCKET socket) {
    m_api.close(socket);
}

template <typename Api>
    requires(PosixSocketApi<Api>&& PosixTcpConnectionApi<Api>)
template <typename>
TcpSocketConnection<Api>::TcpSocketConnection(SocketGuard<Api> socket) 
    : TcpSocketConnection(Api(), std::move(socket)) {
    // left blank intentionally
}

template <typename Api>
    requires(PosixSocketApi<Api>&& PosixTcpConnectionApi<Api>)
TcpSocketConnection<Api>::TcpSocketConnection(Api api, SocketGuard<Api> socket) 
    : m_api(std::move(api)), m_socket(std::move(socket)) {
    // left blank intentionally
}

template <typename Api>
    requires(PosixSocketApi<Api>&& PosixTcpConnectionApi<Api>)
Buffer TcpSocketConnection<Api>::recv(size_t size) {
    Buffer data(size);
    const int result = m_api.recv(*m_socket, reinterpret_cast<char*>(data.data()), CastUtils::cast<int>(data.size()), 0);
    if (result == SOCKET_ERROR) {
        throw typename Api::ExceptionType();
    }
    data.resize(result);
    return data;
}

template <typename Api>
    requires(PosixSocketApi<Api>&& PosixTcpConnectionApi<Api>)
size_t TcpSocketConnection<Api>::send(const Buffer& data) {
    const int result = m_api.send(*m_socket, reinterpret_cast<const char*>(data.data()), CastUtils::cast<int>(data.size()), 0);
    if (result == SOCKET_ERROR) {
        throw typename Api::ExceptionType();
    }
    return result;
}

template <typename Api>
    requires(PosixSocketApi<Api> && PosixTcpServerApi<Api> && PosixTcpConnectionApi<Api>)
template <typename>
TcpSocketServer<Api>::TcpSocketServer(const std::string& ip, uint16_t port) 
    : TcpSocketServer(Api(), ip, port) {
    // left blank intentionally
}

template <typename Api>
    requires(PosixSocketApi<Api> && PosixTcpServerApi<Api> && PosixTcpConnectionApi<Api>) 
TcpSocketServer<Api>::TcpSocketServer(Api api, const std::string& ip, uint16_t port) 
    : m_address(impl::createSocketAddress(ip, port)), 
      m_socket(impl::createTcpSocket(api)), 
      m_api(std::move(api)) {
    if (m_api.bind(*m_socket, reinterpret_cast<sockaddr*>(&m_address), sizeof(m_address)) == SOCKET_ERROR ||
        m_api.listen(*m_socket, 1) == SOCKET_ERROR) {
        throw typename Api::ExceptionType();
    }
}

template <typename Api>
    requires(PosixSocketApi<Api> && PosixTcpServerApi<Api> && PosixTcpConnectionApi<Api>) 
TcpSocketConnection<Api> TcpSocketServer<Api>::waitForConnection() {
    const SOCKET connectionSocket = m_api.accept(*m_socket, nullptr, nullptr);
    if (connectionSocket == INVALID_SOCKET) {
        throw typename Api::ExceptionType();
    }
    return { SocketGuard<Api>(connectionSocket) };
    }

template <typename Api>
SocketGuard<Api> impl::createTcpSocket(Api& api) {
    const auto socket = api.create(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socket == INVALID_SOCKET) {
        throw typename Api::ExceptionType();
    }
    return { socket };
}

sockaddr_in impl::createSocketAddress(const std::string& ip, uint16_t port) {
    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = impl::getIpAddrees(ip);
    address.sin_port = htons(port);
    return address;
}

long impl::getIpAddrees(const std::string& ip) {
    unsigned long address = 0;
    if (inet_pton(AF_INET, ip.c_str(), &address) != 1) {
        throw BadIpAddress();
    }
    if (address == INADDR_NONE) {
        throw BadIpAddress();
    }
    return address;
}
