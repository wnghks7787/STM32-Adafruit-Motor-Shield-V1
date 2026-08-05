/*
 * motor.h
 *
 *  Created on: 2026. 8. 3.
 *      Author: 3-30
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include <stdint.h>
#include <stdbool.h>

#define MOTOR1_A 2
#define MOTOR1_B 3
#define MOTOR2_A 1
#define MOTOR2_B 4
#define MOTOR4_A 0
#define MOTOR4_B 6
#define MOTOR3_A 5
#define MOTOR3_B 7

#define MOTOR_PWM_MAX 4199U
#define MOTOR_PWM_MIN 0U

typedef enum {
	MOTOR_1 = 0,
	MOTOR_2,
	MOTOR_3,
	MOTOR_4
} MotorId_t;

typedef enum
{
    MOTOR_DIR_FORWARD = 0,
    MOTOR_DIR_BACKWARD
} MotorDirection_t;

void Motor_Init(void);

void Motor_Apply(void);
void Motor_Stop(MotorId_t motor);

void Motor_SetDirection(MotorId_t motor, MotorDirection_t direction);

void Motor_SetSpeed(MotorId_t motor, uint8_t percent);



#endif /* INC_MOTOR_H_ */
