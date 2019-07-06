#ifndef __ENGINE_H__
#define __ENGINE_H__



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

// Includes propietarios NDS
#include <nds.h>



// Funcion RunGame();
void RunGame(void);
// Nucleo principal de ejecuccion del juego



// Funcion InitGameplay();
void InitGameplay(void);
// Inicializa el engine para una nueva partida



// Funcion GameEngine();
extern u8 GameEngine(void);
// Motor del juego



// Funcion EngineBackgroundProcesses();
void EngineBackgroundProcesses(void);
// Ejecuta todos los procesos de segundo plano durante la partida
// Enemigos, animaciones, eventos, etc.



// Funcion EngineBackgroundProcessesIdle();
void EngineBackgroundProcessesIdle(void);
// Ejecuta todos los procesos de segundo plano durante la partida
// Animaciones y gestion de sonidos pendientes.



// Funcion PlayGame();
void PlayGame(void);
// Ejecucion normal del juego



// Funcion PlayerDead();
void PlayerDead(void);
// Gestiona la muerte del personaje



// Funcion ReviveCharacter();
void ReviveCharacter(void);
// Revive al personaje despues de su muerte



// Funcion CancelDinamicEvents();
void CancelDinamicEvents(void);
// Cancela los eventos dinamicos marcados para ser eliminados



// Funcion SpecialEvents();
void SpecialEvents(void);
// Gestion de eventos especiales



// Funcion PauseGame();
extern bool PauseGame(void);
// Funcion de pausa del juego



// Funcion GameExit();
void GameExit(void);
// Salida del juego (forzada desde la pausa)





#endif
