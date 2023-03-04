#pragma once

#include "Defs.h"

struct MockFixture final {
    NTSTATUS setup() {
        setupCallCount++;
        return STATUS_SUCCESS;
    }
    
    void teardown() {
        teardownCallCount++;
    }

    // setup and teardown occurres outside the context of the object so it must be static
    static uint32_t setupCallCount;
    static uint32_t teardownCallCount;
};

uint32_t MockFixture::setupCallCount = 0;
uint32_t MockFixture::teardownCallCount = 0;
