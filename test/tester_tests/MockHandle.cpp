#include "tester/Defs.h"
#include "MockHandle.h"

using std::wstring;
using std::optional;
using testing::NiceMock;

std::optional<NiceMock<MockHandleTraits>> MockHandleTraits::currMock{};

bool MockHandleTraits::close(HandleType handle) {
    return currMock->mockClose(handle);
}
