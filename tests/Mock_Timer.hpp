#pragma once

#include "gmock/gmock.h"
#include "ITimer.hpp"

class Mock_Timer : public ITimer
{
public:
    // ITimer Interface
    MOCK_METHOD(bool, start, (), (override));
    MOCK_METHOD(bool, stop, (), (override));
    MOCK_METHOD(bool, isRunning, (), (override));
    MOCK_METHOD(bool, setCallbackFunc, (const timerCallbackFunc_t &cbFunc), (override));
    MOCK_METHOD(bool, setInterval, (timerInterval_t interval), (override));
    MOCK_METHOD(timerInterval_t, getInterval, (), (const, override));
};
