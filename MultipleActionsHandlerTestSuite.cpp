#include <gtest/gtest.h>
#include "MultipleActionsHandler.hpp"

using ::testing::Test;

struct MultipleActionsHandlerTestSuite : Test
{
    /* MultipleActionsHandlerTestSuite() */
    /* { */
        
    /* } */
    /* MultipleActionsHandler<unsigned, unsigned, unsigned> sut{MultipleActionsHandler{1u, 123u, 7u}}; */
    MultipleActionsHandler sut{1u, 123u, 7u};
};

TEST_F(MultipleActionsHandlerTestSuite, test)
{
    sut.markAsDone(1u);
    sut.markAsDone(123u);
    ASSERT_FALSE(sut.isHandlingFinished());
    sut.markAsDone(7u);
    ASSERT_TRUE(sut.isHandlingFinished());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
