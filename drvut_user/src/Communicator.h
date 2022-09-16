#pragma once

#include "Connection.h"
#include "RequestsRouter.h"

template <Connection ConnectionType, RequestsRouter RouterType>
class Communicator {
public:
    Communicator(ConnectionType connection, RouterType router);

    void run();

private:
    ConnectionType m_connection;
    RouterType m_router;
};

#include "Communicator.inl"
