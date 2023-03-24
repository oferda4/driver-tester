#include "Stream.h"

ConnectionTerminatedInTheMiddle::ConnectionTerminatedInTheMiddle()
    : std::exception("connection terminated in a middle of an operation") {
    // intentionally left blank
}
