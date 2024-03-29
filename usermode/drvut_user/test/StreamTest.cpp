#include "Stream.h"

#include <gtest/gtest.h>

#include "Buffer.h"
#include "MockConnection.h"

using testing::_;
using testing::Return;

namespace {
Buffer getFakeBuffer(size_t size);

constexpr uint32_t ARBITRARY_BUFFER_SIZE = 4096;
constexpr uint32_t ARBITRARY_CHUNK_SIZE = 1024;
static_assert(ARBITRARY_BUFFER_SIZE > ARBITRARY_CHUNK_SIZE);
static_assert(ARBITRARY_BUFFER_SIZE % ARBITRARY_CHUNK_SIZE == 0);

constexpr uint32_t SIZE_BUFFER_SIZE =
    static_cast<uint32_t>(sizeof(StreamImpl<MoveableMockConnection>::SizeType));
}

TEST(StreamTest, Send) {
    MoveableMockConnection connection;
    EXPECT_CALL(connection.getMock(), send(_))
        .Times(ARBITRARY_BUFFER_SIZE / ARBITRARY_CHUNK_SIZE + 1)
        .WillOnce(Return(SIZE_BUFFER_SIZE))
        .WillRepeatedly(Return(ARBITRARY_CHUNK_SIZE));

    StreamImpl stream(std::move(connection));
    ASSERT_NO_THROW(stream.send(getFakeBuffer(ARBITRARY_BUFFER_SIZE)));
}

TEST(StreamTest, Recv) {
    MoveableMockConnection connection;
    EXPECT_CALL(connection.getMock(), recv(_))
        .Times(ARBITRARY_BUFFER_SIZE / ARBITRARY_CHUNK_SIZE + 1)
        .WillOnce(Return(BufferUtils::fromNumber(
            static_cast<StreamImpl<MoveableMockConnection>::SizeType>(ARBITRARY_BUFFER_SIZE))))
        .WillRepeatedly(Return(getFakeBuffer(ARBITRARY_CHUNK_SIZE)));

    StreamImpl stream(std::move(connection));
    ASSERT_NO_THROW((void)stream.recv());
}

TEST(StreamTest, SendInterruptedWhileSendingSize) {
    MoveableMockConnection connection;
    EXPECT_CALL(connection.getMock(), send(_))
        .Times(2)
        .WillOnce(Return(SIZE_BUFFER_SIZE - 1))
        .WillOnce(Return(0));

    StreamImpl stream(std::move(connection));
    ASSERT_THROW(stream.send(getFakeBuffer(ARBITRARY_BUFFER_SIZE)),
                 ConnectionTerminatedInTheMiddle);
}

TEST(StreamTest, SendInterruptedWhileSendingData) {
    MoveableMockConnection connection;
    EXPECT_CALL(connection.getMock(), send(_))
        .Times(3)
        .WillOnce(Return(SIZE_BUFFER_SIZE))
        .WillOnce(Return(ARBITRARY_CHUNK_SIZE))
        .WillOnce(Return(0));

    StreamImpl stream(std::move(connection));
    ASSERT_THROW(stream.send(getFakeBuffer(ARBITRARY_BUFFER_SIZE)),
                 ConnectionTerminatedInTheMiddle);
}

TEST(StreamTest, RecvInterruptedInTheMiddleOfReceivingSize) {
    MoveableMockConnection connection;
    EXPECT_CALL(connection.getMock(), recv(_))
        .Times(2)
        .WillOnce(Return(getFakeBuffer(SIZE_BUFFER_SIZE - 1)))
        .WillOnce(Return(Buffer()));

    StreamImpl stream(std::move(connection));
    ASSERT_THROW((void)stream.recv(), ConnectionTerminatedInTheMiddle);
}

TEST(StreamTest, RecvInterruptedInTheMiddleOfReceivingData) {
    MoveableMockConnection connection;
    EXPECT_CALL(connection.getMock(), recv(_))
        .Times(3)
        .WillOnce(Return(BufferUtils::fromNumber(
            static_cast<StreamImpl<MoveableMockConnection>::SizeType>(ARBITRARY_BUFFER_SIZE))))
        .WillOnce(Return(getFakeBuffer(ARBITRARY_CHUNK_SIZE)))
        .WillOnce(Return(Buffer()));

    StreamImpl stream(std::move(connection));
    ASSERT_THROW((void)stream.recv(), ConnectionTerminatedInTheMiddle);
}

namespace {
Buffer getFakeBuffer(size_t size) {
    return Buffer(size, 0);
}
}