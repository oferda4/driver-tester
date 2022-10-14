#include <gtest/gtest.h>

#include "TcpSocket.h"

#include "MockTcpSocket.h"

using testing::_;
using testing::Return;

namespace{
constexpr SOCKET UNINTERESTING_SOCKET_HANDLE = 1;
constexpr uint32_t UNINTERESTING_SIZE = 1024;
constexpr size_t ARBITRARY_BUFFER_SIZE = 2048;

Buffer getFakeBuffer();
}

TEST(TcpSocketConenctionTest, RecvSanity) {
    const Buffer fakeBuffer = getFakeBuffer();
    const SOCKET arbitrarySocket = 15;
    MoveableMockPosixTcpSocketAllTraits traits;
    EXPECT_CALL(traits.getMock(), recv(arbitrarySocket, _, CastUtils::cast<int>(fakeBuffer.size()), 0))
        .Times(1)
        .WillOnce([&fakeBuffer](SOCKET, char* buf, int, int) {
            memcpy(buf, fakeBuffer.data(), fakeBuffer.size());
            return CastUtils::cast<int>(fakeBuffer.size());
        });
    
    TcpSocketConnection<MoveableMockPosixTcpSocketAllTraits> connection(
        std::move(traits),
        SocketGuard<MoveableMockPosixTcpSocketAllTraits>(arbitrarySocket));
    const Buffer result = connection.recv(fakeBuffer.size());
    ASSERT_EQ(result, fakeBuffer);
}

TEST(TcpSocketConenctionTest, RecvPartial) {
    const Buffer fakeBuffer = getFakeBuffer();
    const size_t arbitraryPartialSize = fakeBuffer.size() / 3;
    const SOCKET arbitrarySocket = 27;
    MoveableMockPosixTcpSocketAllTraits traits;
    EXPECT_CALL(traits.getMock(), recv(arbitrarySocket, _, CastUtils::cast<int>(fakeBuffer.size()), 0))
        .Times(1)
        .WillOnce([&fakeBuffer, &arbitraryPartialSize](SOCKET, char* buf, int, int) {
            memcpy(buf, fakeBuffer.data(), arbitraryPartialSize);
            return CastUtils::cast<int>(arbitraryPartialSize);
        });

    TcpSocketConnection<MoveableMockPosixTcpSocketAllTraits> connection(
        std::move(traits),
        SocketGuard<MoveableMockPosixTcpSocketAllTraits>(arbitrarySocket));
    const Buffer result = connection.recv(fakeBuffer.size());
    ASSERT_EQ(result.size(), arbitraryPartialSize);
    ASSERT_EQ(memcmp(result.data(), fakeBuffer.data(), result.size()), 0);
}

TEST(TcpSocketConenctionTest, RecvFails) {
    MoveableMockPosixTcpSocketAllTraits traits;
    EXPECT_CALL(traits.getMock(), recv(_, _, _, _))
        .Times(1)
        .WillOnce(Return(SOCKET_ERROR));
    
    TcpSocketConnection<MoveableMockPosixTcpSocketAllTraits> connection(
        std::move(traits), 
        SocketGuard<MoveableMockPosixTcpSocketAllTraits>(UNINTERESTING_SOCKET_HANDLE));
    EXPECT_THROW(connection.recv(UNINTERESTING_SIZE), 
                 MoveableMockPosixTcpSocketAllTraits::ExceptionType);
}

TEST(TcpSocketConenctionTest, SendSanity) {
    const Buffer fakeBuffer = getFakeBuffer();
    const SOCKET arbitrarySocket = 300;
    MoveableMockPosixTcpSocketAllTraits traits;
    EXPECT_CALL(traits.getMock(), send(arbitrarySocket, _, CastUtils::cast<int>(fakeBuffer.size()), 0))
        .Times(1)
        .WillOnce(Return(CastUtils::cast<int>(fakeBuffer.size())));

    TcpSocketConnection<MoveableMockPosixTcpSocketAllTraits> connection(
        std::move(traits),
        SocketGuard<MoveableMockPosixTcpSocketAllTraits>(arbitrarySocket));
    const auto result = connection.send(fakeBuffer);
    ASSERT_EQ(result, fakeBuffer.size());
}

TEST(TcpSocketConenctionTest, SendPartial) {
    const Buffer fakeBuffer = getFakeBuffer();
    const int arbitraryPartialSize = CastUtils::cast<int>(fakeBuffer.size() / 5);
    const SOCKET arbitrarySocket = 3;
    MoveableMockPosixTcpSocketAllTraits traits;
    EXPECT_CALL(traits.getMock(), send(arbitrarySocket, _, CastUtils::cast<int>(fakeBuffer.size()), 0))
        .Times(1)
        .WillOnce(Return(arbitraryPartialSize));

    TcpSocketConnection<MoveableMockPosixTcpSocketAllTraits> connection(
        std::move(traits),
        SocketGuard<MoveableMockPosixTcpSocketAllTraits>(arbitrarySocket));
    const auto result = connection.send(fakeBuffer);
    ASSERT_EQ(result, arbitraryPartialSize);
}

TEST(TcpSocketConenctionTest, SendFails) {
    MoveableMockPosixTcpSocketAllTraits traits;
    EXPECT_CALL(traits.getMock(), send(_, _, _, _))
        .Times(1)
        .WillOnce(Return(SOCKET_ERROR));

    TcpSocketConnection<MoveableMockPosixTcpSocketAllTraits> connection(
        std::move(traits),
        SocketGuard<MoveableMockPosixTcpSocketAllTraits>(UNINTERESTING_SOCKET_HANDLE));
    EXPECT_THROW(connection.send(getFakeBuffer()),
        MoveableMockPosixTcpSocketAllTraits::ExceptionType);
}

namespace {
Buffer getFakeBuffer() {
    Buffer buffer(ARBITRARY_BUFFER_SIZE);
    for (size_t i = 0; i < buffer.size(); i++) {
        buffer[i] = static_cast<byte>(i);
    }
    return buffer;
}
}
