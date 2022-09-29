#pragma once

#include "Stream.h"
#include "Connection.h"
#include "Server.h"
#include "RequestsRouter.h"

template <Server ServerType, RequestsRouter RouterType>
class Communicator {
public:
    Communicator(ServerType server, RouterType router);

    void run();

private:
    StreamImpl<typename ServerType::ConnectionType> getStream();

    ServerType m_server;
    RouterType m_router;
};

#include "Communicator.inl"
