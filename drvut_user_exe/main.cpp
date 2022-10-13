#include "Defs.h"

#include <iostream>

#include "WsaGuard.h"

namespace {
void trace(const std::string& msg);
void traceUsages();
}

int main(int argc, char* argv[]) {
    WsaGuard wsaGuard;

    if (argc != 3) {
        traceUsages();
    }



    return 0;
}

namespace {
void trace(const std::string& msg) {
    std::cout << msg << std::endl;
}

void traceUsages() {
    trace("Usages: drvut_user.exe <ip> <port>");
}
}
