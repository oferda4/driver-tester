#pragma once

#include "Defs.h"

#include "Service.h"
#include "Handle.h"

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
