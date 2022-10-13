#include <gtest/gtest.h>

#include "TcpSocket.h"

#include "MockTcpSocket.h"

using testing::_;
using testing::Return;

namespace{
constexpr SOCKET UNINTERESTING_SOCKET_HANDLE = 1;
constexpr uint32_t UNINTERESTING_SIZE = 1024;
}

TEST(TcpSocketConenctionTest, RecvSanity) {

}

TEST(TcpSocketConenctionTest, RecvPartial) {
}

TEST(TcpSocketConenctionTest, RecvFails) {
    MoveableMockPosixTcpSocketAllTraits traits;
    EXPECT_CALL(traits.getMock(), recv(_, _, _, _)).Times(1).WillOnce(Return(SOCKET_ERROR));
    TcpSocketConnection<MoveableMockPosixTcpSocketAllTraits> connection(
        std::move(traits), 
        SocketGuard<MoveableMockPosixTcpSocketAllTraits>(UNINTERESTING_SOCKET_HANDLE));
    EXPECT_THROW(connection.recv(UNINTERESTING_SIZE), 
                 MoveableMockPosixTcpSocketAllTraits::ExceptionType);
}
