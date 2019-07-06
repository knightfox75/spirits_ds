#ifndef __BGM_H__
#define __BGM_H__

/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de BGM

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





// Funcion SoundInitBgm();
void SoundInitBgm(void);
// Inicializa la reproduccion de la musica



// Funcion SoundBgmPlayback();
void SoundBgmPlayback(void);
// Controla la musica de fondo



// Funcion SoundBgmCleanUp();
void SoundBgmCleanUp(void);
// Deten y elimina de la memoria cualquier musica




#endif
