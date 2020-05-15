/*
 * motores.h
 *
 *  Created on: May 10, 2020
 *      Author: Grupo 13 sistemas embebidos 2020 II
 */

#ifndef MOTORES_H_
#define MOTORES_H_

#define MAXPWM 1000 + 1

void motores_Init (void);
void motores(int mi, int md);
void motor(int pwm_motor,int *duty1,int *duty2);
#endif /* MOTORES_H_ */
