/*
 * api.c
 *
 *  Created on: May 10, 2020
 *  Author: Usuario
 */

/*---------------------------------------------------------------------------*
 *      				TAREA API											 *
 *---------------------------------------------------------------------------*/
#include "cmsis_os.h"
#include "leds.h"
#include "main.h"
UART_HandleTypeDef huart3;

/* USER CODE END Header_api */
void api(void const * argument)
{
  /* USER CODE BEGIN api */
  /* Infinite loop */
  for(;;)
  {
//envio de datos via BT
    // {
    //   sprintf((char*)uart_buffer_tx,"V%d -P%d -D%d -T%d\n\r",(int)vel_setup.vavg,(int)(10*vel_setup.kpg),(int)(10*vel_setup.kdg),vel_setup.pmw_t);
    //   HAL_UART_Transmit(&huart2, uart_buffer_tx, strlen((char*)uart_buffer_tx),1000);
    //   vel.flag_tx=0;
    // }
    osDelay(1);
  }
  /* USER CODE END api */
}
