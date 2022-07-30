#include "Defs.h"

static constexpr ULONG TEST_DRIVER_POOL_TAG = 'tset';

void* operator new(size_t size) {
    return ExAllocatePoolWithTag(PagedPool, size, TEST_DRIVER_POOL_TAG);
}

void* operator new(size_t, void* p) {
    return p;
}

void operator delete(void* p) {
    ExFreePoolWithTag(p, TEST_DRIVER_POOL_TAG);
}
