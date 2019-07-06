#ifndef __MINIMAP_H__
#define __MINIMAP_H__



/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones del minimapa

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



// Funcion DestroySubscreen();
void DestroySubscreen(void);
// Destruye todos los elementos del subscreen



// Funcion CreateMinimap();
void CreateMinimap(void);
// Crea el minimapa



// Funcion MinimapCamera();
void MinimapCamera(void);
// Gestiona la vision del minimapa



// Funcion DestroyMinimap();
void DestroyMinimap(void);
// Destruye todos los elementos del minimapa



// Funcion UpdateMinimapFog();
void UpdateMinimapFog(void);
// Actualiza la niebla del minimapa





#endif
