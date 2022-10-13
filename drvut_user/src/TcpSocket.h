#pragma once

#include "Defs.h"

#include "Handle.h"
#include "Buffer.h"

template <typename T>
concept PosixTcpSocketTraits = requires(T& traits, 
                                        typename T::HandleType socket,
                                        int af,
                                        int type,
                                        int protocol) {
    { T::ExceptionType };
    std::derived_from<typename T::ExceptionType, std::exception>;
    { traits.create(socket, af, type, protocol) } -> std::same_as<T>;
    { traits.close(socket) } -> std::same_as<int>;
};

template <typename T>
concept PosixTcpServerTraits = requires(T& traits,
                                        typename T::HandleType socket,
                                        const sockaddr& addr, 
                                        int namelen,
                                        int backlog,
                                        sockaddr& outAddr,
                                        int& outAddrLen) {
    { traits.bind(socket, addr, namelen) } -> std::same_as<int>;
    { traits.listen(socket, backlog) } -> std::same_as<int>;
    { traits.accept(socket, outAddr, outAddrLen) } -> std::same_as<typename T::HandleType>;
};

template <typename T>
concept PosixTcpConnectionTraits = requires(T& traits, 
                                            typename T::HandleType socket,
                                            char *buf, 
                                            int len, 
                                            int flags) {
    { traits.recv(socket, buf, len, flags) } -> std::same_as<int>;
    { traits.send(socket, buf, len, flags) } -> std::same_as<int>;
};

template <PosixTcpSocketTraits TcpSocketTraits>
class SocketTraits final {
    using Type = TcpSocketTraits::HandleType;
    void close(Type socket);

private:
    TcpSocketTraits m_traits;
};

template <PosixTcpSocketTraits TcpSocketTraits>
using SocketGuard = HandleGuard<PosixSocketTraits<HandleType, TcpSocketType>>;

template <typename Traits>
    requires(PosixTcpSocketTraits<Traits>&& PosixTcpConnectionTraits<Traits>) 
class SocketConnection final {
public:
    template <typename = std::enable_if_t<std::is_default_constructible_v<Traits>>>
    SocketConnection(SocketGuard<Traits> socket);
    SocketConnection(Traits traits, SocketGuard<Traits> socket);

    Buffer recv(uint32_t size);
    uint32_t send(const Buffer& data);

private:
    SocketGuard<TcpSocketTraits> m_socket;
    Traits traits;
};

#include "TcpSocket.inl"
