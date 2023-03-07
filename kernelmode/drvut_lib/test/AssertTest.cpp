#include <gtest/gtest.h>

#include "Test.h"
#include "Assert.h"
#include "Error.h"

namespace drvut {

TEST(TestAssert, Sanity) {
    internal::ErrorMessageGuard guard;
    internal::TestsManager::destroy();
    auto& manager = internal::TestsManager::instance();

    test("AboutToFailFromAssertion") = []() { 
        assert(false); 
    };

    auto tests = manager.list();
    const auto result = manager.run(tests.at(0).id);

    ASSERT_FALSE(result.passed);
    ASSERT_EQ(std::string(), "assert: unknown");
}

}
