#pragma once

#include <memory>
#include "IAdptWaterValveBistable.hpp"
#include "IValve.hpp"
#include "ITimer.hpp"

class AdptWaterValveBistable : public IValve
{
private:
    std::shared_ptr<IAdptWaterValveBistable> m_WaterValve;
    bool m_IsOpen;
    std::unique_ptr<ITimer> m_Timer;

public:
    AdptWaterValveBistable(std::shared_ptr<IAdptWaterValveBistable> waterValve, std::unique_ptr<ITimer> timer);
    virtual ~AdptWaterValveBistable();

    // IValve interface
    void init();
    void open();;
    void close();;
    bool isOpen() const;

private:
    void resetValve();
};
