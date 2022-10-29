#pragma once

#include "Parser.h"
#include "RequestsHandler.h"

template<typename T>
concept RequestsRouter = requires(T& t, const Buffer& data) {
    { t.route(data) } -> std::same_as<Buffer>;
};

template <RequestsHandler RequestsHandlerType, Parser ParserType>
class RequestsRouterImpl {
public:
    RequestsRouterImpl(RequestsHandlerType handler, ParserType parser);

    Buffer route(const Buffer& data);

private:
    ParserType m_parser;
    RequestsHandlerType m_handler;
};

#include "RequestsRouter.inl"
