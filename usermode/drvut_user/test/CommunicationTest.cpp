#include "Communication.h"

#include <gtest/gtest.h>

#include "MockCommunication.h"
#include "MockRequestsRouter.h"
#include "MockServer.h"

using testing::_;
using testing::Return;

TEST(CommunicationTest, Sanity) {
    MoveableMockCommunicationSetup setup;
    EXPECT_CALL(setup.getMock(), run()).Times(1);
    MoveableMockCommunicationLogic logic;
    EXPECT_CALL(logic.getMock(), run(_)).Times(1);

    Communication communication(std::move(setup), std::move(logic));
    ASSERT_NO_THROW(communication.run());
}

TEST(CommunicationTest, Setup) {
    MoveableMockServer server;
    EXPECT_CALL(server.getMock(), waitForConnection());

    CommunicationSetupImpl<MoveableMockServer> setup(std::move(server));
    ASSERT_NO_THROW(setup.run());
}

TEST(CommunicationTest, Logic) {
    MoveableMockStream stream;
    EXPECT_CALL(stream.getMock(), recv())
        .Times(2)
        .WillOnce(Return(Buffer(1, 0)))
        .WillOnce(Return(Buffer()));
    EXPECT_CALL(stream.getMock(), send(_)).Times(1);

    MoveableMockRequestsRouter router;
    EXPECT_CALL(router.getMock(), route(_)).Times(1);

    CommunicationLogicImpl<MoveableMockStream, MoveableMockRequestsRouter> logic(std::move(router));
    ASSERT_NO_THROW(logic.run(stream));
}