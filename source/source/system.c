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



// Includes C
#include <stdio.h>
#include <time.h>

// Includes propietarios NDS
#include <nds.h>

// Includes NightFox's Lib
#include <nf_lib.h>

//Incluye las librerias del juego
#include "includes.h"



// Funcion BootGame();
void BootGame(void) {

	// Pantalla de espera inicializando NitroFS
	NF_Set2D(0, 0);
	NF_Set2D(1, 0);	
	consoleDemoInit();
	if (NF_GetLanguage() == 5) {
		iprintf("\n Iniciando NitroFS,\n por favor, espere.\n");
	} else {
		iprintf("\n NitroFS init. Please wait.\n");
	}
	swiWaitForVBlank();

	// Define el ROOT e inicializa el sistema de archivos
	NF_SetRootFolder("NITROFS");	// Define la carpeta ROOT para usar NitroFS

	// Inicializa el motor 2D
	NF_Set2D(0, 0);				// Modo 2D_0 en ambas pantallas
	NF_Set2D(1, 0);	

	// Inicializa el sonido (MAXMOD & libnds)
	InitSound();
	NF_InitRawSoundBuffers();	// Inicializa los buffers de sonido

	// Inicializa los fondos tileados
	NF_InitTiledBgBuffers();	// Inicializa los buffers para almacenar fondos
	NF_InitTiledBgSys(0);		// Inicializa los fondos Tileados para la pantalla superior
	NF_InitTiledBgSys(1);		// Iniciliaza los fondos Tileados para la pantalla inferior

	// Inicializa los Sprites
	NF_InitSpriteBuffers();			// Inicializa los buffers para almacenar sprites y paletas
	NF_InitSpriteSys(0, 128);		// Inicializa los sprites para la pantalla superior
	NF_InitSpriteSys(1, 128);		// Inicializa los sprites para la pantalla inferior

	// Inicializa los mapas de colision
	NF_InitCmapBuffers();

	// Inicializa el engine de texto
	NF_InitTextSys(0);
	NF_InitTextSys(1);

	// Define el color del backdrop a negro en ambas pantallas
	setBackdropColor(0);
	setBackdropColorSub(0);


	/*
	-------------------------------------------------
		Inicializaciones de Spirits DS
	-------------------------------------------------
	*/

	// Datos generales del juego
	LoadGameDefaultData();

}



// Funcion ReadKeypad();
void ReadKeypad(void) {

	// Variables
	u16 keys = 0;

	// Lee el teclado via Libnds
	scanKeys();

	// Teclas "HELD"
	keys = keysHeld();
	if (keys & KEY_UP) {KEYHELD.up = true;} else {KEYHELD.up = false;}
	if (keys & KEY_DOWN) {KEYHELD.down = true;} else {KEYHELD.down = false;}
	if (keys & KEY_LEFT) {KEYHELD.left = true;} else {KEYHELD.left = false;}
	if (keys & KEY_RIGHT) {KEYHELD.right = true;} else {KEYHELD.right = false;}
	if (keys & KEY_A) {KEYHELD.a = true;} else {KEYHELD.a = false;}
	if (keys & KEY_B) {KEYHELD.b = true;} else {KEYHELD.b = false;}
	if (keys & KEY_X) {KEYHELD.x = true;} else {KEYHELD.x = false;}
	if (keys & KEY_Y) {KEYHELD.y = true;} else {KEYHELD.y = false;}
	if (keys & KEY_L) {KEYHELD.l = true;} else {KEYHELD.l = false;}
	if (keys & KEY_R) {KEYHELD.r = true;} else {KEYHELD.r = false;}
	if (keys & KEY_START) {KEYHELD.start = true;} else {KEYHELD.start = false;}
	if (keys & KEY_SELECT) {KEYHELD.select = true;} else {KEYHELD.select = false;}

	// Teclas "PRESS"
	keys = keysDown();
	if (keys & KEY_UP) {KEYPRESS.up = true;} else {KEYPRESS.up = false;}
	if (keys & KEY_DOWN) {KEYPRESS.down = true;} else {KEYPRESS.down = false;}
	if (keys & KEY_LEFT) {KEYPRESS.left = true;} else {KEYPRESS.left = false;}
	if (keys & KEY_RIGHT) {KEYPRESS.right = true;} else {KEYPRESS.right = false;}
	if (keys & KEY_A) {KEYPRESS.a = true;} else {KEYPRESS.a = false;}
	if (keys & KEY_B) {KEYPRESS.b = true;} else {KEYPRESS.b = false;}
	if (keys & KEY_X) {KEYPRESS.x = true;} else {KEYPRESS.x = false;}
	if (keys & KEY_Y) {KEYPRESS.y = true;} else {KEYPRESS.y = false;}
	if (keys & KEY_L) {KEYPRESS.l = true;} else {KEYPRESS.l = false;}
	if (keys & KEY_R) {KEYPRESS.r = true;} else {KEYPRESS.r = false;}
	if (keys & KEY_START) {KEYPRESS.start = true;} else {KEYPRESS.start = false;}
	if (keys & KEY_SELECT) {KEYPRESS.select = true;} else {KEYPRESS.select = false;}

	// Teclas "UP"
	keys = keysUp();
	if (keys & KEY_UP) {KEYUP.up = true;} else {KEYUP.up = false;}
	if (keys & KEY_DOWN) {KEYUP.down = true;} else {KEYUP.down = false;}
	if (keys & KEY_LEFT) {KEYUP.left = true;} else {KEYUP.left = false;}
	if (keys & KEY_RIGHT) {KEYUP.right = true;} else {KEYUP.right = false;}
	if (keys & KEY_A) {KEYUP.a = true;} else {KEYUP.a = false;}
	if (keys & KEY_B) {KEYUP.b = true;} else {KEYUP.b = false;}
	if (keys & KEY_X) {KEYUP.x = true;} else {KEYUP.x = false;}
	if (keys & KEY_Y) {KEYUP.y = true;} else {KEYUP.y = false;}
	if (keys & KEY_L) {KEYUP.l = true;} else {KEYUP.l = false;}
	if (keys & KEY_R) {KEYUP.r = true;} else {KEYUP.r = false;}
	if (keys & KEY_START) {KEYUP.start = true;} else {KEYUP.start = false;}
	if (keys & KEY_SELECT) {KEYUP.select = true;} else {KEYUP.select = false;}

}



// Funcion ReadTouchpad();
void ReadTouchpad(void) {

	// Variables
	u16 keys = 0;
	touchPosition touchscreen;

	// Lee el teclado via Libnds
	scanKeys();

	// Verifica el estado del touchscreen
	keys = keysHeld();
	if (keys & KEY_TOUCH) {TOUCHPAD.held = true;} else {TOUCHPAD.held = false;}

	// Lee el TOUCHPAD via Libnds
	touchRead(&touchscreen); 

	// Guarda el estado del touchscreen
	TOUCHPAD.pos_x = touchscreen.px;
	TOUCHPAD.pos_y = touchscreen.py;
	TOUCHPAD.raw_x = touchscreen.rawx;
	TOUCHPAD.raw_y = touchscreen.rawy;
	TOUCHPAD.press_a = touchscreen.z1;
	TOUCHPAD.press_b = touchscreen.z2;

}



// Funcion FadeIn();
void FadeIn(u8 screen, u16 speed) {
	// Brillo Inicial
	s16 brillo = (16 << 8);
	// Mientras el brillo no llegue a 0
	while (brillo > 0) {
		brillo -= speed;
		// Si ya has subido el brillo
		if (brillo <= 0) {
			brillo = 0;
		}
		// Aplica el valor del brillo 
		setBrightness(screen, (0 - (brillo >> 8)));
		swiWaitForVBlank();
	}
}



// Funcion FadeOut();
void FadeOut(u8 screen, u16 speed) {
	// Brillo Inicial
	s16 brillo = 0;
	// Mientras el brillo no llegue a 0
	while (brillo < (16 << 8)) {
		brillo += speed;
		// Si ya has subido el brillo
		if (brillo >= (16 << 8)) {
			brillo = (16 << 8);
		}
		// Aplica el valor del brillo 
		setBrightness(screen, (0 - (brillo >> 8)));
		swiWaitForVBlank();
	}
}



// Funcion WaitTime();
void WaitTime(u16 wait) {
	s16 timer = 0;
	while (timer < wait) {
		timer ++;
		if (timer >= wait) {
			timer = wait;
		}
		swiWaitForVBlank();
	}
}



// Funcion ResetBuffers();
void ResetAll(void) {

	// Variables locales
	u8 screen = 0;
	u8 layer = 0;

	// La pantalla principal es la superior
	lcdMainOnTop();

	// Resetea el modo grafico a 0 en ambas pantallas
	NF_Set2D(0, 0);
	NF_Set2D(1, 0);

	// Borra los buffers de Fondos
	NF_ResetTiledBgBuffers();

	// Borra los buffers de Sprites
	NF_ResetSpriteBuffers();

	// Reinicializa los fondos
	NF_InitTiledBgSys(0);
	NF_InitTiledBgSys(1);

	// Reinicializa los Sprites
	NF_InitSpriteSys(0, 128);
	NF_InitSpriteSys(1, 128);

	// Reinicia los mapas de colisiones
	NF_ResetCmapBuffers();

	// Reinicializa las capas de texto
	NF_InitTextSys(0);
	NF_InitTextSys(1);

	// Reinicia los buffers de sonido (libnds)
	NF_ResetRawSoundBuffers();

	// Elimina los posibles efectos de Alpha Blending
	REG_BLDCNT = BLEND_NONE;
	REG_BLDCNT_SUB = BLEND_NONE;
	REG_BLDALPHA = 0x0F | (0x0F << 8);
	REG_BLDALPHA_SUB = 0x0F | (0x0F << 8);

	// Restaura el color del backdrop a negro en ambas pantallas
	setBackdropColor(0);
	setBackdropColorSub(0);

	// Resetea la posicion de todas las capas de fondo
	for (screen = 0; screen < 2; screen ++) {
		for (layer = 0; layer < 4; layer ++) {
			NF_ScrollBg(screen, layer, 0, 0);
		}
	}

}



// Funcions UpdateBothScreens2D();
void UpdateBothScreens2D(void) {

	NF_SpriteOamSet(0);
	NF_SpriteOamSet(1);

	swiWaitForVBlank();

	oamUpdate(&oamMain);
	oamUpdate(&oamSub);

}



// Funcion UpdateSprite();
void UpdateSprite(u8 screen, u8 sprite, u8 gfx, u8 pal) {

	// Guarda las coordenadas
	s16 x = NF_SPRITEOAM[screen][sprite].x;
	s16 y = NF_SPRITEOAM[screen][sprite].y;

	// Borra el Sprite actual
	NF_DeleteSprite(screen, sprite);

	// Crea el nuevo Sprite
	NF_CreateSprite(screen, sprite, gfx, pal, x, y);

}



// Funcion GetCurrentDate();
void GetCurrentDate(u32* day, u32* month, u32* year) {

	// Variables
	time_t rawtime;
	struct tm * timeinfo;
	time (&rawtime);
	timeinfo = localtime(&rawtime);

	// Opten la fecha
	*day = timeinfo->tm_mday;
	*month = (timeinfo->tm_mon + 1);
	*year = (timeinfo->tm_year + 1900); 

}



// Funcion GetBgRamId();
u8 GetBgRamId(const char* name) {

	// Variables
	u8 n = 0;			// Bucle
	u8 slot = 255;		// Slot seleccionado
	char bg[32];		// Nombre

	// Busca el fondo solicitado
	sprintf(bg, "%s", name);							// Obten el nombre del fondo a buscar
	for (n = 0; n < NF_SLOTS_TBG; n ++) {				// Busca en todos los slots
		if (strcmp(bg, NF_TILEDBG[n].name) == 0) {		// Si lo encuentras
			slot = n;									// Guarda el slot a usar
			n = NF_SLOTS_TBG;							// Deja de buscar
		}
	}

	// Devuleve la ID
	return slot;

}



// Funcion GetBgTileAddress();
u32 GetBgTileAddress(u16 tile_x, u16 tile_y, u8 ramslot) {

	// Obtiene las medidas en tiles del mapa
	u16 size_x = (NF_TILEDBG[ramslot].width >> 3);		// Tiles de ancho
	u16 block_x = (tile_x >> 5);						// nº de pantalla (X)
	u16 block_y = (tile_y >> 5);						// nº de pantalla (Y)
	u32 row_size = ((size_x >> 5) << 11);				// Tamaño en bytes de una fila de pantallas

	// Calcula la posicion de memoria que deberas leer
	// El mapa esta ordenado en bloques de 32x32 tiles, en filas.
	u32 scr_y = (block_y * row_size);				// Desplazamiento en memoria, bloques de pantallas (32x32) sobre Y
	u32 scr_x = (block_x << 11);					// Desplazamiento en memoria, bloques de pantallas (32x32) sobre X
	u32 tls_y = ((tile_y - (block_y << 5)) << 5);	// Desplazamiento en memoria, tiles sobre X
	u32 tls_x = (tile_x - (block_x << 5));			// Desplazamiento en memoria, tiles sobre Y
	u32 address =  scr_y + scr_x + ((tls_y + tls_x) << 1); 

	// Devuelve el la direccion en el buffer del Tile
	return address;

}



// Funcion GetBgTile();
u16 GetBgTile(u16 tile_x, u16 tile_y, u8 ramslot) {

	// Obten la direccion en el buffer del Tile
	u32 address = GetBgTileAddress(tile_x, tile_y, ramslot);

	// Obten los bytes
	u16 lobyte = *(NF_BUFFER_BGMAP[ramslot] + address);
	u16 hibyte = *(NF_BUFFER_BGMAP[ramslot] + (address + 1));

	// Devuelve el valor del tile
	return ((hibyte << 8) + lobyte);

}



// Funcion SetBgTile();
void SetBgTile(u16 tile_x, u16 tile_y, u16 tile, u8 ramslot) {

	// Obten la direccion en el buffer del Tile
	u32 address = GetBgTileAddress(tile_x, tile_y, ramslot);

	// Calcula los valores para el HI-Byte y el LO-Byte
	u16 hibyte = (tile >> 8);
	u16 lobyte = tile - (hibyte << 8);

	// Graba los bytes
	*(NF_BUFFER_BGMAP[ramslot] + address) = lobyte;
	*(NF_BUFFER_BGMAP[ramslot] + (address + 1)) = hibyte;

}



// Funcion CreateScanlines();
void CreateScanlines(void) {

	// Carga las scalines
	NF_LoadTiledBg("8bits/common/bg/scanlines", "scan", 256, 256);

	// Crea las scanlines
	NF_CreateTiledBg(0, 0, "scan");
	NF_CreateTiledBg(1, 0, "scan");

	// Nivel de Alpha
	ScanlinesAlphaLevel();

}


// Funcion DeleteScanlines();
void DeleteScanlines(void) {

	// Crea las scanlines
	NF_DeleteTiledBg(0, 0);
	NF_DeleteTiledBg(1, 0);

	// Carga las scalines
	NF_UnloadTiledBg("scan");

}



// Funcion ScanlinesAlphaLevel();
void ScanlinesAlphaLevel(void) {

	// Si el nivel es 0, oculta el fondo
	if (GAMEOPTIONS[0].scanlines == 0) {
		NF_HideBg(0, 0);
		NF_HideBg(1, 0);
	} else {
		NF_ShowBg(0, 0);
		NF_ShowBg(1, 0);
	}

	
	// Ajusta el nivel de alpha
	switch (GAMEOPTIONS[0].scanlines) {

		case 0:
			REG_BLDCNT = BLEND_NONE;
			REG_BLDCNT_SUB = BLEND_NONE;
			REG_BLDALPHA = 0x0F | (0x0F << 8);
			REG_BLDALPHA_SUB = 0x0F | (0x0F << 8);
			break;

		case 1:
			REG_BLDCNT = BLEND_ALPHA | BLEND_SRC_BG0 | (BLEND_DST_BG1 + BLEND_DST_BG2 + BLEND_DST_BG3 + BLEND_DST_SPRITE);
			REG_BLDALPHA = 0x0F | (0x0C << 8);
			REG_BLDCNT_SUB = BLEND_ALPHA | BLEND_SRC_BG0 | (BLEND_DST_BG1 + BLEND_DST_BG2 + BLEND_DST_BG3 + BLEND_DST_SPRITE);
			REG_BLDALPHA_SUB = 0x0F | (0x0C << 8);
			break;

		case 2:
			REG_BLDCNT = BLEND_ALPHA | BLEND_SRC_BG0 | (BLEND_DST_BG1 + BLEND_DST_BG2 + BLEND_DST_BG3 + BLEND_DST_SPRITE);
			REG_BLDALPHA = 0x0F | (0x09 << 8);
			REG_BLDCNT_SUB = BLEND_ALPHA | BLEND_SRC_BG0 | (BLEND_DST_BG1 + BLEND_DST_BG2 + BLEND_DST_BG3 + BLEND_DST_SPRITE);
			REG_BLDALPHA_SUB = 0x0F | (0x09 << 8);
			break;

		case 3:
			REG_BLDCNT = BLEND_ALPHA | BLEND_SRC_BG0 | (BLEND_DST_BG1 + BLEND_DST_BG2 + BLEND_DST_BG3 + BLEND_DST_SPRITE);
			REG_BLDALPHA = 0x0F | (0x06 << 8);
			REG_BLDCNT_SUB = BLEND_ALPHA | BLEND_SRC_BG0 | (BLEND_DST_BG1 + BLEND_DST_BG2 + BLEND_DST_BG3 + BLEND_DST_SPRITE);
			REG_BLDALPHA_SUB = 0x0F | (0x06 << 8);
			break;

	}


}



// Funcion DeleteBackgrounds();
void DeleteBackgrounds(u8 screen, bool layer0, bool layer1, bool layer2, bool layer3) {

	// Variables
	u8 n = 0;
	bool l[4];

	// Registra las capas a borrar
	l[0] = layer0;
	l[1] = layer1;
	l[2] = layer2;
	l[3] = layer3;

	// Elimina si estan creados, los fondos indicados
	for (n = 0; n < 4; n ++) {
		if (NF_TILEDBG_LAYERS[screen][n].created && l[n]) {
			NF_DeleteTiledBg(screen, n);
		}
	}

}



// Funcion SystemError();
void SystemError(const char* text) {

	// Inicializa el sistema de errores
	consoleDemoInit();		// Inicializa la consola de texto
	consoleClear();			// Borra la pantalla
	setBrightness(3, 0);	// Restaura el brillo

	// Mensaje
	iprintf("Error critico.\n");
	iprintf(text);

	// Deten la ejecucion del codigo
	while (1) swiWaitForVBlank();

}



// Funcion VramUsage();
void VramUsage(void) {

	// Variables
	char text[256];

	// Manda la info de la VRAM a la consola de debug
	sprintf(text, "SCR0 FREE: %05d  USE: %05d   SCR1 FREE: %05d  USE: %05d\n", NF_SPRVRAM[0].free, (131072 - NF_SPRVRAM[0].free), NF_SPRVRAM[1].free, (131072 - NF_SPRVRAM[1].free));
	nocashMessage(text);

}
