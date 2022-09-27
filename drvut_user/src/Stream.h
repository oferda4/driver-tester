#pragma once

#include "Defs.h"

#include "Buffer.h"
#include "Connection.h"

template<typename T>
concept Stream = requires(T& stream, const Buffer& data) {
    { stream.recv() } -> std::same_as<Buffer>;
    { stream.send(data) } -> std::same_as<void>;
};

template<Connection ConnectionType>
class StreamImpl final {
public:
    StreamImpl(ConnectionType connection);

    Buffer recv();
    void send(const Buffer& data);

private:
    ConnectionType m_connection;
};

#include "Stream.inl"
