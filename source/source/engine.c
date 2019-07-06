/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones del motor del juego

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



// Funcion RunGame();
void RunGame(void) {

	/*
	-------------------------------------------------
		Inicializaciones
	-------------------------------------------------
	*/

	// Resetealo todo
	ResetAll();


	/*
	-------------------------------------------------
		Carga de archivos
	-------------------------------------------------
	*/

	LoadingIn();
	LoadGameFiles();
	LoadingOut();


	/*
	-------------------------------------------------
		Inicializa la partida
	-------------------------------------------------
	*/

	InitGameplay();



	/*
	-------------------------------------------------
		Nucleo de ejecucion del juego
	-------------------------------------------------
	*/

	switch (GameEngine()) {

		// Game Exit (desde la pausa)
		case 0:
			GameExit();
			break;

		// Game Over
		case 1:
			GameOver();
			break;

		// Juego completado
		case 2:
			GameDone();
			break;

		default:
			break;

	}

}



// Funcion InitGameplay();
void InitGameplay(void) {

	// Inicializa los datos
	LoadStartGameData();

	// Crea el entorno grafico
	CreateGameStage();
	GuiPause();

	// Inicializa el control de efectos de sonido y la musica
	SoundInitBgm();
	SoundInitSfx();

	// Thread inicial de ejecucion
	MAINGAME.thread = GAMETHREAD_PLAYGAME;
	MAINGAME.player_alive = true;
	MAINGAME.fade_in = true;
	MAINGAME.fade_out = false;
	MAINGAME.brightness = 0;

	// Reproduce la musica
	BGM.next = MOD_PULULATE;

}


// Funcion GameEngine();
u8 GameEngine(void) {

	// Variables
	bool loop = true;		// Control del bucle de ejecucion
	u8 result = 0;			// Devuelve el resultado de la ejecucion


	/*
	-------------------------------------------------
		Nucleo de ejecucion del juego
	-------------------------------------------------
	*/

	while (loop) {

		// Lee el teclado
		ReadKeypad();

		// Efecto Fade In
		if (MAINGAME.fade_in) {
			MAINGAME.brightness += 64;
			if (MAINGAME.brightness >= (16 << 8)) {
				MAINGAME.brightness = (16 << 8);
				MAINGAME.fade_in = false;
			}
			setBrightness(3, ((MAINGAME.brightness >> 8) - 16));
		}

		// Efecto Fade Out
		if (MAINGAME.fade_out) {
			MAINGAME.brightness += 64;
			if (MAINGAME.brightness >= (16 << 8)) {
				MAINGAME.brightness = (16 << 8);
				MAINGAME.fade_out = false;
			}
			setBrightness(3, -(MAINGAME.brightness >> 8));
		}

		// Segun el hilo de ejecucion
		switch (MAINGAME.thread) {

			// Ejecucion normal del juego
			case GAMETHREAD_PLAYGAME:
				PlayGame();
				break;

			// El jugador a muerto
			case GAMETHREAD_PLAYERDEAD:
				PlayerDead();
				break;

			// Gameover
			case GAMETHREAD_GAMEOVER:
				loop = false;
				result = 1;
				break;

			// Game Complete
			case GAMETHREAD_GAMEEND:
				loop = false;
				result = 2;
				break;

			// Dragon's Lair
			case GAMETHREAD_DRAGONSLAIR:
				DragonEyeMain();
				break;

			// Salida forzada desde la pausa
			case GAMETHREAD_GAMEEXIT:
				loop = false;
				break;

			// Error trap
			default:
				break;

		}

		// Actualiza el GUI
		GuiMain();

		// Control de camaras
		CameraMain();

		// Cancela los eventos dinamicos una vez actualizados en pantalla
		CancelDinamicEvents();

		// Eventos especiales
		SpecialEvents();

	}

	// Devuelve el resultado de la ejecucion
	return result;

}



// Funcion EngineBackgroundProcesses();
void EngineBackgroundProcesses(void) {

	NpcMain();				// Control de los NPC
	EnemyMain();			// Control de los enemigos
	CatMain();				// Control del Gato
	DevilMain();			// Control del diablo
	FiretrapAnim();			// Gestion de las hogueras
	EventMain();			// Gestion de eventos

	// Procesos solo del modo Remake
	if (GAMEOPTIONS[0].remake) {
		TorchAnimation();			// Animacion de las antorchas
		LampAnimation();			// Animacion de las lamparas colgantes
		SoundBgmPlayback();			// Reproduccion de la musica
		SoundVoicePlayback();		// Reproduccion de las voces
		SoundSfxPlayHq();
	} else {
		SoundSfxPlay8bits();		// Efectos de sonido
		BGM.current = BGM.next;		// Evita bugs fuera del modo remake con las BGMs
	}

}



// Funcion EngineBackgroundProcessesIdle();
void EngineBackgroundProcessesIdle(void) {

	FiretrapAnim();			// Gestion de las hogueras

	// Procesos solo del modo Remake
	if (GAMEOPTIONS[0].remake) {
		TorchAnimation();			// Animacion de las antorchas
		LampAnimation();			// Animacion de las lamparas colgantes
		SoundBgmPlayback();			// Reproduccion de la musica
		SoundVoicePlayback();		// Reproduccion de las voces
		SoundSfxPlayHq();
	} else {
		SoundSfxPlay8bits();		// Efectos de sonido
		BGM.current = BGM.next;		// Evita bugs fuera del modo remake con las BGMs
	}

}



// Funcion PlayGame();
void PlayGame(void) {

	CharacterMain();						// Control del personaje
	SpellMain();							// Control del lanzamiento de hechizos
	EngineBackgroundProcesses();			// Procesos comunes
	if (CHEATS.enabled) CheatsInGame();		// Cheats IN-GAME
	CollisionsMain();						// Gestion de colisiones entre sprites
	UpdateMinimapFog();						// Actualiza la niebla del minimapa

	// Control de la vida del personaje
	if (!CharacterLiveControl()) {
		MAINGAME.thread = GAMETHREAD_PLAYERDEAD;
		MAINGAME.player_alive = false;
		MAINGAME.player_dead = 0;
	}

	// Activa o desactiva el minimapa
	if (KEYPRESS.x) {
		// Actualiza el estado
		MINIMAP.active = !MINIMAP.active;
		// Si debes activar el minimapa
		if (MINIMAP.active) {
			DestroySubscreen();		// Destruye el sub-screen
			CreateMinimap();		// Crea el minimapa
		} else {
			DestroyMinimap();		// Destruye el minimapa
		}
	}

	// Pausa del juego?
	if (KEYPRESS.start) {
		if (PauseGame()) MAINGAME.thread = GAMETHREAD_GAMEEXIT;
	}

}



// Funcion PlayerDead();
void PlayerDead(void) {

	// Acciones de la muerte del personaje
	switch (MAINGAME.player_dead) {

		// Prepara la animacion de la muerte
		case 0:
			// Frames a usar
			CHARACTER.frame = 17;
			CHARACTER.frame_cnt = 0;
			// Reproduce el sfx de la muerte
			if (GAMEOPTIONS[0].remake) NF_PlayRawSound(SFX_ID_DEAD, 127, 64, false, 0);
			// Si ha muerto, cambio de musica
			if (CHARACTER.lives == 0) BGM.next = MOD_BLOOD_OF_HATRED;
			// Siguiente thread
			MAINGAME.player_dead = 1;
			break;
		
		// Animacion de la muerte
		case 1:
			// Animacion de muerte (Frames 17 a 20)
			CHARACTER.frame_cnt ++;
			if (CHARACTER.frame_cnt > 5) {
				CHARACTER.frame_cnt = 0;
				CHARACTER.frame ++;
				if (CHARACTER.frame > 20) { 
					CHARACTER.frame = 20;
					// Prepara el fade out
					MAINGAME.fade_out = true;
					MAINGAME.brightness = 0;
					// Y salta al siguiente thread
					MAINGAME.player_dead = 2;
				}
			}
			// Ejecucion de otros elementos comunes
			EngineBackgroundProcesses();
			break;

		// Fade out
		case 2:
			// Ejecucion de otros elementos comunes
			EngineBackgroundProcesses();
			// Si has terminado el fade out...
			if (!MAINGAME.fade_out && ((CHARACTER.lives > 0) || (BGM.current == BGM.next))) {
				// Si quedan vidas...
				if (CHARACTER.lives > 0) {
					MAINGAME.player_dead = 3;
				} else {
					MAINGAME.player_dead = 4;
				}
			}
			break;

		// Renacimiento
		case 3:
			ReviveCharacter();	// Resucita al jugador
			break;

		// Game over
		case 4:
			MAINGAME.thread = GAMETHREAD_GAMEOVER;
			break;

	}

}



// Funcion ReviveCharacter();
void ReviveCharacter(void) {

	// Variables
	u8 id = 0;

	// Restaura la posicion del personaje
	CharacterRestorePos();

	// Y rellena la barra de vida
	CHARACTER.energy = (40 << 3);
	CHARACTER.damage = CHARACTER.energy;
	GUI.update_energy_bar = true;

	// Dale un tiempo de invulnerabilidad
	CHARACTER.immunity = CHARACTER_IMMUNITY;

	// Resetea las lamparas
	for (id = 0; id < LAMP_NUM; id ++) {
		LAMP[id].pos_x = LAMP[id].lamp_x, LAMP[id].pos_y = LAMP[id].lamp_y;
		LAMP[id].pos_fx = (LAMP[id].pos_x << 8), LAMP[id].pos_fy = (LAMP[id].pos_y << 8);
		LAMP[id].activated = false;
		LAMP[id].fall = false;
		LAMP[id].timer = 0;
	}

	// Rearma las trampas
	TrapRearm(true);

	// Cancela si se estava lanzando un hechizo
	SPELL.active = false, SPELL.shot = false;
	SPELL.cancel = false;
	SPELL.speed = 0;
	CHARACTER.spell = false;

	// Reinicia al gato
	CAT.activated = false;
	CAT.timer = ((rand() % CAT_RAND_TIME) + CAT_MIN_TIME);

	// Reinicia al Diablo
	DEVIL.activated = false;
	DEVIL.timer = ((rand() % DEVIL_RAND_TIME) + DEVIL_MIN_TIME);
	ARROW.activated = false;

	// Reinicia la "Guarida del Dragon"
	DRAGONEYE.active = false;

	// Ahora, vuelve a la partida normal
	MAINGAME.thread = GAMETHREAD_PLAYGAME;
	MAINGAME.player_alive = true;
	MAINGAME.fade_in = true;
	MAINGAME.brightness = 0;

}



// Funcion CancelDinamicEvents();
void CancelDinamicEvents(void) {

	// Cancela el Hechizo
	if (SPELL.cancel) {
		SPELL.active = false;
		SPELL.cancel = false;
	}

	// Cancela el gato
	if (CAT.cancel) {
		CAT.activated = false;
		CAT.cancel = false;
	}

	// Cancela la flecha
	if (ARROW.cancel) {
		ARROW.activated = false;
		ARROW.cancel = false;
	}

}



// Funcion SpecialEvents();
void SpecialEvents(void) {

	// Eventos durante el juego
	if (MAINGAME.thread == GAMETHREAD_PLAYGAME) {

		// Si has matado a la Aguila, fin del juego
		if (EAGLE.done) MAINGAME.thread = GAMETHREAD_GAMEEND;

		// Si has entrado en la guarida del dragon...
		if ((CHARACTER.stage == 19) && !DRAGONEYE.active) {
			// Activa el evento
			MAINGAME.thread = GAMETHREAD_DRAGONSLAIR;
			DRAGONEYE.active = true;
			DRAGONEYE.animation = 0;
			DRAGONEYE.frame = 0, DRAGONEYE.frame_cnt = 0;
		}

	}

}



// Funcion PauseGame();
bool PauseGame(void) {

	// Variables
	bool loop = true;
	bool result = false;

	// Muestra el cartel de pausa
	NF_ShowSprite(0, PAUSE_SPRITE, true);
	NF_ShowSprite(0, (PAUSE_SPRITE + 1), true);

	// Bucle
	while (loop) {

		// Lee el teclado
		ReadKeypad();

		// Verifica si debes salir de la pausa
		if (KEYPRESS.start) {
			// Oculta el cartel de pausa
			NF_ShowSprite(0, PAUSE_SPRITE, false);
			NF_ShowSprite(0, (PAUSE_SPRITE + 1), false);
			// Vuelve al juego
			loop = false;
		} else {
			// Sal del juego
			if (KEYPRESS.x) {
				loop = false;
				result = true;
			}
		}

		// Procesos comunes
		CameraMain();

		// Procesos solo del modo Remake
		if (GAMEOPTIONS[0].remake) {
			SoundBgmPlayback();			// Reproduccion de la musica
			SoundVoicePlayback();		// Reproduccion de las voces
			SoundSfxPlayHq();
		} else {
			SoundSfxPlay8bits();		// Efectos de sonido
			BGM.current = BGM.next;		// Evita bugs fuera del modo remake con las BGMs
		}

	}

	// Devuelve si se ha pulsado START o X
	return result;

}



// Funcion GameExit();
void GameExit(void) {

	// Variables
	bool loop = true;
	s16 brightness = 0;

	// Bucle de ejecucion
	while (loop) {

		// Ajuste de brillo
		brightness += 64;
		if (brightness >= (16 << 8)) {
			brightness = (16 << 8);
			loop = false;
		}
		setBrightness(3, -(brightness >> 8));
		if (GAMEOPTIONS[0].remake) BgmVolume(((4096 - brightness) >> 2));

		// Procesos comunes
		CameraMain();

	}

	// Deten la musica
	if (GAMEOPTIONS[0].remake) StopBgm();

	SoundSfxCleanUp();
	SoundBgmCleanUp();
	
}
