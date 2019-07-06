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

// Includes C
#include <stdio.h>
#include <time.h>

// Includes propietarios NDS
#include <nds.h>

// Includes librerias propias
#include <nf_lib.h>

// Includes del juego
#include "includes.h"



// Funcion MainMenu();
u8 MainMenu(void) {

	// Variables
	u8 option = 0;
	bool loop = true;

	// Refresca el random
	srand(time(NULL));

	// Menu
	while (loop) {
		if (GAMEOPTIONS[0].remake) {
			option = MainMenuHq();
		} else {
			option = MainMenu8bits();
		}
		if (option != 2) loop = false;
	}

	// Devuelve el resultado del menu
	return option;

}



// Funcion MainMenu8bits();
u8 MainMenu8bits(void) {

	/*
	-------------------------------------------------
		Inicializaciones
	-------------------------------------------------
	*/

	// Variables
	bool loop = true;					// Control de loop
	s8 mm_option = 0;					// Opcion seleccionada del menu
	s8 opt_option = 0;					// Opcion seleccionada de las opciones
	s8 thread = 0;						// Control
	bool update_thread = false;
	s8 next_thread = 0;
	s32 fade = 0;

	// Carga los archivos
	MainMenu8bitsLoadFiles();

	// Prepara los elementos
	MainMenu8bitsCreate();



	/*
	-------------------------------------------------
		Nucleo de los menus
	-------------------------------------------------
	*/

	while (loop) {

		// Lee el teclado
		ReadKeypad();

		// Arbol de procesos, menu principal y de opciones
		switch (thread) {

			case 0:		// Crea el Main menu
				// Crea los fondos
				if (GAMEOPTIONS[0].language == 0) {
					NF_CreateTiledBg(1, 3, "menu_es");
				} else {
					NF_CreateTiledBg(1, 3, "menu_en");
				}
				// Crea los sprites
				NF_CreateSprite(1, 0, 0, 0, 88, 64);
				NF_SpriteFrame(1, 0, 0);
				NF_SpriteLayer(1, 0, 3);
				// Brillo inicial
				fade = (16 << 8);
				// Siguiente thread
				next_thread = 1;
				update_thread = true;
				break;

			case 1:		// Fade In - Menu principal
				fade -= 64;
				if (fade <= 0) {
					fade = 0;
					next_thread = 2;
					update_thread = true;
				}
				setBrightness(3, (0 - (fade >> 8)));
				break;

			case 2:		// Menu Principal
				// Si has pulsado arriba o abajo
				if (KEYPRESS.up && (mm_option > 0)) mm_option --;
				if (KEYPRESS.down && (mm_option < 3)) mm_option ++;
				// Acepta la opcion del menu
				if ((KEYPRESS.a || KEYPRESS.b || KEYPRESS.x || KEYPRESS.y)) {
					switch (mm_option) {
						case 0:		// Jugar
							next_thread = 3;
							update_thread = true;
							break;
						case 1:		// Manual
							next_thread = 3;
							update_thread = true;
							break;
						case 2:		// Opciones
							next_thread = 4;
							update_thread = true;
							break;
						case 3:		// Creditos
							next_thread = 3;
							update_thread = true;
							break;
					}
				}
				// Actualiza los Sprites en pantalla
				NF_MoveSprite(1, 0, 88, (64 + (mm_option * 24)));
				break;

			case 3:		// Salida del menu principal, devuelve la opcion del menu
				fade += 64;
				if (fade >= (16 << 8)) {
					fade = (16 << 8);
					StopBgm();
					next_thread = 100;
					update_thread = true;
				}
				// Ajusta el brillo
				setBrightness(3, (0 - (fade >> 8)));
				// Si es necesario, ajusta el volumen
				BgmVolume(((4096 - fade) >> 2));
				break;

			case 4:		// Sal del menu principal y prepara el menu de opciones
				fade += 64;
				if (fade >= (16 << 8)) {
					fade = (16 << 8);
					next_thread = 5;
					update_thread = true;
				}
				// Ajusta el brillo
				setBrightness(3, (0 - (fade >> 8)));
				break;

			case 5:		// Elimina el menu principal y prepara el menu de opciones
				// Borra los Sprites antiguos
				NF_DeleteSprite(1, 0);
				// Opcion del menu de opciones por defecto
				opt_option = 0;
				// Crea el nuevo fondo
				if (GAMEOPTIONS[0].language == 0) {
					NF_CreateTiledBg(1, 3, "opt_es");
				} else {
					NF_CreateTiledBg(1, 3, "opt_en");
				}
				// Crea los Sprites del indicador de Remake
				if (GAMEOPTIONS[0].remake) {
					NF_CreateSprite(1, 0, 0, 0, 132, 72);
				} else {
					NF_CreateSprite(1, 0, 0, 0, 36, 72);
				}
				NF_SpriteFrame(1, 0, 1);
				NF_SpriteLayer(1, 0, 3);
				// Crea los Sprites del indicador de Idioma
				if (GAMEOPTIONS[0].language == 0) {
					NF_CreateSprite(1, 1, 0, 0, 60, 120);
				} else {
					NF_CreateSprite(1, 1, 0, 0, 132, 120);
				}
				NF_SpriteFrame(1, 1, 0);
				NF_SpriteLayer(1, 1, 3);
				// Crea los Sprites del indicador de nivel de scanline
				NF_CreateSprite(1, 2, 0, 0, (44 + (GAMEOPTIONS[0].scanlines * 40)), 168);
				NF_SpriteFrame(1, 2, 0);
				NF_SpriteLayer(1, 2, 3);
				// Siguiente thread
				next_thread = 6;
				update_thread = true;
				break;

			case 6:		// Fade In - Menu de opciones
				fade -= 64;
				if (fade <= 0) {
					fade = 0;
					next_thread = 7;
					update_thread = true;
				}
				setBrightness(3, (0 - (fade >> 8)));
				break;

			case 7:		// Menu de opciones
				// Si has pulsado arriba o abajo
				if (KEYPRESS.up && (opt_option > 0)) opt_option --;
				if (KEYPRESS.down && (opt_option < 2)) opt_option ++;
				switch (opt_option) {
					case 0:		// Modo de juego
						// Pasa de modo remake a 8 bits
						if (GAMEOPTIONS[0].remake && KEYPRESS.left) {
							NF_MoveSprite(1, 0, 36, 72);
							GAMEOPTIONS[0].remake = false;
						}
						// Pasa de modo 8 bits a remake
						if (!GAMEOPTIONS[0].remake && KEYPRESS.right) {
							NF_MoveSprite(1, 0, 132, 72);
							GAMEOPTIONS[0].remake = true;
						}
						// Marca esta opcion como seleccionada
						NF_SpriteFrame(1, 0, 1);
						NF_SpriteFrame(1, 1, 0);
						NF_SpriteFrame(1, 2, 0);
						break;
					case 1:		// Idioma
						// Pasa de Ingles a Español
						if ((GAMEOPTIONS[0].language == 1) && KEYPRESS.left) {
							NF_MoveSprite(1, 1, 60, 120);
							NF_CreateTiledBg(1, 3, "opt_es");
							GAMEOPTIONS[0].language = 0;
						}
						// Pasa de Español a Ingles
						if ((GAMEOPTIONS[0].language == 0) && KEYPRESS.right) {
							NF_MoveSprite(1, 1, 132, 120);
							NF_CreateTiledBg(1, 3, "opt_en");
							GAMEOPTIONS[0].language = 1;
						}
						// Marca esta opcion como seleccionada
						NF_SpriteFrame(1, 0, 0);
						NF_SpriteFrame(1, 1, 1);
						NF_SpriteFrame(1, 2, 0);
						break;
					case 2:		// Nivel de Scanline
						if ((GAMEOPTIONS[0].scanlines > 0) && KEYPRESS.left) {
							GAMEOPTIONS[0].scanlines --;
							ScanlinesAlphaLevel();
						}
						if ((GAMEOPTIONS[0].scanlines < 3) && KEYPRESS.right) {
							GAMEOPTIONS[0].scanlines ++;
							ScanlinesAlphaLevel();
						}
						// Marca esta opcion como seleccionada
						NF_MoveSprite(1, 2, (44 + (GAMEOPTIONS[0].scanlines * 40)), 168);
						NF_SpriteFrame(1, 0, 0);
						NF_SpriteFrame(1, 1, 0);
						NF_SpriteFrame(1, 2, 1);
						break;
				}
				// Si se la pulsado A o B
				if ((KEYPRESS.a || KEYPRESS.b || KEYPRESS.x || KEYPRESS.y)) {
					// Guarda las opciones
					WriteSavegame();
					// Dependiendo si se ha cambiado o no el modo de juego
					if (GAMEOPTIONS[0].remake) {
						// Siguiente thread
						next_thread = 3;
						update_thread = true;
					} else {
						// Siguiente thread
						next_thread = 8;
						update_thread = true;
					}
				}
				break;

			case 8:			// Fade Out del Menu de opciones
				fade += 64;
				if (fade >= (16 << 8)) {
					fade = (16 << 8);
					next_thread = 9;
					update_thread = true;
				}
				// Ajusta el brillo
				setBrightness(3, (0 - (fade >> 8)));
				break;

			case 9:			// Elimina el menu de opciones y vuelve al menu principal
				// Elimina los sprites
				NF_DeleteSprite(1, 0);
				NF_DeleteSprite(1, 1);
				NF_DeleteSprite(1, 2);
				// Opcion del menu principal por defecto
				mm_option = 0;
				// Cambio de thread
				next_thread = 0;
				update_thread = true;
				break;

			case 100:		// Sal del menu
				loop = false;
				break;

		}

		// Cambio de thread?
		if (update_thread) {
			thread = next_thread;
			update_thread = false;
		}

		// Sincronismo
		NF_SpriteOamSet(1);
		swiWaitForVBlank();
		oamUpdate(&oamSub);

	}

	// Devuelve el resultado
	return mm_option;

}



// Funcion MainMenu8bitsLoadFiles();
void MainMenu8bitsLoadFiles(void) {

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

	// Carga los fondos
	if (CHEATS.enabled) {
		NF_LoadTiledBg("8bits/menu/bg/m_cheat_8b", "title", 256, 256);
	} else {
		NF_LoadTiledBg("8bits/menu/bg/m_title_8b", "title", 256, 256);
	}
	NF_LoadTiledBg("8bits/menu/bg/m_menu_8b_en", "menu_en", 256, 256);
	NF_LoadTiledBg("8bits/menu/bg/m_menu_8b_es", "menu_es", 256, 256);
	NF_LoadTiledBg("8bits/menu/bg/m_opt_8b_en", "opt_en", 256, 256);
	NF_LoadTiledBg("8bits/menu/bg/m_opt_8b_es", "opt_es", 256, 256);

	// Carga los Sprites
	NF_LoadSpriteGfx("8bits/menu/sprite/m_arrow", 0, 16, 16);
	NF_LoadSpritePal("8bits/menu/sprite/m_arrow", 0);

	// Carga la musica
	LoadBgm(MOD_SPIRITS_8B);

}



// Funcion MainMenu8bitsCreate();
void MainMenu8bitsCreate(void) {

	// Ajuste del brillo
	setBrightness(3, -16);

	// Transfiere los sprites a la VRAM
	NF_VramSpriteGfx(1, 0, 0, false);
	NF_VramSpritePal(1, 0, 0);

	// Crea el titulo
	NF_CreateTiledBg(0, 3, "title");

	// Crea las scanlines
	CreateScanlines();

	// Reproduce la musica
	PlayBgm();

}



// Funcion MainMenuHq();
u8 MainMenuHq(void) {

	/*
	-------------------------------------------------
		Inicializaciones
	-------------------------------------------------
	*/

	// Variables
	u8 menu = 0;		// Opcion devuelta por el menu
	bool loop = true;	// Control del menu


	// Carga los archivos
	MainMenuHqLoadFiles();

	// Prepara los elementos
	MainMenuHqCreate();

	// Nucleo
	while (loop) {

		// Menu Principal
		menu = MainMenuHqMenu();

		if (menu == 2) {
			// Menu de opciones
			MainMenuHqOptions();
			if (!GAMEOPTIONS[0].remake) loop = false;
		} else {
			loop = false;
		}

	}

	// Devuelve el resultado
	return menu;

}



// Funcion MainMenuHqLoadFiles();
void MainMenuHqLoadFiles(void) {

	/*
	-------------------------------------------------
		Inicializaciones
	-------------------------------------------------
	*/

	// Variables
	u8 language = 0;
	char lang[4];
	char filename[64];
	char name[32];
	u8 id = 0;
	u8 n = 0;

	// Resetealo todo
	ResetAll();


	/*
	-------------------------------------------------
		Carga de archivos
	-------------------------------------------------
	*/

	// Carga los fondos (Comunes)
	if (CHEATS.enabled) {
		NF_LoadTiledBg("hq/menu/bg/m_cheat_hq", "title_bg", 256, 256);
	} else {
		NF_LoadTiledBg("hq/menu/bg/m_title_hq", "title_bg", 256, 256);
	}
	NF_LoadTiledBg("hq/menu/bg/m_menu_hq_bg", "menu_bg", 256, 256);
	NF_LoadTiledBg("hq/menu/bg/m_opt_hq_bg", "opt_bg", 256, 256);

	// Segun idioma
	for (language = 0; language <= 1; language ++) {
		switch (language) {
			case 0:
				sprintf(lang, "es");
				break;
			case 1:
				sprintf(lang, "en");
				break;
		}

		// Fondos - Menu
		sprintf(filename, "hq/menu/bg/m_menu_hq_text_%s", lang);
		sprintf(name, "menu_%s", lang);
		NF_LoadTiledBg(filename, name, 256, 256);

		// Fondos - Opciones
		sprintf(filename, "hq/menu/bg/m_opt_hq_text_%s", lang);
		sprintf(name, "opt_%s", lang);
		NF_LoadTiledBg(filename, name, 256, 256);

		// Sprites
		for (n = 1; n <= 3; n ++) {
			sprintf(filename, "hq/menu/sprite/mb%02d_%s", n, lang);
			NF_LoadSpriteGfx(filename, id, 32, 16);
			id ++;
		}

		// Paletas de Sprites
		sprintf(filename, "hq/menu/sprite/mmbutton_%s", lang);
		NF_LoadSpritePal(filename, language);

	}

	// Carga Sprites de los enemigos
	id = 21;
	for (n = 1; n <= 3; n ++) {
		sprintf(filename, "hq/game/sprite/pal03/spr%02d", n);
		NF_LoadSpriteGfx(filename, id, 64, 64);
		id ++;
	}
	NF_LoadSpritePal("hq/game/sprite/pal/pal03", 3);
	// Carga Sprites de los NPC
	for (n = 4; n <= 5; n ++) {
		sprintf(filename, "hq/game/sprite/pal01/spr%02d", n);
		NF_LoadSpriteGfx(filename, id, 64, 64);
		id ++;
	}
	NF_LoadSpriteGfx("hq/game/sprite/pal01/spr10", id, 64, 64);
	NF_LoadSpritePal("hq/game/sprite/pal/pal01", 5);

	// Carga Sprites Menu de opciones
	NF_LoadSpriteGfx("hq/menu/sprite/omb", 30, 64, 64);
	NF_LoadSpritePal("hq/menu/sprite/omb", 4);

	// Carga Sprites Menu de opciones
	NF_LoadSpriteGfx("hq/menu/sprite/omb_mark", 31, 32, 64);
	NF_LoadSpritePal("hq/menu/sprite/omb_mark", 2);

	// Carga la musica
	LoadBgm(MOD_SPIRITS_HQ);

}



// Funcion MainMenuHqCreate();
void MainMenuHqCreate(void) {

	// Variables
	u8 n = 0;

	// Ajuste del brillo
	setBrightness(3, -16);

	// Transfiere los sprites a la VRAM
	// 0 - 5 > Botones menu principal
	for (n = 0; n < 6; n ++) {
		NF_VramSpriteGfx(1, n, n, false);
	}
	// 21 - 23 > Enemigos
	// 24 - 26 > NPC
	for (n = 21; n <= 26; n ++) {
		NF_VramSpriteGfx(1, n, n, true);
	}
	// 30 > Botones del menu de opciones
	NF_VramSpriteGfx(1, 30, 30, false);
	NF_VramSpriteGfx(1, 31, 31, false);

	// Transfiere las paletas a la VRAM
	// 0 - 1 > Botones menu principal
	// 2 - Marcador menu opciones
	// 3 - Enemigos
	// 4 - Botones del menu de opciones
	// 5 - NPC
	for (n = 0; n <= 5 ; n ++) {
		NF_VramSpritePal(1, n, n);
	}

	// Crea el titulo
	NF_CreateTiledBg(0, 3, "title_bg");

	// Reproduce la musica
	PlayBgm();

}



// Funcion MainMenuHqMenu();
u8 MainMenuHqMenu(void) {

	// Variables
	u8 gfx = 0;			// Id de grafico de sprite
	u8 spr = 0;			// Id de sprite
	u8 pal = 0;			// Paleta

	s8 op = 0;			// Opciones del menu
	s8 last_op = 0;

	bool loop = true;	// Loop del menu

	s32 fade = 0;			// Control del fade
	bool fade_in = false;
	bool fade_out = false;

	// Control de los sprites de los enemigos moviendose
	typedef struct {
		u8 spr;
		s32 x;
		s32 y;
		s32 fx;
		s32 fy;
		u8 frame;
		u8 frame_cnt;
		u8 anim_speed;
		s32 speed;
		bool flip;
	} enemy_info;
	enemy_info enemy[3];

	// Control tactil del menu
	typedef struct {
		s16 bx[4];
		s16 by[4];
		bool newpress;
	} touch_info;
	touch_info touch;

	u8 n = 0;			// Variables

	// Parametros iniciales del goul
	enemy[0].spr = 21;
	enemy[0].x = (int)(rand() % 256), enemy[0].y = 110;
	enemy[0].fx = (enemy[0].x << 8), enemy[0].fy = (enemy[0].y << 8);
	enemy[0].frame = (int)(rand() % 4), enemy[0].frame_cnt = 0, enemy[0].anim_speed = 7; 
	if (((int)(rand() % 100)) > 50) {
		enemy[0].speed = 256;
		enemy[0].flip = false;
	} else {
		enemy[0].speed = -256;
		enemy[0].flip = true;
	}
	// Parametros iniciales del fantasma
	enemy[1].spr = 22;
	enemy[1].x = (int)(rand() % 256), enemy[1].y = 20;
	enemy[1].fx = (enemy[1].x << 8), enemy[1].fy = (enemy[1].y << 8);
	enemy[1].frame = (int)(rand() % 4), enemy[1].frame_cnt = 0, enemy[1].anim_speed = 9;
	if (((int)(rand() % 100)) > 50) {
		enemy[1].speed = 224;
		enemy[1].flip = false;
	} else {
		enemy[1].speed = -224;
		enemy[1].flip = true;
	}
	// Parametros iniciales del hombre lobo
	enemy[2].spr = 23;
	enemy[2].x = (int)(rand() % 256), enemy[2].y = 110;
	enemy[2].fx = (enemy[2].x << 8), enemy[2].fy = (enemy[2].y << 8);
	enemy[2].frame = (int)(rand() % 4), enemy[2].frame_cnt = 0, enemy[2].anim_speed = 6;
	if (((int)(rand() % 100)) > 50) {
		enemy[2].speed = 288;
		enemy[2].flip = false;
	} else {
		enemy[2].speed = -288;
		enemy[2].flip = true;
	}


	// Crea los fondos
	NF_CreateTiledBg(1, 3, "menu_bg");
	if (GAMEOPTIONS[0].language == 0) {
		NF_CreateTiledBg(1, 2, "menu_es");
	} else {
		NF_CreateTiledBg(1, 2, "menu_en");
	}

	// Crea los Sprites del menu
	if (GAMEOPTIONS[0].language == 0) {
		gfx = 0;
		pal = 0;
	} else {
		gfx = 3;
		pal = 1;
	}
	for (n = 0; n < 4; n ++) {
		// Registra la coordenada del primer sprite del boton
		touch.bx[n] = (56 + (n << 4));
		touch.by[n] = (72 + (n * 24));
		// Crea los sprites
		NF_CreateSprite (1, spr, gfx, pal, (56 + (n << 4)), (72 + (n * 24)));
		NF_SpriteLayer(1, spr, 2);
		NF_CreateSprite (1, (spr + 1), (gfx + 1), pal, (56 + 32 + (n << 4)), (72 + (n * 24)));
		NF_SpriteLayer(1, (spr + 1), 2);
		NF_CreateSprite (1, (spr + 2), (gfx + 2), pal, (56 + 64 + (n << 4)), (72 + (n * 24)));
		NF_SpriteLayer(1, (spr + 2), 2);
		spr += 3;
	}

	// Pon los frames tocan a cada sprite del menu
	for (n = 0; n < 4; n ++) {
		if (op == n) {
			gfx = 4;
		} else {
			gfx = 0;
		}
		for (spr = 0; spr < 3; spr ++) {
			NF_SpriteFrame(1, (spr + (n * 3)), (n + gfx));
		}
	}

	// Crea los Sprites de los enemigos
	for (n = 0; n < 3; n ++) {
		NF_CreateSprite(1, enemy[n].spr, enemy[n].spr, 3, enemy[n].x, enemy[n].y);
		NF_SpriteLayer(1, enemy[n].spr, 3);
		NF_SpriteFrame(1, enemy[n].spr, enemy[n].frame);
		NF_HflipSprite(1, enemy[n].spr, enemy[n].flip);
	}

	// Sincronismo (Actualiza el contenido de la pantalla)
	ReadKeypad();
	ReadTouchpad();
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamSub);

	// Inicializaciones del menu
	fade = (16 <<8 );
	fade_in = true;
	fade_out = false;
	if (TOUCHPAD.held) {
		touch.newpress = false;
	} else {
		touch.newpress = true;
	}

	// Bucle del menu
	while (loop) {

		// Lee el teclado
		ReadKeypad();
		ReadTouchpad();

		// Selecciona una opcion del menu
		if (!fade_out) {
			if (KEYPRESS.up && (op > 0)) op --;
			if (KEYPRESS.down && (op < 3)) op ++;
		}

		// Si se pulsa A o B o X o Y, acepta la opcion seleccionada
		if ((KEYPRESS.a || KEYPRESS.b || KEYPRESS.x || KEYPRESS.y) && !fade_in && !fade_out) fade_out = true;

		// Control tactil del menu
		if (TOUCHPAD.held) {
			if (touch.newpress) {
				// Marca que se ha tocado la pantalla
				touch.newpress = false;
				// Si no hay efecto fade activo
				if (!fade_in && !fade_out) {
					// Mira si se ha tocado algun boton valido
					for (n = 0; n < 4; n ++) {
						if (
							(TOUCHPAD.pos_x >= touch.bx[n])
							&&
							(TOUCHPAD.pos_x <= (touch.bx[n] + 96))
							&&
							(TOUCHPAD.pos_y >= touch.by[n])
							&&
							(TOUCHPAD.pos_y <= (touch.by[n] + 16))
							) {
							// Opcion valida
							op = n;
							fade_out = true;
							n = 4;
						}
					}
				}
			}
		} else {
			// Si se ha levantado el lapiz, nuevo toque listo
			touch.newpress = true;
		}

		// Si es necesario, actualiza los botones del menu
		if (op != last_op) {
			for (n = 0; n < 4; n ++) {
				if (op == n) {
					gfx = 4;
				} else {
					gfx = 0;
				}
				for (spr = 0; spr < 3; spr ++) {
					NF_SpriteFrame(1, (spr + (n * 3)), (n + gfx));
				}
			}
			last_op = op;
		}

		// Movimientos de los enemigos
		for (n = 0; n < 3; n ++) {
			// Desplazamiento en pantalla
			enemy[n].fx += enemy[n].speed;
			enemy[n].x = (enemy[n].fx >> 8);
			if ((enemy[n].fx < -(63 << 8)) || (enemy[n].fx > (255 << 8))) {
				enemy[n].speed = -enemy[n].speed;
				enemy[n].flip = !enemy[n].flip;
			}
			// Animacion
			enemy[n].frame_cnt ++;
			if (enemy[n].frame_cnt > enemy[n].anim_speed) {
				enemy[n].frame_cnt = 0;
				enemy[n].frame ++;
				if (enemy[n].frame > 3) enemy[n].frame = 0;
			}
			// Actualiza el sprite
			NF_MoveSprite(1, enemy[n].spr, enemy[n].x, enemy[n].y);
			NF_SpriteFrame(1, enemy[n].spr, enemy[n].frame);
			NF_HflipSprite(1, enemy[n].spr, enemy[n].flip);
		}

		// Fade IN
		if (fade_in) {
			fade -= 64;
			if (fade <= 0) {
				fade = 0;
				fade_in = false;
			}
			setBrightness(3, (0 - (fade >> 8)));
		}

		// Fade OUT
		if (fade_out) {
			fade += 64;
			if (fade >= (16 << 8)) {
				fade = (16 << 8);
				fade_out = false;
				loop = false;
				if (op != 2) StopBgm();
			}
			// Ajusta el brillo
			setBrightness(3, (0 - (fade >> 8)));
			// Si es necesario, ajusta el volumen
			if (op != 2) BgmVolume(((4096 - fade) >> 2));
		}

		// Sincronismo
		NF_SpriteOamSet(1);
		swiWaitForVBlank();
		oamUpdate(&oamSub);

	}

	// Eliminacion del menu
	// - Borra fondos
	NF_DeleteTiledBg(1, 2);
	NF_DeleteTiledBg(1, 3);
	// - Borra sprites
	spr = 0;
	for (n = 0; n < 4; n ++) {
		NF_DeleteSprite (1, spr);
		NF_DeleteSprite (1, (spr + 1));
		NF_DeleteSprite (1, (spr + 2));
		spr += 3;
	}
	for (n = 0; n < 3; n ++) {
		NF_DeleteSprite(1, enemy[n].spr);
	}
	// - Sincronismo (Actualiza el contenido de la pantalla)
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamSub);

	// Devuelve el resultado
	return op;

}



// Funcion MainMenuHqOptions();
void MainMenuHqOptions(void) {

	// Variables
	s8 op = 0;			// Opciones del menu
	s8 last_op = 0;

	bool loop = true;	// Loop del menu

	s32 fade = 0;			// Control del fade
	bool fade_in = false;
	bool fade_out = false;

	u8 n = 0;

	// Control de los sprites de los enemigos moviendose
	typedef struct {
		u8 spr;
		s32 x;
		s32 y;
		s32 fx;
		s32 fy;
		u8 frame;
		u8 frame_cnt;
		u8 anim_speed;
		s32 speed;
		bool flip;
	} enemy_info;
	enemy_info enemy[3];

	// Control tactil del menu
	typedef struct {
		s16 bx[4];
		s16 by[4];
		bool newpress;
		s16 opt;
	} touch_info;
	touch_info touch;

	// Parametros iniciales de la Armadura
	enemy[0].spr = 24;
	enemy[0].x = (int)(rand() % 128), enemy[0].y = 110;
	enemy[0].fx = (enemy[0].x << 8), enemy[0].fy = (enemy[0].y << 8);
	enemy[0].frame = (int)(rand() % 4), enemy[0].frame_cnt = 0, enemy[0].anim_speed = 6; 
	if (((int)(rand() % 100)) > 50) {
		enemy[0].speed = 256;
		enemy[0].flip = false;
	} else {
		enemy[0].speed = -256;
		enemy[0].flip = true;
	}
	// Parametros iniciales de la princesa
	enemy[1].spr = 25;
	enemy[1].x = (((int)(rand() % 128)) + 127), enemy[1].y = 110;
	enemy[1].fx = (enemy[1].x << 8), enemy[1].fy = (enemy[1].y << 8);
	enemy[1].frame = (int)(rand() % 4), enemy[1].frame_cnt = 0, enemy[1].anim_speed = 6;
	if (((int)(rand() % 100)) > 50) {
		enemy[1].speed = 256;
		enemy[1].flip = false;
	} else {
		enemy[1].speed = -256;
		enemy[1].flip = true;
	}
	// Parametros iniciales del Aguila
	enemy[2].spr = 26;
	enemy[2].x = (int)(rand() % 256), enemy[2].y = 20;
	enemy[2].fx = (enemy[2].x << 8), enemy[2].fy = (enemy[2].y << 8);
	enemy[2].frame = (int)(rand() % 4), enemy[2].frame_cnt = 0, enemy[2].anim_speed = 9;
	if (((int)(rand() % 100)) > 50) {
		enemy[2].speed = 192;
		enemy[2].flip = false;
	} else {
		enemy[2].speed = -192;
		enemy[2].flip = true;
	}


	// Crea los fondos
	NF_CreateTiledBg(1, 3, "opt_bg");
	if (GAMEOPTIONS[0].language == 0) {
		NF_CreateTiledBg(1, 2, "opt_es");
	} else {
		NF_CreateTiledBg(1, 2, "opt_en");
	}

	// Crea los Sprites del menu
	NF_CreateSprite (1, 10, 30, 4, 64, 48);
	NF_SpriteLayer(1, 10, 2);
	NF_CreateSprite (1, 11, 30, 4, 144, 48);
	NF_SpriteLayer(1, 11, 2);
	NF_CreateSprite (1, 12, 30, 4, 64, 120);
	NF_SpriteLayer(1, 12, 2);
	NF_CreateSprite (1, 13, 30, 4, 144, 120);
	NF_SpriteLayer(1, 13, 2);

	if (GAMEOPTIONS[0].remake) {
		NF_CreateSprite (1, 0, 31, 2, 176, 48);
		NF_SpriteLayer(1, 0, 2);
	} else {
		NF_CreateSprite (1, 0, 31, 2, 96, 48);
		NF_SpriteLayer(1, 0, 2);
	}

	if (GAMEOPTIONS[0].language == 0) {
		NF_CreateSprite (1, 1, 31, 2, 96, 120);
		NF_SpriteLayer(1, 1, 2);
	} else {
		NF_CreateSprite (1, 1, 31, 2, 176, 120);
		NF_SpriteLayer(1, 1, 2);
	}



	// Pon los frames tocan a cada sprite del menu
	if (op == 0) {
		NF_SpriteFrame(1, 10, 1);
		NF_SpriteFrame(1, 11, 3);
		NF_SpriteFrame(1, 12, 4);
		NF_SpriteFrame(1, 13, 6);
		NF_SpriteFrame(1, 0, 1);
		NF_SpriteFrame(1, 1, 0);
	} else {
		NF_SpriteFrame(1, 10, 0);
		NF_SpriteFrame(1, 11, 2);
		NF_SpriteFrame(1, 12, 5);
		NF_SpriteFrame(1, 13, 7);
		NF_SpriteFrame(1, 0, 0);
		NF_SpriteFrame(1, 1, 1);
	}


	// Crea los Sprites de los enemigos
	for (n = 0; n < 3; n ++) {
		NF_CreateSprite(1, enemy[n].spr, enemy[n].spr, 5, enemy[n].x, enemy[n].y);
		NF_SpriteLayer(1, enemy[n].spr, 3);
		NF_SpriteFrame(1, enemy[n].spr, enemy[n].frame);
		NF_HflipSprite(1, enemy[n].spr, enemy[n].flip);
	}

	// Sincronismo (Actualiza el contenido de la pantalla)
	ReadKeypad();
	ReadTouchpad();
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamSub);

	// Inicializaciones del menu
	fade = (16 <<8 );
	fade_in = true;
	fade_out = false;

	if (TOUCHPAD.held) {
		touch.newpress = false;
	} else {
		touch.newpress = true;
	}
	touch.bx[0] = 72, touch.by[0] = 48;
	touch.bx[1] = 152, touch.by[1] = 48;
	touch.bx[2] = 72, touch.by[2] = 120;
	touch.bx[3] = 152, touch.by[3] = 120;

	// Bucle del menu
	while (loop) {

		// Lee el teclado
		ReadKeypad();
		ReadTouchpad();

		// Selecciona una opcion del menu
		if (!fade_out) {
			if (KEYPRESS.up && (op > 0)) op --;
			if (KEYPRESS.down && (op < 1)) op ++;
			if (op == 0) {
				if (GAMEOPTIONS[0].remake) {
					if (KEYPRESS.left) {
						NF_MoveSprite(1, 0, 96, 48);
						GAMEOPTIONS[0].remake = false;
					}
				} else {
					if (KEYPRESS.right) {
						NF_MoveSprite(1, 0, 176, 48);
						GAMEOPTIONS[0].remake = true;
					}
				}
			} else {
				if (GAMEOPTIONS[0].language == 0) {
					if (KEYPRESS.right) {
						NF_MoveSprite(1, 1, 176, 120);
						NF_DeleteTiledBg(1, 2);
						NF_CreateTiledBg(1, 2, "opt_en");
						GAMEOPTIONS[0].language = 1;
					}
				} else {
					if (KEYPRESS.left) {
						NF_MoveSprite(1, 1, 96, 120);
						NF_DeleteTiledBg(1, 2);
						NF_CreateTiledBg(1, 2, "opt_es");
						GAMEOPTIONS[0].language = 0;
					}
				}
			}
		}

		// Si se pulsa A o B o X o Y, acepta la opcion seleccionada
		if ((KEYPRESS.a || KEYPRESS.b || KEYPRESS.x || KEYPRESS.y) && !fade_in && !fade_out) fade_out = true;

		// Control tactil del menu
		if (TOUCHPAD.held) {
			if (touch.newpress) {
				// Marca que se ha tocado la pantalla
				touch.newpress = false;
				// Si no hay efecto fade activo
				if (!fade_in && !fade_out) {
					// Mira si se ha tocado algun boton valido
					touch.opt = 255;
					for (n = 0; n < 4; n ++) {
						if (
							(TOUCHPAD.pos_x >= touch.bx[n])
							&&
							(TOUCHPAD.pos_x <= (touch.bx[n] + 48))
							&&
							(TOUCHPAD.pos_y >= touch.by[n])
							&&
							(TOUCHPAD.pos_y <= (touch.by[n] + 64))
							) {
							// Opcion valida
							touch.opt = n;
							n = 4;
						}
					}
					// Segun lo que se ha tocado...
					switch (touch.opt) {
						case 0:		// 8 bits
							op = 0;
							NF_MoveSprite(1, 0, 96, 48);
							GAMEOPTIONS[0].remake = false;
							break;
						case 1:		// Remake
							op = 0;
							NF_MoveSprite(1, 0, 176, 48);
							GAMEOPTIONS[0].remake = true;
							break;
						case 2:		// ESP
							op = 1;
							NF_MoveSprite(1, 1, 96, 120);
							NF_DeleteTiledBg(1, 2);
							NF_CreateTiledBg(1, 2, "opt_es");
							GAMEOPTIONS[0].language = 0;
							break;
						case 3:		// ENG
							op = 1;
							NF_MoveSprite(1, 1, 176, 120);
							NF_DeleteTiledBg(1, 2);
							NF_CreateTiledBg(1, 2, "opt_en");
							GAMEOPTIONS[0].language = 1;
							break;
						case 255:	// Sal del menu
							fade_out = true;
							break;
					}
				}
			}
		} else {
			// Si se ha levantado el lapiz, nuevo toque listo
			touch.newpress = true;
		}

		// Si es necesario, actualiza los botones del menu
		if (op != last_op) {
			if (op == 0) {
				NF_SpriteFrame(1, 10, 1);
				NF_SpriteFrame(1, 11, 3);
				NF_SpriteFrame(1, 12, 4);
				NF_SpriteFrame(1, 13, 6);
				NF_SpriteFrame(1, 0, 1);
				NF_SpriteFrame(1, 1, 0);
			} else {
				NF_SpriteFrame(1, 10, 0);
				NF_SpriteFrame(1, 11, 2);
				NF_SpriteFrame(1, 12, 5);
				NF_SpriteFrame(1, 13, 7);
				NF_SpriteFrame(1, 0, 0);
				NF_SpriteFrame(1, 1, 1);
			}
			last_op = op;
		}


		// Movimientos de los enemigos
		for (n = 0; n < 3; n ++) {
			// Desplazamiento en pantalla
			enemy[n].fx += enemy[n].speed;
			enemy[n].x = (enemy[n].fx >> 8);
			if ((enemy[n].fx < -(63 << 8)) || (enemy[n].fx > (255 << 8))) {
				enemy[n].speed = -enemy[n].speed;
				enemy[n].flip = !enemy[n].flip;
			}
			// Animacion
			enemy[n].frame_cnt ++;
			if (enemy[n].frame_cnt > enemy[n].anim_speed) {
				enemy[n].frame_cnt = 0;
				enemy[n].frame ++;
				if (enemy[n].frame > 3) enemy[n].frame = 0;
			}
			// Actualiza el sprite
			NF_MoveSprite(1, enemy[n].spr, enemy[n].x, enemy[n].y);
			NF_SpriteFrame(1, enemy[n].spr, enemy[n].frame);
			NF_HflipSprite(1, enemy[n].spr, enemy[n].flip);
		}

		// Fade IN
		if (fade_in) {
			fade -= 64;
			if (fade <= 0) {
				fade = 0;
				fade_in = false;
			}
			setBrightness(3, (0 - (fade >> 8)));
		}

		// Fade OUT
		if (fade_out) {
			fade += 64;
			if (fade >= (16 << 8)) {
				fade = (16 << 8);
				fade_out = false;
				loop = false;
				if (!GAMEOPTIONS[0].remake) StopBgm();
			}
			// Ajusta el brillo
			setBrightness(3, (0 - (fade >> 8)));
			// Si es necesario, ajusta el volumen
			if (!GAMEOPTIONS[0].remake) BgmVolume(((4096 - fade) >> 2));
		}

		// Sincronismo
		NF_SpriteOamSet(1);
		swiWaitForVBlank();
		oamUpdate(&oamSub);

	}

	// Eliminacion del menu
	// - Borra fondos
	NF_DeleteTiledBg(1, 2);
	NF_DeleteTiledBg(1, 3);
	// - Borra sprites
	for (n = 0; n < 3; n ++) {
		NF_DeleteSprite(1, enemy[n].spr);
	}
	for (n = 10; n <= 13; n ++) {
		NF_DeleteSprite(1, n);
	}
	for (n = 0; n <= 1; n ++) {
		NF_DeleteSprite(1, n);
	}
	// - Sincronismo (Actualiza el contenido de la pantalla)
	NF_SpriteOamSet(1);
	swiWaitForVBlank();
	oamUpdate(&oamSub);

	// Guarda las opciones
	WriteSavegame();

}