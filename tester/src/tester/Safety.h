#pragma once

#include "Exceptions.h"
#include "Tracer.h"

class Safety {
public:
    template <ExceptionTracer Tracer, typename Func>
    static void tryExecute(Func f);
};

#include "Safety.inl"
