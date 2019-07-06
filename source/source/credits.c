/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de Creditos

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




// Funcion Credits();
void Credits(void) {

	// Resetealo todo
	ResetAll();

	// Variables
	u32 height = 0;		// Tamaño de la capa de creditos

	// Carga archivos
	CreditsLoadFiles();

	// Crea el escenario
	CreditsCreate();

	// Carga las capas de texto
	if (GAMEOPTIONS[0].language == 0) {
		height = CreditsLoadText("credits/text/credits_es.txt");
	} else {
		height = CreditsLoadText("credits/text/credits_en.txt");
	}
	// Actualiza la capa de texto
	NF_UpdateTextLayers();

	// Kernel de los creditos
	CreditsKernel(height);

}



// Funcion CreditsLoadFiles();
void CreditsLoadFiles(void) {

	// Si es modo remake o 8 bits...
	if (GAMEOPTIONS[0].remake) {
		// Carga los fondos
		NF_LoadTiledBg("credits/hq/bg/credits_up_hq", "papyre_up", 256, 256);
		NF_LoadTiledBg("credits/hq/bg/credits_down_hq", "papyre_down", 256, 256);
		// Carga la musica
		LoadBgm(MOD_ANDEVASTU);
	} else {
		// Carga los fondos
		NF_LoadTiledBg("credits/8bits/bg/credits_up_8b", "papyre_up", 256, 256);
		NF_LoadTiledBg("credits/8bits/bg/credits_down_8b", "papyre_down", 256, 256);
		// Carga la musica
		LoadBgm(MOD_SPIRITS_8B);
	}

}



// Funcion CreditsCreate();
void CreditsCreate(void) {

	// Crea los fondos
	if (GAMEOPTIONS[0].remake) {
		NF_CreateTiledBg(0, 3, "papyre_up");
		NF_CreateTiledBg(1, 3, "papyre_down");
	} else {
		NF_CreateTiledBg(0, 2, "papyre_up");
		NF_CreateTiledBg(1, 2, "papyre_down");
	}

	// Habilita el efecto blending
	if (GAMEOPTIONS[0].remake) {
		REG_BLDCNT = BLEND_ALPHA | BLEND_SRC_BG2 | BLEND_DST_BG3;
		REG_BLDCNT_SUB = BLEND_ALPHA | BLEND_SRC_BG2 | BLEND_DST_BG3;
	} else {
		CreateScanlines();
	}

}



// Funcion CreditsLoadText();
u32 CreditsLoadText(const char* file) {

	// Variables
	char* buffer;			// Buffer para almacenar el texto
	u32 size = 0;			// Tamaño del archivo
	buffer = NULL;
	FILE* file_id;			// Declara los punteros a los ficheros
	char filename[256];		// Variable para almacenar el path al archivo
	u32 lines = 0;			// Numero de lineas en el texto
	u32 y_size = 0;			// Altura de la capa de texto
	char text[64];			// Buffer de la linea de texto
	u16 len = 0;			// Longitud de la linea de texto
	s16 x = 0;				// Coordenadas para escribir el texto
	s16 y = 0;
	bool newline = false;	// Nueva linea
	u32 chr = 0;			// Caracter dentro de la linea
	u32 n = 0;				// Uso general

	sprintf(filename, "%s/%s", NF_ROOTFOLDER, file);
	file_id = fopen(filename, "rb");
	if (file_id) {	// Si el archivo existe...
		// Obten el tamaño del archivo
		fseek(file_id, 0, SEEK_END);
		size = ftell(file_id);
		rewind(file_id);
		// Reserva el espacio en RAM
		buffer = (char*) calloc (size, sizeof(char));
		if (buffer == NULL) {		// Si no hay suficiente RAM libre
			NF_Error(102, NULL, size);
		}
		// Lee el archivo y ponlo en la RAM
		fread(buffer, 1, size, file_id);
	} else {	// Si el archivo no existe...
		NF_Error(101, filename, 0);
	}
	fclose(file_id);		// Cierra el archivo

	// Cuenta lineas
	for (n = 0; n < size; n ++) {
		if (buffer[n] == 0x0a) lines ++;
	}

	// Calcula el tamaño de la capa de texto
	n = (480 + (lines << 4) + 480);
	y_size = (((n >> 8) + 1) << 8);

	// Carga las fuentes
	NF_LoadTextFont16("credits/text/credits", "top", 256, y_size, 0);
	NF_LoadTextFont16("credits/text/credits", "bottom", 256, y_size, 0);

	// Crea las capas de texto
	if (GAMEOPTIONS[0].remake) {
		NF_CreateTextLayer16(0, 2, 0, "top");
		NF_CreateTextLayer16(1, 2, 0, "bottom");
		NF_DefineTextColor(0, 2, 0, 0, 0, 0);
		NF_DefineTextColor(1, 2, 0, 0, 0, 0);
	} else {
		NF_CreateTextLayer16(0, 3, 0, "top");
		NF_CreateTextLayer16(1, 3, 0, "bottom");
		NF_DefineTextColor(0, 3, 0, 31, 31, 31);
		NF_DefineTextColor(1, 3, 0, 31, 31, 31);
	}

	// Prepara la escritura de texto
	memset(text, 0, sizeof(text));
	y = 30;

	// Escribe el texto en las capas
	for (n = 0; n < size; n++) {

		// Si es una nueva linea
		if (newline) {
			// Escribe la linea actual
			text[chr] = '\0';
			len = strlen(text);
			x = (16 - (len >> 1));
			if (GAMEOPTIONS[0].remake) {
				NF_WriteText16(0, 2, x, y, text);
				NF_WriteText16(1, 2, x, y, text);
			} else {
				NF_WriteText16(0, 3, x, y, text);
				NF_WriteText16(1, 3, x, y, text);
			}
			// Preparate para una nueva linea
			memset(text, 0, sizeof(text));
			chr = 0;
			y ++;
			// Linea completada
			newline = false;
		}

		// Copia los caracteres del buffer a la linea
		if ((buffer[n] != 0x0d) && (buffer[n] != 0x0a)) {
			text[chr] = buffer[n];
			chr ++;
		} else {
			// Si es final de linea, marcalo
			if (buffer[n] == 0x0a) newline = true;
		}

	}

	// Libera el buffer de texto
	free(buffer);

	// Devuelve el tamaño real de la capa de texto
	return  ((30 + lines + 30) << 4);

}



// Funcion CreditsKernel();
void CreditsKernel(u32 height) {

	//////////////////////////
	// Ejecuta los creditos //
	//////////////////////////

	// Variables
	bool loop = true;		// Main loop

	s16 fade = (16 << 8);	// Brillo
	bool fade_in = true;	// Flag Fade in
	bool fade_out = false;	// Flag Fade Out

	u32 y = 0;
	u32 y_end = (height - (30 << 4));

	// Habilita la ejecucion del efecto blending (si es remake)
	if (GAMEOPTIONS[0].remake) {
		irqSet(IRQ_HBLANK, CreditsBlending);
		irqEnable(IRQ_HBLANK);
	}

	// Reproduce la musica
	PlayBgm();


	// Ejecuta hasta terminar la carrera
	while (loop) {

		// Lee el teclado
		ReadKeypad();

		// Effecto "fade in"
		if (fade_in) {
			fade -= 64;
			if (fade <= 0) {
				fade = 0;
				fade_in = false;
			}
			setBrightness(3, (0 - (fade >> 8)));
		}

		// Effecto "fade out"
		if (fade_out) {
			fade += 64;
			if (fade >= (16 << 8)) {
				fade = (16 << 8);
				fade_out = false;
				loop = false;
			}
			// Ajusta el brillo
			setBrightness(3, (0 - (fade >> 8)));
			// Ajusta el volumen
			BgmVolume(((4096 - fade) >> 2));
		}

		// Control del final de los creditos, si no se esta realizando ningun efecto
		if (!fade_in && !fade_out) {

			// Sal de los creditos si se presiona la A, B, X o Y
			if (KEYPRESS.a || KEYPRESS.b || KEYPRESS.x || KEYPRESS.y) {
				fade_out = true;
			}

		}

		// Calcula la posicion de la capa de texto
		if (y < (y_end << 8)) y += 128;
		if (!fade_in && !fade_out) {
			if (y >= (y_end << 8)) {
				y = (y_end << 8);
				fade_out = true;
			}
		}

		// Actualiza el OAM de Sprites
		NF_SpriteOamSet(0);
		NF_SpriteOamSet(1);

		// Espera al sincronismo vertical
		swiWaitForVBlank();

		// Actualiza el OAM de Libnds
		oamUpdate(&oamMain);
		oamUpdate(&oamSub);

		// Actualiza el scroll de texto
		if (GAMEOPTIONS[0].remake) {
			NF_ScrollBg(0, 2, 0, (y >> 8));
			NF_ScrollBg(1, 2, 0, ((y >> 8) + 288));
		} else {
			NF_ScrollBg(0, 3, 0, (y >> 8));
			NF_ScrollBg(1, 3, 0, ((y >> 8) + 288));
		}

	}

	// Deshabilita la interrupcion
	if (GAMEOPTIONS[0].remake) {
		irqDisable(IRQ_HBLANK);
	}

	// Para la musica
	StopBgm();

}



// Funcion CreditsBlending();
void CreditsBlending(void) {

	// Deshabilita la interrupcion
	irqDisable(IRQ_HBLANK);

	// Variables
	s16 line = VLINE;
	s16 alpha = 0;

	// Si la linea de dibujado esta en pantalla
	if (line < 192) {

		// Blending pantalla superior
		if (line >= 0 && line <= 63) {
			alpha = (16 - (line >> 2));
		} else {
			alpha = 0;
		}
		REG_BLDALPHA = alpha | (alpha << 8);

		// Blending pantalla inferior
		if (line >= 127 && line <= 191) {
			alpha = (16 - ((191 - line) >> 2));
		} else {
			alpha = 0;
		}
		REG_BLDALPHA_SUB = alpha | (alpha << 8);

	}

	// Vuelve a habilitar el HBLANK
	irqEnable(IRQ_HBLANK);

}
