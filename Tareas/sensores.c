/*
 * sensores.c
 *
 *  Created on: 14/05/2020
 *  Author: Usuario
 */

/*---------------------------------------------------------------------------*
 *      				TAREA SENSORES										 *
 *---------------------------------------------------------------------------*/


#include "sensores.h"
#include "cmsis_os.h"                                           // CMSIS RTOS header file
#include <stdlib.h>
#include "VELOCISTA.h"
#include "main.h"

extern TIM_HandleTypeDef htim15;// instancia timer

extern velocista_st vel;
extern velocista_setup_st vel_setup;
uint32_t sensor_timing[NUM_SENSORES];

int Sensores_peso[8] = {-35,-20,-15,-8,8,15,20,35};
volatile int32_t sensores_actual[NUM_SENSORES];
volatile int32_t sensores_estado[NUM_SENSORES];

volatile int ultimo_error_valido;

int sensores_leidos[NUM_SENSORES];
volatile	int	suma = 0;
volatile	int	num_sensors  = 0;

//CALIBRACION
uint32_t max_sens[NUM_SENSORES];
uint32_t min_sens[NUM_SENSORES];

void sensores(void const * argument)
{

	  GPIO_InitTypeDef GPIO_InitStruct = {0};

	HAL_TIM_Base_Start(&htim15);
	vel.sensores = 0;

		for(int is=0; is < NUM_SENSORES ; is ++)
			{
				vel.tr_sens[is]  = 1000; //Default Value
			}


  /* Infinite loop */
  for(;;)
  {
	  /*Configure GPIO OUTPUT pin : S8_Pin */
	    GPIO_InitStruct.Pin = S8_Pin;
	    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    HAL_GPIO_Init(S8_GPIO_Port, &GPIO_InitStruct);

	    /*Configure GPIO  OUTPUT pins : S7_Pin S6_Pin S5_Pin S4_Pin
	                             S3_Pin S2_Pin S1_Pin */
	    GPIO_InitStruct.Pin = S7_Pin|S6_Pin|S5_Pin|S4_Pin
	                            |S3_Pin|S2_Pin|S1_Pin;
	    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	    //SENSORES EN ALTO
	    HAL_GPIO_WritePin(GPIOB, S1_Pin, GPIO_PIN_SET);
	    HAL_GPIO_WritePin(GPIOB, S2_Pin, GPIO_PIN_SET);
	    HAL_GPIO_WritePin(GPIOB, S3_Pin, GPIO_PIN_SET);
	    HAL_GPIO_WritePin(GPIOB, S4_Pin, GPIO_PIN_SET);
	    HAL_GPIO_WritePin(GPIOB, S5_Pin, GPIO_PIN_SET);
	    HAL_GPIO_WritePin(GPIOB, S6_Pin, GPIO_PIN_SET);
	    HAL_GPIO_WritePin(GPIOB, S7_Pin, GPIO_PIN_SET);
	    HAL_GPIO_WritePin(S8_GPIO_Port, S8_Pin, GPIO_PIN_SET);

	    /*Configure GPIO INPUT pin : S8_Pin */
	    GPIO_InitStruct.Pin = S8_Pin;
	    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    HAL_GPIO_Init(S8_GPIO_Port, &GPIO_InitStruct);

	    /*Configure GPIO INPUT pins : S7_Pin S6_Pin S5_Pin S4_Pin
	                             S3_Pin S2_Pin S1_Pin */
	    GPIO_InitStruct.Pin = S7_Pin|S6_Pin|S5_Pin|S4_Pin
	                            |S3_Pin|S2_Pin|S1_Pin;
	    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		//LEER SENSORES
		for(int i=0; i<NUM_SENSORES ; i++)
		{
			sensores_leidos[i] = 1;
			sensor_timing[i] = TIME_OUT_BLANCO; //frecuencia 1M -- 500 es 0.5ms
																//PERO SE DESCARGA EN LINEA A 0.25ms
			sensores_estado[i] = 1; //LINEA NEGRA

		}
		TIM15->CNT = 0;

		while(( sensores_leidos[0] ||
								sensores_leidos[1] ||
								sensores_leidos[2] ||
								sensores_leidos[3] ||
								sensores_leidos[4] ||
								sensores_leidos[5]	) && TIM15->CNT < TIME_OUT_BLANCO)
				{
							if(!HAL_GPIO_ReadPin(GPIOB, S1_Pin) && sensores_leidos[0])
							{
								 sensor_timing[0] = TIM15->CNT;
								 sensores_leidos[0] = 0;
								 sensores_estado[0] = 0;
							}

							if(!HAL_GPIO_ReadPin(GPIOB, S2_Pin) && sensores_leidos[1])
							{
								 sensor_timing[1] = TIM15->CNT;
								 sensores_leidos[1] = 0;
								 sensores_estado[1] = 0;

							}

								if(!HAL_GPIO_ReadPin(GPIOB, S3_Pin) && sensores_leidos[2])
							{
								 sensor_timing[2] = TIM15->CNT;
								 sensores_leidos[2] = 0;
								 sensores_estado[2] = 0;

							}

							if(!HAL_GPIO_ReadPin(GPIOB, S4_Pin) && sensores_leidos[3])
							{
								 sensor_timing[3] = TIM15->CNT;
								 sensores_leidos[3] = 0;
								 sensores_estado[3] = 0;
							}

							if(!HAL_GPIO_ReadPin(GPIOB, S5_Pin) && sensores_leidos[4])
							{
								 sensor_timing[4] = TIM15->CNT;
								 sensores_leidos[4] = 0;
								 sensores_estado[4] = 0;
							}

							if(!HAL_GPIO_ReadPin(GPIOB, S6_Pin) && sensores_leidos[5])
							{
								 sensor_timing[5] = TIM15->CNT;
								 sensores_leidos[5] = 0;
								 sensores_estado[5] = 0;

							}

							if(!HAL_GPIO_ReadPin(GPIOB, S7_Pin) && sensores_leidos[6])
							{
								 sensor_timing[6] = TIM15->CNT;
								 sensores_leidos[6] = 0;
								 sensores_estado[6] = 0;

							}

							if(!HAL_GPIO_ReadPin(S8_GPIO_Port, S8_Pin) && sensores_leidos[7])
							{
								 sensor_timing[7] = TIM15->CNT;
								 sensores_leidos[7] = 0;
								 sensores_estado[7] = 0;

							}
					}

					vel_setup.tipopista = 2; //PISTA BLANCA


					if(vel_setup.tipopista == 1) //LINEA
					{
						for(int i=0; i<NUM_SENSORES ; i++)
							{
								if(sensores_estado[i] == 1)
								   sensores_estado[i] = 0;
								else
								   sensores_estado[i] = 1;
							}
					}
					 suma = 0;
					 num_sensors = 0;

					for(int i=0; i<NUM_SENSORES ; i++)
						{
							if(sensores_estado[i] == 1)
								{
									suma += Sensores_peso[i];
									num_sensors++;
								 }
						}

					if(num_sensors == 0) //Si no lee ningun mantiene el anterior
						{
							if(vel.sensores > 10)
								{
									vel.sensores = 45; //MAXIMO ERROR
								}
							else if(vel.sensores < -10)
								{
									vel.sensores = -45;
								}
							else //PERDIDA DE LINEA DE FRENTE
								{
									vel.sensores = 0;
								}
						  }
					else
						{
							vel.sensores = suma/num_sensors;
						}




    osDelay(1);
  }

}


/*---------------------------------------------------------------------------*
 *      			Funcion	Calibracion: FONDO PISTA  						 *
 *---------------------------------------------------------------------------*/

void Sensores_Calibracion_Backgound(void)
{

for(int ind=0; ind < 100 ; ind ++)
			{
				for(int is=0; is < NUM_SENSORES ; is ++) //Leer los sensores y guardar los valores iniciales
					{
						 vel.fondo_pista[is] += sensor_timing[is];
					}
					osDelay(5);
			}

	for(int is=0; is < NUM_SENSORES ; is ++) //Leer los sensores y guardar los valores promedio de fondo de pista
		{
			 vel.fondo_pista[is] = vel.fondo_pista[is]/100;
	  }

}



/*---------------------------------------------------------------------------*
 *      			Funcion	Calibracion: LINEA		  						 *
 *---------------------------------------------------------------------------*/


void Sensores_Calibracion_Line(void)
{

	for(int is=0; is < NUM_SENSORES ; is ++)
		{
			vel.tr_sens[is]  = 0;
			max_sens[is]     = 0;
			min_sens[is]     = 10000;
		}

	 for(int ind=0; ind < 1500 ; ind ++)
				 {
					  for(int is=0; is < NUM_SENSORES ; is ++) //Leer los sensores y guardar el maximo, el minimo y promedio
				      {
								  if(sensor_timing[is] > max_sens[is])
										max_sens[is] = sensor_timing[is];

								  if(sensor_timing[is] < min_sens[is])
										 min_sens[is] = sensor_timing[is];

					              //vel.tr_sens[is] = (min_sens[is] + max_sens[is])/2;
									      vel.tr_sens[is] = TIME_OUT_BLANCO - 10;
				      }

						 osDelay(2);
				}

		//definir color de PISTA
				if ((vel.fondo_pista[0] > vel.tr_sens[0]) && (vel.fondo_pista[NUM_SENSORES-1] > vel.tr_sens[NUM_SENSORES-1]))
				{
				     vel_setup.tipopista = 1; // pista < negro
				}

				else if ((vel.fondo_pista[0] < vel.tr_sens[0]) && (vel.fondo_pista[NUM_SENSORES-1] < vel.tr_sens[NUM_SENSORES-1]))
				{
				     vel_setup.tipopista = 2; // pista > Blanco
				}
	      else
				{
					vel_setup.tipopista = 2; //SET MANUAL
				}

}


