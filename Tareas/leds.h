/*
 * leds.h
 *
 *  Created on: May 11, 2020
 *      Author: Grupo 13 sistemas embebidos 2020 II
 */

#ifndef LEDS_H_
#define LEDS_H_

#include "stm32l4xx_hal.h"

#define LD1_Pin GPIO_PIN_4
#define LD1_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA

void leds(int LD1, int LD2);

#endif /* LEDS_H_ */
