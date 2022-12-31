#pragma once

#include "Defs.h"

EXTERN_C NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath);

EXTERN_C void initializeTests();
