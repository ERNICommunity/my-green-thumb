#pragma once

#include <memory>
#include "Service.hpp"

class ServiceStatus : public Service
{

public:
    ServiceStatus(std::shared_ptr<ITask> task) : Service(task){};
    virtual ~ServiceStatus() = default;

private:
    // Service Interface
    bool setup()
    {
        GPIO_InitTypeDef GPIO_InitStruct = {0};

        /* GPIO Ports Clock Enable */
        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();

        /*Configure GPIO pin Output Level */
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_RESET);

        /*Configure GPIO pin Output Level */
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);

        /*Configure GPIO pin : PA5 */
        GPIO_InitStruct.Pin = GPIO_PIN_5;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        /*Configure GPIO pin : PB14 */
        GPIO_InitStruct.Pin = GPIO_PIN_14;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        // Set initial values
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);

        return true;
    };

    bool dispose()
    {
        return true;
    };

    void doWork()
    {
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
    };
};