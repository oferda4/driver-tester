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

void FixturesManager::initialize() {
    sm_manager = new FixturesManager;
}

}
}