#pragma once

#include <gtest/gtest.h>

class HandleTest : public testing::Test {
public:
    virtual ~HandleTest() = default;

private:
    void SetUp() override;
    void TearDown() override;
};
