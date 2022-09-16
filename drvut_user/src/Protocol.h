#pragma once

#include "Defs.h"
#include "Buffer.h"
#include "Messages.h"

enum class RequestType : uint32_t {
    LIST_FIXTURES
};

struct Request {
    RequestType type;
    Buffer input;
};

template<typename T>
concept Protocol = requires(T& t, const Buffer& data, const ListFixturesOutput& listFixturesOutput) {
    { t.parse(data) } -> std::same_as<Request>;
    { t.parseListFixturesInput(data) } -> std::same_as<ListFixturesInput>;
    { t.parseListFixturesOutput(listFixturesOutput) } -> std::same_as<Buffer>;
};
