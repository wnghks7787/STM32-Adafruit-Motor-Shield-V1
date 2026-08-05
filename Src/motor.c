/*
 * motor.c
 *
 *  Created on: 2026. 8. 3.
 *      Author: 3-30
 */

#include "motor.h"
#include "shift595.h"

extern TIM_HandleTypeDef htim3;

static uint8_t s_motor_bits = 0;

static void Motor_SetBit(uint8_t bit, bool value) {
	if(value) {
		s_motor_bits |= (1 << bit);
	} else {
		s_motor_bits &= ~(1 << bit);
	}
}


/*
 * @ brief: Motor를 초기화하는 코드. 모터가 추가되면 여기서 PWM 타이머도 시작시켜야 합니다.
 * @ htim3, TIM_CHANNEL_2은 모두 motor1에 대한 설정입니다.
 */
void Motor_Init(void) {
	// MOTOR1 TIM
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);

	Shift595_Init();
}

void Motor_SetDirection(MotorId_t motor, MotorDirection_t direction) {
	switch(motor) {
	case MOTOR_1:
		if(direction == MOTOR_DIR_FORWARD) {
			Motor_SetBit(MOTOR1_A, true);
			Motor_SetBit(MOTOR1_B, false);
		} else {
			Motor_SetBit(MOTOR1_A, false);
			Motor_SetBit(MOTOR1_B, true);
		}
		break;
	case MOTOR_2:
		if(direction == MOTOR_DIR_FORWARD) {
			Motor_SetBit(MOTOR2_A, true);
			Motor_SetBit(MOTOR2_B, false);
		} else {
			Motor_SetBit(MOTOR2_A, false);
			Motor_SetBit(MOTOR2_B, true);
		}
		break;
	default:
		break;
	}
}

/*
 * @ brief: speed는 0~ 100 %로 잡습니다.
 */
void Motor_SetSpeed(MotorId_t motor, uint8_t speed) {
	uint16_t motor_pwm_speed = MOTOR_PWM_MAX * speed / 100;
	switch(motor) {
	case MOTOR_1:
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, motor_pwm_speed);
		break;
	default:
		break;
	}
}

void Motor_Apply() {
	Shift595_Write(s_motor_bits);
}

void Motor_Stop(MotorId_t motor) {
	switch(motor) {
	case MOTOR_1:
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, MOTOR_PWM_MIN);
		break;
	default:
		break;
	}
	Shift595_Write(s_motor_bits);
}
