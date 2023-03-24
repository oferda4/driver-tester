#include <gtest/gtest.h>

#include "drvut/internal/Memory.h"

#include "LeakCounter.h"

namespace drvut::internal {

TEST(MemoryTest, GuardingOnDtor) {
    {
        auto ptr = std::unique_ptr<LeakCounter>(new LeakCounter());
        ASSERT_EQ(LeakCounter::leaked, 1);
    }
    ASSERT_EQ(LeakCounter::leaked, 0);
}

TEST(MemoryTest, Get) {
    auto* raw = new int(0);
    auto ptr = std::unique_ptr<int>(raw);
    ASSERT_EQ(ptr.get(), raw);
}

TEST(MemoryTest, CompareToNullptr) {
    auto ptr = std::unique_ptr<int>(new int(0));
    ASSERT_NE(ptr, nullptr);
    ptr = std::unique_ptr<int>(static_cast<int*>(nullptr));
    ASSERT_EQ(ptr, nullptr);
}

TEST(MemoryTest, Release) {
    auto* raw = new LeakCounter();
    {
        auto ptr = std::unique_ptr<LeakCounter>(raw);
        ASSERT_EQ(ptr.release(), raw);
        ASSERT_EQ(ptr, nullptr);
    }
    ASSERT_EQ(LeakCounter::leaked, 1);
    delete raw;
}

TEST(MemoryTest, MoveCtor) {
    auto ptr = std::unique_ptr<LeakCounter>(new LeakCounter());
    {
        auto ptrAfterMoved = std::unique_ptr<LeakCounter>(std::move(ptr));
        auto* raw = ptr.get();
        ASSERT_EQ(LeakCounter::leaked, 1);
    }
    ASSERT_EQ(LeakCounter::leaked, 0);
    ASSERT_EQ(ptr, nullptr);
}

TEST(MemoryTest, MoveAssingnment_ToEmpty) {
    auto ptr = std::unique_ptr<LeakCounter>(new LeakCounter());
    auto* raw = ptr.get();
    {
        auto ptrAfterMoved = std::unique_ptr<LeakCounter>(static_cast<LeakCounter*>(nullptr));
        ptrAfterMoved = std::move(ptr);
        ASSERT_EQ(ptrAfterMoved.get(), raw);
        ASSERT_EQ(LeakCounter::leaked, 1);
    }
    ASSERT_EQ(LeakCounter::leaked, 0);
    ASSERT_EQ(ptr, nullptr);
}

TEST(MemoryTest, MoveAssingnment_ToNotEmpty) {
    auto ptr = std::unique_ptr<LeakCounter>(new LeakCounter());
    auto* raw = ptr.get();
    {
        auto ptrAfterMoved = std::unique_ptr<LeakCounter>(new LeakCounter());
        ptrAfterMoved = std::move(ptr);
        ASSERT_EQ(ptrAfterMoved.get(), raw);
        ASSERT_EQ(LeakCounter::leaked, 1);
    }
    ASSERT_EQ(LeakCounter::leaked, 0);
    ASSERT_EQ(ptr, nullptr);
}

}
