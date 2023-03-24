#include <gtest/gtest.h>

#include "drvut/Defs.h"

#include "drvut/internal/Resource.h"
#include "MockResource.h"

namespace drvut::internal {

TEST(ResourceTest, Functionality) {
    MoveableMockResource resource;
    EXPECT_CALL(resource.getMock(), initialize()).Times(1);
    EXPECT_CALL(resource.getMock(), destroy()).Times(1);
    {
        ResourceGuard<MoveableMockResource> guard(std::move(resource));
        ASSERT_TRUE(NT_SUCCESS(guard.init()));
    }
}

TEST(ResourceTest, MoveCtor) {
    MoveableMockResource resource;
    EXPECT_CALL(resource.getMock(), initialize()).Times(1);
    EXPECT_CALL(resource.getMock(), destroy()).Times(1);

    ResourceGuard<MoveableMockResource> guard(std::move(resource));
    ASSERT_TRUE(NT_SUCCESS(guard.init()));
    ResourceGuard<MoveableMockResource> guardAfterMove(std::move(guard));
    ASSERT_ANY_THROW(guard.get());
    ASSERT_NO_THROW(guardAfterMove.get());
}

TEST(ResourceTest, MoveAssignment_ToNonInitialized) {
    MoveableMockResource resource;
    MoveableMockResource resourceBeforeMove;
    EXPECT_CALL(resource.getMock(), initialize()).Times(1);
    EXPECT_CALL(resource.getMock(), destroy()).Times(1);
    EXPECT_CALL(resourceBeforeMove.getMock(), initialize()).Times(0);
    EXPECT_CALL(resourceBeforeMove.getMock(), destroy()).Times(0);

    ResourceGuard<MoveableMockResource> guard(std::move(resource));
    ResourceGuard<MoveableMockResource> guardAfterMove(std::move(resourceBeforeMove));
    guardAfterMove = std::move(guard);

    ASSERT_TRUE(NT_SUCCESS(guardAfterMove.init()));
    ASSERT_ANY_THROW(guard.get());
    ASSERT_NO_THROW(guardAfterMove.get());
}

TEST(ResourceTest, MoveAssignment_ToInitialized) {
    MoveableMockResource resource;
    MoveableMockResource resourceBeforeMove;
    EXPECT_CALL(resource.getMock(), initialize()).Times(1);
    EXPECT_CALL(resource.getMock(), destroy()).Times(1);
    EXPECT_CALL(resourceBeforeMove.getMock(), initialize()).Times(1);
    EXPECT_CALL(resourceBeforeMove.getMock(), destroy()).Times(1);

    ResourceGuard<MoveableMockResource> guard(std::move(resource));
    ResourceGuard<MoveableMockResource> guardAfterMove(std::move(resourceBeforeMove));
    guardAfterMove.init();
    guardAfterMove = std::move(guard);

    ASSERT_NO_THROW(guardAfterMove.init());
    ASSERT_ANY_THROW(guard.get());
    ASSERT_NO_THROW(guardAfterMove.get());
}

TEST(ResourceTest, GuardingWhenAlreadyInitialized) {
    MoveableMockResource resource;
    EXPECT_CALL(resource.getMock(), initialize()).Times(0);
    EXPECT_CALL(resource.getMock(), destroy()).Times(1);
    { ResourceGuard<MoveableMockResource> guard(std::move(resource), true); }
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
    { ResourceGuard<MoveableMockResource> guard(std::move(resource)); }
}

}
