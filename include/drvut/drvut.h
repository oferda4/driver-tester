#pragma once

#include "drvut/Defs.h"

#include "drvut/Test.h"
#include "drvut/Assert.h"
#include "drvut/Printable.h"

EXTERN_C NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath);

EXTERN_C void initializeTests();
