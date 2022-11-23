#include <gtest/gtest.h>

#include "IoctlHandler.h"

namespace drvut::internal {

TEST(IoctlHandlerTest, InvalidCode) {
    const uint32_t arbitraryInvalidCode = -1;
    TestsManager::destroy();
    ASSERT_EQ(IoctlHandler::handle(TestsManager::instance(), 
                                   arbitraryInvalidCode, 
                                   BufferView(nullptr, 0), 
                                   BufferView(nullptr, 0)),
              STATUS_INVALID_PARAMETER_1);
}

}