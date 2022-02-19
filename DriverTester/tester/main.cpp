#include "Defs.h"

#include "SCManager.h"
#include "Service.h"

static void traceUsage();

int main(ULONG argc, PTCHAR argv[]) {
    if (argc < 2) {
        traceUsage();
        return -1;
    }

    traceInfo("Installing driver");
    SCManager manager;
    Service driverService = manager.createService(L"DriverTest", argv[1]);
    traceInfo("Starting driver");
    driverService.start();
    
    traceInfo("Cleaning up and exit");
    return 0;
}

void traceUsage() {
    traceInfo("Usage - tester.exe path_to_test_sys");
}
