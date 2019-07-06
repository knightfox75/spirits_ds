#ifndef __SYSTEM_H__
#define __SYSTEM_H__

/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de sistema

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



// Funcion BootGame();
void BootGame(void);
// Inicializa el engine del juego



// Funcion ReadKeypad();
void ReadKeypad(void);
// Lee el keypad y actualiza el array de datos del mismo



// Funcion ReadTouchpad();
void ReadTouchpad(void);
// Lee el TOUCHPAD y actualiza el array de datos del mismo



// Funcion FadeIn();
void FadeIn(u8 screen, u16 speed);
// Efecto FadeIn en ambas pantallas
// Toma el control del programa hasta finalizar la ejecuccion



// Funcion FadeOut();
void FadeOut(u8 screen, u16 speed);
// Efecto FadeOut en ambas pantallas
// Toma el control del programa hasta finalizar la ejecuccion



// Funcion WaitTime();
void WaitTime(u16 wait);
// Espera los frames indicados
// Toma el control del programa hasta finalizar la ejecucion



// Funcion ResetAll();
void ResetAll(void);
// Vacia todos los buffers



// Funcions UpdateBothScreens2D();
void UpdateBothScreens2D(void);
// Actualiza los Sprites (2D) y espera al sincronismo



// Funcion UpdateSprite();
void UpdateSprite(u8 screen, u8 sprite, u8 gfx, u8 pal);
// Cambia el grafico y paleta para el Sprite dado



// Funcion GetCurrentDate();
void GetCurrentDate(u32* day, u32* month, u32* year);
// Obten la fecha actual



// Funcion GetBgRamId();
extern u8 GetBgRamId(const char* name);
// Devuelve la ID del buffer en RAM donde esta el fondo solicitado



// Funcion GetBgTileAddress();
extern u32 GetBgTileAddress(u16 tile_x, u16 tile_y, u8 ramslot);
// Devuelve la direccion donde esta el tile solicitado en el buffer



// Funcion GetBgTile();
extern u16 GetBgTile(u16 tile_x, u16 tile_y, u8 ramslot);
// Devuelve el valor del tile de la posicion solicitada



// Funcion SetBgTile();
void SetBgTile(u16 tile_x, u16 tile_y, u16 tile, u8 ramslot);
// Cambia el valor del tile de la posicion solicitada



// Funcion CreateScanlines();
void CreateScanlines(void);
// Carga y crea las scanlines


// Funcion DeleteScanlines();
void DeleteScanlines(void);
// Borra las scanlines



// Funcion ScanlinesAlphaLevel();
void ScanlinesAlphaLevel(void);
// Nivel de alpha de la pantalla de scanlines



// Funcion DeleteBackgrounds();
void DeleteBackgrounds(u8 screen, bool layer0, bool layer1, bool layer2, bool layer3);
// Limpieza de los fondos creados



// Funcion SystemError();
void SystemError(const char* text);
// Error critico (Debug)



// Funcion VramUsage();
void VramUsage(void);
// Estado de la VRAM (Debug)



#endif
