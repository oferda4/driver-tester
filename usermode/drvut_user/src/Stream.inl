#pragma once

#include "Stream.h"
#include "CastUtils.h"

template <Connection ConnectionType>
StreamImpl<ConnectionType>::StreamImpl(ConnectionType connection)
    : m_connection(std::move(connection)) {
    // Left blank intentionally
}

template <Connection ConnectionType>
Buffer StreamImpl<ConnectionType>::recv() {
    SizeType size = BufferUtils::toNumber<SizeType>(recvAll(sizeof(SizeType)));
    return recvAll(size);
}

template <Connection ConnectionType>
void StreamImpl<ConnectionType>::send(const Buffer& data) {
    sendAll(BufferUtils::fromNumber(CastUtils::cast<SizeType>(data.size())));
    sendAll(data);
}

template <Connection ConnectionType>
Buffer StreamImpl<ConnectionType>::recvAll(SizeType size) {
    Buffer buffer;
    while (buffer.size() < size) {
        const Buffer newBuffer = m_connection.recv(size - static_cast<SizeType>(buffer.size()));
        if (newBuffer.empty()) {
            throw ConnectionTerminatedInTheMiddle();
        }
        BufferUtils::append(buffer, newBuffer);
    }
    return buffer;
}

template <Connection ConnectionType>
void StreamImpl<ConnectionType>::sendAll(const Buffer& buffer) {
    SizeType bytesSent = 0;
    while (bytesSent < buffer.size()) {
        const auto currSent = m_connection.send(Buffer(buffer.begin() + bytesSent, buffer.end()));
        if (!currSent) {
            throw ConnectionTerminatedInTheMiddle();
        }
        bytesSent += CastUtils::cast<SizeType>(currSent);
    }
}
