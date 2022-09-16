#pragma once

#include "Protocol.h"
#include "RequestsHandler.h"

template<typename T>
concept RequestsRouter = requires(T& t, const Buffer& data) {
    { t.route(data) } -> std::same_as<Buffer>;
};

template <RequestsHandler RequestsHandlerType, Protocol ProtocolType>
class RequestsRouterImpl {
public:
    RequestsRouterImpl(RequestsHandlerType handler, ProtocolType protocol);

    Buffer route(const Buffer& data);

private:
    RequestsHandlerType m_handler;
    Protocol m_protocol;
};

#include "RequestsRouter.inl"
