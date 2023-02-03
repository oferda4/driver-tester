#pragma once

#include "Communication.h"

template <Server ServerType>
CommunicationSetupImpl<ServerType>::CommunicationSetupImpl(ServerType server)
    : m_server(std::move(server)) {
    // left blank intentionally
}

template <Server ServerType>
StreamImpl<typename ServerType::ConnectionType> CommunicationSetupImpl<ServerType>::run() {
    return StreamImpl<typename ServerType::ConnectionType>(m_server.waitForConnection());
}

template <Stream StreamType, RequestsRouter RouterType>
CommunicationLogicImpl<StreamType, RouterType>::CommunicationLogicImpl(RouterType router)
    : m_router(std::move(router)) {
    // left blank intentionally
}

template <Stream StreamType, RequestsRouter RouterType>
void CommunicationLogicImpl<StreamType, RouterType>::run(StreamType& stream) {
    Buffer data = stream.recv();
    while (!data.empty()) {
        Buffer response = m_router.route(data);
        stream.send(response);
        data = stream.recv();
    }
}

template <
    CommunicationSetup CommunicationSetupType,
    CommunicationLogic<CommunicationSetupStreamType<CommunicationSetupType>> CommunicationLogicType>
Communication<CommunicationSetupType, CommunicationLogicType>::Communication(
    CommunicationSetupType setup, CommunicationLogicType logic)
    : m_setup(std::move(setup)), m_logic(std::move(logic)) {
    // left blank intentionally
}

template <
    CommunicationSetup CommunicationSetupType,
    CommunicationLogic<CommunicationSetupStreamType<CommunicationSetupType>> CommunicationLogicType>
void Communication<CommunicationSetupType, CommunicationLogicType>::run() {
    auto stream = m_setup.run();
    m_logic.run(stream);
}
