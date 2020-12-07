
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <memory>

#include "stm32l4xx_hal.h"
#include "MoistureSensorDFRobot.hpp"
#include "AdptMoistureSensorDFRobot.hpp"
#include "IMoistureSensor.hpp"
#include "WaterRegulator.hpp"
#include "ServiceWaterRegulator.hpp"
#include "ServiceStatus.hpp"
#include "AdptWaterValve.hpp"
#include "WaterValveBistable.hpp"

#include "AdptSpinTimer.hpp"
#include "TaskTimer.hpp"

#include "Timer.h"
#include "STM32UptimeInfoAdapter.h"

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Error_Handler(void);
void DummyCallBack(void);

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  // Set the STM32 platform dependend time base for the SpinTimer
  auto uptimeInfo = UptimeInfo::Instance();
  uptimeInfo->setAdapter(new STM32UptimeInfoAdapter());

  ServiceStatus serviceStatus(
      std::make_shared<TaskTimer>(
        1, 
        "TimerStatus", 
        500, 
        std::unique_ptr<AdptSpinTimer>(new AdptSpinTimer())));

  std::shared_ptr<MoistureSensorDFRobot> moistureSensor = std::make_shared<MoistureSensorDFRobot>();
  std::shared_ptr<WaterValveBistable> waterValve = std::make_shared<WaterValveBistable>(
      std::unique_ptr<AdptSpinTimer>(new AdptSpinTimer()));
  std::shared_ptr<WaterRegulator> waterRegulator = std::make_shared<WaterRegulator>(
    std::dynamic_pointer_cast<IMoistureSensor>(moistureSensor), 
    std::dynamic_pointer_cast<IValve>(waterValve));

  ServiceWaterRegulator serviceWaterRegulator(
    std::make_shared<TaskTimer>(1, "TimerWaterRegulator", 50, std::unique_ptr<AdptSpinTimer>(new AdptSpinTimer())),
    waterRegulator);

  if (!serviceStatus.start())
  {
    Error_Handler();
  }

  if (!serviceWaterRegulator.start())
  {
    Error_Handler();
  }

  /* Infinite loop */
  for (;;)
  {
    scheduleTimers();
    HAL_Delay(10);
  }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCCLKSOURCE_SYSCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM4 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM4)
  {
    HAL_IncTick();
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  while(1)
  {
    // Error
  }
}

#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  //printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
}
#endif /* USE_FULL_ASSERT */

/******************************** END OF FILE ********************************/
