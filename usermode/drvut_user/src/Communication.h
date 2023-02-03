#pragma once

#include "Stream.h"
#include "Connection.h"
#include "Server.h"
#include "RequestsRouter.h"

template <typename T>
concept CommunicationSetup = requires(T& setup) {
                                 { setup.run() } -> Stream;
                             };

template <Server ServerType>
class CommunicationSetupImpl final {
public:
    explicit CommunicationSetupImpl(ServerType server);

    StreamImpl<typename ServerType::ConnectionType> run();

private:
    ServerType m_server;
};

template <typename T, typename StreamType>
concept CommunicationLogic = requires(T& logic, StreamType& stream) {
                                 Stream<StreamType>;
                                 { logic.run(stream) } -> std::same_as<void>;
                             };

template <Stream StreamType, RequestsRouter RouterType>
class CommunicationLogicImpl final {
public:
    explicit CommunicationLogicImpl(RouterType router);

    void run(StreamType& stream);

private:
    RouterType m_router;
};

template <CommunicationSetup CommunicationSetupType>
using CommunicationSetupStreamType = decltype(std::declval<CommunicationSetupType>().run());

template <
    CommunicationSetup CommunicationSetupType,
    CommunicationLogic<CommunicationSetupStreamType<CommunicationSetupType>> CommunicationLogicType>
class Communication final {
public:
    Communication(CommunicationSetupType setup, CommunicationLogicType logic);

    void run();

private:
    CommunicationSetupType m_setup;
    CommunicationLogicType m_logic;
};

#include "Communication.inl"
