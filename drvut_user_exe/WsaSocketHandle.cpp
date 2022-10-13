#include "WsaSocketHandle.h"

void WsaSocketHandleTraits::close(SOCKET socket) {
    (void)closesocket(socket);
}
