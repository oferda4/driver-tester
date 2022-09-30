#include <gtest/gtest.h>

#include "Communication.h"

#include "MockCommunication.h"
#include "MockServer.h"

using testing::_;

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