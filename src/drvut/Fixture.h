#pragma once

#include <vector>
#include <string>

#include "Test.h"

namespace drvut {
namespace internal {

class FixturesManager {
public:
    static FixturesManager& getInstance();
    static void destroy();

private:
    static void initialize();

    static FixturesManager* sm_manager;
};

}
}

#include "Fixture.inl"
