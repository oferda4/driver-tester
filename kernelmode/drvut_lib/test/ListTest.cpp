#include "gtest/gtest.h"

#include <list>

#include "List.h"

namespace drvut {
namespace internal {

namespace {
struct LeakCounter {
    LeakCounter() { leaked++; }
    ~LeakCounter() { leaked--; }
    NOCOPY(LeakCounter);
    LeakCounter(LeakCounter&& other) noexcept { leaked++; }
    LeakCounter& operator=(LeakCounter&& other) {
        leaked++;
        return *this;
    }

    static uint32_t leaked;
};
uint32_t LeakCounter::leaked = 0;

void insertAndAssert(List<int>& list, ::std::list<int>& prototype, int value);
}

TEST(ListTest, Functionality) {
    List<int> list;
    ::std::list<int> prototype;
    int arbitraryValues[] = { 1, 5, -11 };

    ASSERT_EQ(list.size(), 0);
    for (auto value : arbitraryValues) {
        insertAndAssert(list, prototype, value);
    }
}

TEST(ListTest, Dtor) {
    constexpr uint32_t arbitraryNumberOfValues = 10;
    static_assert(arbitraryNumberOfValues > 0);

    {
        List<LeakCounter> list;
        for (uint32_t i = 0; i < arbitraryNumberOfValues; i++) {
            list.push_back(LeakCounter());
        }
        ASSERT_EQ(LeakCounter::leaked, arbitraryNumberOfValues);
    }
    ASSERT_EQ(LeakCounter::leaked, 0);
}

namespace {

void insertAndAssert(List<int>& list, ::std::list<int>& prototype, int value) {
    list.push_back(value);
    prototype.push_back(value);
    
    ASSERT_EQ(list.size(), prototype.size());
    ASSERT_EQ(list.head()->value, *prototype.begin());
    ASSERT_EQ(static_cast<const List<int>&>(list).head()->value, *prototype.begin());

    auto* node = list.head();
    auto expected = prototype.begin();
    for (; node != nullptr && expected != prototype.end() ; node = node->next, expected++) {
        ASSERT_EQ(node->value, *expected);
    }
    ASSERT_EQ(node, nullptr);
    ASSERT_EQ(expected, prototype.end());
}

}

}
}
