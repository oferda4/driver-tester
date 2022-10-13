#pragma once

#include "Defs.h"

#include "Handle.h"
#include "Buffer.h"

struct BadIpAddress : std::exception {
    // left blank intentionally
};

template <typename T>
concept PosixSocketTraits = requires(T& traits, 
                                     typename T::HandleType socket,
                                     int af,
                                     int type,
                                     int protocol) {
    { T::ExceptionType };
    std::derived_from<typename T::ExceptionType, std::exception>;
    { traits.create(socket, af, type, protocol) } -> std::same_as<typename T::HandleType>;
    { traits.close(socket) } -> std::same_as<int>;
};

template <typename T>
concept PosixTcpServerTraits = requires(T& traits,
                                        typename T::HandleType socket,
                                        const sockaddr_in& addr, 
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

template <PosixSocketTraits TcpSocketTraits>
class SocketHandleTraits final {
    using Type = TcpSocketTraits::HandleType;
    void close(Type socket);

private:
    TcpSocketTraits m_traits;
};

template <PosixSocketTraits TcpSocketTraits>
using SocketGuard = HandleGuard<PosixSocketTraits<HandleType, TcpSocketType>>;

template <typename Traits>
    requires(PosixSocketTraits<Traits> && PosixTcpConnectionTraits<Traits>) 
class TcpSocketConnection final {
public:
    template <typename = std::enable_if_t<std::is_default_constructible_v<Traits>>>
    explicit TcpSocketConnection(SocketGuard<Traits> socket);
    TcpSocketConnection(Traits traits, SocketGuard<Traits> socket);

    Buffer recv(uint32_t size);
    uint32_t send(const Buffer& data);

private:
    SocketGuard<SocketHandleTraits<Traits>> m_socket;
    Traits m_traits;
};

template <typename Traits>
    requires(PosixSocketTraits<Traits> && PosixTcpServerTraits<Traits> && PosixTcpConnectionTraits<Traits>) 
class TcpSocketServer final {
public:
    using ConnectionType<Traits> = TcpSocketConnection;

    template <typename = std::enable_if_t<std::is_default_constructible_v<Traits>>>
    explicit TcpSocketServer(const std::string& ip, uint16_t port);
    TcpSocketServer(Traits traits, const std::string& ip, uint16_t port);

    TcpSocketConnection<Traits> waitForConnection();

private:
    SocketGuard<SocketHandleTraits<Traits>> m_socket;
    Traits m_traits;
    sockaddr_in m_address;
};

#include "TcpSocket.inl"
