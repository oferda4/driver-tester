#include "LeakCounter.h"

namespace drvut::internal {

uint32_t LeakCounter::leaked = 0;

LeakCounter::LeakCounter() { 
    leaked++; 
}

LeakCounter::~LeakCounter() { 
    leaked--; 
}

LeakCounter::LeakCounter(LeakCounter&& other) noexcept { 
    leaked++; 
}

}