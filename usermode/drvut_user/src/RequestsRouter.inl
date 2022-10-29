#pragma once

#include "RequestsRouter.h"

template <RequestsHandler RequestsHandlerType, Parser ParserType>
RequestsRouterImpl<RequestsHandlerType, ParserType>::RequestsRouterImpl(RequestsHandlerType handler, ParserType parser) 
    : m_handler(std::move(handler)), m_parser(std::move(parser)) {
    // Left blank intentionally
}

template <RequestsHandler RequestsHandlerType, Parser ParserType>
Buffer RequestsRouterImpl<RequestsHandlerType, ParserType>::route(const Buffer& data) {
    ParsedRequest request = m_parser.parseRequest(data);
    switch (request.type) {
    case RequestType::LIST_FIXTURES:
        return m_parser.parseListFixturesOutput(
            m_handler.listFixtures(
                request.input.listFixturesInput));
    case RequestType::LIST_TESTS:
        return m_parser.parseListTestsOutput(
            m_handler.listTests(
                request.input.listTestsInput));
    case RequestType::RUN_TEST:
        return m_parser.parseRunTestOutput(
            m_handler.runTest(
                request.input.runTestInput));
    }

    throw std::exception("invalid request");
}