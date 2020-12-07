#include "MoistureSensorDFRobot.hpp"

const bool MoistureSensorDFRobot::init()
{
    if (!gpioInit())
    {
        return false;
    }

    if (!adcInit())
    {
        return false;
    }

    // Calibrate The ADC On Power-Up For Better Accuracy
    if (HAL_ADCEx_Calibration_Start(&m_AdcHandle, ADC_SINGLE_ENDED) != HAL_OK)
    {
        return false;
    }

    return true;
}

const std::optional<uint32_t> MoistureSensorDFRobot::readValue()
{
    std::optional<uint32_t> adcValue = {};
    // Start ADC Conversion
    HAL_ADC_Start(&m_AdcHandle);
    // Poll ADC1 Perihperal & TimeOut
    if (HAL_ADC_PollForConversion(&m_AdcHandle, 100) == HAL_OK)
    {
        adcValue = HAL_ADC_GetValue(&m_AdcHandle);
    }
    // Stop ADC Conversion
    HAL_ADC_Stop(&m_AdcHandle);

    return adcValue;
}

bool MoistureSensorDFRobot::gpioInit()
{
    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOC_CLK_ENABLE();

    return true;
}

bool MoistureSensorDFRobot::adcInit()
{
    ADC_MultiModeTypeDef multimode = {0};
    ADC_ChannelConfTypeDef sConfig = {0};

    /** Common config
  */
    m_AdcHandle.Instance = ADC1;
    m_AdcHandle.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
    m_AdcHandle.Init.Resolution = ADC_RESOLUTION_12B;
    m_AdcHandle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    m_AdcHandle.Init.ScanConvMode = ADC_SCAN_DISABLE;
    m_AdcHandle.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    m_AdcHandle.Init.LowPowerAutoWait = DISABLE;
    m_AdcHandle.Init.ContinuousConvMode = DISABLE;
    m_AdcHandle.Init.NbrOfConversion = 1;
    m_AdcHandle.Init.DiscontinuousConvMode = DISABLE;
    m_AdcHandle.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    m_AdcHandle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    m_AdcHandle.Init.DMAContinuousRequests = DISABLE;
    m_AdcHandle.Init.Overrun = ADC_OVR_DATA_PRESERVED;
    m_AdcHandle.Init.OversamplingMode = DISABLE;
    if (HAL_ADC_Init(&m_AdcHandle) != HAL_OK)
    {
        return false;
    }
    /** Configure the ADC multi-mode
  */
    multimode.Mode = ADC_MODE_INDEPENDENT;
    if (HAL_ADCEx_MultiModeConfigChannel(&m_AdcHandle, &multimode) != HAL_OK)
    {
        return false;
    }
    /** Configure Regular Channel
  */
    sConfig.Channel = ADC_CHANNEL_14;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_6CYCLES_5;
    sConfig.SingleDiff = ADC_SINGLE_ENDED;
    sConfig.OffsetNumber = ADC_OFFSET_NONE;
    sConfig.Offset = 0;
    if (HAL_ADC_ConfigChannel(&m_AdcHandle, &sConfig) != HAL_OK)
    {
        return false;
    }

    return true;
}
