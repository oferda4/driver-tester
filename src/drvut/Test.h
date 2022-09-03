#pragma once

#include "Messages.h"

namespace drvut {
namespace internal {

class Test {
public:
    virtual ~Test() = default;

    virtual TestResult run() = 0;
};

}
}
