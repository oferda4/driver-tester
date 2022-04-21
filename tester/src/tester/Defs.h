#pragma once

#include <windows.h>
#include <string>

#include "Exceptions.h"

#define NOCOPY(className)                 \
    className(const className&) = delete; \
    className& operator=(const className&) = delete
#define MOVEABLE(className)                    \
    className(className&&) noexcept = default; \
    className& operator=(className&&) noexcept = default

template <typename Func>
void tryExecute(Func f) {
    try {
        f();
    } catch (const Exception& exc) {
        traceException(exc);
    }
}
