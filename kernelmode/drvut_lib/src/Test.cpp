#include "Test.h"

#include "Defs.h"

namespace drvut{
namespace internal {

static constexpr auto POOL_TAG = 'tset';

TestsManager* TestsManager::sm_manager = nullptr;

TestsManager& TestsManager::instance() {
    if (!sm_manager) {
        initialize();
    }
    return *sm_manager;
}

void TestsManager::destroy() {
    delete sm_manager;
}

Array<TestInfo> TestsManager::list() const {
    Array<TestInfo> info(m_testsData.size());
    size_t index = 0;
    const auto* node = m_testsData.head();
    for (; node; node = node->next, index++) {
        info.at(index) = node->value.info;
    }
    return info;
}

void TestsManager::initialize() {
    sm_manager = new TestsManager;
}

}
}