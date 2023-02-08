#pragma once

#include "Defs.h"

struct MockFixture final {
    MockFixture() {
        teardownCallCount = 0;
    }

    NTSTATUS setup() {
        return STATUS_SUCCESS;
    }
    
    void teardown() {
    }

    uint32_t setupCallCount = 0;
    // teardown occurres outside the context of the object so it must be static
    static uint32_t teardownCallCount;
};

uint32_t MockFixture::teardownCallCount = 0;
