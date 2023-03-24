#pragma once

#include "drvut/Defs.h"
#include "drvut/internal/Concepts.h"

namespace drvut {
namespace internal {

template <typename T>
concept Resource = requires(T& resource) {
                       { resource.initialize() } -> std::same_as<NTSTATUS>;
                       { resource.destroy() } -> std::same_as<NTSTATUS>;
                   };

template <Resource T>
class ResourceGuard final {
public:
    ResourceGuard(T resource, bool isValid = false);
    ~ResourceGuard();
    ResourceGuard(ResourceGuard&& other) noexcept;
    ResourceGuard<T>& operator=(ResourceGuard&& other);
    NOCOPY(ResourceGuard);

    /**
     * These function throws if we're in a bad state as we prefer a
     * deterministic failure then undefined behavior.
     */
    NTSTATUS init();
    T& get();
    const T& get() const;

    void leak();

private:
    void destroyIfValid();

    T m_resource;
    bool m_isValid;
};

}
}

#include "drvut/internal/Resource.inl"
