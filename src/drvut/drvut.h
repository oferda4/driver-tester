#pragma once

#include "Defs.h"

#if DBG
#define TRACE(_x_)            \
    DbgPrint("TestDriver: "); \
    DbgPrint(_x_);

#else
#define TRACE(_x_)
#endif
