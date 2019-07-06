#ifndef __MENU_H__
#define __MENU_H__



/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de Menu

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



// Funcion MainMenu();
extern u8 MainMenu(void);
// Menu principal del juego



// Funcion MainMenu8bits();
extern u8 MainMenu8bits(void);
// Menu principal 8 bits



// Funcion MainMenu8bitsLoadFiles();
void MainMenu8bitsLoadFiles(void);
// Carga los archivos del menu 8 bits



// Funcion MainMenu8bitsCreate();
void MainMenu8bitsCreate(void);
// Prepara los elementos del menu principal y de opciones de 8 bits



// Funcion MainMenuHq();
extern u8 MainMenuHq(void);
// Menu principal Hq



// Funcion MainMenuHqLoadFiles();
void MainMenuHqLoadFiles(void);
// Carga los archivos del menu Hq



// Funcion MainMenuHqCreate();
void MainMenuHqCreate(void);
// Prepara los elementos del menu principal y de opciones Hq



// Funcion MainMenuHqMenu();
extern u8 MainMenuHqMenu(void);
// Menu principal del juego



// Funcion MainMenuHqOptions();
void MainMenuHqOptions(void);
// Menu de opciones del juego




#endif
