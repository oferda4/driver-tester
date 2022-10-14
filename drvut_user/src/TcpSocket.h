#pragma once

#include "Defs.h"

#include "Handle.h"
#include "Buffer.h"

struct BadIpAddress : std::exception {
    // left blank intentionally
};

template <typename T>
concept PosixSocketTraits = requires(T& traits, 
                                     SOCKET socket) {
    { T::ExceptionType };
    std::derived_from<typename T::ExceptionType, std::exception>;
    { traits.close(socket) } -> std::same_as<int>;
};

template <typename T>
concept PosixTcpServerTraits = requires(T& traits,
                                        SOCKET socket,
                                        int af,
                                        int type,
                                        int protocol,
                                        const sockaddr_in* addr, 
                                        int namelen,
                                        int backlog,
                                        sockaddr* outAddr,
                                        int* outAddrLen) {
    { traits.create(af, type, protocol) } -> std::same_as<SOCKET>;
    { traits.bind(socket, addr, namelen) } -> std::same_as<int>;
    { traits.listen(socket, backlog) } -> std::same_as<int>;
    { traits.accept(socket, outAddr, outAddrLen) } -> std::same_as<SOCKET>;
};

template <typename T>
concept PosixTcpConnectionTraits = requires(T& traits, 
                                            SOCKET socket,
                                            char *buf,
                                            const char *bufToSend,
                                            int len, 
                                            int flags) {
    { traits.recv(socket, buf, len, flags) } -> std::same_as<int>;
    { traits.send(socket, bufToSend, len, flags) } -> std::same_as<int>;
};

template <PosixSocketTraits TcpSocketTraits>
class SocketHandleTraits final {
public:
    using Type = SOCKET;
    void close(SOCKET socket);

private:
    TcpSocketTraits m_traits;
};

template <PosixSocketTraits TcpSocketTraits>
using SocketGuard = HandleGuard<SocketHandleTraits<TcpSocketTraits>>;

template <typename Traits>
    requires(PosixSocketTraits<Traits> && PosixTcpConnectionTraits<Traits>) 
class TcpSocketConnection final {
public:
    template <typename = std::enable_if_t<std::is_default_constructible_v<Traits>>>
    explicit TcpSocketConnection(SocketGuard<Traits> socket);
    TcpSocketConnection(Traits traits, SocketGuard<Traits> socket);

    Buffer recv(size_t size);
    size_t send(const Buffer& data);

private:
    Traits m_traits;
    SocketGuard<Traits> m_socket;
};

template <typename Traits>
    requires(PosixSocketTraits<Traits> && PosixTcpServerTraits<Traits> && PosixTcpConnectionTraits<Traits>) 
class TcpSocketServer final {
public:
    using ConnectionType = TcpSocketConnection<Traits>;

    template <typename = std::enable_if_t<std::is_default_constructible_v<Traits>>>
    explicit TcpSocketServer(const std::string& ip, uint16_t port);
    TcpSocketServer(Traits traits, const std::string& ip, uint16_t port);

    TcpSocketConnection<Traits> waitForConnection();

private:
    sockaddr_in m_address;
    SocketGuard<Traits> m_socket;
    Traits m_traits;
};

#include "TcpSocket.inl"
