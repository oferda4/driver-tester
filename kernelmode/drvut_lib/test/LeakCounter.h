#pragma once

#include "Defs.h"

namespace drvut::internal {

struct LeakCounter {
    LeakCounter();
    ~LeakCounter();
    NOCOPY(LeakCounter);
    LeakCounter(LeakCounter&& other) noexcept;
    LeakCounter& operator=(LeakCounter&& other) = delete;

    static uint32_t leaked;
};

}