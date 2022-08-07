#pragma once

#include "List.h"
#include "Memory.h"

namespace drvut {
namespace internal {

class Fixture {
public:
    virtual ~Fixture() = default;

    virtual void setup() = 0;
    virtual void teardown() = 0;
};

class FixturesManager final {
public:
    static FixturesManager& getInstance();
    static void destroy();

private:
    FixturesManager() = default;
    static void initialize();

    static FixturesManager* sm_manager;

    List<std::unique_ptr<Fixture>> m_fixtures;
};

}
}

#include "Fixture.inl"
