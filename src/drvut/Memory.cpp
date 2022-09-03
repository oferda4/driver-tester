#include "Defs.h"

static constexpr ULONG TEST_DRIVER_POOL_TAG = 'tset';

void* __cdecl operator new(size_t size) {
    void* result = ExAllocatePool2(PagedPool, size, TEST_DRIVER_POOL_TAG);
    if (!result) {
        ExRaiseStatus(STATUS_BAD_DATA);
    }
    return result;
}

void* __cdecl operator new(size_t, void* p) {
    return p;
}

void __cdecl operator delete(void* p, size_t) {
    ExFreePoolWithTag(p, TEST_DRIVER_POOL_TAG);
}
