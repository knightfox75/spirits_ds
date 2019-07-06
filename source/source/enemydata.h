#ifndef __ENEMYDATA_H__
#define __ENEMYDATA_H__



/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de Carga de datos de los enemigos

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




// Funcion LoadDefaultEnemyData();
void LoadDefaultEnemyData(void);
// Carga los parametros estaticos de los enemigos



// Funcion LoadStartEnemyData();
void LoadStartEnemyData(void);
// Carga los datos iniciales de los enemigos



// Funcion LoadStartGoulData();
void LoadStartGoulData(void);
// Carga los datos iniciales de los gouls



// Funcion LoadStartPhantomData();
void LoadStartPhantomData(void);
// Carga los datos iniciales de los fantasmas



// Funcion LoadStartWolfData();
void LoadStartWolfData(void);
// Carga los datos iniciales de los lobos





#endif
