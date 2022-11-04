#include "Fixture.h"

#include "Defs.h"

namespace drvut{
namespace internal {

static constexpr auto POOL_TAG = 'txif';

FixturesManager* FixturesManager::sm_manager = nullptr;

FixturesManager& FixturesManager::instance() {
    if (!sm_manager) {
        initialize();
    }
    return *sm_manager;
}

void FixturesManager::destroy() {
    delete sm_manager;
}

Array<TestInfo> FixturesManager::listTests(uint32_t fixtureId) {
    const auto& fixture = *ListUtils::find(m_fixturesData, 
                                           fixtureId, 
                                           [](const std::unique_ptr<FixtureData>& f, uint32_t id) { return f->info.id == id; });
    if (fixture == nullptr) {
        return { 0 };
    }

    Array<TestInfo> info(fixture->tests.size());
    size_t index = 0;
    const auto* node = fixture->tests.head();
    for (; node; node = node->next, index++) {
        info.at(index) = node->value.info;
    }
    return info;
}

void FixturesManager::initialize() {
    sm_manager = new FixturesManager;
}

}
}