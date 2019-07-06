#ifndef __SOUND_H__
#define __SOUND_H__

/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de sonido

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



// Funcion InitSound();
void InitSound(void);
// Inicializa la libreria de sonido MAXMOD con el banco de sonido seleccionado



// Funcion LoadBgm();
void LoadBgm(u32 bgm);
// Carga un archivo MOD en RAM



// Funcion PlayBgm();
void PlayBgm(void);
// Reproducel en loop el archivo MOD cargado en RAM



// Funcion StopBgm();
void StopBgm(void);
// Para la reproduccion de un MOD y descargalo de la memoria



// Funcion LoadSfx();
void LoadSfx(u32 id);
// Carga en RAM el SFX con el ID especificado



// Funcion UnloadSfx();
void UnloadSfx(u32 id);
// Descarga en RAM el SFX con el ID especificado



// Funcion PlaySfx();
void PlaySfx(u32 id);
// Reproduce el SFX con el ID indicado



// Funcion StopSfx();
void StopSfx(u32 id);
// Deten el SFX con el ID indicado



// Funcion StopAllSfx();
void StopAllSfx(void);
// Deten todos los sonidos y reinicia el sistema de SFX de MAXMOD



// Funcion SfxFreq();
void SfxFreq(u32 id, u32 freq);
// Cambia la fecuencia del sample con la ID dada



// Funcion BgmVolume();
void BgmVolume(u32 volume);
// Cambia el volumen de la musica de fondo



// Funcion SfxVolume();
void SfxVolume(u32 id, u32 volume);
// Cambia el volumen de los efectos de sonido





#endif
