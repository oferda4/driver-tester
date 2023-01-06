#pragma once

#include "Test.h"

namespace drvut {
namespace internal {

template <uint32_t nameSize>
void TestsManager::add(std::unique_ptr<Test> test, char const (&name)[nameSize]) {
        static_assert(nameSize <= Ioctl::MAX_NAME_SIZE);
    Ioctl::TestInfo info{};
    info.id = m_freeId++;
    memcpy(info.name, name, nameSize);
    m_testsData.push_back({ std::move(info), std::move(test) });
}

template <typename T>
RegularTest::RegularTest(T func) : m_testFunc(new TestFuncImpl(std::move(func))) {
    // itnentionally left blank
}

template <typename T>
RegularTest& RegularTest::operator=(T func) {
    m_testFunc = std::unique_ptr<TestFunc>(new TestFuncImpl(std::move(func)));
    return *this;
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

template <uint32_t nameSize>
internal::RegularTest& test(char const (&name)[nameSize]) {
    auto testPtr = new internal::RegularTest();
    auto& testObjRef = *testPtr;
    internal::TestsManager::instance().add(internal::std::unique_ptr<internal::Test>(testPtr), name);
    return testObjRef;
}

}