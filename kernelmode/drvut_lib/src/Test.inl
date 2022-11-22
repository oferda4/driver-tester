#pragma once

#include "Test.h"

namespace drvut::internal {

template <uint32_t nameSize>
void TestsManager::add(std::unique_ptr<Test> test, char const (&name)[nameSize]) {
    static_assert(nameSize <= MAX_NAME_SIZE);
    TestInfo info{};
    info.id = m_freeId++;
    memcpy(info.name, name, nameSize);
    m_testsData.push_back({ std::move(info), std::move(test) });
}

template<typename TestFunc>
RegularTest<TestFunc>::RegularTest(TestFunc testFunc) : m_testFunc(std::move(testFunc)) {
    // intentionally left blank
}

template <typename TestFunc>
TestResult RegularTest<TestFunc>::run() {
    return { m_testFunc() };
}

}