/*
 * register.c
 *
 *  Created on: 23 déc. 2018
 *      Author: romain
 */

#include "Register.h"

/*
 * Initialise l'integralites des parametres de positionnement des pates
 */
void Registre_init()
{
	REGS.v1=0;
	REGS.v2=1;
	/*
	 * Permet d'identifier la patte
	 */
	REGS.patte=ID_PATTE;

	/*
	 * OPMODE :
	 *  0 : inactif, pas d'asservissement
	 *  1 : asservissement de position
	 */
	REGS.opmode=0;

	/*
	 * VLIMIT :
	 * Permet de regler la vitesse limite de la PWM
	 * valeur entre 0 et 1
	 * 1 : PWM a la vitesse maximale
	 */
	REGS.vlimit1=VMAX;
	REGS.vlimit2=VMAX;
	REGS.vlimit3=VMAX;
	REGS.vlimit4=VMAX;

	/*
	 * Position minimale et maximale atteignable par chaque moteur
	 * en supposant pos 0 patte perpendiculaire au corps et horizontale
	 */
	REGS.max_pos1=32767;
	REGS.min_pos1=-32767;

	REGS.max_pos2=32767;
	REGS.min_pos2=-32767;

	REGS.max_pos3=32767;
	REGS.min_pos3=-32767;

	REGS.max_pos4=32767;
	REGS.min_pos4=-32767;

	/*
	 * Initialisation des valeurs de KP
	 */
	REGS.kp1=0.0005;
	REGS.kp2=0.0005;
	REGS.kp3=0.0005;
	REGS.kp4=0.0005;

	/*
	 * Initialisation des valeurs de KI
	 */
	REGS.ki1=0;
	REGS.ki2=0;
	REGS.ki3=0;
	REGS.ki4=0;
}
