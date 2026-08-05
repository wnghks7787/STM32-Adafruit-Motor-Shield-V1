/*
 * shift595.c
 *
 *  Created on: 2026. 8. 3.
 *      Author: 3-30
 */


#include "shift595.h"

static uint8_t s_data = 0;

static void Shift595_PulseClock(void)
{
    HAL_GPIO_WritePin(MOTOR_CLK_GPIO_Port,
                      MOTOR_CLK_Pin,
                      GPIO_PIN_RESET);

    __NOP();
    __NOP();

    HAL_GPIO_WritePin(MOTOR_CLK_GPIO_Port,
                      MOTOR_CLK_Pin,
                      GPIO_PIN_SET);

    __NOP();
    __NOP();

    HAL_GPIO_WritePin(MOTOR_CLK_GPIO_Port,
                      MOTOR_CLK_Pin,
                      GPIO_PIN_RESET);
}

static void Shift595_PulseLatch(void)
{
    HAL_GPIO_WritePin(MOTOR_LATCH_GPIO_Port,
                      MOTOR_LATCH_Pin,
                      GPIO_PIN_RESET);

    __NOP();
    __NOP();

    HAL_GPIO_WritePin(MOTOR_LATCH_GPIO_Port,
                      MOTOR_LATCH_Pin,
                      GPIO_PIN_SET);

    __NOP();
    __NOP();

    HAL_GPIO_WritePin(MOTOR_LATCH_GPIO_Port,
                      MOTOR_LATCH_Pin,
                      GPIO_PIN_RESET);
}

void Shift595_Init(void)
{
    s_data = 0;

    /* Enable(Active Low) */
    HAL_GPIO_WritePin(MOTOR_EN_GPIO_Port,
                      MOTOR_EN_Pin,
                      GPIO_PIN_RESET);

    Shift595_Write(0x00);
}

void Shift595_Write(uint8_t data)
{
    s_data = data;

    for(int i = 7; i >= 0; i--)
    {
        GPIO_PinState bit =
            (data & (1 << i)) ? GPIO_PIN_SET : GPIO_PIN_RESET;

        HAL_GPIO_WritePin(MOTOR_DATA_GPIO_Port,
                          MOTOR_DATA_Pin,
                          bit);

        Shift595_PulseClock();
    }

    Shift595_PulseLatch();
}
