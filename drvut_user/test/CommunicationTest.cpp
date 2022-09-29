#include <gtest/gtest.h>

#include "Communication.h"

#include "MockCommunication.h"

using testing::_;

TEST(CommunicatorTest, Sanity) {
    MoveableMockCommunicationSetup setup;
    EXPECT_CALL(setup.getMock(), run()).Times(1);
    MoveableMockCommunicationLogic logic;
    EXPECT_CALL(logic.getMock(), run(_)).Times(1);

    Communication<decltype(setup), decltype(logic)> communication(std::move(setup), std::move(logic));
    ASSERT_NO_THROW(communication.run());
}
