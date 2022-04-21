#pragma once

#include "Defs.h"

#include "Handle.h"
#include "Exceptions.h"

struct ServiceHandleTraits {
    MOVEABLE(ServiceHandleTraits);

    using HandleType = SC_HANDLE;
    using ExceptionType = WinAPIException<>;
    
    static constexpr HandleType INVALID_VALUE = nullptr;
    static bool close(HandleType handle);
};

using ServiceHandle = Handle<ServiceHandleTraits>;

template <typename T>
concept ServiceManagerAPI = requires(T, const std::wstring& name, const std::wstring& pePath) {
    { T::create(name, pePath) } -> std::same_as<typename T::HandleType>;
    { T::open(name) } -> std::same_as<typename T::HandleType>;
};

template <typename T>
concept ServiceControlAPI = requires(T, typename T::HandleType& handle) {
    { T::start(handle) } -> std::same_as<void>;
    { T::stop(handle) } -> std::same_as<void>;
    { T::remove(handle) } -> std::same_as<void>;
};

template <typename API>
concept ServiceAPI = ServiceManagerAPI<API> && ServiceControlAPI<API>;

struct WinServiceAPI {
    using HandleType = ServiceHandle;

    static void start(HandleType& handle);
    static void stop(HandleType& handle);
    static void remove(HandleType& handle);
    static HandleType create(const std::wstring& name, const std::wstring& pePath);
    static HandleType open(const std::wstring& name);
};

class SCManager final {
public:
    using HandleType = ServiceHandle;

    SCManager();
    NOCOPY(SCManager);
    MOVEABLE(SCManager);

    HandleType create(const std::wstring& name, const std::wstring& pePath);
    HandleType open(const std::wstring& name);

private:
    ServiceHandle m_handle;
};
