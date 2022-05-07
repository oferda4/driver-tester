#pragma once

#include "Safety.h"

template <ExceptionTracer Tracer, typename Func>
void Safety::tryExecute(Func f) {
    try {
        f();
    } catch (const Exception& exc) {
        Tracer::exception(exc);
    }
}
