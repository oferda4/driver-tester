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
