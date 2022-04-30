#pragma once

#include "Safety.h"

template <typename Func, ExceptionTracer Tracer>
void Safety::tryExecute(Func f) {
    try {
        f();
    } catch (const Exception& exc) {
        Tracer::exception(exc);
    }
}
