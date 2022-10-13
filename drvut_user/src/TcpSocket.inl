#pragma once

#include "TcpSocket.h"

template<PosixTcpSocketTraits TcpSocketTraits>
void SocketTraits<TcpSocketTraits>::close(Type socket) {
    m_traits.close(socket);
}

template <typename Traits>
    requires(PosixTcpSocketTraits<Traits>&& PosixTcpConnectionTraits<Traits>)
template <typename>
SocketConnection<Traits>::SocketConnection(SocketGuard<Traits> socket) 
    : SocketConnection(Traits(), std::move(socket)) {
    // left blank intentionally
}

template <typename Traits>
    requires(PosixTcpSocketTraits<Traits>&& PosixTcpConnectionTraits<Traits>)
SocketConnection<Traits>::SocketConnection(Traits traits, SocketGuard<Traits> socket) 
    : m_traits(traits), m_socket(std::move(socket)) {
    // left blank intentionally
}

template <typename Traits>
    requires(PosixTcpSocketTraits<Traits>&& PosixTcpConnectionTraits<Traits>)
Buffer SocketConnection<Traits>::recv(uint32_t size) {
    Buffer data(size);
    const int result = m_trais.recv(*m_socket, data.data(), data.size(), 0);
    if (result == SOCKET_ERROR) {
        throw Traits::ExceptionType();
    }
    data.resize(result);
    return data;
}

template <typename Traits>
    requires(PosixTcpSocketTraits<Traits>&& PosixTcpConnectionTraits<Traits>)
uint32_t SocketConnection<Traits>::send(const Buffer& data) {
    Buffer data(size);
    const int result = m_trais.send(*m_socket, data.data(), data.size(), 0);
    if (result == SOCKET_ERROR) {
        throw Traits::ExceptionType();
    }
    return result;
}