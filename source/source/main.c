/*
-------------------------------------------------

	Spirits DS

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



/*
-------------------------------------------------
	Main() - Bloque general del programa
-------------------------------------------------
*/

int main(int argc, char **argv) {

	/*
	-------------------------------------------------
		Inicializaciones
	-------------------------------------------------
	*/

	// Inicia el hardware de la DS y el entorno
	BootGame();

	// Verifica el archivo de guardado de datos
	CheckSavegame(argv[0]);


	/*
	-------------------------------------------------
		Presentacion del juego
	-------------------------------------------------
	*/
	//Compo();
	Opening();



	/*
	-------------------------------------------------
		Nucleo de ejecucion
	-------------------------------------------------
	*/

	// Bucle (repite para siempre)
	while(1) {

		// Segun la opcion del menu...
		switch (MainMenu()) {
			case 0:		// Juego
				RunGame();
				break;
			case 1:		// Como jugar
				HowTo();
				break;
			case 3:		// Creditos
				Credits();
				break;
			default:	// Nada, opcion por defecto
				break;
		}

	}

	// Devuelve el resultado
	return 0; 

}
