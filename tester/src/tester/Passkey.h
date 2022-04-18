#pragma once

#include "Defs.h"

/**
 * A simple implementation of the passkey idiom.
 */
template <class T>
class Passkey {
private:
    Passkey() = default;
    MOVEABLE(Passkey);

    friend T;
};
