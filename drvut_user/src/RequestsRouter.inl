#pragma once

#include "RequestsRouter.h"

template <RequestsHandler RequestsHandlerType, Protocol ProtocolType>
RequestsRouterImpl<RequestsHandlerType, ProtocolType>::RequestsRouterImpl(RequestsHandlerType handler, ProtocolType protocol) 
    : m_handler(std::move(handler)), m_protocol(std::move(protocol)) {
    // Left blank intentionally
}

template <RequestsHandler RequestsHandlerType, Protocol ProtocolType>
Buffer RequestsRouterImpl<RequestsHandlerType, ProtocolType>::route(const Buffer& data) {
    Request request = m_protocol.parse(data);
    switch (request.type) {
    case RequestType::LIST_FIXTURES:
        return m_protocol.parseListFixturesOutput(
            m_handler.listFixtures(
                m_protocol.parseListFixturesInput(data)
            )
        );
    }

    throw std::exception("invalid request");
}