#pragma once

#include "Exceptions.h"
#include "Tracer.h"

class Safety {
public:
    template <typename Func, ExceptionTracer Tracer>
    static void tryExecute(Func f);
};

#include "Safety.inl"
