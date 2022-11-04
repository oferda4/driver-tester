#pragma once

#include "List.h"
#include "Memory.h"
#include "Test.h"
#include "Messages.h"
#include "Array.h"

namespace drvut {
namespace internal {

class Fixture {
public:
    virtual ~Fixture() = default;

    virtual void setup() {}
    virtual void teardown() {}

protected:
    virtual PVOID* getContext();
};

struct FixtureData {
    FixtureInfo info{};
    std::unique_ptr<Fixture> fixture;
    List<TestData> tests;
};

class FixturesManager final {
public:
    static FixturesManager& instance();
    static void destroy();

    Array<TestInfo> listTests(uint32_t fixtureId);

private:
    FixturesManager() = default;
    static void initialize();

    static FixturesManager* sm_manager;

    List<std::unique_ptr<FixtureData>> m_fixturesData;
};

}
}

#include "Fixture.inl"
