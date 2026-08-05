# STM32 Adafruit Motor Shield V1

STM32 HAL project support code for driving an Adafruit Motor Shield V1 style motor driver.

This repository contains a small motor control layer and a STM32CubeIDE example project. The current implementation uses a 74HC595-compatible shift register interface for motor direction control and TIM3 PWM output for motor speed control.

## Features

- Direction control through shift-register output bits
- PWM speed control from 0 to 100%
- Simple C API for STM32 HAL projects
- STM32CubeIDE example project for `STM32F401RETx`

## Repository Layout

```text
.
+-- Inc/                    # Reusable library headers
|   +-- motor.h
|   +-- shift595.h
+-- Src/                    # Reusable library sources
|   +-- motor.c
|   +-- shift595.c
+-- Example/                # STM32CubeIDE example project
|   +-- MotorShieldTest.ioc
|   +-- Core/
|   +-- Drivers/
+-- LICENSE
+-- README.md
```

## Hardware Assumptions

The example project is configured around an STM32F401RE target and uses STM32 HAL.

Default example pin mapping:

| Signal | STM32 Pin |
| --- | --- |
| Motor latch | PA6 |
| Motor PWM | PA7 / TIM3 CH2 |
| Motor enable | PA8 |
| Motor data | PA9 |
| Motor clock | PB5 |

`MOTOR_EN` is treated as active-low.

## Importing Into Your Project

There is no special installation step.

Add the files from this repository's `Src/` directory to your STM32 project's source folder, and add the files from `Inc/` to your STM32 project's include folder.

For example:

```text
Src/motor.c      -> YourProject/Core/Src/motor.c
Src/shift595.c   -> YourProject/Core/Src/shift595.c
Inc/motor.h      -> YourProject/Core/Inc/motor.h
Inc/shift595.h   -> YourProject/Core/Inc/shift595.h
```

Then include `motor.h` from your application code.

## Basic Usage

After importing the files, include `motor.h`.

```c
#include "motor.h"

int main(void)
{
    HAL_Init();

    /* Initialize clocks, GPIO, and TIM3 PWM first. */

    Motor_Init();

    Motor_SetDirection(MOTOR_1, MOTOR_DIR_FORWARD);
    Motor_SetSpeed(MOTOR_1, 100);
    Motor_Apply();

    while (1)
    {
    }
}
```

## Required STM32 Configuration

Before calling `Motor_Init()`, configure:

- GPIO output pins for latch, enable, data, and clock
- A PWM timer channel for motor speed
- `TIM3` with `TIM_CHANNEL_2`, or update `motor.c` to use your chosen timer/channel

The example uses:

- `extern TIM_HandleTypeDef htim3`
- `TIM_CHANNEL_2`
- PWM period `4199`

The speed API maps `0` to `100` percent onto `0` to `MOTOR_PWM_MAX`.

## API

```c
void Motor_Init(void);
void Motor_SetDirection(MotorId_t motor, MotorDirection_t direction);
void Motor_SetSpeed(MotorId_t motor, uint8_t percent);
void Motor_Apply(void);
void Motor_Stop(MotorId_t motor);
```

Motor IDs:

```c
MOTOR_1
MOTOR_2
MOTOR_3
MOTOR_4
```

Directions:

```c
MOTOR_DIR_FORWARD
MOTOR_DIR_BACKWARD
```

## Current Implementation Status

At the moment, PWM speed control is implemented for `MOTOR_1` using `TIM3` channel 2.

Direction bit definitions exist for all four motors, and direction control is currently handled for `MOTOR_1` and `MOTOR_2`. To use every motor channel, extend `Motor_SetSpeed()`, `Motor_Stop()`, and any missing direction cases with the timer channels used by your hardware setup.

## Example Project

Open `Example/MotorShieldTest.ioc` or the `Example/` folder in STM32CubeIDE.

The example initializes the peripherals, waits one second, then runs `MOTOR_1` forward at full speed.

## License

This project is licensed under the terms in `LICENSE`.
