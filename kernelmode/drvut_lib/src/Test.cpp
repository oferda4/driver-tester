#include "Test.h"

#include "Defs.h"

namespace drvut::internal {

static constexpr auto POOL_TAG = 'tset';

TestsManager* TestsManager::sm_manager = nullptr;

RegularTest::RegularTest() : RegularTest([]() { return STATUS_SUCCESS; }) {
    // intentionally left blank
}

Ioctl::TestResult RegularTest::run() {
    return { (*m_testFunc)() };
}

TestsManager& TestsManager::instance() {
    if (!sm_manager) {
        initialize();
    }
    return *sm_manager;
}

void TestsManager::destroy() {
    delete sm_manager;
    sm_manager = nullptr;
}

uint64_t TestsManager::getNumberOfTests() const {
    return m_testsData.size();
}

Array<Ioctl::TestInfo> TestsManager::list() const {
    Array<Ioctl::TestInfo> info(m_testsData.size());
    size_t index = 0;
    const auto* node = m_testsData.head();
    for (; node; node = node->next, index++) {
        info.at(index) = node->value.info;
    }
    return info;
}

Ioctl::TestResult TestsManager::run(uint32_t id) {
    TestData* test = ListUtils::find(
        m_testsData, id, [](const TestData& data, uint32_t id) { return data.info.id == id; });
    if (!test) {
        ExRaiseStatus(STATUS_INVALID_PARAMETER);
    }
    return test->test->run();
}

void TestsManager::initialize() {
    sm_manager = new TestsManager;
}

}