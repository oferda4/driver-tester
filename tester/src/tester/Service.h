#pragma once

#include "Defs.h"

#include "Handle.h"
#include "Exceptions.h"
#include "Passkey.h"

struct ServiceHandleTraits {
    MOVEABLE(ServiceHandleTraits);

    using HandleType = SC_HANDLE;
    using ExceptionType = WinAPIException<>;
    
    static constexpr HandleType INVALID_VALUE = nullptr;
    static bool close(HandleType handle);
};

using ServiceHandle = Handle<ServiceHandleTraits>;

template <typename T>
concept ServiceAPI = requires(T, typename T::HandleType& handle) {
    { T::start(handle) } -> std::same_as<void>;
    { T::stop(handle) } -> std::same_as<void>;
    { T::remove(handle) } -> std::same_as<void>;
};

struct WinServiceAPI {
    using HandleType = ServiceHandle;

    void start(HandleType& handle);
    void stop(HandleType& handle);
    void remove(HandleType& handle);
};

template <typename T>
concept ServiceManager = requires(T, const std::wstring& name, const std::wstring& pePath) {
    { T::HandleType };
    { T::create(name, pePath) } -> std::same_as<typename T::HandleType>;
    { T::open(name) } -> std::same_as<typename T::HandleType>;
};

class SCManager final {
public:
    using HandleType = ServiceHandle;

    static HandleType create(const std::wstring& name, const std::wstring& pePath);
    static HandleType open(const std::wstring& name);

private:
    SCManager();
    NOCOPY(SCManager);
    MOVEABLE(SCManager);

    HandleType createInternal(const std::wstring& name, const std::wstring& pePath);
    HandleType openInternal(const std::wstring& name);

    ServiceHandle m_handle;
};
