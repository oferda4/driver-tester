#pragma once

#include "Communicator.h"

template <Stream StreamType, RequestsRouter RouterType>
Communicator<StreamType, RouterType>::Communicator(StreamType stream, RouterType rotuer)
    : m_stream(std::move(stream)), m_router(std::move(router)) {
    // Left blank intentionally
}

template <Stream StreamType, RequestsRouter RouterType>
void Communicator<StreamType, RouterType>::run() {
    Buffer data = m_connection.recv();
    while (!data.empty()) {
        Buffer response = m_router.route(data);
        m_stream.send(response);
        data = m_stream.recv();
    }
}
