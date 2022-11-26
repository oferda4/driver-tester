#pragma once

#include "Test.h"

namespace drvut {
namespace internal {

template <uint32_t nameSize>
void TestsManager::add(std::unique_ptr<Test> test, char const (&name)[nameSize]) {
    static_assert(nameSize <= MAX_NAME_SIZE);
    TestInfo info{};
    info.id = m_freeId++;
    memcpy(info.name, name, nameSize);
    m_testsData.push_back({ std::move(info), std::move(test) });
}

template <typename T>
RegularTest::RegularTest(T func) : m_testFunc(new TestFuncImpl(func)) {
    // itnentionally left blank
}

template <typename T>
TestFuncImpl<T>::TestFuncImpl(T func) : m_func(std::move(func)) { 
    // left blank intentionally
}

template <typename T>
NTSTATUS TestFuncImpl<T>::operator()() { 
    return m_func(); 
}

}

template <uint32_t nameSize, typename T>
void test(char const (&name)[nameSize], T testFunc) {
    auto testObj = internal::std::unique_ptr<internal::RegularTest>(new internal::RegularTest(std::move(testFunc)));
    internal::TestsManager::instance().add(std::move(testObj), name);
}

}