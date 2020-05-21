/*
 * motores.c
 *
 *  Created on: May 10, 2020
 *  Author: Usuario
 */

/*---------------------------------------------------------------------------*
 *      				TAREA MOTORES										 *
 *---------------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "leds.h"
#include "motores.h"
#include <stdlib.h>
extern TIM_HandleTypeDef htim1;



/*---------------------------------------------------------------------------*
 *      		FUNCION PRINCIPAL: motores									 *
 *---------------------------------------------------------------------------*/

void motores (int mi, int md)
{
	int duty_md1;
	int duty_md2;
	int duty_mi1;
	int duty_mi2;

	//izquierda
	motor(mi, &duty_mi1, &duty_mi2);
	TIM1->CCR1 = duty_mi1;
	TIM1->CCR2 = duty_mi2;

	//derecha
	motor(md, &duty_md1, &duty_md2);
	TIM1->CCR4 = duty_md1;
	TIM1->CCR3 = duty_md2;


}

/*---------------------------------------------------------------------------*
 *      		FUNCION : Inicializacion de motores							 *
 *---------------------------------------------------------------------------*/

void motores_Init (void)
{
	HAL_TIM_PWM_Start_IT(&htim1,TIM_CHANNEL_1);// activar pwm motores
	HAL_TIM_PWM_Start_IT(&htim1,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start_IT(&htim1,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start_IT(&htim1,TIM_CHANNEL_4);

	TIM1->CCR1 = 0;//duty1 0 motor izquierdo
	TIM1->CCR2 = 0;//duty2 0 motor izquierdo
	TIM1->CCR3 = 0;//duty2 0 motor derecho
	TIM1->CCR4 = 0;//duty1 0 motor derecho
    osDelay(1);

}

/*---------------------------------------------------------------------------*
 *      		FUNCION : linealizar pwm pr motor 							 *
 *---------------------------------------------------------------------------*/

void motor(int pwm_motor,int *duty1,int *duty2){

	if( pwm_motor >= 100)
		{
		pwm_motor = 99;
		}
		else if(pwm_motor <= -100)
		{
		   pwm_motor = -99;
		}

		if(pwm_motor > 0)
		{
		  *duty2 = MAXPWM - abs(pwm_motor)*10;
		  *duty1 = MAXPWM;
		}
		else if ( pwm_motor < 0   )
		{
		  *duty2 = MAXPWM;
		  *duty1 = MAXPWM - abs(pwm_motor)*10;

		}
		else
         {
		  *duty2 = MAXPWM;
		  *duty1 = MAXPWM;
		}
	    osDelay(1);
}





