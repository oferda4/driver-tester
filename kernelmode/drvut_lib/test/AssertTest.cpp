#include "drvut/Assert.h"

#include <gtest/gtest.h>

#include "drvut/Test.h"
#include "drvut/internal/Error.h"

namespace drvut {

TEST(TestAssert, Sanity) {
    internal::ErrorMessageGuard guard;
    internal::TestsManager::destroy();
    auto& manager = internal::TestsManager::instance();

    // making sure using the proper assertion
    #undef assert
    test("AboutToFailFromAssertion") = []() { 
        assert(false); 
    };

    auto tests = manager.list();
    const auto result = manager.run(tests.at(0).id);

    ASSERT_FALSE(result.passed);
    ASSERT_EQ(std::string(result.msg), "assert: unknown");
}

}
