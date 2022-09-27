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
    const size_t arbitraryBufferSize = 4096;
    const size_t arbitraryChunkSize = 1024;
    static_assert(arbitraryBufferSize > arbitraryChunkSize);
    static_assert(arbitraryBufferSize % arbitraryChunkSize == 0);

    MoveableMockConnection connection;
    
    EXPECT_CALL(connection.getMock(), send(_))
        .WillRepeatedly(Return(arbitraryChunkSize))
        .Times(arbitraryBufferSize / arbitraryChunkSize);

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
        .WillRepeatedly(Return(getFakeBuffer(arbitraryChunkSize)))
        .Times(arbitraryBufferSize / arbitraryChunkSize);

    StreamImpl stream(std::move(connection));
    ASSERT_NO_THROW((void)stream.recv());
}

namespace {
Buffer getFakeBuffer(size_t size) {
    return Buffer(size, 0);
}
}