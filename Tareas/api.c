/*
 * api.c
 *
 *  Created on: May 10, 2020
 *      Author: Grupo 13 sistemas embebidos 2020 II
 */

#include "cmsis_os.h"
#include "leds.h"

/* USER CODE END Header_api */
void api(void const * argument)
{
  /* USER CODE BEGIN api */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END api */
}
