#include <gtest/gtest.h>
#include "MultipleActionsHandler.hpp"

using ::testing::Test;

namespace
{
using HandlerIdType = unsigned;
using MultipleActionsHandlerT = MultipleActionsHandler<HandlerIdType>;

constexpr HandlerIdType FIRST{1u};
constexpr HandlerIdType SECOND{123u};
constexpr HandlerIdType THIRD{7u};
}

struct MultipleActionsHandlerTestSuite : Test
{
    MultipleActionsHandlerT sut{FIRST, SECOND, THIRD};
};

TEST_F(MultipleActionsHandlerTestSuite, test)
{
    sut.markAsDone(FIRST);
    sut.markAsDone(SECOND);
    ASSERT_FALSE(sut.isHandlingFinished());
    sut.markAsDone(THIRD);
    ASSERT_TRUE(sut.isHandlingFinished());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
