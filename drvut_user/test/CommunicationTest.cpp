#include <gtest/gtest.h>

#include "Communication.h"

#include "MockServer.h"

TEST(CommunicatorTest, FullRun) {
    MoveableMockServer server;
    EXPECT_CALL(server.getMock(), waitForConnection());
}
