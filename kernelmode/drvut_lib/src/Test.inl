#pragma once

#include "Test.h"
#include "TupleUtils.h"
#include "Error.h"

namespace drvut {
namespace internal {

namespace impl {
inline Ioctl::TestResult getErrorResult();
}

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
Ioctl::TestResult TestFuncImpl<T>::operator()() {
    Ioctl::TestResult result = { .passed = true, .msg = {} };

    if constexpr (Traits::ArgumentsTypes::size == 0) {
        __try {
            m_func();
        } __except (EXCEPTION_EXECUTE_HANDLER) {
            result = impl::getErrorResult();
        }
    } else {
        typename Traits::ArgumentsTypes::NonReferenceTuple args;
        // TODO: handle failure in setup
        TupleUtils::forEach(args, [](auto& fixture) { fixture.setup(); });
        __try {
            TupleUtils::apply(m_func, args);
        } __except (EXCEPTION_EXECUTE_HANDLER) {
            result = impl::getErrorResult();
        }
        TupleUtils::forEach(args, [](auto& fixture) { fixture.teardown(); });
    }

    return result;
}

Ioctl::TestResult impl::getErrorResult() {
     Ioctl::TestResult result = {};
     result.passed = false;
     auto& errorMsg = ErrorMessage::view();
     memcpy(result.msg, errorMsg.data(), min(sizeof(Ioctl::TestResult::msg), errorMsg.size()));
     return result;
}

}

template <uint32_t nameSize>
internal::RegularTest& test(char const (&name)[nameSize]) {
    auto testPtr = new internal::RegularTest();
    auto& testObjRef = *testPtr;
    internal::TestsManager::instance().add(internal::std::unique_ptr<internal::Test>(testPtr),
                                           name);
    return testObjRef;
}
}