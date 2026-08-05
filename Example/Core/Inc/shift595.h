/*
 * shift595.h
 *
 *  Created on: 2026. 8. 3.
 *      Author: 3-30
 */

#ifndef INC_SHIFT595_H_
#define INC_SHIFT595_H_

#include "main.h"
#include <stdint.h>

void Shift595_Init(void);
void Shift595_Write(uint8_t data);

#endif /* INC_SHIFT595_H_ */
