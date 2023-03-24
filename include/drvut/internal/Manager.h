#pragma once

#include <vector>

#include "drvut/Fixture.h"

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
