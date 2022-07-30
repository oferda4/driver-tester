#pragma once

#include <ntddk.h>
#include <stdint.h>
#include "Utility.h"

#define NOCOPY(className)                 \
    className(const className&) = delete; \
    className& operator=(const className&) = delete
#define MOVEABLE(className)                    \
    className(className&&) noexcept = default; \
    className& operator=(className&&) noexcept = default
#define NOMOVE(className)                     \
    className(className&&) noexcept = delete; \
    className& operator=(className&&) noexcept = delete

#define CHECK_AND_RETHROW(status)   \
    if (!NT_SUCCESS(status)) {      \
        return status;              \
    }

void* __cdecl operator new(size_t size);
void* __cdecl operator new(size_t, void* p);
void __cdecl operator delete(void* p);