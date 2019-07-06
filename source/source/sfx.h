#ifndef __SFX_H__
#define __SFX_H__

/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de SFX

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





// Funcion SoundInitSfx();
void SoundInitSfx(void);
// Inicializa la reproduccion de sonidos



// Funcion SoundSfxPlay8bits();
void SoundSfxPlay8bits(void);
// Reproduce los efectos de sonido



// Funcion SoundSfxPlayHq();
void SoundSfxPlayHq(void);



// Funcion SoundVoicePlayback();
void SoundVoicePlayback(void);
// Reproduce las voces



// Funcion SoundSfxCleanUp();
void SoundSfxCleanUp(void);
// Deten y elimina de la memoria cualquier efecto de sonido





#endif
