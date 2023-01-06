#pragma once

#include "Array.h"
#include "Memory.h"
#include "List.h"
#include "Ioctl.h"

namespace drvut {
namespace internal {

class TestFunc {
public:
    virtual ~TestFunc() = default;
    virtual NTSTATUS operator()() = 0;
};

template <typename T>
class TestFuncImpl final : public TestFunc {
public:
    // TODO: add trait to test the function is of the proper form
    TestFuncImpl(T func);
    NTSTATUS operator()() override;

private:
    T m_func;
};

class Test {
public:
    virtual ~Test() = default;
    virtual Ioctl::TestResult run() = 0;
};

class RegularTest final : public Test {
public:
    template<typename T>
    RegularTest(T func);
    RegularTest();
    template <typename T>
    RegularTest& operator=(T func);

    Ioctl::TestResult run() override;

private:
    std::unique_ptr<TestFunc> m_testFunc;
};

struct TestData {
    Ioctl::TestInfo info{};
    std::unique_ptr<Test> test;
};

class TestsManager final {
public:
    static TestsManager& instance();
    static void destroy();

    uint64_t getNumberOfTests() const;
    Array<Ioctl::TestInfo> list() const;
    Ioctl::TestResult run(uint32_t id);
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

template <uint32_t nameSize>
internal::RegularTest& test(char const (&name)[nameSize]);

}

#include "Test.inl"
