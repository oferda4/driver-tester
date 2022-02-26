#include "drvut.h"

#include <string.h>

static constexpr auto NT_DEVICE_NAME = L"\\Device\\TestDriver";
static constexpr auto DOS_DEVICE_NAME = L"\\DosDevices\\TestDriver";

static void unloadDriver(PDRIVER_OBJECT DriverObject);

NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {
	NTSTATUS        status;
	UNICODE_STRING  ntUnicodeString;
	UNICODE_STRING  ntWin32NameString;
	PDEVICE_OBJECT  deviceObject = NULL;

	UNREFERENCED_PARAMETER(RegistryPath);

	__debugbreak();
	TRACE("Driver Entry\n");

	RtlInitUnicodeString(&ntUnicodeString, NT_DEVICE_NAME);

	status = IoCreateDevice(DriverObject, 0, &ntUnicodeString, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &deviceObject);

	if (!NT_SUCCESS(status))
	{
		TRACE("Couldn't create the device object\n");
		return status;
	}

	DriverObject->DriverUnload = unloadDriver;

	RtlInitUnicodeString(&ntWin32NameString, DOS_DEVICE_NAME);

	status = IoCreateSymbolicLink(&ntWin32NameString, &ntUnicodeString);

	if (!NT_SUCCESS(status)) {
		TRACE("Couldn't create symbolic link\n");
		IoDeleteDevice(deviceObject);
	}

	return status;
}

void unloadDriver(PDRIVER_OBJECT DriverObject) {
	PDEVICE_OBJECT deviceObject = DriverObject->DeviceObject;
	UNICODE_STRING uniWin32NameString;

	PAGED_CODE();

	TRACE("Unload Driver\n");

	RtlInitUnicodeString(&uniWin32NameString, DOS_DEVICE_NAME);
	IoDeleteSymbolicLink(&uniWin32NameString);

	if (deviceObject) {
		IoDeleteDevice(deviceObject);
	}
}