#pragma once

namespace drvut {
namespace internal {

class FixturesManager final {
public:
    static FixturesManager& getInstance();
    static void destroy();

private:
    FixturesManager() = default;
    static void initialize();

    static FixturesManager* sm_manager;
};

}
}

#include "Fixture.inl"
