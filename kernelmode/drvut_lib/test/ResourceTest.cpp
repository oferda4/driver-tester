#include <gtest/gtest.h>

#include "Resource.h"
#include "MockResource.h"

namespace drvut {
namespace internal {

TEST(ResourceTest, Functionality) {
    MoveableMockResource resource;
    EXPECT_CALL(resource.getMock(), initialize()).Times(1);
    EXPECT_CALL(resource.getMock(), destroy()).Times(1);
    {
        ResourceGuard<MoveableMockResource> guard(std::move(resource));
        ASSERT_TRUE(NT_SUCCESS(guard.init()));
    }
}

// TODO: test move ctor and assignment

TEST(ResourceTest, GuardingWhenAlreadyInitialized) {
    MoveableMockResource resource;
    EXPECT_CALL(resource.getMock(), initialize()).Times(0);
    EXPECT_CALL(resource.getMock(), destroy()).Times(1);
    {
        ResourceGuard<MoveableMockResource> guard(std::move(resource), true);
    }
}

TEST(ResourceTest, CannotInitializeTwice) {
    MoveableMockResource resource;
    EXPECT_CALL(resource.getMock(), initialize()).Times(1);
    EXPECT_CALL(resource.getMock(), destroy()).Times(1);
    ResourceGuard<MoveableMockResource> guard(std::move(resource));

    ASSERT_TRUE(NT_SUCCESS(guard.init()));
    ASSERT_ANY_THROW(guard.init());
}

TEST(ResourceTest, DoNotDestroyIfNotInitialized) {
    MoveableMockResource resource;
    EXPECT_CALL(resource.getMock(), initialize()).Times(0);
    EXPECT_CALL(resource.getMock(), destroy()).Times(0);
    {
        ResourceGuard<MoveableMockResource> guard(std::move(resource));
    }
}

}
}
