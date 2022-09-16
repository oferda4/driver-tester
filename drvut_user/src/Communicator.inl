#pragma once

#include "Communicator.h"

template <Connection ConnectionType, RequestsRouter RouterType>
Communicator<ConnectionType, RouterType>::Communicator(ConnectionType connection, RouterType rotuer)
    : m_connection(std::move(connection)), m_router(std::move(router)) {
    // Left blank intentionally
}

template <Connection ConnectionType, RequestsRouter RouterType>
void Communicator<ConnectionType, RouterType>::run() {
    Buffer data = m_connection.recv();
    while (!data.empty()) {
        Buffer response = m_router.route(data);
        m_connection.send(response);
        data = m_connection.recv();
    }
}
