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



// Includes C
#include <stdio.h>

// Includes propietarios NDS
#include <nds.h>

// Includes de MAXMOD
#include <maxmod9.h>

// Includes NightFox's Lib
#include <nf_lib.h>

//Incluye las librerias del juego
#include "includes.h"



// Funcion InitSound();
void InitSound(void) {

	// Inicializa MAXMOD con en banco de sonido seleccionado
	mmInitDefault("snd/sbf/spirits.sbf");

	// Modo Maxmod (30 canales interpolados por soft)
	mmSelectMode(MM_MODE_C);

	// Reserva los canales 0, 1, 2 para libnds sound system
	mmLockChannels(BIT(0) | BIT(1) | BIT(2) | BIT (4));

	// No esta sonando ningun MOD
	SOUNDTRACK.playback = false;
	SOUNDTRACK.track_id = -1;

	// Inicializa el audio de libnds
	soundEnable();

}



// Funcion LoadBgm();
void LoadBgm(u32 bgm) {

	// Guarda el ID del track
	SOUNDTRACK.track_id = bgm;

	// Carga el track
	mmLoad(bgm);

}



// Funcion PlayBgm();
void PlayBgm(void) {

	// Reproduce el mod
	mmStart(SOUNDTRACK.track_id, MM_PLAY_LOOP);

	// Ajusta y guarda el volumen
	BgmVolume(1024);
	SOUNDTRACK.volume = 1024;

	// Y marca que se esta reproduciendo un MOD
	SOUNDTRACK.playback = true;

}



// Funcion StopBgm();
void StopBgm(void) {

	// Si esta sonando

	if (SOUNDTRACK.playback) {

		// Deten el BGM actual
		mmStop();

		// Descargalo de la memoria
		mmUnload(SOUNDTRACK.track_id);

		// Y marca que no esta sonando ningun MOD
		SOUNDTRACK.playback = false;
		SOUNDTRACK.track_id = -1;

	}
	
}



// Funcion LoadSfx();
void LoadSfx(u32 id) {

	// Guarda el ID del SFX
	SFX[id].sfx_id = id;

	// Carga el SFX en RAM
	mmLoadEffect(id);

}



// Funcion UnloadSfx();
void UnloadSfx(u32 id) {

	// Descarga el SFX en RAM
	mmUnloadEffect(SFX[id].sfx_id);

}



// Funcion PlaySfx();
void PlaySfx(u32 id) {

	// Reproduce el SFX del ID indicado
	SFX[id].handle = mmEffect(SFX[id].sfx_id);

	// Al volumen indicado
	SfxVolume(id, 1024);

}



// Funcion StopSfx();
void StopSfx(u32 id) {

	// Deten el SFX del ID indicado
	mmEffectCancel(SFX[id].handle);

}



// Funcion StopAllSfx();
void StopAllSfx(void) {

	// Deten todos los SFX
	mmEffectCancelAll();

}



// Funcion SfxFreq();
void SfxFreq(u32 id, u32 freq) {

	// Cambia la frecuencia del sample
	mmEffectRate(SFX[id].handle, freq);

}



// Funcion BgmVolume();
void BgmVolume(u32 volume) {

	// Variables
	s32 level = volume;

	// Fix del volumen
	if (level < 0) level = 0;
	if (level > 1024) level = 1024;

	// Aplica el volumen
	mmSetModuleVolume(level);

	// Guarda el volumen actual
	SOUNDTRACK.volume = volume;

}



// Funcion SfxVolume();
void SfxVolume(u32 id, u32 volume) {

	// Variables
	s32 level = volume;

	// Fix del volumen
	if (level < 0) level = 0;
	if (level > 255) level = 255;

	// Aplica el volumen
	mmEffectVolume(SFX[id].handle, level);

	// Guarda el volumen actual
	SFX[id].volume = volume;

}
