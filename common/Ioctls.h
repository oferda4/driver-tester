#pragma once

#include "Defs.h"

#define IOCTL_Device_Function CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_READ_DATA)
