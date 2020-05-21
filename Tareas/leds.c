/*
 * leds.c
 *
 *  Created on: May 11, 2020
 *  Author: Usuario
 */


#include "cmsis_os.h"
#include "leds.h"
#include "main.h"

void leds(int LD1, int LD2){

		if(LD1==1){
			HAL_GPIO_WritePin(LD1_GPIO_Port,LD1_Pin,GPIO_PIN_SET);
		}
		else{
			HAL_GPIO_WritePin(LD1_GPIO_Port,LD1_Pin,GPIO_PIN_RESET);
		}
		if(LD2==1){
			HAL_GPIO_WritePin(LD2_GPIO_Port,LD2_Pin,GPIO_PIN_SET);
		}
		else{
			HAL_GPIO_WritePin(LD2_GPIO_Port,LD2_Pin,GPIO_PIN_RESET);
		}

}
