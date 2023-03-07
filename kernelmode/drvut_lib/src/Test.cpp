#include "Test.h"

#include "Defs.h"
#include "Error.h"

namespace drvut::internal {

static constexpr auto POOL_TAG = 'tset';

TestsManager* TestsManager::sm_manager = nullptr;

RegularTest::RegularTest() : RegularTest([]() {}) {
    // intentionally left blank
}

Ioctl::TestResult RegularTest::run() {
    Ioctl::TestResult result = { .passed = true, .msg = {} };
    char msg[sizeof(Ioctl::TestResult::msg)] = {};
    ErrorMessage::reset();

    __try {
        (*m_testFunc)();
    } __except (EXCEPTION_EXECUTE_HANDLER) {
        result.passed = false;
        auto& errorMsg = ErrorMessage::view();
        const auto actualSize = min(sizeof(Ioctl::TestResult::msg), errorMsg.size());
        memcpy(msg, 
               errorMsg.data(), 
               actualSize);
    }

    *(result.msg+0) = 10;
    *(result.msg+1) = 11;
    *(result.msg+2) = 12;

    memcpy(__builtin_addressof(result.msg), msg, sizeof(msg));

    return result;
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