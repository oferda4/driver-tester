#pragma once

#include "Defs.h"

#include "Buffer.h"
#include "Connection.h"

struct ConnectionTerminatedInTheMiddle : std::exception {
    ConnectionTerminatedInTheMiddle();
};

template<typename T>
concept Stream = requires(T& stream, const Buffer& data) {
    { stream.recv() } -> std::same_as<Buffer>;
    { stream.send(data) } ;//-> std::same_as<void>;
};

template<Connection ConnectionType>
class StreamImpl final {
public:
    using SizeType = uint64_t;

    explicit StreamImpl(ConnectionType connection);

    Buffer recv();
    void send(const Buffer& data);

private:
    Buffer recvAll(SizeType size);
    void sendAll(const Buffer& buffer);

    ConnectionType m_connection;
};

#include "Stream.inl"
