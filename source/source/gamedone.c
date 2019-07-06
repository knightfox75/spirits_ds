/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones del Juego completado

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

// Includes C
#include <stdio.h>

// Includes propietarios NDS
#include <nds.h>

// Includes librerias propias
#include <nf_lib.h>

// Includes del juego
#include "includes.h"





// Funcion GameDone();
void GameDone(void) {

	SoundSfxCleanUp();		// Limpia los Sfx
	GameDoneAnimation();	// Animacion de la muerte del aguila
	GameDoneScreen();		// Pantalla de victoria
	SoundBgmCleanUp();		// Limpia la BGM

}



// Funcion GameDoneAnimation();
void GameDoneAnimation(void) {

	// Variables
	bool loop = true;
	u8 thread = 0;
	u8 next_thread = 0;
	bool update_thread = false;
	s16 brightness = 0;

	// Bucle de ejecucion
	while (loop) {

		// Lee el teclado
		ReadKeypad();

		// Segun el thread
		switch (thread) {

			// Inicializa la animacion
			case 0:
				EAGLE.frame_cnt = 0;
				BGM.next = MOD_FOREST_OF_SUNLIGHT;
				next_thread = 1;
				update_thread = true;
				break;

			// Animacion de la muerte del aguila
			case 1:
				EAGLE.frame_cnt ++;
				if (EAGLE.frame_cnt > 5) {
					EAGLE.frame_cnt = 0;
					EAGLE.frame ++;
					if (EAGLE.frame > 5) {
						EAGLE.frame = 5;
						EAGLE.show = false;
						next_thread = 2;
						update_thread = true;
					}
				}
				break;

			// Animacion del personaje
			case 2:
				CHARACTER.immunity = 0;
				CHARACTER.show = true;
				CHARACTER.frame = 21;
				next_thread = 3;
				update_thread = true;
				break;

			// Espera a que se pulse un boton
			case 3:
				if ((KEYPRESS.a || KEYPRESS.b || KEYPRESS.x || KEYPRESS.y) && (BGM.current == BGM.next)) {
					next_thread = 4;
					update_thread = true;
				}
				break;

			// Fade-out
			case 4:
				brightness += 64;
				if (brightness >= (16 << 8)) {
					brightness = (16 << 8);
					loop = false;
				}
				setBrightness(3, -(brightness >> 8));
				break;

			// Error trap
			default:
				break;

		}

		// Actualiza procesos
		if (update_thread) {
			update_thread = false;
			thread = next_thread;
		}

		// Procesos comunes
		EngineBackgroundProcessesIdle();
		CameraMain();

	}
	
}



// Funcion GameDoneScreen();
void GameDoneScreen(void) {

	/*
	-------------------------------------------------
		Inicializaciones
	-------------------------------------------------
	*/

	// Resetealo todo
	ResetAll();

	// Variables locales
	bool loop = true;		// Control de loop
	s16 fade = (16 << 8);	// Brillo
	bool fade_in = true;	// Flag Fade in
	bool fade_out = false;	// Flag Fade Out


	/*
	-------------------------------------------------
		Carga de archivos
	-------------------------------------------------
	*/

	// Carga los fondos
	if (GAMEOPTIONS[0].remake) {
		NF_LoadTiledBg("hq/menu/bg/m_title_hq", "sc0", 256, 256);
		if (GAMEOPTIONS[0].language == 0) {
			NF_LoadTiledBg("hq/gamedone/bg/gamedone_hq_es", "sc1", 256, 256);
		} else {
			NF_LoadTiledBg("hq/gamedone/bg/gamedone_hq_en", "sc1", 256, 256);
		}
	} else {
		NF_LoadTiledBg("8bits/menu/bg/m_title_8b", "sc0", 256, 256);
		if (GAMEOPTIONS[0].language == 0) {
			NF_LoadTiledBg("8bits/gamedone/bg/gamedone_8b_es", "sc1", 256, 256);
		} else {
			NF_LoadTiledBg("8bits/gamedone/bg/gamedone_8b_en", "sc1", 256, 256);
		}
	}


	/*
	-------------------------------------------------
		Crea las pantallas
	-------------------------------------------------
	*/

	// Brillo
	setBrightness(3, -16);

	// Crea las scanlines
	if (!GAMEOPTIONS[0].remake) CreateScanlines();

	// Crea los fondos
	NF_CreateTiledBg(0, 3, "sc0");
	NF_CreateTiledBg(1, 3, "sc1");


	// Menu
	while (loop) {

		// Lee el telcado
		ReadKeypad();

		// Espera a la pulsacion de la tecla
		if (!fade_in && !fade_out) {
			if ((KEYPRESS.a || KEYPRESS.b || KEYPRESS.x || KEYPRESS.y)) fade_out = true;
		}

		// Effecto "fade in"
		if (fade_in) {
			fade -= 64;
			if (fade <= 0) {
				fade = 0;
				fade_in = false;
			}
			setBrightness(3, (0 - (fade >> 8)));
		}

		// Effecto "fade out"
		if (fade_out) {
			fade += 64;
			if (fade >= (16 << 8)) {
				fade = (16 << 8);
				fade_out = false;
				loop = false;
				// Deten la musica
				if (GAMEOPTIONS[0].remake) StopBgm();
			}
			// Ajusta el brillo
			setBrightness(3, (0 - (fade >> 8)));
			// Ajusta el volumen
			if (GAMEOPTIONS[0].remake) BgmVolume(((4096 - fade) >> 2));
		}

		// Espera al sincronismo
		swiWaitForVBlank();

	}

}