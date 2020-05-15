/*
 * velocista.h
 *
 *  Created on: May 12, 2020
 *      Author: Usuario
 */

#ifndef VELOCISTA_H_
#define VELOCISTA_H_

#include <stdint.h>

#define CONTROL_INT_MAX 15000
#define NUM_SENSORES 8

typedef struct{

	uint16_t version;
	//variables de control
    float  vavg;
	float  kpg;
	float  kdg;
	float  kig;

  int    pmw_t;   //VEL VARIA DE 0 a 9

  int	tipopista; //"2" > Blanco ,"1" < NEGRO


	int remoto_enable;
	int sw_enable;

	uint16_t aux1;
	uint16_t aux2;
	uint16_t aux3;
	uint16_t aux4;
	uint16_t aux5;
	uint16_t aux6;
	uint16_t aux7;
	uint16_t aux8;


} velocista_setup_st;


typedef struct{

  int start;
	int flag_inicio_lento;

 uint16_t sensores_bin;
 uint16_t sensores_bin_filt_ant;
 uint16_t sensores_bin_filt;


 signed int encoder_d;
 signed int encoder_i;

 signed int position_d;
 signed int position_i;
 signed int direction_d;
 signed int direction_i;

 signed int pmw_d;
 signed int pmw_i;
 float      pwmd;


  signed int sensores;
  uint32_t tr_sens[NUM_SENSORES];
  uint32_t fondo_pista[NUM_SENSORES];

	float  contol_velocidad;
	int detect_recta_ant;
	int detect_recta;

	int flag_tx;

	float teta_b[20];
	long int suma_i;

	unsigned char contador_time;

} velocista_st;

#endif /* VELOCISTA_H_ */
