#include "tester/Defs.h"

#include "tester/SCManager.h"
#include "tester/Service.h"

using std::exception;
using std::wstring;

static constexpr auto DRIVER_SERVICE_NAME = L"DriverTest";

static void traceUsage();
static void cleanup(const wstring& pePath);
static void run(const wstring& pePath);
static wstring getAbsolutePath(const wstring& name);

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

    traceInfo(L"Finish");
    return 0;
}

void traceUsage() {
    traceInfo(L"Usage - tester.exe path_to_test_sys [--cleanup]");
}

void cleanup(const wstring& pePath) {
    traceInfo(L"Cleaning up driver");
    SCManager manager;
    Service driverService = manager.openService(DRIVER_SERVICE_NAME);
    traceInfo(L"Stopping driver");
    tryExecute([&]() { driverService.stop(); });
    traceInfo(L"Deleting driver");
    driverService.remove();
}

void run(const wstring& pePath) {
    traceInfo(L"Installing driver");
    const wstring fullPEPath = getAbsolutePath(pePath);
    SCManager manager;
    Service driverService = manager.createService(DRIVER_SERVICE_NAME, fullPEPath);
    traceInfo(L"Starting driver");
    driverService.start();
    traceInfo(L"Stopping driver");
    driverService.stop();
    traceInfo(L"Deleting driver");
    driverService.remove();
}

wstring getAbsolutePath(const wstring& name) {
    wchar_t fullFilePath[MAX_PATH];
    if (GetFullPathName(name.c_str(), MAX_PATH, fullFilePath, nullptr) == 0) {
        throw WinAPIException(L"Failed getting file full path");
    }
    return fullFilePath;
}
