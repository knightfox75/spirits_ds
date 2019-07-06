#ifndef __SAVE_H__
#define __SAVE_H__





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





// Includes propietarios NDS
#include <nds.h>


// Funcion CheckSavegame();
void CheckSavegame(const char* path);
// Verifica el archivo de guardado y crealo si no existe



// Funcion WriteSavegame();
void WriteSavegame(void);
// Guarda los datos del juego



// Funcion ReadSavegame();
void ReadSavegame(void);
// Carga los datos del juego



// Funcion CheckSavegameFile();
void CheckSavegameFile(void);
// Verifica si el archivo de guardado.
// Si existe, cargalo, si no, crea uno de nuevo.



// Funcion WriteSavegame();
void WriteSavegameFile(void);
// Guarda los datos en un archivo



// Funcion ReadSavegame();
void ReadSavegameFile(void);
// Carga los datos desde un archivo



// Funcion CheckSavegameSRAM();
void CheckSavegameSRAM(void);
// EMULADOR - SRAM
// Verifica si el archivo de guardado.
// Si existe, cargalo, si no, crea uno de nuevo.



// Funcion WriteSRAM();
void WriteSRAM(void);
// Guarda los datos en SRAM (Emulador)



// Funcion WriteSRAM();
void ReadSRAM(void);
// Lee los datos en SRAM (Emulador)



// Funcion CheckFATWrite();
bool CheckFATWrite(const char* path);
// Verifica si puedes escribir en FAT



// Funcion SavedataChecksum();
u32 SavedataChecksum(void);
// Verifica la integridad de los datos



// Funcion InitGameData();
void InitGameData(void);
// Inicializa todos los datos del juego





#endif
