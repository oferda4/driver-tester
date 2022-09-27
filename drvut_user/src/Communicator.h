#pragma once

#include "Stream.h"
#include "RequestsRouter.h"

template <Stream StreamType, RequestsRouter RouterType>
class Communicator {
public:
    Communicator(StreamType stream, RouterType router);

    void run();

private:
    StreamType m_stream;
    RouterType m_router;
};

#include "Communicator.inl"
