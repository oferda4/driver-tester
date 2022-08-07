#include "tester/Defs.h"

#include "tester/Tester.h"
#include "tester/Safety.h"

using std::exception;
using std::wstring;

static constexpr auto DRIVER_SERVICE_NAME = L"DriverTest";

static void traceUsage();
static void cleanup(const wstring& pePath);
static void run(const wstring& pePath);
static wstring getAbsolutePath(const wstring& name);

int wmain(int argc, wchar_t* argv[]) {
    if (argc < 2) {
        traceUsage();
        return -1;
    }

    if (argc > 2) {
        if (argc != 3 || wcscmp(argv[2], L"--cleanup") != 0) {
            traceUsage();
            return -1;
        }
        Safety::tryExecute<StdOutTracer>([&]() { cleanup(argv[1]); });
    } else {
        Safety::tryExecute<StdOutTracer>([&]() { run(argv[1]); });
    }

    return 0;
}

void traceUsage() {
    StdOutTracer::info(L"Usage - tester.exe path_to_test_sys [--cleanup]");
}

void cleanup(const wstring& pePath) {
    StdOutTracer::info(L"Cleaning up driver");
    SCManager manager;
    auto driverService = manager.open(DRIVER_SERVICE_NAME);
    StdOutTracer::info(L"Stopping driver");
    Safety::tryExecute<StdOutTracer>([&]() { driverService.stop(); });
    StdOutTracer::info(L"Deleting driver");
    driverService.remove();
}

void run(const wstring& pePath) {
    // WinTester tester(std::wstring(DRIVER_SERVICE_NAME), pePath);
}

wstring getAbsolutePath(const wstring& name) {
    wchar_t fullFilePath[MAX_PATH];
    if (GetFullPathName(name.c_str(), MAX_PATH, fullFilePath, nullptr) == 0) {
        throw WinAPIException(L"Failed getting file full path");
    }
    return fullFilePath;
}
