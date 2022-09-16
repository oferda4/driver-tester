#pragma once

#include "Defs.h"
#include "Messages.h"

template<typename T>
concept RequestsHandler = requires(T& t, const ListFixturesInput& listFixturesInput) {
    { t.listFixtures(listFixturesInput) } -> std::same_as<ListFixturesOutput>;
};
