#ifndef __GUI_H__
#define __GUI_H__



/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de la GUI

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





// Funcion GuiMain();
void GuiMain(void);
// Nucleo de ejecucion de la GUI



// Funcion GuiCreate();
void GuiCreate(void);
// Crea la GUI



// Funcion GuiUpdateLiveBar();
void GuiUpdateLiveBar(void);
// Actualiza la barra de energia



// Funcion GuiUpdateLivesCounter();
void GuiUpdateLivesCounter(void);
// Actualiza el contador de vidas



// Funcion GuiPause();
void GuiPause(void);
// Crea el cartel de pausa y escondelo





#endif
