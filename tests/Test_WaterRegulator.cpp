#include "gtest/gtest.h"

#include "IMoistureSensor.hpp"
#include "IValve.hpp"
#include "WaterRegulator.hpp"

class IMoistureSensorMock : public IMoistureSensor
{
    MOCK_CONST_METHOD1((std::optional<float>), getValue, (std::optional<float>));
}

class IValveMock : public IValve
{
    public:
    MOCK_METHOD( bool, init, bool(const bool));
    MOCK_METHOD( void, open, ()) ;
    MOCK_METHOD( void, close, ());
    MOCK_CONST_METHOD1( isOpen, (bool(const bool)));
}

TEST(MyTestSuite, TaskTimer_Creation)
{

}

TEST(MyTestSuite, TaskTimer_StartStop)
{

}

TEST(MyTestSuite, TaskTimer_ChangeInterval)
{

}

TEST(MyTestSuite, TaskTimer_ChangeCbFunc)
{

}