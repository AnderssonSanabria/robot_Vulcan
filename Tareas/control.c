/*
 * control.c
 *
 *  Created on: May 10, 2020
 *  Author: Usuario
 */

/*---------------------------------------------------------------------------*
 *      				TAREA SENSORES										 *
 *---------------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "leds.h"
#include "motores.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "motores.h"
#include "velocista.h"
#include "sensores.h"
#include "control.h"


//ESTRUCTURA GLOBAL DEL PROYECTO
velocista_st vel;
velocista_setup_st vel_setup;

void control(void const * argument)
{
	Default_Setup ();					// cargar valores iniciales

	motores_Init();
	motores(0,0);
	Sensores_Calibracion_Backgound();
	leds(1,1);							//motores ok, calibracion fondo ok

	osDelay(2000);						// inicio calibracion de linea
	motores(30,-30);
	leds(1,1);
	osDelay(200);
	Sensores_Calibracion_Line();
							//calibracion de linea ok
	osDelay(2);
	leds(0,0);
	/*---------------------------------------------------------------------------*
	 *      				Fin calibracion										 *
	 *---------------------------------------------------------------------------*/


	 vel.suma_i  = 0;
	 for (int i=1;i>=9;i++)				//valores de sensores en cero
	 {
		 vel.teta_b[i] = 0;
	  }

	 for (int i=9;i>0;i--)				// Carga de valores de los sensores
	 {
		 vel.teta_b[i] =vel.teta_b[i-1];
	  }

	 vel.teta_b[0] = vel.sensores;

     if(vel.teta_b[0] == 0 )
     {
    	 vel.suma_i  = 0;
     }
     	 if(vel.suma_i >= CONTROL_INT_MAX) //limite maximo variables de control
     		{
     		 vel.suma_i = CONTROL_INT_MAX;
     		}
     	else if(vel.suma_i <= -CONTROL_INT_MAX)//limite minimo variables de control
     	{
     		vel.suma_i = -CONTROL_INT_MAX;
     	}
     	else
     	{
     		vel.suma_i += (vel.teta_b[0]);
     	}

     	int integral = (vel_setup.kig * vel.suma_i);//integral
     					vel.pwmd = (vel.teta_b[0]*vel_setup.kpg) +  (vel_setup.kdg*(vel.teta_b[0] - vel.teta_b[3])) + integral;//PID


     					if(vel.pwmd>20)
     						{

     							vel.pwmd = 20;
     						}
     					if(vel.pwmd<-20)
     						{
     							vel.pwmd = -20;
     						}

     					vel.pmw_d = (int) - vel.pwmd;
     					vel.pmw_i = (int)  vel.pwmd;

     					motores(vel.pmw_i,vel.pmw_d);

     					//Direccionales
     					if(vel.pwmd > 0)
     						{
     						    leds(1, 0);
     						}
     					else
     						{
     						    leds(0, 1);
     						}
     					osDelay(2);


	while(1)
	{
		float pwml,pwmr;

		 for (int i=19;i>0;i--)		// Carga de valores de los sensores
		 {
			 vel.teta_b[i] =vel.teta_b[i-1];
		  }
		vel.teta_b[0] = vel.sensores;

		vel.detect_recta_ant = vel.detect_recta;
		vel.detect_recta = 1;

		for(int i=0 ; i<20; i++)
		{
			if( vel.teta_b[i] > 8 || vel.teta_b[i] < -8)
		  {
			  vel.detect_recta = 0;
			}

		}


		if(vel.detect_recta)
		{
		   leds(0, 0);
		}
		else //ES CURVA
		 {
			 if(vel.detect_recta_ant)
			 {
//					 vel.pmw_d = (int) -100;
//				   vel.pmw_i = (int) -100;
//					 osDelay(20);
			 }
		     leds(1,1);
		}


		vel.pwmd = (vel.teta_b[0]*vel_setup.kpg) +  (vel_setup.kdg*(vel.teta_b[0] - vel.teta_b[8]));//PID

				    if(vel.pwmd >= 0)
						{//la diferencia es positiva
		          pwml = vel_setup.vavg;//0 + (vel.pwmd*0.2);
					    pwmr = vel_setup.vavg - vel.pwmd;
						}
						else
						{//la diferencia es negativa
		           pwml = vel_setup.vavg  + vel.pwmd;
					     pwmr = vel_setup.vavg;// - (vel.pwmd*0.2);
						}

		//			    pwmr = vel_setup.vavg - vel.pwmd;
		//			    pwml = vel_setup.vavg  + vel.pwmd;

						vel.pmw_d = (int) pwmr;
						vel.pmw_i = (int) pwml;

						motores(vel.pmw_i,vel.pmw_d);


		leds(1,1);
		osDelay(1);

	}


}


/*---------------------------------------------------------------------------*
 *      				Valores iniciales									 *
 *---------------------------------------------------------------------------*/

void Default_Setup (void)
{

		vel_setup.tipopista = 2; //SET MANUAL

		vel_setup.kpg     = 2.0;   //2.0  en test noche y vuelta
		vel_setup.kdg     = 7.2;   //3.0 EN PRIMERA
		vel_setup.kig     = 0.0005;

		vel_setup.vavg    =  80;     //Control de velocidad - MINIMO 65

		vel_setup.pmw_t   =  5;      //0 A 9

		vel.sensores = 0;
		vel.pmw_d =  0;
		vel.pmw_i =  0;

		vel_setup.remoto_enable = 1;
		vel_setup.sw_enable = 0;
		vel.start = 0XFF;
}
