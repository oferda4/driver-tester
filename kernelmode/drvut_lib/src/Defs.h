#pragma once

#ifdef AMD64
#include <ntifs.h>

void* __cdecl operator new(size_t size);
void* __cdecl operator new(size_t, void* p);
void __cdecl operator delete(void* p, size_t);

using uint32_t = unsigned int;

#else
#include <Windows.h>
#include <exception>

#define ExRaiseStatus(status) throw ::std::exception("exception raised",  status)
#endif

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

#if DBG
#define TRACE(_x_)            \
    DbgPrint("TestDriver: "); \
    DbgPrint(_x_);

#else
#define TRACE(_x_)
#endif
