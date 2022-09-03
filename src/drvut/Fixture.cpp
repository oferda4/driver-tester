#include "Fixture.h"

#include "Defs.h"

namespace drvut{
namespace internal {

static constexpr auto POOL_TAG = 'txif';

FixturesManager* FixturesManager::sm_manager = nullptr;

FixturesManager& FixturesManager::getInstance() {
    if (!sm_manager) {
        initialize();
    }
    return *sm_manager;
}

void FixturesManager::destroy() {
    delete sm_manager;
}

Array<FixtureInfo> FixturesManager::getFixturesInfo() {
    Array<FixtureInfo> info(m_fixturesData.size());
    size_t index = 0;
    auto* node = m_fixturesData.head();
    for (; node; node = node->next, index++) {
        memcpy(&info.at(index), &node->value, sizeof(FixtureInfo));
    }
    return info;
}

void FixturesManager::initialize() {
    sm_manager = new FixturesManager;
}

}
}