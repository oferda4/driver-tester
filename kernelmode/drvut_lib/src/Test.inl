#pragma once

#include "Test.h"

namespace drvut::internal {

template<typename TestFunc>
RegularTest<TestFunc>::RegularTest(TestFunc testFunc) : m_testFunc(std::move(testFunc)) {
    // intentionally left blank
}

template <typename TestFunc>
TestResult RegularTest<TestFunc>::run() {
    return { m_testFunc() };
}

}