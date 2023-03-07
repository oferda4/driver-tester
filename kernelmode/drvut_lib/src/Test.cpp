#include "Test.h"

#include "Defs.h"
#include "Error.h"

namespace drvut::internal {

namespace {
Ioctl::TestResult getErrorResult();
}

TestsManager* TestsManager::sm_manager = nullptr;

RegularTest::RegularTest() : RegularTest([]() {}) {
    // intentionally left blank
}

Ioctl::TestResult RegularTest::run() {
    ErrorMessage::reset();
    __try {
        (*m_testFunc)();
    } __except (EXCEPTION_EXECUTE_HANDLER) {
        return getErrorResult();
    }

    return { .passed = true, .msg = {} };
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

namespace {
Ioctl::TestResult getErrorResult() {
    Ioctl::TestResult result = {};
    result.passed = false;
    auto& errorMsg = ErrorMessage::view();
    memcpy(result.msg, errorMsg.data(), min(sizeof(Ioctl::TestResult::msg), errorMsg.size()));
    return result;
}
}

}