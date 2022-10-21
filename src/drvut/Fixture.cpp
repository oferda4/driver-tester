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

Array<FixtureInfo> FixturesManager::listFixtures() {
    Array<FixtureInfo> info(m_fixturesData.size());
    size_t index = 0;
    auto* node = m_fixturesData.head();
    for (; node; node = node->next, index++) {
        info.at(index) = node->value->info;
    }
    return info;
}

Array<TestInfo> FixturesManager::listTests(uint32_t fixtureId) {
    auto findIdFunc = [](const std::unique_ptr<FixtureData>& f, uint32_t id) { return f->info.id == id; };
    static_assert(Comparator<std::unique_ptr<FixtureData>, uint32_t, decltype(findIdFunc)>);
    
    const FixtureData* fixture = m_fixturesData.find<uint32_t, decltype(findIdFunc)>(fixtureId, findIdFunc);

    Array<TestInfo> info(m_fixturesData.size());
    size_t index = 0;
    auto* node = m_fixturesData.head();
    for (; node; node = node->next, index++) {
        if (node->value->info.id == fixtureId) {

        }
        info.at(index) = node->value->info;
    }
    return info;
}

void FixturesManager::initialize() {
    sm_manager = new FixturesManager;
}

}
}