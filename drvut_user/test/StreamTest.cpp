#include <gtest/gtest.h>

#include "Stream.h"
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
}

TEST(StreamTest, send) {
    MoveableMockConnection connection;
    EXPECT_CALL(connection.getMock(), send(_))
        .Times(ARBITRARY_BUFFER_SIZE / ARBITRARY_CHUNK_SIZE + 1)
        .WillOnce(Return(static_cast<uint32_t>(sizeof(StreamImpl<MoveableMockConnection>::SizeType))))
        .WillRepeatedly(Return(ARBITRARY_CHUNK_SIZE));

    StreamImpl stream(std::move(connection));
    ASSERT_NO_THROW(stream.send(getFakeBuffer(ARBITRARY_BUFFER_SIZE)));
}

TEST(StreamTest, recv) {
    MoveableMockConnection connection;
    EXPECT_CALL(connection.getMock(), recv(_))
        .Times(ARBITRARY_BUFFER_SIZE / ARBITRARY_CHUNK_SIZE + 1)
        .WillOnce(Return(BufferUtils::fromNumber(static_cast<StreamImpl<MoveableMockConnection>::SizeType>(ARBITRARY_BUFFER_SIZE))))
        .WillRepeatedly(Return(getFakeBuffer(ARBITRARY_CHUNK_SIZE)));

    StreamImpl stream(std::move(connection));
    ASSERT_NO_THROW((void)stream.recv());
}

// TODO: test connection termination in the middle of send / recv

namespace {
Buffer getFakeBuffer(size_t size) {
    return Buffer(size, 0);
}
}