#pragma once

#ifdef AMD64
// clang-format off
#include <ntifs.h>
// clang-format on

void* __cdecl operator new(size_t size);
void* __cdecl operator new(size_t, void* p);
void __cdecl operator delete(void* p, size_t);

using uint8_t = unsigned char;
using uint32_t = unsigned int;
using uint64_t = unsigned long long;

#else
// clang-format off
#include <Windows.h>
// clang-format on

#include <exception>

// Windows kernel specific definitions
#define ExRaiseStatus(status) throw ::std::exception("exception raised", status)
#define NTSTATUS int32_t
#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)
#define STATUS_SUCCESS ((NTSTATUS)0x00000000L)
#define STATUS_INVALID_STATE_TRANSITION ((NTSTATUS)0xC000A003L)
#define STATUS_INVALID_PARAMETER_1 ((NTSTATUS)0xC00000EFL)
#define STATUS_INVALID_PARAMETER_2 ((NTSTATUS)0xC00000F0L)
#define STATUS_INVALID_PARAMETER_3 ((NTSTATUS)0xC00000F1L)
#define STATUS_INVALID_PARAMETER_4 ((NTSTATUS)0xC00000F2L)
#define STATUS_BUFFER_TOO_SMALL ((NTSTATUS)0xC0000023L)

// For gtest exception catching inside out namespace
namespace drvut::internal::std {
using exception = ::std::exception;
}

#undef assert

#endif

#include "drvut/internal/Utility.h"

#define NOCOPY(className)                                                                          \
    className(const className&) = delete;                                                          \
    className& operator=(const className&) = delete
#define MOVEABLE(className)                                                                        \
    className(className&&) noexcept = default;                                                     \
    className& operator=(className&&) noexcept = default
#define NOMOVE(className)                                                                          \
    className(className&&) noexcept = delete;                                                      \
    className& operator=(className&&) noexcept = delete

#define CHECK_AND_RETHROW(status)                                                                  \
    if (!NT_SUCCESS(status)) {                                                                     \
        return status;                                                                             \
    }

#if DBG
#define TRACE(_x_)                                                                                 \
    DbgPrint("TestDriver: ");                                                                      \
    DbgPrint(_x_);

#else
#define TRACE(_x_)
#endif
