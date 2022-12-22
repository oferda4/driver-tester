#pragma once

#include "Defs.h"

#include "Handle.h"
#include "Buffer.h"
#include "Connection.h"

struct BadIpAddress : std::exception {
    // left blank intentionally
};

template <typename T>
concept PosixSocketApi = requires(T& api, 
                                  SOCKET socket) {
    typename T::ExceptionType;
    std::derived_from<typename T::ExceptionType, std::exception>;
    { api.close(socket) } -> std::same_as<int>;
};

template <typename T>
concept PosixTcpServerApi = requires(T& api,
                                     SOCKET socket,
                                     int af,
                                     int type,
                                     int protocol,
                                     const sockaddr* addr, 
                                     int namelen,
                                     int backlog,
                                     sockaddr* outAddr,
                                     int* outAddrLen) {
    { api.create(af, type, protocol) } -> std::same_as<SOCKET>;
    { api.bind(socket, addr, namelen) } -> std::same_as<int>;
    { api.listen(socket, backlog) } -> std::same_as<int>;
    { api.accept(socket, outAddr, outAddrLen) } -> std::same_as<SOCKET>;
};

template <typename T>
concept PosixTcpConnectionApi = requires(T& api, 
                                         SOCKET socket,
                                         char *buf,
                                         const char *bufToSend,
                                         int len, 
                                         int flags) {
    { api.recv(socket, buf, len, flags) } -> std::same_as<int>;
    { api.send(socket, bufToSend, len, flags) } -> std::same_as<int>;
};

template <PosixSocketApi TcpSocketApi>
class SocketHandleTraits final {
public:
    using Type = SOCKET;
    void close(SOCKET socket);

private:
    TcpSocketApi m_api;
};

template <PosixSocketApi TcpSocketApi>
using SocketGuard = HandleGuard<SocketHandleTraits<TcpSocketApi>>;

template <typename Api>
    requires(PosixSocketApi<Api> && PosixTcpConnectionApi<Api>) 
class TcpSocketConnection final {
public:
    template <typename = std::enable_if_t<std::is_default_constructible_v<Api>>>
    explicit TcpSocketConnection(SocketGuard<Api> socket);
    TcpSocketConnection(Api api, SocketGuard<Api> socket);

    Buffer recv(size_t size);
    size_t send(const Buffer& data);

private:
    Api m_api;
    SocketGuard<Api> m_socket;
};

template <typename Api>
    requires(PosixSocketApi<Api> && PosixTcpServerApi<Api> && PosixTcpConnectionApi<Api>) 
class TcpSocketServer final {
public:
    using ConnectionType = TcpSocketConnection<Api>;

    template <typename = std::enable_if_t<std::is_default_constructible_v<Api>>>
    explicit TcpSocketServer(const std::string& ip, uint16_t port);
    TcpSocketServer(Api api, const std::string& ip, uint16_t port);

    TcpSocketConnection<Api> waitForConnection();

private:
    sockaddr_in m_address;
    SocketGuard<Api> m_socket;
    Api m_api;
};

#include "TcpSocket.inl"
