#ifndef __ITEM_H__
#define __ITEM_H__



/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de gestion de los items

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




// Funcion GetCristallball();
void GetCristallball(void);
// Obten la Bola de cristal



// Funcion GetSpellbook();
void GetSpellbook(void);
// Obten el libro de hechizos



// Funcion GetMagicwand();
void GetMagicwand(void);
// Obten la varita magica



// Funcion CameraItemHide();
void CameraItemHide(u8 screen, u8 stage);
// Ocultacion de los Items



// Funcion CameraItemShow();
void CameraItemShow(u8 screen, u8 stage);
// Muestra los Items



// Funcion CristallballCamHide();
void CristallballCamHide(u8 screen, u8 stage);
// Oculta la bola y su pedestal



// Funcion CristallballCamShow();
void CristallballCamShow(u8 screen, u8 stage);
// Muestra la bola y su pedestal



// Funcion SpellbookCamHide();
void SpellbookCamHide(u8 screen, u8 stage);
// Oculta el libro y su pedestal;



// Funcion SpellbookCamShow();
void SpellbookCamShow(u8 screen, u8 stage);
// Muestra el libro y su pedestal



// Funcion MagicwandCamHide();
void MagicwandCamHide(u8 screen, u8 stage);
// Oculta la Varita magica



// Funcion MagicwandCamShow();
void MagicwandCamShow(u8 screen, u8 stage);
// Muestra la varita magica





#endif
