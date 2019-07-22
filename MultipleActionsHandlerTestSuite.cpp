#include <gtest/gtest.h>
#include "MultipleActionsHandler.hpp"

using ::testing::Test;

namespace
{
using HandlerIdType = unsigned;
using MultipleActionsHandlerT = MultipleActionsHandler<HandlerIdType>;

template <HandlerIdType N>
constexpr HandlerIdType VALUE{N};
}

struct MultipleActionsHandlerTestSuite : Test
{
    MultipleActionsHandlerT sut{VALUE<1>, VALUE<2>, VALUE<3>};
};

TEST_F(MultipleActionsHandlerTestSuite, shallProperlyFinishHandlingAfterAllIdsMarked)
{
    sut.markAsDone(VALUE<2>);
    sut.markAsDone(VALUE<3>);
    sut.markAsDone(VALUE<1>);
    ASSERT_TRUE(sut.isHandlingFinished());
}

TEST_F(MultipleActionsHandlerTestSuite, shallNotFinishHandlingWhenNotAllNotificationsReceived)
{
    sut.markAsDone(VALUE<3>);
    sut.markAsDone(VALUE<1>);
    ASSERT_FALSE(sut.isHandlingFinished());
}

TEST_F(MultipleActionsHandlerTestSuite, shallFinishHandlingAfterAllIdsMarkedAtOnce)
{
    sut.markAllAsDone();
    ASSERT_TRUE(sut.isHandlingFinished());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
