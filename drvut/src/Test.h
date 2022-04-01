#pragma once

#include <string>
#include <functional>

namespace drvtest {
    namespace ut {

        struct Test {
            std::string name{};
            std::function<void()> run;
        };

    }
}
