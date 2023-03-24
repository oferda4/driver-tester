#include "TcpSocket.h"

#include <gtest/gtest.h>

#include "MockTcpSocket.h"

using testing::_;
using testing::Return;

namespace {
constexpr SOCKET UNINTERESTING_SOCKET_HANDLE = 1;
constexpr SOCKET ARBITRARY_SOCKET_HANDLE = 46;
constexpr uint32_t UNINTERESTING_SIZE = 1024;
constexpr size_t ARBITRARY_BUFFER_SIZE = 2048;
const std::string ARBITRARY_IP_ADDRESS = "1.2.3.4";
const uint16_t ARBITRARY_PORT = 101;

Buffer getFakeBuffer();
}

TEST(TcpSocketConenctionTest, RecvSanity) {
    const Buffer fakeBuffer = getFakeBuffer();
    MoveableMockPosixTcpSocketAllApi api;
    EXPECT_CALL(api.getMock(),
                recv(ARBITRARY_SOCKET_HANDLE, _, CastUtils::cast<int>(fakeBuffer.size()), 0))
        .Times(1)
        .WillOnce([&fakeBuffer](SOCKET, char* buf, int, int) {
            memcpy(buf, fakeBuffer.data(), fakeBuffer.size());
            return CastUtils::cast<int>(fakeBuffer.size());
        });

    TcpSocketConnection<MoveableMockPosixTcpSocketAllApi> connection(
        std::move(api), SocketGuard<MoveableMockPosixTcpSocketAllApi>(ARBITRARY_SOCKET_HANDLE));
    const Buffer result = connection.recv(fakeBuffer.size());
    ASSERT_EQ(result, fakeBuffer);
}

TEST(TcpSocketConenctionTest, RecvPartial) {
    const Buffer fakeBuffer = getFakeBuffer();
    const size_t arbitraryPartialSize = fakeBuffer.size() / 3;
    MoveableMockPosixTcpSocketAllApi api;
    EXPECT_CALL(api.getMock(),
                recv(ARBITRARY_SOCKET_HANDLE, _, CastUtils::cast<int>(fakeBuffer.size()), 0))
        .Times(1)
        .WillOnce([&fakeBuffer, &arbitraryPartialSize](SOCKET, char* buf, int, int) {
            memcpy(buf, fakeBuffer.data(), arbitraryPartialSize);
            return CastUtils::cast<int>(arbitraryPartialSize);
        });

    TcpSocketConnection<MoveableMockPosixTcpSocketAllApi> connection(
        std::move(api), SocketGuard<MoveableMockPosixTcpSocketAllApi>(ARBITRARY_SOCKET_HANDLE));
    const Buffer result = connection.recv(fakeBuffer.size());
    ASSERT_EQ(result.size(), arbitraryPartialSize);
    ASSERT_EQ(memcmp(result.data(), fakeBuffer.data(), result.size()), 0);
}

TEST(TcpSocketConenctionTest, RecvFails) {
    MoveableMockPosixTcpSocketAllApi api;
    EXPECT_CALL(api.getMock(), recv(_, _, _, _)).Times(1).WillOnce(Return(SOCKET_ERROR));

    TcpSocketConnection<MoveableMockPosixTcpSocketAllApi> connection(
        std::move(api), SocketGuard<MoveableMockPosixTcpSocketAllApi>(UNINTERESTING_SOCKET_HANDLE));
    EXPECT_THROW(connection.recv(UNINTERESTING_SIZE),
                 MoveableMockPosixTcpSocketAllApi::ExceptionType);
}

TEST(TcpSocketConenctionTest, SendSanity) {
    const Buffer fakeBuffer = getFakeBuffer();
    MoveableMockPosixTcpSocketAllApi api;
    EXPECT_CALL(api.getMock(),
                send(ARBITRARY_SOCKET_HANDLE, _, CastUtils::cast<int>(fakeBuffer.size()), 0))
        .Times(1)
        .WillOnce(Return(CastUtils::cast<int>(fakeBuffer.size())));

    TcpSocketConnection<MoveableMockPosixTcpSocketAllApi> connection(
        std::move(api), SocketGuard<MoveableMockPosixTcpSocketAllApi>(ARBITRARY_SOCKET_HANDLE));
    const auto result = connection.send(fakeBuffer);
    ASSERT_EQ(result, fakeBuffer.size());
}

TEST(TcpSocketConenctionTest, SendPartial) {
    const Buffer fakeBuffer = getFakeBuffer();
    const int arbitraryPartialSize = CastUtils::cast<int>(fakeBuffer.size() / 5);
    MoveableMockPosixTcpSocketAllApi api;
    EXPECT_CALL(api.getMock(),
                send(ARBITRARY_SOCKET_HANDLE, _, CastUtils::cast<int>(fakeBuffer.size()), 0))
        .Times(1)
        .WillOnce(Return(arbitraryPartialSize));

    TcpSocketConnection<MoveableMockPosixTcpSocketAllApi> connection(
        std::move(api), SocketGuard<MoveableMockPosixTcpSocketAllApi>(ARBITRARY_SOCKET_HANDLE));
    const auto result = connection.send(fakeBuffer);
    ASSERT_EQ(result, arbitraryPartialSize);
}

TEST(TcpSocketConenctionTest, SendFails) {
    MoveableMockPosixTcpSocketAllApi api;
    EXPECT_CALL(api.getMock(), send(_, _, _, _)).Times(1).WillOnce(Return(SOCKET_ERROR));

    TcpSocketConnection<MoveableMockPosixTcpSocketAllApi> connection(
        std::move(api), SocketGuard<MoveableMockPosixTcpSocketAllApi>(UNINTERESTING_SOCKET_HANDLE));
    EXPECT_THROW(connection.send(getFakeBuffer()), MoveableMockPosixTcpSocketAllApi::ExceptionType);
}

TEST(TcpSocketServerTest, Initialization) {
    MoveableMockPosixTcpSocketAllApi api;
    EXPECT_CALL(api.getMock(), create(AF_INET, SOCK_STREAM, IPPROTO_TCP))
        .Times(1)
        .WillOnce(Return(ARBITRARY_SOCKET_HANDLE));
    EXPECT_CALL(api.getMock(), bind(ARBITRARY_SOCKET_HANDLE, _, sizeof(sockaddr_in)))
        .Times(1)
        .WillOnce(Return(0));
    EXPECT_CALL(api.getMock(), listen(ARBITRARY_SOCKET_HANDLE, 1)).Times(1).WillOnce(Return(0));
    ASSERT_NO_THROW(TcpSocketServer<MoveableMockPosixTcpSocketAllApi>(
        std::move(api), ARBITRARY_IP_ADDRESS, ARBITRARY_PORT));
}

TEST(TcpSocketServerTest, FailsCreating) {
    MoveableMockPosixTcpSocketAllApi api;
    EXPECT_CALL(api.getMock(), create(AF_INET, SOCK_STREAM, IPPROTO_TCP))
        .Times(1)
        .WillOnce(Return(INVALID_SOCKET));
    ASSERT_THROW(TcpSocketServer<MoveableMockPosixTcpSocketAllApi>(
                     std::move(api), ARBITRARY_IP_ADDRESS, ARBITRARY_PORT),
                 FakeExceptionForMockPosixSocket);
}

TEST(TcpSocketServerTest, FailsBinding) {
    MoveableMockPosixTcpSocketAllApi api;
    EXPECT_CALL(api.getMock(), create(_, _, _)).Times(1).WillOnce(Return(ARBITRARY_SOCKET_HANDLE));
    EXPECT_CALL(api.getMock(), bind(ARBITRARY_SOCKET_HANDLE, _, sizeof(sockaddr_in)))
        .Times(1)
        .WillOnce(Return(SOCKET_ERROR));
    ASSERT_THROW(TcpSocketServer<MoveableMockPosixTcpSocketAllApi>(
                     std::move(api), ARBITRARY_IP_ADDRESS, ARBITRARY_PORT),
                 FakeExceptionForMockPosixSocket);
}

TEST(TcpSocketServerTest, FailsListening) {
    MoveableMockPosixTcpSocketAllApi api;
    EXPECT_CALL(api.getMock(), create(_, _, _)).Times(1).WillOnce(Return(ARBITRARY_SOCKET_HANDLE));
    EXPECT_CALL(api.getMock(), bind(_, _, _)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(api.getMock(), listen(ARBITRARY_SOCKET_HANDLE, 1))
        .Times(1)
        .WillOnce(Return(SOCKET_ERROR));
    ASSERT_THROW(TcpSocketServer<MoveableMockPosixTcpSocketAllApi>(
                     std::move(api), ARBITRARY_IP_ADDRESS, ARBITRARY_PORT),
                 FakeExceptionForMockPosixSocket);
}

TEST(TcpSocketServerTest, BadAddress) {
    const std::string badIpAddress = "400.1.1.1";
    ASSERT_THROW(TcpSocketServer<MoveableMockPosixTcpSocketAllApi>(badIpAddress, ARBITRARY_PORT),
                 BadIpAddress);
}

TEST(TcpSocketServerTest, WaitForConnection) {
    MoveableMockPosixTcpSocketAllApi api;
    EXPECT_CALL(api.getMock(), create(_, _, _)).Times(1).WillOnce(Return(ARBITRARY_SOCKET_HANDLE));
    EXPECT_CALL(api.getMock(), bind(_, _, _)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(api.getMock(), listen(_, _)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(api.getMock(), accept(ARBITRARY_SOCKET_HANDLE, nullptr, nullptr)).Times(1);

    TcpSocketServer<MoveableMockPosixTcpSocketAllApi> server(std::move(api), ARBITRARY_IP_ADDRESS,
                                                             ARBITRARY_PORT);
    ASSERT_NO_THROW((void)server.waitForConnection());
}

TEST(TcpSocketServerTest, WaitForConnectionFails) {
    MoveableMockPosixTcpSocketAllApi api;
    EXPECT_CALL(api.getMock(), create(_, _, _))
        .Times(1)
        .WillOnce(Return(UNINTERESTING_SOCKET_HANDLE));
    EXPECT_CALL(api.getMock(), bind(_, _, _)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(api.getMock(), listen(_, _)).Times(1).WillOnce(Return(0));
    EXPECT_CALL(api.getMock(), accept(_, _, _)).Times(1).WillOnce(Return(SOCKET_ERROR));

    TcpSocketServer<MoveableMockPosixTcpSocketAllApi> server(std::move(api), ARBITRARY_IP_ADDRESS,
                                                             ARBITRARY_PORT);
    ASSERT_THROW((void)server.waitForConnection(), FakeExceptionForMockPosixSocket);
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
