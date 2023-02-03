#pragma once

#include <vector>

#include "Fixture.h"

namespace drvtest {
namespace ut {

class Manager {
public:
    void add(Fixture fixture);
    void list();

private:
    std::vector<Fixture> m_fixtures;
};

}
}
