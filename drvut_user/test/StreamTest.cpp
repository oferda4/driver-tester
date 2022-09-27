#include <gtest/gtest.h>

#include "Stream.h"
#include "Buffer.h"

#include "MockConnection.h"

using testing::_;
using testing::Return;

namespace {
Buffer getFakeBuffer(size_t size);
}

TEST(StreamTest, send) {
    const uint32_t arbitraryBufferSize = 4096;
    const uint32_t arbitraryChunkSize = 1024;
    static_assert(arbitraryBufferSize > arbitraryChunkSize);
    static_assert(arbitraryBufferSize % arbitraryChunkSize == 0);

    MoveableMockConnection connection;
    
    EXPECT_CALL(connection.getMock(), send(_))
        .Times(arbitraryBufferSize / arbitraryChunkSize + 1)
        .WillOnce(Return(static_cast<uint32_t>(sizeof(StreamImpl<MoveableMockConnection>::SizeType))))
        .WillRepeatedly(Return(arbitraryChunkSize));

    StreamImpl stream(std::move(connection));
    ASSERT_NO_THROW(stream.send(getFakeBuffer(arbitraryBufferSize)));
}

TEST(StreamTest, recv) {
    const size_t arbitraryBufferSize = 4096;
    const size_t arbitraryChunkSize = 1024;
    static_assert(arbitraryBufferSize > arbitraryChunkSize);
    static_assert(arbitraryBufferSize % arbitraryChunkSize == 0);

    MoveableMockConnection connection;

    EXPECT_CALL(connection.getMock(), recv(_))
        .Times(arbitraryBufferSize / arbitraryChunkSize + 1)
        .WillOnce(Return(BufferUtils::fromNumber(static_cast<StreamImpl<MoveableMockConnection>::SizeType>(arbitraryBufferSize))))
        .WillRepeatedly(Return(getFakeBuffer(arbitraryChunkSize)));

    StreamImpl stream(std::move(connection));
    ASSERT_NO_THROW((void)stream.recv());
}

namespace {
Buffer getFakeBuffer(size_t size) {
    return Buffer(size, 0);
}
}