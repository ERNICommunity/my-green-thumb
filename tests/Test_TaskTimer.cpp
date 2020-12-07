#include "gtest/gtest.h"

#include "TaskTimer.hpp"
#include "Mock_Timer.hpp"

using ::testing::AtLeast;
using ::testing::Return;

std::string taskName("TaskTest");
uint32_t taskId = 9;
timerInterval_t taskInterval1 = 10;
timerInterval_t taskInterval2 = 100;
timerCallbackFunc_t taskCbFunction([](void) { ; });
auto mockTimer = std::unique_ptr<Mock_Timer>(new Mock_Timer());
auto rawMockTimer = mockTimer.get();

TaskTimer taskTimer(
    taskId,
    taskName,
    taskInterval1,
    std::move(mockTimer),
    [](void) { ; });

TEST(MyTestSuite, TaskTimer_Creation)
{
    // ASSERT_DEATH(
    //     {
    //         TaskTimer taskTimer1(1, "Test", taskInterval1, std::unique_ptr<Mock_Timer>());

    //         EXPECT_CALL(*rawMockTimer, start())
    //             .Times(AtLeast(1))
    //             .WillOnce(Return(true));
    //         taskTimer1.start();
    //     },
    //     "");
}

TEST(MyTestSuite, TaskTimer_StartStop)
{
    EXPECT_CALL(*rawMockTimer, isRunning())
        .Times(AtLeast(1))
        .WillOnce(Return(false));
    ASSERT_FALSE(taskTimer.isRunning());

    EXPECT_CALL(*rawMockTimer, start())
        .Times(AtLeast(1))
        .WillOnce(Return(true));
    ASSERT_TRUE(taskTimer.start());

    EXPECT_CALL(*rawMockTimer, isRunning())
        .Times(AtLeast(1))
        .WillOnce(Return(true));
    ASSERT_TRUE(taskTimer.isRunning());

    EXPECT_CALL(*rawMockTimer, stop())
        .Times(AtLeast(1))
        .WillOnce(Return(true));
    ASSERT_TRUE(taskTimer.stop());

    EXPECT_CALL(*rawMockTimer, isRunning())
        .Times(AtLeast(1))
        .WillOnce(Return(false));
    ASSERT_FALSE(taskTimer.isRunning());
}

TEST(MyTestSuite, TaskTimer_ChangeInterval)
{
    EXPECT_CALL(*rawMockTimer, getInterval())
        .Times(AtLeast(1))
        .WillOnce(Return(taskInterval1));
    auto taskInfo = taskTimer.getInfo();
    ASSERT_EQ(taskInfo.id, taskId);
    ASSERT_EQ(taskInfo.name, taskName);
    ASSERT_EQ(taskInfo.interval_ms, taskInterval1);
    // TODO: Test func

    EXPECT_CALL(*rawMockTimer, setInterval(taskInterval2))
        .Times(AtLeast(1))
        .WillOnce(Return(true));
    taskTimer.changeInterval(taskInterval2);

    EXPECT_CALL(*rawMockTimer, getInterval())
        .Times(AtLeast(1))
        .WillOnce(Return(taskInterval2));
    taskInfo = taskTimer.getInfo();
    ASSERT_EQ(taskInfo.interval_ms, taskInterval2);
}

TEST(MyTestSuite, TaskTimer_ChangeCbFunc)
{
    ASSERT_FALSE(taskTimer.setTaskFunction(nullptr));

    // TODO: Find a way to test if the callback function is set
    // EXPECT_CALL(*rawMockTimer, setCallbackFunc(taskCbFunction))
    //     .Times(AtLeast(1))
    //     .WillOnce(Return(true));
    ASSERT_TRUE(taskTimer.setTaskFunction(taskCbFunction));
}