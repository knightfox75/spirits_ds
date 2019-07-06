/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones del manual - Inicializaciones

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




// Funcion HowToLoad();
void HowToLoad(void) {

	// Variables
	FILE* file_id;			// Puntero de fichero
	char filename[128];		// Variable para almacenar el path al archivo
	char lang[4];			// Idioma

	/*
	-------------------------------------------------
		Carga los archivos del juego para crear
		la simulacion
	-------------------------------------------------
	*/

	LoadingIn();
	LoadGameFiles();
	LoadingOut();


	/*
	-------------------------------------------------
		Carga los archivos del tutorial para
		la simulacion
	-------------------------------------------------
	*/

	// Fondos
	if (GAMEOPTIONS[0].remake) {
		NF_LoadTiledBg("howto/hq/bg/papyre_hq", "papyre", 256, 256);
	} else {
		NF_LoadTiledBg("howto/8bits/bg/papyre_8b", "papyre", 256, 256);
	}

	// Sprites
	if (GAMEOPTIONS[0].remake) {
		NF_LoadSpriteGfx("howto/hq/sprite/button_a_hq", 100, 32, 32);
		NF_LoadSpritePal("howto/hq/sprite/button_a_hq", 30);
	} else {
		NF_LoadSpriteGfx("howto/8bits/sprite/button_a_8b", 100, 32, 32);
		NF_LoadSpritePal("howto/8bits/sprite/button_a_8b", 30);
	}

	// Fuentes
	NF_LoadTextFont16("howto/text/tutorial", "tutorial", 256, 256, 0);

	// Carga el archivo de texto
	if (GAMEOPTIONS[0].language) {
		sprintf(lang, "en");
	} else {
		sprintf(lang, "es");
	}
	sprintf(filename, "%s/howto/text/tutorial_%s.txt", NF_ROOTFOLDER, lang);
	file_id = fopen(filename, "rb");
	if (file_id) {	// Si el archivo existe...
		// Obten el tamaño del archivo
		fseek(file_id, 0, SEEK_END);
		TUTORIAL.text_size = ftell(file_id);
		rewind(file_id);
		// Reserva el espacio en RAM
		TUTORIAL.text_buffer = (char*) calloc (TUTORIAL.text_size, sizeof(char));
		if (TUTORIAL.text_buffer == NULL) {		// Si no hay suficiente RAM libre
			NF_Error(102, NULL, TUTORIAL.text_size);
		}
		// Lee el archivo y ponlo en la RAM
		fread(TUTORIAL.text_buffer, 1, TUTORIAL.text_size, file_id);
	} else {	// Si el archivo no existe...
		NF_Error(101, filename, 0);
	}
	fclose(file_id);		// Cierra el archivo

}


// Funcion HowToInit();
void HowToInit(void) {

	// Inicializa el juego para la simulacion
	LoadStartGameData();

	// Crea el entorno
	HowToCreate();

	// Thread inicial de ejecucion de la simulacion
	MAINGAME.thread = 0;
	MAINGAME.player_alive = false;
	MAINGAME.fade_in = true;
	MAINGAME.fade_out = false;
	MAINGAME.brightness = 0;

	// Control del texto del tutorial
	TUTORIAL.text_pos = 0;
	TUTORIAL.page_active = false;
	TUTORIAL.eof = false;

	// Musica que sonara en el tutorial
	BGM.next = MOD_PULULATE;

}



// Funcion HowToCreate();
void HowToCreate(void) {

	/*
	-------------------------------------------------
		Tareas especificas de cada modo
	-------------------------------------------------
	*/

	if (GAMEOPTIONS[0].remake) {
		NF_VramSpriteGfx(1, ID_TORCH, TORCH_SPR_ID, false);
		NF_VramSpriteGfx(1, ID_FLAME, FLAME_SPR_ID, false);
	} else {
		CreateScanlines();		// Crea los fondos para el efecto scanlines
	}


	/*
	-------------------------------------------------
		Paletas de la simulacion
	-------------------------------------------------
	*/

	if (GAMEOPTIONS[0].remake) {	// Modo Remake

		// Paleta Character
		NF_VramSpritePal(1, CHARACTER_SPR_PAL, CHARACTER_SPR_PAL);
		// Paleta Items
		NF_VramSpritePal(1, ITEM_SPR_PAL, ITEM_SPR_PAL);
		// Paleta NPC
		NF_VramSpritePal(1, NPC_SPR_PAL, NPC_SPR_PAL);
		// Paleta Enemigos
		NF_VramSpritePal(1, ENEMY_SPR_PAL, ENEMY_SPR_PAL);
		// Paleta Enemigos especiales
		NF_VramSpritePal(1, DEVIL_SPR_PAL, DEVIL_SPR_PAL);
		// Paleta Interruptores
		NF_VramSpritePal(1, SWITCH_SPR_PAL, SWITCH_SPR_PAL);
		// Paleta Puertas
		NF_VramSpritePal(1, DOOR_SPR_PAL, DOOR_SPR_PAL);
		// Paleta Muros mobiles
		NF_VramSpritePal(1, HWALL_SPR_PAL, HWALL_SPR_PAL);
		// Paleta Trampas
		NF_VramSpritePal(1, TRAP_SPR_PAL, TRAP_SPR_PAL);
		// Paleta Lamparas
		NF_VramSpritePal(1, LAMP_SPR_PAL, LAMP_SPR_PAL);
		// Paleta Hogueras
		NF_VramSpritePal(1, FIRETRAP_SPR_PAL, FIRETRAP_SPR_PAL);

	} else {	// Modo original

		// Paleta Character
		NF_VramSpritePal(1, SPRITE_8BITS_PAL, CHARACTER_SPR_PAL);
		// Paleta Items
		NF_VramSpritePal(1, SPRITE_8BITS_PAL, ITEM_SPR_PAL);
		// Paleta NPC
		NF_VramSpritePal(1, SPRITE_8BITS_PAL, NPC_SPR_PAL);
		// Paleta Enemigos
		NF_VramSpritePal(1, SPRITE_8BITS_PAL, ENEMY_SPR_PAL);
		// Paleta Enemigos especiales
		NF_VramSpritePal(1, SPRITE_8BITS_PAL, DEVIL_SPR_PAL);
		// Paleta Interruptores
		NF_VramSpritePal(1, SPRITE_8BITS_PAL, SWITCH_SPR_PAL);
		// Paleta Puertas
		NF_VramSpritePal(1, SPRITE_8BITS_PAL, DOOR_SPR_PAL);
		// Paleta Muros mobiles
		NF_VramSpritePal(1, SPRITE_8BITS_PAL, HWALL_SPR_PAL);
		// Paleta Trampas
		NF_VramSpritePal(1, SPRITE_8BITS_PAL, TRAP_SPR_PAL);
		// Paleta Lamparas
		NF_VramSpritePal(1, SPRITE_8BITS_PAL, LAMP_SPR_PAL);
		// Paleta Hogueras
		NF_VramSpritePal(1, SPRITE_8BITS_PAL, FIRETRAP_SPR_PAL);

	}


	/*
	-------------------------------------------------
		Paletas de la GUI y Minimapa
	-------------------------------------------------
	*/

	if (GAMEOPTIONS[0].remake) {	// Modo Remake
		// Paleta GUI
		NF_VramSpritePal(1, GUI_SPR_PAL, GUI_SPR_PAL);
		// Paleta Minimapa
		NF_VramSpritePal(1, MINIMAP_SPR_PAL, MINIMAP_SPR_PAL);
	} else {
		// Paleta GUI
		NF_VramSpritePal(1, SPRITE_8BITS_PAL, GUI_SPR_PAL);
		// Paleta Minimapa
		NF_VramSpritePal(1, SPRITE_8BITS_PAL, MINIMAP_SPR_PAL);
	}


	/*
	-------------------------------------------------
		Creacion del entorno de la simulacion
	-------------------------------------------------
	*/

	GuiCreate();										// Crea la GUI en la pantalla inferior
	CHARACTER.pos_x = 624;								// Posicion inicial del personaje para le tutorial
	CHARACTER.pos_fx = (CHARACTER.pos_x << 8);
	HowToCamera(CHARACTER.pos_x, CHARACTER.pos_y);		// Genera los fondos y sprites del juego para la simulacion


	/*
	-------------------------------------------------
		Creacion del GUI de la pantalla superior
	-------------------------------------------------
	*/

	// Fondos en la pantalla superior
	NF_CreateTiledBg(0, 3, "papyre");

	// Capa de texto
	NF_CreateTextLayer16(0, 2, 0, "tutorial");
	if (GAMEOPTIONS[0].remake) {
		NF_DefineTextColor(0, 2, 0, 0, 0, 0);
	} else {
		NF_DefineTextColor(0, 2, 0, 31, 31, 31);
	}

	// Sprites (BOTON A)
	NF_VramSpriteGfx(0, 100, 0, false);
	NF_VramSpritePal(0, 30, 0);
	NF_CreateSprite(0, 0, 0, 0, 215, 151);
	NF_SpriteLayer(0, 0, 2);
	NF_ShowSprite(0, 0, false);



	/*
	-------------------------------------------------
		Sonido
	-------------------------------------------------
	*/

	// Inicializa el control de efectos de sonido y la musica
	SoundInitBgm();
	SoundInitSfx();

}




