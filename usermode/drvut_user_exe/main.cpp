#include "Defs.h"

#include <iostream>

#include "WsaGuard.h"
#include "WsaTcpSocket.h"
#include "WinFile.h"
#include "WinIoctlApi.h"

#include "RequestsHandler.h"
#include "RequestsRouter.h"
#include "ProtobufParser.h"
#include "Communication.h"

namespace {
struct BadArgument  : std::exception {
    // left blank intentionally
};

void trace(const std::string& msg);
void traceUsages();
uint16_t getPortFromArg(const char* portArg);

const std::wstring DEVICE_NAME = L"\\\\.\\TestDriver";
}

int main(int argc, char* argv[]) {
    WsaGuard wsaGuard;

    if (argc != 3) {
        traceUsages();
        return 1;
    }

    WsaTcpSocketServer server(argv[1], getPortFromArg(argv[2]));
    WinFileCreationApi creationApi;
    RequestsHandlerImpl<WinFileApi, WinIoctlApi> handler(DEVICE_NAME, creationApi);
    RequestsRouterImpl router(std::move(handler), ProtobufParser());
    
    Communication communication(CommunicationSetupImpl<WsaTcpSocketServer>(std::move(server)), 
                                CommunicationLogicImpl<StreamImpl<WsaTcpConnection>, decltype(router)>(std::move(router)));
    communication.run();
    
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
