#ifndef __NPCDATA_H__
#define __NPCDATA_H__



/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de gestion de los datos
	de los NPC

	Requiere DevkitARM
	Requiere NightFox's Lib

	Codigo por NightFox
	http://www.nightfoxandco.com
	Inicio 02 de Septiembre del 2011

	(c)2008 - 2012 NightFox & Co.

-------------------------------------------------
*/



/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/

// Includes propietarios NDS
#include <nds.h>





// Funcion LoadDefaultNpcData();
void LoadDefaultNpcData(void);
// Carga los datos estaticos de los NPC



// Funcion SetArmor();
void SetArmor(u8 pos);
// Posiciona la armadura



// Funcion SetPrincess();
void SetPrincess(u8 pos);
// Posiciona la princesa



// Funcion SetEagle();
void SetEagle(u8 pos);
// Posiciona la aguila





#endif
