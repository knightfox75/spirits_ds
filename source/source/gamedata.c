/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de Carga de datos

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



// Funcion LoadGameDefaultData();
void LoadGameDefaultData(void) {

	/*
	-------------------------------------------------
		Datos del juego (Fijos)
	-------------------------------------------------
	*/

	LoadDefaultStageData();			// Carga la info de las pantallas
	LoadDefaultRandomData();		// Carga la info de las posiciones aleatorias
	LoadDefaultCharacterData();		// Carga la info del personaje
	LoadDefaultSpellData();			// Carga la info del hechizo
	LoadDefaultEnemyData();			// Carga la info de los enemigos
	LoadDefaultDevilcatData();		// Carga la info del gato y el diablo
	LoadDefaultItemData();			// Carga la info de los items
	LoadDefaultNpcData();			// Carga la info de los NPC
	LoadDefaultSwtichData();		// Carga la info de los interruptores
	LoadDefaultDoorData();			// Carga la info de las puertas
	LoadDefaultHwallData();			// Carga la info de los muros ocultos
	LoadDefaultTrapData();			// Carga la info de las trampas
	LoadDefaultLampData();			// Carga la info de las lamparas
	LoadDefaultFiretrapData();		// Carga la info de las hogueras
	LoadDefaultTorchData();			// Carga la info de las antorchas y velas
	LoadDefaultGuiData();			// Carga la info de la GUI
	LoadDefaultCheatsData();		// Carga la info inicial de los trucos

}



// Funcion LoadDefaultStageData();
void LoadDefaultStageData(void) {

	/*
	-------------------------------------------------
		Variables locales
	-------------------------------------------------
	*/

	u8 n = 0;

	/*
	-------------------------------------------------
		Carga la info de las pantallas
	-------------------------------------------------
	*/

	// Dummy (para el minimap)
	STAGE[0].bg_width[1] = 0, STAGE[0].bg_height[1] = 0;
	STAGE[0].stg_width = 0, STAGE[0].stg_height = 0;
	// Resto de pantallas
	for (n = 1; n <= 19; n ++) {
		switch (n) {
			case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18:
				STAGE[n].bg_width[1] = 2048, STAGE[n].bg_height[1] = 256, STAGE[n].bg_speed[1] = 1;
				STAGE[n].bg_width[2] = 2048, STAGE[n].bg_height[2] = 256, STAGE[n].bg_speed[2] = 1;
				STAGE[n].bg_speed[3] = 3;
				STAGE[n].stg_width = 1920, STAGE[n].stg_height = 192;
				break;
			case 9:
				STAGE[n].bg_width[1] = 1280, STAGE[n].bg_height[1] = 256, STAGE[n].bg_speed[1] = 1;
				STAGE[n].bg_width[2] = 1024, STAGE[n].bg_height[2] = 256, STAGE[n].bg_speed[2] = 2;
				STAGE[n].bg_speed[3] = 3;
				STAGE[n].stg_width = 1152, STAGE[n].stg_height = 192;
				break;
			case 10:
				STAGE[n].bg_width[1] = 1280, STAGE[n].bg_height[1] = 256, STAGE[n].bg_speed[1] = 1;
				STAGE[n].bg_width[2] = 1280, STAGE[n].bg_height[2] = 256, STAGE[n].bg_speed[2] = 1;
				STAGE[n].bg_speed[3] = 3;
				STAGE[n].stg_width = 1152, STAGE[n].stg_height = 192;
				break;
			case 19:
				STAGE[n].bg_width[1] = 256, STAGE[n].bg_height[1] = 256, STAGE[n].bg_speed[1] = 1;
				STAGE[n].bg_width[2] = 256, STAGE[n].bg_height[2] = 256, STAGE[n].bg_speed[2] = 1;
				STAGE[n].bg_speed[3] = 3;
				STAGE[n].stg_width = 256, STAGE[n].stg_height = 192;
				break;
		}
	}
	// Dummy (para el minimap)
	STAGE[0].stg_top = 0, STAGE[0].stg_bottom = 0, STAGE[0].stg_left = 0, STAGE[0].stg_right = 0;
	// Lado Izquierdo
	STAGE[1].stg_top = 0, STAGE[1].stg_bottom = 191, STAGE[1].stg_left = 0, STAGE[1].stg_right = 1919;
	STAGE[2].stg_top = 192, STAGE[2].stg_bottom = 383, STAGE[2].stg_left = 0, STAGE[2].stg_right = 1919;
	STAGE[3].stg_top = 384, STAGE[3].stg_bottom = 575, STAGE[3].stg_left = 0, STAGE[3].stg_right = 1919;
	STAGE[4].stg_top = 576, STAGE[4].stg_bottom = 767, STAGE[4].stg_left = 0, STAGE[4].stg_right = 1919;
	STAGE[5].stg_top = 768, STAGE[5].stg_bottom = 959, STAGE[5].stg_left = 0, STAGE[5].stg_right = 1919;
	STAGE[6].stg_top = 960, STAGE[6].stg_bottom = 1151, STAGE[6].stg_left = 0, STAGE[6].stg_right = 1919;
	STAGE[7].stg_top = 1152, STAGE[7].stg_bottom = 1343, STAGE[7].stg_left = 0, STAGE[7].stg_right = 1919;
	STAGE[8].stg_top = 1344, STAGE[8].stg_bottom = 1535, STAGE[8].stg_left = 0, STAGE[8].stg_right = 1919;
	// Centro
	STAGE[9].stg_top = 768, STAGE[9].stg_bottom = 959, STAGE[9].stg_left = 1920, STAGE[9].stg_right = 3071;
	STAGE[10].stg_top = 960, STAGE[10].stg_bottom = 1151, STAGE[10].stg_left = 1920, STAGE[10].stg_right = 3071;
	// Lado derecho
	STAGE[11].stg_top = 384, STAGE[11].stg_bottom = 575, STAGE[11].stg_left = 3072, STAGE[11].stg_right = 4991;
	STAGE[12].stg_top = 576, STAGE[12].stg_bottom = 767, STAGE[12].stg_left = 3072, STAGE[12].stg_right = 4991;
	STAGE[13].stg_top = 768, STAGE[13].stg_bottom = 959, STAGE[13].stg_left = 3072, STAGE[13].stg_right = 4991;
	STAGE[14].stg_top = 960, STAGE[14].stg_bottom = 1151, STAGE[14].stg_left = 3072, STAGE[14].stg_right = 4991;
	STAGE[15].stg_top = 1152, STAGE[15].stg_bottom = 1343, STAGE[15].stg_left = 3072, STAGE[15].stg_right = 4991;
	STAGE[16].stg_top = 1344, STAGE[16].stg_bottom = 1535, STAGE[16].stg_left = 3072, STAGE[16].stg_right = 4991;
	STAGE[17].stg_top = 1536, STAGE[17].stg_bottom = 1727, STAGE[17].stg_left = 3072, STAGE[17].stg_right = 4991;
	STAGE[18].stg_top = 1728, STAGE[18].stg_bottom = 1919, STAGE[18].stg_left = 3072, STAGE[18].stg_right = 4991;
	// Sala del dragon
	STAGE[19].stg_top = 1920, STAGE[19].stg_bottom = 2111, STAGE[19].stg_left = 3512, STAGE[19].stg_right = 3767;

	// Asigna los decorados de fondo
	for (n = 1; n <= 19; n ++) {
		switch (n) {
			// Decorados que usan el fondo FOREST01
			case 1: case 2: case 3: case 4: case 11: case 12:
				sprintf(STAGE[n].bg3name, "forest01");
				break;
			// Decorados que usan el fondo FOREST02
			case 5: case 9: case 13:
				sprintf(STAGE[n].bg3name, "forest02");
				break;
			// Decorados que usan el fondo CATACOMB01
			case 6: case 7: case 8: case 10: case 14: case 15: case 16: case 17: case 18: case 19:
				sprintf(STAGE[n].bg3name, "catacomb01");
				break;
		}
	}

}



// Funcion LoadDefaultRandomData();
void LoadDefaultRandomData(void) {

	/*
	-------------------------------------------------
		Carga los datos estaticos de las
		posiciones aleatorias
	-------------------------------------------------
	*/

	/** Castillo 1 **/
	RANDOM_POS[0].x = 1785, RANDOM_POS[0].y = 351, RANDOM_POS[0].stage = 2; RANDOM_POS[0].npc = false;
	RANDOM_POS[1].x = 1495, RANDOM_POS[1].y = 543, RANDOM_POS[1].stage = 3; RANDOM_POS[1].npc = true;
	RANDOM_POS[2].x = 192, RANDOM_POS[2].y = 735, RANDOM_POS[2].stage = 4; RANDOM_POS[2].npc = true;
	RANDOM_POS[3].x = 1215, RANDOM_POS[3].y = 735, RANDOM_POS[3].stage = 4; RANDOM_POS[3].npc = true;
	RANDOM_POS[4].x = 1535, RANDOM_POS[4].y = 735, RANDOM_POS[4].stage = 4; RANDOM_POS[4].npc = false;
	RANDOM_POS[5].x = 223, RANDOM_POS[5].y = 927, RANDOM_POS[5].stage = 5; RANDOM_POS[5].npc = true;
	RANDOM_POS[6].x = 447, RANDOM_POS[6].y = 1119, RANDOM_POS[6].stage = 6; RANDOM_POS[6].npc = true;
	RANDOM_POS[7].x = 1279, RANDOM_POS[7].y = 1119, RANDOM_POS[7].stage = 6; RANDOM_POS[7].npc = true;
	RANDOM_POS[8].x = 359, RANDOM_POS[8].y = 1311, RANDOM_POS[8].stage = 7; RANDOM_POS[8].npc = false;
	RANDOM_POS[9].x = 1799, RANDOM_POS[9].y = 1311, RANDOM_POS[9].stage = 7; RANDOM_POS[9].npc = true;
	RANDOM_POS[10].x = 143, RANDOM_POS[10].y = 1503, RANDOM_POS[10].stage = 8; RANDOM_POS[10].npc = false;
	RANDOM_POS[11].x = 1759, RANDOM_POS[11].y = 1503, RANDOM_POS[11].stage = 8; RANDOM_POS[11].npc = true;

	/** Pasadizo inferior **/
	RANDOM_POS[12].x = 2119, RANDOM_POS[12].y = 1119, RANDOM_POS[12].stage = 10; RANDOM_POS[12].npc = true;

	/** Castillo 2 **/
	RANDOM_POS[13].x = 3455, RANDOM_POS[13].y = 543, RANDOM_POS[13].stage = 11; RANDOM_POS[13].npc = false;
	RANDOM_POS[14].x = 4511, RANDOM_POS[14].y = 543, RANDOM_POS[14].stage = 11; RANDOM_POS[14].npc = false;
	RANDOM_POS[15].x = 3903, RANDOM_POS[15].y = 751, RANDOM_POS[15].stage = 12; RANDOM_POS[15].npc = false;
	RANDOM_POS[16].x = 4239, RANDOM_POS[16].y = 735, RANDOM_POS[16].stage = 12; RANDOM_POS[16].npc = true;
	RANDOM_POS[17].x = 4911, RANDOM_POS[17].y = 927, RANDOM_POS[17].stage = 13; RANDOM_POS[17].npc = true;
	RANDOM_POS[18].x = 4191, RANDOM_POS[18].y = 1119, RANDOM_POS[18].stage = 14; RANDOM_POS[18].npc = false;
	RANDOM_POS[19].x = 3503, RANDOM_POS[19].y = 1311, RANDOM_POS[19].stage = 15; RANDOM_POS[19].npc = false;
	RANDOM_POS[20].x = 3663, RANDOM_POS[20].y = 1311, RANDOM_POS[20].stage = 15; RANDOM_POS[20].npc = false;
	RANDOM_POS[21].x = 4343, RANDOM_POS[21].y = 1327, RANDOM_POS[21].stage = 15; RANDOM_POS[21].npc = true;
	RANDOM_POS[22].x = 3663, RANDOM_POS[22].y = 1503, RANDOM_POS[22].stage = 16; RANDOM_POS[22].npc = true;
	RANDOM_POS[23].x = 4223, RANDOM_POS[23].y = 1503, RANDOM_POS[23].stage = 16; RANDOM_POS[23].npc = true;
	RANDOM_POS[24].x = 3551, RANDOM_POS[24].y = 1695, RANDOM_POS[24].stage = 17; RANDOM_POS[24].npc = true;
	RANDOM_POS[25].x = 3895, RANDOM_POS[25].y = 1695, RANDOM_POS[25].stage = 17; RANDOM_POS[25].npc = false;
	RANDOM_POS[26].x = 4711, RANDOM_POS[26].y = 1695, RANDOM_POS[26].stage = 17; RANDOM_POS[26].npc = false;
	RANDOM_POS[27].x = 3487, RANDOM_POS[27].y = 1903, RANDOM_POS[27].stage = 18; RANDOM_POS[27].npc = true;
	RANDOM_POS[28].x = 4239, RANDOM_POS[28].y = 1887, RANDOM_POS[28].stage = 18; RANDOM_POS[28].npc = true;

}



// Funcion LoadStartGameData();
void LoadStartGameData(void) {

	/*
	-------------------------------------------------
		Inicializa el random
	-------------------------------------------------
	*/

	srand(time(NULL));


	/*
	-------------------------------------------------
		Resetea el el gestor de eventos
	-------------------------------------------------
	*/

	EVENT.active = false;		// Ningun evento activo
	EVENT.new_event = false;	// Flag de nuevo evento abajo
	EVENT.id = 255;				// Resetea la Id de envento


	/*
	-------------------------------------------------
		Resetea el el gestor de trucos
	-------------------------------------------------
	*/

	CHEATS.map = true;		// Truco del mapa disponible


	/*
	-------------------------------------------------
		Parametros iniciales de la partida
	-------------------------------------------------
	*/

	LoadStartCharacterData();		// Personaje
	LoadStartSpellData();			// Hehcizo
	LoadStartEnemyData();			// Enemigos
	LoadStartDevilcatData();		// Gato y Diablo
	LoadStartSwitchData();			// Interruptores
	LoadStartDoorData();			// Puertas
	LoadStartHwallData();			// Muros moviles
	LoadStartTrapData();			// Trampas
	LoadStartLampData();			// Lamparas
	LoadStartFiretrapData();		// Hogueras
	LoadStartTorchData();			// Antorchas y velas
	LoadStartGuiData();				// GUI
	GetRandomPlaces();				// Posiciona los items y los NPC
	CameraStart();					// Parametros iniciales de las camaras

}



// Funcion GetRandomPlaces();
void GetRandomPlaces(void) {

	/*
	0 - Bola de cristal			
	1 - Armadura			NPC
	2 - Libro de hechizos
	3 - Princesa			NPC
	4 - Varita
	5 - Aguila				NPC
	*/

	// Variables
	s8 randpos[6];			// Guarda las Ids de las posiciones
	bool stage[20];			// Flag de posicion en stage usada
	bool npc = false;		// La id es para un NPC?
	bool next = false;		// Siguiente posicion
	u8 n = 0;				// Uso general
	s16 pos = 0;		

	// Reinicia los marcadores de posicion
	for (n = 0; n < MAX_ITEM_POS; n ++) {
		RANDOM_POS[n].in_use = false;
	}

	// Reinicia el marcador de stages
	for (n = 1; n <= 19; n ++) {
		stage[n] = false;
	}

	// Obten 6 posiciones aleatorias
	for (n = 0; n < 6; n ++) {
		// Mientras no tengas una posicion valida...
		next = false;
		while (!next) {
			// Calcula la posicion
			pos = (int)(rand() % MAX_ITEM_POS);
			if (pos > (MAX_ITEM_POS - 1)) pos = 0;
			// Verifica que no este en uso ni este en un stage repetido
			if (!RANDOM_POS[pos].in_use && !stage[RANDOM_POS[pos].stage]) {
				// Si la posicion es para un NPC, verificacion adicional
				if (!(npc && !RANDOM_POS[pos].npc)) {
					// Asigna la posicion
					randpos[n] = pos;
					// Marcala como usada y calcula la siguiente
					RANDOM_POS[pos].in_use = true;
					stage[RANDOM_POS[pos].stage] = true;
					next = true;
					// Y cambia el indicador de NPC
					npc = !npc;
				}
			}
		}
	}

	// Asigna la posicion de todos los elementos
	SetCristallBall(randpos[0]);	// Bola de cristal
	SetSpellbook(randpos[2]);		// Libro de hechizos
	SetMagicwand(randpos[4]);		// Varita magica

	// Asigna la posicion a todos los NPC
	SetArmor(randpos[1]);		// Armadura
	SetPrincess(randpos[3]);	// Princesa
	SetEagle(randpos[5]);		// Aguila

}
