/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones del GAME OVER

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



// Funcion GameOver();
void GameOver(void) {

	SoundSfxCleanUp();	// Limpia los SFX pendientes
	GameOverScreen();	// Pantalla de game over
	SoundBgmCleanUp();	// Limpia la BGM

}



// Funcion GameOverScreen();
void GameOverScreen(void) {

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
	u16 snd_id = 0;			// ID del sonido de la risa


	/*
	-------------------------------------------------
		Carga de archivos
	-------------------------------------------------
	*/

	// Carga los fondos
	if (GAMEOPTIONS[0].remake) {
		NF_LoadTiledBg("hq/menu/bg/m_title_hq", "sc0", 256, 256);
		NF_LoadTiledBg("hq/gameover/bg/gameover_hq", "sc1", 256, 256);
	} else {
		NF_LoadTiledBg("8bits/menu/bg/m_title_8b", "sc0", 256, 256);
		NF_LoadTiledBg("8bits/gameover/bg/gameover_8b", "sc1", 256, 256);
	}

	// Carga SFX
	if (GAMEOPTIONS[0].remake) {
		NF_LoadRawSound("snd/raw/laughter", 31, 22050, 0);
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

	// Reproduce la risa
	if (GAMEOPTIONS[0].remake) snd_id = NF_PlayRawSound(31, 127, 64, false, 0);

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

	// Asegurate de que la risa no siga sonando
	if (GAMEOPTIONS[0].remake) soundKill(snd_id);

}