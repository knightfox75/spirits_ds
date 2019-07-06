/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones del manual - Engine

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
#include <string.h>

// Includes propietarios NDS
#include <nds.h>

// Includes librerias propias
#include <nf_lib.h>

// Includes del juego
#include "includes.h"




// Funcion HowToEngine();
void HowToEngine(u16 camera) {

	// Variables
	s32 cam_x, cam_y;

	CharacterMain();				// Control del personaje
	SpellMain();					// Control del lanzamiento de hechizos
	EngineBackgroundProcesses();	// Procesos comunes
	CollisionsMain();				// Gestion de colisiones entre sprites
	UpdateMinimapFog();				// Actualiza la niebla del minimapa

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

	// Actualiza el GUI
	CHARACTER.energy = (40 << 3);
	CHARACTER.damage = CHARACTER.energy;
	GuiMain();

	// Sigue a este objetivo indicado
	switch (camera) {
		case 1:
			cam_x = SPELLBOOK.cam_x;
			cam_y = SPELLBOOK.cam_y;
			break;
		case 2:
			cam_x = MAGICWAND.cam_x;
			cam_y = MAGICWAND.cam_y;
			break;
		case 3:
			cam_x = PRINCESS.pos_x;
			cam_y = PRINCESS.pos_y;
			break;
		case 4:
			cam_x = ARMOR.pos_x;
			cam_y = ARMOR.pos_y;
			break;
		case 5:
			cam_x = EAGLE.pos_x;
			cam_y = EAGLE.pos_y;
			break;
		default:
			cam_x = CHARACTER.pos_x;
			cam_y = CHARACTER.pos_y;
			break;
	}

	// Posicion de la camara
	HowToCamera(cam_x, cam_y);

	// Cancela los eventos dinamicos una vez actualizados en pantalla
	CancelDinamicEvents();

}



// Funcion HowToCamera();
void HowToCamera(s32 pos_x, s32 pos_y) {

	if (MINIMAP.active) {

		// Camara del Minimapa
		MinimapCamera();

		// Actualiza los sprites
		NF_SpriteOamSet(0);
		NF_SpriteOamSet(1);

		// Espera al sincronismo vertical
		swiWaitForVBlank();

		// Actualiza los OAM's de libnds
		oamUpdate(&oamMain);
		oamUpdate(&oamSub);

		// Actualiza los fondos
		HowToUpdateBg();

	} else {
	
		// Camara Superior
		CameraView(1, pos_x, pos_y);

		// Actualiza los sprites
		NF_SpriteOamSet(0);
		NF_SpriteOamSet(1);

		// Espera al sincronismo vertical
		swiWaitForVBlank();

		// Actualiza los OAM's de libnds
		oamUpdate(&oamMain);
		oamUpdate(&oamSub);

		// Actualiza los fondos
		HowToUpdateBg();

	}

}



// Funcion HowToUpdateBg();
void HowToUpdateBg(void) {

	/*
	-------------------------------------------------
		Actualiza los fondos
	-------------------------------------------------
	*/

	if (MINIMAP.active) {	/* Con el MINIMAP activo */
				
		// Actualiza el minimap
		NF_ScrollBg(1, MINIMAP_LAYER, MINIMAP.bg_x, MINIMAP.bg_y);
		NF_ScrollBg(1, MINIMAP_FOG_LAYER, MINIMAP.bg_x, MINIMAP.bg_y);

	} else {				/* Modo normal */

		if (GAMEOPTIONS[0].remake) {
			CameraUpdateBgHq(1);
		} else {
			CameraUpdateBg8bits(1);
		}

	}

}



// Funcion HowToKeypadOverride();
void HowToKeypadOverride(void) {

	// Resetea los valores de KEYPRESS
	KEYPRESS.up = false;
	KEYPRESS.down = false;
	KEYPRESS.left = false;
	KEYPRESS.right = false;
	KEYPRESS.a = false;
	KEYPRESS.b = false;
	KEYPRESS.x = false;
	KEYPRESS.y = false;
	KEYPRESS.r = false;
	KEYPRESS.l = false;
	KEYPRESS.start = false;
	KEYPRESS.select = false;

	// Resetea los valores de KEYHELD
	KEYHELD.up = false;
	KEYHELD.down = false;
	KEYHELD.left = false;
	KEYHELD.right = false;
	KEYHELD.a = false;
	KEYHELD.b = false;
	KEYHELD.x = false;
	KEYHELD.y = false;
	KEYHELD.r = false;
	KEYHELD.l = false;
	KEYHELD.start = false;
	KEYHELD.select = false;

}



// TutorialGetTextPage();
void TutorialGetTextPage(void) {

	// Variables
	bool endofpage = false;			// Flag de fin de pagina
	u16 row = 0;					// Fila
	u16 column = 0;					// Columna


	// Si aun no se ha alcanzado el final del archivo...
	if (!TUTORIAL.eof) {

		// Resetea el buffer de texto
		memset(TUTORIAL.page, 0, sizeof(TUTORIAL.page));

		// Crea una pagina
		while (!endofpage) {

			// Si no es fin de linea...
			if (TUTORIAL.text_buffer[TUTORIAL.text_pos] != 0x0D) {

				// Segun el caracter leido....
				switch (TUTORIAL.text_buffer[TUTORIAL.text_pos]) {
					case 0x3E:		// >	Siguiente pagina
						// Muevete mas alla del siguiente salto de linea
						TUTORIAL.text_pos += 2;
						// Guarda el numero de lineas de la pagina
						TUTORIAL.lines = row;
						// Marca el final de pagina de texto
						endofpage = true;
						break;
					case 0x3C:		// <	Fin de texto
						// Guarda el numero de lineas de la pagina
						TUTORIAL.lines = row;
						// Marca el final de pagina de texto
						endofpage = true;
						TUTORIAL.eof = true;
						break;
					default:		// Imprime el caracter
						TUTORIAL.page[row][column] = TUTORIAL.text_buffer[TUTORIAL.text_pos];
						column ++;
						if (column > 28) column = 28;	// Limite de la linea (error trap)
						break;
				}

				// Siguiente caracter en el buffer
				TUTORIAL.text_pos ++;

			} else {

				// Salta los dos caracteres del retorno de linea
				TUTORIAL.text_pos += 2;
				// Y salta de linea en el buffer de texto
				row ++;
				column = 0;
				// Verifica los limites de lineas (error trap)
				if (row == 9) {
					TUTORIAL.lines = row;
					endofpage = true;
				}

			}

			// Hecho esto, limpia la pantalla
			NF_ClearTextLayer16(0, 2);

			// Y calcula las variables a usar
			TUTORIAL.char_x = 0;
			TUTORIAL.char_y = 0;
			TUTORIAL.characters = strlen(TUTORIAL.page[0]);
			TUTORIAL.pos_x = (15 - (TUTORIAL.characters >> 1));
			TUTORIAL.pos_y = (5 - (TUTORIAL.lines >> 1));
			TUTORIAL.page_active = true;

		}

	}
	
}



// Funcion TutorialWritePage();
void TutorialWritePage(void) {

	// Variables
	char text[2];

	// Si esta activa la escritura de la pagina...
	if (TUTORIAL.page_active) {
		// Escribe la letra actual
		text[0] = TUTORIAL.page[TUTORIAL.char_y][TUTORIAL.char_x];
		text[1] = '\0';
		NF_WriteText16(0, 2, TUTORIAL.pos_x, TUTORIAL.pos_y, text);
		NF_UpdateTextLayers();
		// Siguiente letra
		TUTORIAL.char_x ++;
		if (TUTORIAL.char_x >= TUTORIAL.characters) {
			// Si hay un cambio de linea
			TUTORIAL.char_x = 0;
			TUTORIAL.char_y ++;
			if (TUTORIAL.char_y >= TUTORIAL.lines) {
				// Si es el final de pagina
				TUTORIAL.page_active = false;
			} else {
				// Calculos para la linea nueva
				TUTORIAL.pos_y ++;
				TUTORIAL.characters = strlen(TUTORIAL.page[TUTORIAL.char_y]);
				TUTORIAL.pos_x = (15 - (TUTORIAL.characters >> 1));
			}
		} else {
			TUTORIAL.pos_x ++;
		}
	}

}
