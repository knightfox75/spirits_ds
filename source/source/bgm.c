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



// Includes C
#include <stdio.h>

// Includes propietarios NDS
#include <nds.h>

// Includes NightFox's Lib
#include <nf_lib.h>

//Incluye las librerias del juego
#include "includes.h"





// Funcion SoundInitBgm();
void SoundInitBgm(void) {

	// Inicializa las estucturas de control
	BGM.current = -1;
	BGM.next = -1;
	BGM.play = false;
	BGM.stop = false;
	BGM.status = 0;
	BGM.volume = 1024;

}



// Funcion SoundBgmPlayback();
void SoundBgmPlayback(void) {

	// Deten la musica si has recivido el comando STOP
	if (BGM.stop) {

		// Si esta sonando algo
		if (SOUNDTRACK.playback) {
			BGM.volume = SOUNDTRACK.volume;
			BGM.volume -= 16;
			if (BGM.volume < 0) BGM.volume = 0;
			BgmVolume(BGM.volume);
			// Si ya has bajado todo el volumen, deten la musica
			if (BGM.volume == 0) {
				StopBgm();
				BGM.stop = false;
				BGM.current = -1;
				BGM.next = -1;
			}
		} else {
			// Si no, anula el comando
			BGM.stop = false;
		}

	} else {	// Si no has recivido orden de detener la musica

		// Cambio de musica (Si no hay ninguna voz sonando)
		if ((BGM.next != BGM.current) && !VOICE.play) {
			// Si actualmente no hay ninguna musica sonando, cargala y reproducela
			if (!SOUNDTRACK.playback) {
				LoadBgm(BGM.next);
				PlayBgm();
				BGM.volume = SOUNDTRACK.volume;
				BGM.current = BGM.next;
			} else {
				// Si hay una cancion en curso, baja el volumen
				BGM.volume = SOUNDTRACK.volume;
				BGM.volume -= 16;
				if (BGM.volume < 0) BGM.volume = 0;
				BgmVolume(BGM.volume);
				// Si ya has bajado todo el volumen, deten la musica
				if (BGM.volume == 0) {
					StopBgm();
				}
			}
		}

	}

}


// Funcion SoundBgmCleanUp();
void SoundBgmCleanUp(void) {

	// Si hay alguna musica sonando, detenla
	if (SOUNDTRACK.playback) {
		StopBgm();
		BGM.stop = false;
		BGM.current = -1;
		BGM.next = -1;
	}

}