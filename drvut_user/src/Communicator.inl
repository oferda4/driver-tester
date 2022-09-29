#pragma once

#include "Communicator.h"

template <Server ServerType, RequestsRouter RouterType>
Communicator<ServerType, RouterType>::Communicator(ServerType server, RouterType rotuer)
    : m_server(std::move(server)), m_router(std::move(router)) {
    // Left blank intentionally
}

template <Server ServerType, RequestsRouter RouterType>
void Communicator<ServerType, RouterType>::run() {
    auto stream = getStream();
    Buffer data = stream.recv();
    while (!data.empty()) {
        Buffer response = m_router.route(data);
        m_stream.send(response);
        data = m_stream.recv();
    }
}

template <Server ServerType, RequestsRouter RouterType>
StreamImpl<typename ServerType::ConnectionType> Communicator<ServerType, RouterType>::getStream() {
    return { m_server.waitForConnection() };
}
