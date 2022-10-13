#pragma once

#include "TcpSocket.h"

namespace impl {
template <PosixSocketTraits Traits>
SocketGuard<SocketHandleTraits<Traits>> createTcpSocket(Traits& traits);
inline sockaddr_in createSocketAddress(const std::string& ip, uint16_t port);
inline long getIpAddrees(const std::string& ip);
}

template<PosixSocketTraits TcpSocketTraits>
void SocketHandleTraits<TcpSocketTraits>::close(Type socket) {
    m_traits.close(socket);
}

template <typename Traits>
    requires(PosixSocketTraits<Traits>&& PosixTcpConnectionTraits<Traits>)
template <typename>
TcpSocketConnection<Traits>::TcpSocketConnection(SocketGuard<Traits> socket) 
    : TcpSocketConnection(Traits(), std::move(socket)) {
    // left blank intentionally
}

template <typename Traits>
    requires(PosixSocketTraits<Traits>&& PosixTcpConnectionTraits<Traits>)
TcpSocketConnection<Traits>::TcpSocketConnection(Traits traits, SocketGuard<Traits> socket) 
    : m_traits(std::move(traits)), m_socket(std::move(socket)) {
    // left blank intentionally
}

template <typename Traits>
    requires(PosixSocketTraits<Traits>&& PosixTcpConnectionTraits<Traits>)
Buffer TcpSocketConnection<Traits>::recv(uint32_t size) {
    Buffer data(size);
    const int result = m_trais.recv(*m_socket, data.data(), data.size(), 0);
    if (result == SOCKET_ERROR) {
        throw typename Traits::ExceptionType();
    }
    data.resize(result);
    return data;
}

template <typename Traits>
    requires(PosixSocketTraits<Traits>&& PosixTcpConnectionTraits<Traits>)
uint32_t TcpSocketConnection<Traits>::send(const Buffer& data) {
    Buffer data(size);
    const int result = m_trais.send(*m_socket, data.data(), data.size(), 0);
    if (result == SOCKET_ERROR) {
        throw typename Traits::ExceptionType();
    }
    return result;
}

template <typename Traits>
    requires(PosixSocketTraits<Traits> && PosixTcpServerTraits<Traits>) 
template <typename>
TcpSocketServer<Traits>::TcpSocketServer(const std::string& ip, uint16_t port) 
    : TcpSocketServer(Traits(), ip, port) {
    // left blank intentionally
}

template <typename Traits>
    requires(PosixSocketTraits<Traits> && PosixTcpServerTraits<Traits>) 
TcpSocketServer<Traits>::TcpSocketServer(Traits traits, const std::string& ip, uint16_t port) 
    : m_socket(impl::createTcpSocket(traits)), 
      m_traits(std::move(traits)),
      m_address(impl::createSocketAddress(ip, port)) {
    if (m_traits.bind(*m_socket, &m_address, sizeof(m_address)) == SOCKET_ERROR ||
        m_traits.listen(*m_socket, 1) == SOCKET_ERROR) {
        throw typename Traits::ExceptionType();
    }
}

template <typename Traits>
    requires(PosixSocketTraits<Traits> && PosixTcpServerTraits<Traits>) 
TcpSocketConnection<Traits> TcpSocketServer<Traits>::waitForConnection() {
    const typename Traits::HandleType connectionSocket = m_traits.accept(*m_socket, nullptr, nullptr);
    if (connectinoSocket == INVALID_SOCKET) {
        typename throw Traits::ExceptionType();
    }
    return { connectionSocket };
}

template <PosixSocketTraits Traits>
SocketGuard<SocketHandleTraits<Traits>> impl::createTcpSocket(Traits& traits) {
    typename Traits::HandleType socket = traits.create(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socket == INVALID_SOCKET) {
        throw typename Traits::ExceptionType();
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
    const long address = inet_addr(ip.c_str());
    if (address == INADDR_NONE) {
        throw BadIpAddress();
    }
    return address;
}
