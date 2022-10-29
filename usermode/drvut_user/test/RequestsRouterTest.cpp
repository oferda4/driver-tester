#include <gtest/gtest.h>

#include "RequestsRouter.h"

#include "MockRequestsHandler.h"
#include "MockParser.h"

using testing::_;
using testing::Return;

TEST(RequestsRouterTest, RoutingListFixtures) {
    MoveableMockRequestsHandler handler;
    MoveableMockParser parser; 
    Buffer fakeBuffer;

    EXPECT_CALL(parser.getMock(), parseRequest(_))
        .WillOnce(
            Return(ParsedRequest{ .type = RequestType::LIST_FIXTURES, 
                                  .input = { .listFixturesInput = {} } })
        );
    EXPECT_CALL(parser.getMock(), parseListFixturesOutput(_))
        .WillOnce(
            Return(fakeBuffer)
        );
    
    EXPECT_CALL(handler.getMock(), listFixtures(_))
        .WillOnce(
            Return(ListFixturesOutput())
        );

    RequestsRouterImpl router(std::move(handler), std::move(parser));
    ASSERT_NO_THROW((void)router.route(fakeBuffer));
}

TEST(RequestsRouterTest, RoutingListTests) {
    MoveableMockRequestsHandler handler;
    MoveableMockParser parser;
    Buffer fakeBuffer;

    EXPECT_CALL(parser.getMock(), parseRequest(_))
        .WillOnce(
            Return(ParsedRequest { .type = RequestType::LIST_TESTS, 
                                   .input = { .listTestsInput =  {} } })
        );
    EXPECT_CALL(parser.getMock(), parseListTestsOutput(_))
        .WillOnce(
            Return(fakeBuffer));

    EXPECT_CALL(handler.getMock(), listTests(_))
        .WillOnce(
            Return(ListTestsOutput()));

    RequestsRouterImpl router(std::move(handler), std::move(parser));
    ASSERT_NO_THROW((void)router.route(fakeBuffer));
}

TEST(RequestsRouterTest, RoutingRunTest) {
    MoveableMockRequestsHandler handler;
    MoveableMockParser parser;
    Buffer fakeBuffer;

    EXPECT_CALL(parser.getMock(), parseRequest(_))
        .WillOnce(
            Return(ParsedRequest { .type = RequestType::RUN_TEST, 
                                   .input = { .runTestInput = {} } })
        );
    EXPECT_CALL(parser.getMock(), parseRunTestOutput(_))
        .WillOnce(
            Return(fakeBuffer));

    EXPECT_CALL(handler.getMock(), runTest(_))
        .WillOnce(
            Return(RunTestOutput()));

    RequestsRouterImpl router(std::move(handler), std::move(parser));
    ASSERT_NO_THROW((void)router.route(fakeBuffer));
}
