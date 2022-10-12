#include "Defs.h"

#include <iostream>

namespace {
void trace(const std::string& msg);
void traceUsages();
}

int main(int argc, char* argv[]) {
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
