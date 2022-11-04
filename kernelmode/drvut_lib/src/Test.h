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

struct TestData {
    TestInfo info{};
    std::unique_ptr<Test> test;
};

class TestsManager final {
public:
    static TestsManager& instance();
    static void destroy();

    Array<TestInfo> list() const;

private:
    TestsManager() = default;
    static void initialize();

    static TestsManager* sm_manager;

    List<TestData> m_testsData;
};

}
}
