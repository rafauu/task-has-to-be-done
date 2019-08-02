#include <gtest/gtest.h>
#include "MultipleActionsHandler.hpp"

using ::testing::Test;

namespace
{
template <auto N>
constexpr auto VALUE{N};
}

struct MultipleActionsHandlerTestSuite : Test
{
protected:
    MultipleActionsHandler<VALUE<1>,
                           VALUE<2>,
                           VALUE<3>> sut{};
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

TEST_F(MultipleActionsHandlerTestSuite, shallNotFinishHandlingWhenNotAllInitialValuesAndSomeAdditionalMarked)
{
    sut.markAsDone(VALUE<3>);
    sut.markAsDone(VALUE<1>);
    sut.markAsDone(VALUE<17>);
    sut.markAsDone(VALUE<18>);
    sut.markAsDone(VALUE<19>);
    ASSERT_FALSE(sut.isHandlingFinished());
}

TEST_F(MultipleActionsHandlerTestSuite, shallFinishHandlingWhenAdditionalValuesMarkedBetweenInitial)
{
    sut.markAsDone(VALUE<60>);
    sut.markAsDone(VALUE<3>);
    sut.markAsDone(VALUE<70>);
    sut.markAsDone(VALUE<2>);
    sut.markAsDone(VALUE<80>);
    sut.markAsDone(VALUE<1>);
    ASSERT_TRUE(sut.isHandlingFinished());
}

TEST_F(MultipleActionsHandlerTestSuite, shallNotFinishHandlingWhenNoIdsMarked)
{
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
