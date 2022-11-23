#pragma once

#include "Messages.h"
#include "Array.h"
#include "Memory.h"
#include "List.h"

namespace drvut {
namespace internal {

class Test {
public:
    virtual ~Test() = default;
    virtual TestResult run() = 0;
};

template<typename TestFunc>
class RegularTest final : public Test {
public:
    // TODO: add trait to test the function is of the proper form
    RegularTest(TestFunc testFunc);
    TestResult run() override;

private:
    TestFunc m_testFunc;
};

struct TestData {
    TestInfo info{};
    std::unique_ptr<Test> test;
};

class TestsManager final {
public:
    static TestsManager& instance();
    static void destroy();

    Array<TestInfo> list() const;
    TestResult run(uint32_t id);
    template <uint32_t nameSize>
    void add(std::unique_ptr<Test> test, char const (&name)[nameSize]);

private:
    TestsManager() = default;
    static void initialize();

    static TestsManager* sm_manager;

    List<TestData> m_testsData;
    uint32_t m_freeId = 0;
};

}
}

#include "Test.inl"
