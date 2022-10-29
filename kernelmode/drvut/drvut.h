#pragma once

#include "Defs.h"

#if DBG
#define TRACE(_x_)            \
    DbgPrint("TestDriver: "); \
    DbgPrint(_x_);

#else
#define TRACE(_x_)
#endif

EXTERN_C NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath);
