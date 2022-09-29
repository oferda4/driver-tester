#include <gtest/gtest.h>

#include "RequestsRouter.h"

#include "MockRequestsHandler.h"
#include "MockProtocol.h"

using testing::_;
using testing::Return;

TEST(RequestsRouterTest, routingListFixtures) {
    MoveableMockRequestsHandler handler;
    MoveableMockProtocol protocol; 
    Buffer fakeBuffer;

    EXPECT_CALL(protocol.getMock(), parse(_))
        .WillOnce(
            Return(Request(RequestType::LIST_FIXTURES, fakeBuffer))
        );
    EXPECT_CALL(protocol.getMock(), parseListFixturesOutput(_))
        .WillOnce(
            Return(fakeBuffer)
        );
    EXPECT_CALL(protocol.getMock(), parseListFixturesInput(_))
        .WillOnce(
            Return(ListFixturesInput())
        );

    EXPECT_CALL(handler.getMock(), listFixtures(_))
        .WillOnce(
            Return(ListFixturesOutput())
        );

    RequestsRouterImpl router(std::move(handler), std::move(protocol));
    ASSERT_NO_THROW((void)router.route(fakeBuffer));
}

TEST(RequestsRouterTest, routingListTests) {
    MoveableMockRequestsHandler handler;
    MoveableMockProtocol protocol;
    Buffer fakeBuffer;

    EXPECT_CALL(protocol.getMock(), parse(_))
        .WillOnce(
            Return(Request(RequestType::LIST_TESTS, fakeBuffer)));
    EXPECT_CALL(protocol.getMock(), parseListTestsOutput(_))
        .WillOnce(
            Return(fakeBuffer));
    EXPECT_CALL(protocol.getMock(), parseListTestsInput(_))
        .WillOnce(
            Return(ListTestsInput()));

    EXPECT_CALL(handler.getMock(), listTests(_))
        .WillOnce(
            Return(ListTestsOutput()));

    RequestsRouterImpl router(std::move(handler), std::move(protocol));
    ASSERT_NO_THROW((void)router.route(fakeBuffer));
}

TEST(RequestsRouterTest, routingRunTest) {
    MoveableMockRequestsHandler handler;
    MoveableMockProtocol protocol;
    Buffer fakeBuffer;

    EXPECT_CALL(protocol.getMock(), parse(_))
        .WillOnce(
            Return(Request(RequestType::RUN_TEST, fakeBuffer)));
    EXPECT_CALL(protocol.getMock(), parseRunTestOutput(_))
        .WillOnce(
            Return(fakeBuffer));
    EXPECT_CALL(protocol.getMock(), parseRunTestInput(_))
        .WillOnce(
            Return(RunTestInput()));

    EXPECT_CALL(handler.getMock(), runTest(_))
        .WillOnce(
            Return(RunTestOutput()));

    RequestsRouterImpl router(std::move(handler), std::move(protocol));
    ASSERT_NO_THROW((void)router.route(fakeBuffer));
}
