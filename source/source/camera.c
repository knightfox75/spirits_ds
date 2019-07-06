/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones del sistema de camaras

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





// Funcion CameraStart();
void CameraStart(void) {

	// Variables
	u8 n = 0;

	// Reinicia los parametros de las camaras
	CAMERA[0].bg_x = 0, CAMERA[1].bg_x = 0;
	CAMERA[0].current_stage = 0, CAMERA[1].current_stage = 0;
	CAMERA[0].new_stage = 0, CAMERA[1].new_stage = 0;

	// Inicializa camara inferior
	// (la superior sigue siempre por defecto al personaje)
	SUBCAM.available[0] = true;
	SUBCAM.slot = 0;
	for (n = 1; n < 6; n ++) {
		SUBCAM.available[n] = false;
	}

}



// Funcion CameraMain();
void CameraMain(void) {

	// Dependiendo si esta o no activo el minimapa
	if (MINIMAP.active) {
		CameraMinimap();
	} else {
		CameraNormal();
	}

}



// Funcion CameraNormal();
void CameraNormal(void) {

	// Camara Superior
	CameraView(0, CHARACTER.pos_x, CHARACTER.pos_y);

	// Camara Inferior
	CameraView(1, CAMERA[1].cam_x, CAMERA[1].cam_y);

	// Actualiza los sprites
	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);

	// Espera al sincronismo vertical
	swiWaitForVBlank();

	// Actualiza los OAM's de libnds
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);

	// Actualiza los fondos
	CameraUpdateBg();

	// Control de la subcamara (Dejalo listo para el siguiente frame)
	SubcamControl();

}



// Funcion CameraMinimap();
void CameraMinimap(void) {

	// Camara Superior
	CameraView(0, CHARACTER.pos_x, CHARACTER.pos_y);

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
	CameraUpdateBg();

}



// Funcion CameraView();
void CameraView(u8 screen, s32 pos_x, s32 pos_y) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	u8 stage = GetStage(pos_x, pos_y);		// Almacena en que stage esta la coordenada


	/*
	-------------------------------------------------
		Gestion del decorado
	-------------------------------------------------
	*/

	// Obten el stage de la camara
	CAMERA[screen].new_stage = stage;

	// Calcula la posicion del fondo en la pantalla
	CAMERA[screen].bg_x = ((pos_x - 128) - STAGE[stage].stg_left);
	if (CAMERA[screen].bg_x < 0) CAMERA[screen].bg_x = 0;
	if (CAMERA[screen].bg_x > ((STAGE[stage].stg_width - 1) - 256)) CAMERA[screen].bg_x = ((STAGE[stage].stg_width - 1) - 256);


	/*
	-------------------------------------------------
		Gestion de los sprites (Ocultalos)
	-------------------------------------------------
	*/

	// Resetea el flag de visibilidad en la pantalla del personaje
	if (screen == 0) EVENT.on_main_screen = false;

	CameraCharacterHide(screen, stage);		// Personaje
	CameraNpcHide(screen, stage);			// NPC
	CameraItemHide(screen, stage);			// Items
	CameraGoulHide(screen, stage);			// Gouls
	CameraPhantomHide(screen, stage);		// Fantasmas
	CameraWolfHide(screen, stage);			// Lobos
	CatCamHide(screen, stage);				// Gato
	CameraDevilHide(screen, stage);			// Diablo y flecha
	CameraSwitchHide(screen, stage);		// Interruptores
	CameraDoorHide(screen, stage);			// Puertas
	CameraHwallHide(screen, stage);			// Muros mobiles
	CameraTrapHide(screen, stage);			// Trampas
	LampCamHide(screen, stage);				// Lampara
	FiretrapCamHide(screen, stage);			// Hoguera
	SpellCamHide(screen, stage);			// Hechizo
	DragonEyeCamHide(screen, stage);		// Ojos del dragon

	// Solo en modo remake
	if (GAMEOPTIONS[0].remake) {
		CameraTorchHide(screen, stage);		// Antorchas y velas
	}


	/*
	-------------------------------------------------
		Rearme automatico de trampas
	-------------------------------------------------
	*/

	TrapRearm(false);


	/*
	-------------------------------------------------
		Gestion de los sprites (Muestralos)
	-------------------------------------------------
	*/

	CameraCharacterShow(screen, stage);		// Personaje
	CameraNpcShow(screen, stage);			// NPC
	CameraItemShow(screen, stage);			// Items
	CameraGoulShow(screen, stage);			// Gouls
	CameraPhantomShow(screen, stage);		// Fantasmas
	CameraWolfShow(screen, stage);			// Lobos
	CatCamShow(screen, stage);				// Gato
	CameraDevilShow(screen, stage);			// Diablo y flecha
	CameraSwitchShow(screen, stage);		// Interruptores
	CameraDoorShow(screen, stage);			// Puertas
	CameraHwallShow(screen, stage);			// Muros mobiles
	CameraTrapShow(screen, stage);			// Trampas
	LampCamShow(screen, stage);				// Lamparas
	FiretrapCamShow(screen, stage);			// Hogueras
	SpellCamShow(screen, stage);			// Hechizo
	DragonEyeCamShow(screen, stage);		// Ojos del dragon

	// Solo en modo remake
	if (GAMEOPTIONS[0].remake) {
		CameraTorchShow(screen, stage);		// Antorchas y velas
	}

}



// Funcion GetStage();
u8 GetStage(s32 pos_x, s32 pos_y) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	u8 n = 0;			// Uso general
	u8 stage = 0;		// Stage donde estas


	/*
	-------------------------------------------------
		Busca en que Stage esta la coordenada
	-------------------------------------------------
	*/

	// Busca la coordenada en los stages
	for (n = 1; n <= 19; n ++) {
		if (
			(pos_y >= STAGE[n].stg_top)
			&&
			(pos_y <= STAGE[n].stg_bottom)
			&&
			(pos_x >= STAGE[n].stg_left)
			&&
			(pos_x <= STAGE[n].stg_right)
			) {
			// Si coincide, devuelve el resultado
			stage = n;
			n = 19;
		}
	}

	// Devuelve el resultado
	return stage;

}



// Funcion CameraUpdateBg();
void CameraUpdateBg(void) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	u8 screen = 0;		// Pantalla


	/*
	-------------------------------------------------
		Actualiza los fondos
	-------------------------------------------------
	*/

	if (MINIMAP.active) {	/* Con el MINIMAP activo */
		
		// Actualiza la pantalla superior
		if (GAMEOPTIONS[0].remake) {
			CameraUpdateBgHq(0);
		} else {
			CameraUpdateBg8bits(0);
		}
		
		// Actualiza el minimap
		NF_ScrollBg(1, MINIMAP_LAYER, MINIMAP.bg_x, MINIMAP.bg_y);
		NF_ScrollBg(1, MINIMAP_FOG_LAYER, MINIMAP.bg_x, MINIMAP.bg_y);

	} else {				/* Modo normal */

		// Actualiza ambas pantallas
		for (screen = 0; screen < 2; screen ++) {
			if (GAMEOPTIONS[0].remake) {
				CameraUpdateBgHq(screen);
			} else {
				CameraUpdateBg8bits(screen);
			}
		}

	}

}



// Funcion CameraUpdateBg8bits();
void CameraUpdateBg8bits(u8 screen) {

	// Variables
	char bgname[16];		// Id del fondo

	// Actualiza el fondo si es necesario
	if (CAMERA[screen].current_stage != CAMERA[screen].new_stage) {
		// Elimina los fondos previamente creados
		DeleteBackgrounds(screen, false, true, false, false);
		// Crea el nuevo fondo
		sprintf(bgname, "stg%02d", CAMERA[screen].new_stage);
		NF_CreateTiledBg(screen, SPRITES_LAYER, bgname);
		CAMERA[screen].current_stage = CAMERA[screen].new_stage;
	}

	// Actualiza el scroll
	NF_ScrollBg(screen, SPRITES_LAYER, CAMERA[screen].bg_x, 0);

}



// Funcion CameraUpdateBgHq();
void CameraUpdateBgHq(u8 screen) {

	// Variables
	char bgname[16];		// Id del fondo
	s32 pos_x[4];

	// Actualiza el fondo si es necesario
	if (CAMERA[screen].current_stage != CAMERA[screen].new_stage) {

		// Elimina los fondos previamente creados
		DeleteBackgrounds(screen, false, true, true, true);

		// Crea capa principal
		sprintf(bgname, "stg%02d_1", CAMERA[screen].new_stage);
		NF_CreateTiledBg(screen, BG_MAIN_LAYER, bgname);
		// Crea capa secundaria
		sprintf(bgname, "stg%02d_2", CAMERA[screen].new_stage);
		NF_CreateTiledBg(screen, BG_SUB_LAYER, bgname);

		// Crea capa decorado
		if (CAMERA[screen].new_stage != 19) NF_CreateTiledBg(screen, BG_SCENE_LAYER, STAGE[CAMERA[screen].new_stage].bg3name);

		// Actualiza el Stage actual
		CAMERA[screen].current_stage = CAMERA[screen].new_stage;

	}

	// Calcula el efecto parallax
	pos_x[1] = CAMERA[screen].bg_x;
	pos_x[2] = ((pos_x[1] * 6) >> 3);
	pos_x[3] = ((pos_x[2] * 6) >> 3);

	// Fix de posicion
	if (CAMERA[screen].current_stage == 9) pos_x[3] += 216;
	if ((CAMERA[screen].current_stage == 19) && screen == 0) {
		pos_x[2] = CAMERA[screen].bg_x;
		pos_x[3] = CAMERA[screen].bg_x;
	}

	// Actualiza el scroll
	NF_ScrollBg(screen, BG_MAIN_LAYER, pos_x[STAGE[CAMERA[screen].current_stage].bg_speed[BG_MAIN_LAYER]], 0);
	NF_ScrollBg(screen, BG_SUB_LAYER, pos_x[STAGE[CAMERA[screen].current_stage].bg_speed[BG_SUB_LAYER]], 0);
	NF_ScrollBg(screen, BG_SCENE_LAYER, pos_x[STAGE[CAMERA[screen].current_stage].bg_speed[BG_SCENE_LAYER]], 0);

}



// Funcion SubcamControl();
void SubcamControl(void) {

	// Si se ha disparado algun evento...
	if (EVENT.active && !EVENT.on_main_screen) {

		CAMERA[1].cam_x = EVENT.pos_x, CAMERA[1].cam_y = EVENT.pos_y;

	} else {	// Si no hay algun evento fuera de pantalla, subcam normal

		// Si pulsas R, siguiente item
		if (KEYPRESS.r && !KEYPRESS.l) {
			SUBCAM.slot ++;
			if (SUBCAM.slot > 5) SUBCAM.slot = 0;
			while(!SUBCAM.available[SUBCAM.slot]) {
				SUBCAM.slot ++;
				if (SUBCAM.slot > 5) SUBCAM.slot = 0;
			}
		}

		// Si pulsas L, item anterior
		if (!KEYPRESS.r && KEYPRESS.l) {
			SUBCAM.slot --;
			if (SUBCAM.slot < 0) SUBCAM.slot = 5;
			while(!SUBCAM.available[SUBCAM.slot]) {
				SUBCAM.slot --;
				if (SUBCAM.slot < 0) SUBCAM.slot = 5;
			}
		}

		// Pasa las coordenadas a la sub-cam, dependiendo del objetivo a seguir
		switch (SUBCAM.slot) {
			case 0:		// Bola de cristal
				CAMERA[1].cam_x = CRISTALLBALL.cam_x, CAMERA[1].cam_y = CRISTALLBALL.cam_y;
				break;
			case 1:		// Libro de hechizos
				CAMERA[1].cam_x = SPELLBOOK.cam_x, CAMERA[1].cam_y = SPELLBOOK.cam_y;
				break;
			case 2:		// Varita magica
				CAMERA[1].cam_x = MAGICWAND.cam_x, CAMERA[1].cam_y = MAGICWAND.cam_y;
				break;
			case 3:		// Armadura
				CAMERA[1].cam_x = ARMOR.pos_x, CAMERA[1].cam_y = ARMOR.pos_y;
				break;
			case 4:		// Princesa
				CAMERA[1].cam_x = PRINCESS.pos_x, CAMERA[1].cam_y = PRINCESS.pos_y;
				break;
			case 5:		// Aguila
				CAMERA[1].cam_x = EAGLE.pos_x, CAMERA[1].cam_y = EAGLE.pos_y;
				break;
			default:	// En caso de error, sigue a la bola
				CAMERA[1].cam_x = CRISTALLBALL.cam_x, CAMERA[1].cam_y = CRISTALLBALL.cam_y;
				break;
		}

	}

}
