#ifndef __TORCHDATA_H__
#define __TORCHDATA_H__



/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de Carga de datos de las antorchas y velas

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



// Funcion LoadDefaultTorchData();
void LoadDefaultTorchData(void);
// Carga los valores estaticos de las antorchas y velas



// Funcion LoadStartTorchData();
void LoadStartTorchData(void);
// Carga los valores de inicio de partida de las antorchas y velas



#endif
