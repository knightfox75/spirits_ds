/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de guardado de datos

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
#include <string.h>
#include <unistd.h>

// Includes propietarios NDS
#include <nds.h>

// Includes NightFox's Lib
#include <nf_lib.h>

//Incluye las librerias del juego
#include "includes.h"



// Funcion CheckSavegame();
void CheckSavegame(const char* path) {

	// Verifica si es un emulador o el hardware real
	if (CheckFATWrite(path)) {
		// Operaciones en el hardware real
		sprintf(SAVEFILEPATH, path);
		IS_EMULATOR = false;
		CheckSavegameFile();
	} else {
		// Operaciones en el emulador
		IS_EMULATOR = true;
		CheckSavegameSRAM();
	}

}


// Funcion WriteSavegame();
void WriteSavegame(void) {

	// Guardalos donde tocan
	if (IS_EMULATOR) {
		if (USE_SRAM && !REG_DSIMODE) WriteSRAM();
	} else {
		WriteSavegameFile();
	}

}



// Funcion ReadSavegame();
void ReadSavegame(void) {

	// Guardalos donde tocan
	if (IS_EMULATOR) {
		if (USE_SRAM && !REG_DSIMODE) ReadSRAM();
	} else {
		ReadSavegameFile();
	}

}




// Funcion CheckSavegameFile();
void CheckSavegameFile(void) {

	// Variables
	bool filefound = false;		// Existe el fichero
	u16 l = 0;					// Longitud del path al archivo
	FILE* savefile;				// Puntero de archivo
	u32 checksum = 0;			// Checksum del savedata

	// Añade la extension .SAV al archivo de guardado
	l = strlen(SAVEFILEPATH);
	SAVEFILEPATH[(l - 3)] = 's';
	SAVEFILEPATH[(l - 2)] = 'a';
	SAVEFILEPATH[(l - 1)] = 'v';

	// Verifica si existe el archivo de guardado
	savefile = fopen(SAVEFILEPATH, "rb");
	if (savefile) {
		filefound = true;
	} else {
		filefound = false;
	}
	fclose(savefile);

	// Si el archivo de guardado existe...
	if (filefound) {
		// Lee el archivo
		ReadSavegameFile();
		// Realiza el checksum de los datos cargados
		checksum = SavedataChecksum();
		// Verifica si hay discrepancias
		if (
			(checksum != CHECKSUM[0].value)
			||
			(CHECKSUM[0].version != SAVEGAMEVERSION)
			||
			(strcmp(CHECKSUM[0].magic, "SPIRITSDS") != 0)
			) {
			// Si las hay, inicializa los datos del juego
			InitGameData();
			// Graba el archivo
			WriteSavegameFile();
		}
	} else {	// Si no existe, crea los datos de guardado y crealo
		// Inicializa los datos del juego
		InitGameData();
		// Graba el archivo
		WriteSavegameFile();
	}

}



// Funcion WriteSavegameFile();
void WriteSavegameFile(void) {

	// Variables
	FILE* savefile;				// Puntero de archivo

	// Alamacena el CHECKSUM
	CHECKSUM[0].value = SavedataChecksum();

	// Crea el Archivo
	savefile = fopen(SAVEFILEPATH, "wb");

	// Graba los datos solo en caso de poder escribir el archivo
	if (savefile) {
		fwrite((void*)&CHECKSUM, sizeof(CHECKSUM), 1, savefile);
		fwrite((void*)&GAMEOPTIONS, sizeof(GAMEOPTIONS), 1, savefile);
	}

	// Cierra el archivo
	fclose(savefile);

}



// Funcion ReadSavegameFile();
void ReadSavegameFile(void) {

	// Variables
	FILE* savefile;				// Puntero de archivo

	// Abre el Archivo
	savefile = fopen(SAVEFILEPATH, "rb");

	// Si el archivo se a abierto con exito
	if (savefile) {
		// Borra el contenido previo
		memset((void*)&CHECKSUM, 0, sizeof(CHECKSUM));
		memset((void*)&GAMEOPTIONS, 0, sizeof(GAMEOPTIONS));
		// Lee los datos
		fread((void*)&CHECKSUM, sizeof(CHECKSUM), 1, savefile);
		fread((void*)&GAMEOPTIONS, sizeof(GAMEOPTIONS), 1, savefile);
	}

	// Cierra el archivo
	fclose(savefile);

}



// Funcion CheckSavegameSRAM();
void CheckSavegameSRAM(void) {

	// Variables
	u32 checksum = 0;		// Checksum de los datos del juego

	// Carga los datos de la SRAM
	if (USE_SRAM && !REG_DSIMODE) ReadSRAM();

	// Calcula el Checksum
	checksum = SavedataChecksum();

	// Si hay discrepancias
	if (
		(checksum != CHECKSUM[0].value)
		||
		(CHECKSUM[0].version != SAVEGAMEVERSION)
		||
		(strcmp(CHECKSUM[0].magic, "SPIRITSDS") != 0)
		) {
		// Inicializa los datos del juego
		InitGameData();
		// Guarda los datos
		if (USE_SRAM && !REG_DSIMODE) WriteSRAM();
	}

}



// Funcion WriteSRAM();
void WriteSRAM(void) {

	// Variables
	u16 adress = 0;			// Posicion en la SRAM
	u16 i = 0;				// Indice
	bool slot2 = false;		// Propietario actual del SLOT2

	// Alamacena el CHECKSUM
	CHECKSUM[0].value = SavedataChecksum();

	// Si no lo es, haz al ARM9 propietario del SLOT2 y guarda el propietario actual
	slot2 = (REG_EXMEMCNT & ARM7_OWNS_ROM) == 0;
	sysSetCartOwner(true);

	// Copia los datos del bloque CHECKSUM
	for (i = 0; i < sizeof(CHECKSUM); i ++) {
		((u8*)SRAM)[adress] = ((u8*)CHECKSUM)[i];
		adress ++;
	}

	// Copia los datos del bloque GAMEOPTIONS
	for (i = 0; i < sizeof(GAMEOPTIONS); i ++) {
		((u8*)SRAM)[adress] = ((u8*)GAMEOPTIONS)[i];
		adress ++;
	}

	// Devuelve el propietario del SLOT2 al propietario anterior
	sysSetCartOwner(slot2);

}



// Funcion WriteSRAM();
void ReadSRAM(void) {

	// Variables
	u16 adress = 0;			// Posicion en la SRAM
	u16 i = 0;				// Indice
	bool slot2 = false;		// Propietario actual del SLOT2

	// Borra el contenido previo
	memset((void*)&CHECKSUM, 0, sizeof(CHECKSUM));
	memset((void*)&GAMEOPTIONS, 0, sizeof(GAMEOPTIONS));

	// Si no lo es, haz al ARM9 propietario del SLOT2 y guarda el propietario actual
	slot2 = (REG_EXMEMCNT & ARM7_OWNS_ROM) == 0;
	sysSetCartOwner(true);

	// Copia los datos del bloque CHECKSUM
	for (i = 0; i < sizeof(CHECKSUM); i ++) {
		((u8*)CHECKSUM)[i] = ((u8*)SRAM)[adress];
		adress ++;
	}

	// Copia los datos del bloque GAMEOPTIONS
	for (i = 0; i < sizeof(GAMEOPTIONS); i ++) {
		((u8*)GAMEOPTIONS)[i] = ((u8*)SRAM)[adress];
		adress ++;
	}

	// Devuelve el propietario del SLOT2 al propietario anterior
	sysSetCartOwner(slot2);

}



// Verifica si puedes escribir en FAT
bool CheckFATWrite(const char* path) {

	// Variables
	bool filefound = false;		// Existe el fichero
	u16 l = 0;					// Longitud del path al archivo
	FILE* savefile;				// Puntero de archivo
	char testfile[256];			// Nombre de archivo

	// Almacena el path
	sprintf(testfile, path);

	// Añade la extension .CHK al archivo de verificacion
	l = strlen(testfile);
	testfile[(l - 3)] = 'c';
	testfile[(l - 2)] = 'h';
	testfile[(l - 1)] = 'k';

	// Verifica si puedes abrir en el archivo de verificacion
	savefile = fopen(testfile, "rb");
	if (savefile) {
		filefound = true;
	} else {
		filefound = false;
	}
	fclose(savefile);

	// Si no puedes, crea uno e intentalo abrir de nuevo
	if (!filefound) {
		savefile = fopen(testfile, "wb");
		fclose(savefile);
		savefile = fopen(testfile, "rb");
		if (savefile) filefound = true;
		fclose(savefile);
	}

	return filefound;

}



// Funcion SavedataChecksum();
u32 SavedataChecksum(void) {

	// Variables
	u16 i = 0;
	u32 checksum = 0;

	// Checksum de los datos del bloque GAMEOPTIONS
	for (i = 0; i < sizeof(GAMEOPTIONS); i ++) {
		checksum += ((u8*)GAMEOPTIONS)[i];
	}

	// Variables
	return checksum;

}



// Funcion InitGameData();
void InitGameData(void) {
	
	// Magic String del checksum
	sprintf(CHECKSUM[0].magic, "SPIRITSDS");
	CHECKSUM[0].magic[9] = '\0';

	// Identificador de la version
	CHECKSUM[0].version = SAVEGAMEVERSION;

	// Opciones del juego por defecto
	GAMEOPTIONS[0].remake = true;		// Modo Remake por defecto
	GAMEOPTIONS[0].scanlines = 1;		// Scanlines a nivel 2

	// Inicializa el Idioma por defecto (basado en el del usuario)
	if (NF_GetLanguage() == 5) {
		GAMEOPTIONS[0].language = 0;	// Español
	} else {
		GAMEOPTIONS[0].language = 1;	// Ingles
	}

}