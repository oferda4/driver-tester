#include "Defs.h"

#include "SCManager.h"
#include "Service.h"

using std::exception;
using std::wstring;

static constexpr auto DRIVER_SERVICE_NAME = L"DriverTest";

static void traceUsage();
static void cleanup(const wstring& pePath);
static void run(const wstring& pePath);

int wmain(int argc, wchar_t *argv[]) {
    if (argc < 2) {
        traceUsage();
        return -1;
    }

    if (argc > 2) {
        if (argc != 3 || wcscmp(argv[2], L"--cleanup") != 0) {
            traceUsage();
            return -1;
        }
        tryExecute([&]() { cleanup(argv[1]); });
    } else {
        tryExecute([&]() { run(argv[1]); });
    }

    traceInfo("Finish");
    return 0;
}

void traceUsage() {
    traceInfo("Usage - tester.exe path_to_test_sys [--cleanup]");
}

void cleanup(const wstring& pePath) {
    traceInfo("Cleaning up driver");
    // Simply open the service and let it's dtor make all the cleanups
    SCManager().openService(DRIVER_SERVICE_NAME);
}

void run(const wstring& pePath) {
    traceInfo("Installing driver");
    SCManager manager;
    Service driverService = manager.createService(DRIVER_SERVICE_NAME, pePath);
    traceInfo("Starting driver");
    driverService.start();
}
