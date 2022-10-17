#include "Defs.h"

#include <iostream>

#include "WsaGuard.h"
#include "WsaTcpSocket.h"

namespace {
struct BadArgument  : std::exception {
    // left blank intentionally
};

void trace(const std::string& msg);
void traceUsages();
uint16_t getPortFromArg(const char* portArg);
}

int main(int argc, char* argv[]) {
    WsaGuard wsaGuard;

    if (argc != 3) {
        traceUsages();
    }

    WsaTcpSocketServer server(argv[1], getPortFromArg(argv[2]));

    return 0;
}

namespace {
void trace(const std::string& msg) {
    std::cout << msg << std::endl;
}

void traceUsages() {
    trace("usages: drvut_user.exe <ip> <port>");
}

uint16_t getPortFromArg(const char* portArg) {
    const int argAsInt = atoi(portArg);
    if (argAsInt == 0 || argAsInt == INT_MAX || argAsInt == INT_MIN) {
        trace("bad port argument given");
        throw BadArgument();
    }
    return CastUtils::cast<uint16_t>(argAsInt);
}
}
