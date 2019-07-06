/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de los eventos
	(Interruptores, puertas, trampas)

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



// Funcion EventMain();
void EventMain(void) {

	EventCheckSwitch();		// Verifica los interruptores
	EventRun();				// Ejecuta los eventos pendientes (relacionados con los interruptores

	LampEvent();			// Ejecuta los eventos relacionados con las lamparas

}



// Funcion EventCloseDoor();
void EventCloseDoor(u8 door) {

	// Variables
	s32 start_x = DOOR[door].door_x;
	s32 start_y = DOOR[door].door_y;
	s32 end_x = (start_x + DOOR[door].size_x);
	s32 end_y = (start_y + DOOR[door].size_y);
	s32 x = 0, y = 0;

	// Haz los cambios en el mapa
	for (y = start_y; y < end_y; y += 8) {
		for (x = start_x; x < end_x; x += 8) {
			NF_SetTile(MAINMAP_SLOT, x, y, T_WALL);
		}
	}

}



// Funcion EventOpenDoor();
void EventOpenDoor(u8 door) {

	// Variables
	s32 start_x = DOOR[door].door_x;
	s32 end_x = (start_x + DOOR[door].size_x);
	s32 x = 0;
	s32 y = (DOOR[door].pos_y + DOOR[door].size_y);

	// Haz los cambios en el mapa
	for (x = start_x; x < end_x; x += 8) {
		NF_SetTile(MAINMAP_SLOT, x, y, T_AIR);
	}

}



// Funcion EventCloseHwall();
void EventCloseHwall(u8 hwall) {

	// Variables
	s32 start_x = HWALL[hwall].hwall_x;
	s32 start_y = HWALL[hwall].hwall_y;
	s32 end_x = (start_x + HWALL[hwall].size_x);
	s32 end_y = (start_y + HWALL[hwall].size_y);
	s32 x = 0, y = 0;

	// Haz los cambios en el mapa
	for (y = start_y; y < end_y; y += 8) {
		for (x = start_x; x < end_x; x += 8) {
			NF_SetTile(MAINMAP_SLOT, x, y, T_WALL);
		}
	}

}


// Funcion EventOpenHwallRight();
void EventOpenHwallRight(u8 hwall) {

	// Variables
	s32 start_y = HWALL[hwall].hwall_y;
	s32 end_y = (start_y + HWALL[hwall].size_y);
	s32 x = (HWALL[hwall].pos_x + HWALL[hwall].size_x);
	s32 y = 0;

	// Haz los cambios en el mapa
	for (y = start_y; y < end_y; y += 8) {
		NF_SetTile(MAINMAP_SLOT, x, y, T_AIR);
	}

}



// Funcion EventOpenHwallUp();
void EventOpenHwallUp(u8 hwall) {

	// Variables
	s32 start_x = HWALL[hwall].hwall_x;
	s32 end_x = (start_x + HWALL[hwall].size_x);
	s32 x = 0;
	s32 y = (HWALL[hwall].pos_y - 8);

	// Haz los cambios en el mapa
	for (x = start_x; x < end_x; x += 8) {
		NF_SetTile(MAINMAP_SLOT, x, y, T_AIR);
	}

}



// Funcion EventCheckSwitch();
void EventCheckSwitch(void) {

	// Variables
	u16 tile = 255;		// Tile devuelto
	s32 x = 0, y = 0;	// Posicion a verificar
	s16 n = 0;			// Uso general
	
	// Si el personaje esta saltando y no hay activo ningun otro evento...
	if (CHARACTER.is_jump && !EVENT.active) {
		// Adquiere el tile de la posicion
		x = CHARACTER.pos_x;
		y = (CHARACTER.pos_y - CHARACTER.up[0]);
		tile = NF_GetTile(MAINMAP_SLOT, x, y);
		// Verifica si has tocado algun interruptor valido
		for (n = 0; n < SWITCH_NUM; n ++) {
			// Has tocado un interruptor
			if ((n + T_SWITCH_0) == tile) {
				// El interruptor estava desactivado
				if (!SWITCH[n].activated) {
					// Activa el interruptor
					SWITCH[n].activated = true;
					// Registra el ID de evento
					EVENT.id = n;
					// Indica que hay un nuevo evento pendiente
					EVENT.active = true;
					EVENT.new_event = true;
					// Sal de la rutina
					n = SWITCH_NUM;
				}
			}
		}
	}

}



// Funcion EventRun();
void EventRun(void) {

	// Si hay algun evento activo
	if (EVENT.active) {
		// Ejecutalo segun la ID del Evento
		switch (EVENT.id) {
			// Evento 0 - Puerta nº00, Stage 01
			case 0:
				Event00();
				break;
			// Evento 1 - Puerta nº01, Stage 04
			case 1:
				Event01();
				break;
			// Evento 2 - Puerta nº02, Stage 05
			case 2:
				Event02();
				break;
			// Evento 3 - Puerta nº03, Stage 07
			case 3:
				Event03();
				break;
			// Evento 4 - Puertas nº04 y nº05, Stage 14
			case 4:
				Event04();
				break;
			// Evento 5 - Muro nº00, Stage 16
			case 5:
				Event05();
				break;
			// Evento 6 - Trampa nº00, Stage 16
			case 6:
				Event06();
				break;
			// Evento 7 - Muro nº01 y nº02, Stage 16
			case 7:
				Event07();
				break;
			// Evento 8 - Puerta nº06, Stage 17
			case 8:
				Event08();
				break;
			// Evento 9 - Muro nº03, Stage 17
			case 9:
				Event09();
				break;
			// Evento 10 - Trampa nº01, Stage 17
			case 10:
				Event10();
				break;
			// Por defecto, nada
			default:
				EVENT.active = false;
				EVENT.id = 255;
				break;
		}
	}

}



// Funcion Event00();
void Event00(void) {

	// Registra la localizacion del evento
	if (EVENT.new_event) {
		EVENT.pos_x = DOOR[0].door_x, EVENT.pos_y = DOOR[0].door_y;
		EVENT.stage = GetStage(EVENT.pos_x, EVENT.pos_y);
		EVENT.new_event = false;
	}

	// Si la puerta no esta abierta
	if (DOOR[0].pos_y > 32) {

		// Desplaza la puerta de Y:96 a Y:32
		DOOR[0].pos_fy -= 64;
		DOOR[0].pos_y = (DOOR[0].pos_fy >> 8);

	} else {	// Si ya se ha abierto

		// Ajusta la posicion
		DOOR[0].pos_y = 32;
		// Marca la puerta como abierta
		DOOR[0].activated = true;
		// Marca el evento como finalizado
		EVENT.active = false;
		EVENT.id = 255;

	}

	// Modifica, si es necesario, el mapa
	if ((DOOR[0].pos_y % 8) == 0) EventOpenDoor(0);

}



// Funcion Event01();
void Event01(void) {

	// Registra la localizacion del evento
	if (EVENT.new_event) {
		EVENT.pos_x = DOOR[1].door_x, EVENT.pos_y = DOOR[1].door_y;
		EVENT.stage = GetStage(EVENT.pos_x, EVENT.pos_y);
		EVENT.new_event = false;
	}

	// Si la puerta no esta abierta
	if (DOOR[1].pos_y > 544) {

		// Desplaza la puerta de Y:640 a Y:544
		DOOR[1].pos_fy -= 64;
		DOOR[1].pos_y = (DOOR[1].pos_fy >> 8);

	} else {	// Si ya se ha abierto

		// Ajusta la posicion
		DOOR[1].pos_y = 544;
		// Marca la puerta como abierta
		DOOR[1].activated = true;
		// Marca el evento como finalizado
		EVENT.active = false;
		EVENT.id = 255;

	}

	// Modifica, si es necesario, el mapa
	if ((DOOR[1].pos_y % 8) == 0) EventOpenDoor(1);

}



// Funcion Event02();
void Event02(void) {

	// Registra la localizacion del evento
	if (EVENT.new_event) {
		EVENT.pos_x = DOOR[2].door_x, EVENT.pos_y = DOOR[2].door_y;
		EVENT.stage = GetStage(EVENT.pos_x, EVENT.pos_y);
		EVENT.new_event = false;
	}

	// Si la puerta no esta abierta
	if (DOOR[2].pos_y > 752) {

		// Desplaza la puerta de Y:816 a Y:752
		DOOR[2].pos_fy -= 64;
		DOOR[2].pos_y = (DOOR[2].pos_fy >> 8);

	} else {	// Si ya se ha abierto

		// Ajusta la posicion
		DOOR[2].pos_y = 752;
		// Marca la puerta como abierta
		DOOR[2].activated = true;
		// Marca el evento como finalizado
		EVENT.active = false;
		EVENT.id = 255;

	}

	// Modifica, si es necesario, el mapa
	if ((DOOR[2].pos_y % 8) == 0) EventOpenDoor(2);

}



// Funcion Event03();
void Event03(void) {

	// Registra la localizacion del evento
	if (EVENT.new_event) {
		EVENT.pos_x = DOOR[3].door_x, EVENT.pos_y = DOOR[3].door_y;
		EVENT.stage = GetStage(EVENT.pos_x, EVENT.pos_y);
		EVENT.new_event = false;
	}

	// Si la puerta no esta abierta
	if (DOOR[3].pos_y > 1072) {

		// Desplaza la puerta de Y:1168 a Y:1072
		DOOR[3].pos_fy -= 64;
		DOOR[3].pos_y = (DOOR[3].pos_fy >> 8);

	} else {	// Si ya se ha abierto

		// Ajusta la posicion
		DOOR[3].pos_y = 1072;
		// Marca la puerta como abierta
		DOOR[3].activated = true;
		// Marca el evento como finalizado
		EVENT.active = false;
		EVENT.id = 255;

	}

	// Modifica, si es necesario, el mapa
	if ((DOOR[3].pos_y % 8) == 0) EventOpenDoor(3);

}



// Funcion Event04();
void Event04(void) {

	// Registra la localizacion del evento
	if (EVENT.new_event) {
		EVENT.pos_x = DOOR[4].door_x, EVENT.pos_y = DOOR[4].door_y;
		EVENT.stage = GetStage(EVENT.pos_x, EVENT.pos_y);
		EVENT.new_event = false;
	}

	// Si la puerta no esta abierta
	if (DOOR[4].pos_y > 928) {

		// Desplaza la puerta de Y:1008 a Y:928
		DOOR[4].pos_fy -= 64, DOOR[5].pos_fy -= 64;
		DOOR[4].pos_y = (DOOR[4].pos_fy >> 8), DOOR[5].pos_y = (DOOR[5].pos_fy >> 8);

	} else {	// Si ya se ha abierto

		// Ajusta la posicion
		DOOR[4].pos_y = 928, DOOR[5].pos_y = 928;
		// Marca la puerta como abierta
		DOOR[4].activated = true, DOOR[5].activated = true;
		// Marca el evento como finalizado
		EVENT.active = false;
		EVENT.id = 255;

	}

	// Modifica, si es necesario, el mapa
	if ((DOOR[4].pos_y % 8) == 0) {
		EventOpenDoor(4);
		EventOpenDoor(5);
	}

}



// Funcion Event05();
void Event05(void) {

	// Registra la localizacion del evento
	if (EVENT.new_event) {
		EVENT.pos_x = HWALL[0].hwall_x, EVENT.pos_y = HWALL[0].hwall_y;
		EVENT.stage = GetStage(EVENT.pos_x, EVENT.pos_y);
		EVENT.new_event = false;
	}

	// Si la puerta no esta abierta
	if (HWALL[0].pos_x > 4320) {

		// Desplaza la puerta de X:4384 a X:4320
		HWALL[0].pos_fx -= 64;
		HWALL[0].pos_x = (HWALL[0].pos_fx >> 8);

	} else {	// Si ya se ha abierto

		// Ajusta la posicion
		HWALL[0].pos_x = 4320;
		// Marca la puerta como abierta
		HWALL[0].activated = true;
		// Marca el evento como finalizado
		EVENT.active = false;
		EVENT.id = 255;

	}

	// Modifica, si es necesario, el mapa
	if ((HWALL[0].pos_x % 8) == 0) EventOpenHwallRight(0);

}



// Funcion Event06();
void Event06(void) {

	// Variables
	u8 id = 0;

	// Calcula la velocidad de desplazamiento
	s32 speed = ((TRAP[0].pos_fy - (TRAP[0].trap_y << 8)) >> 3);
	if (speed < 256) speed = 256;

	// Registra la localizacion del evento
	if (EVENT.new_event) {
		EVENT.pos_x = TRAP[0].trap_x, EVENT.pos_y = TRAP[0].trap_y;
		EVENT.stage = GetStage(EVENT.pos_x, EVENT.pos_y);
		EVENT.new_event = false;
	}

	// Si la trampa no ha alcanzado al posicion deseada
	if (TRAP[0].pos_y < 1424) {

		// Desplaza la trampa de Y:1344 a Y:1424
		TRAP[0].pos_fy += speed;
		TRAP[0].pos_y = (TRAP[0].pos_fy >> 8);

		// Desplaza los interruptores anexados
		for (id = 5; id <= 7; id ++) {
			SWITCH[id].pos_y = (TRAP[0].pos_y + 55);
		}

	} else {	// Si ya se ha abierto

		// Ajusta la posicion
		TRAP[0].pos_y = 1424;
		// Desplaza los interruptores anexados
		for (id = 5; id <= 7; id ++) {
			SWITCH[id].pos_y = (TRAP[0].pos_y + 48 + 7);
		}
		// Marca la puerta como abierta
		TRAP[0].activated = true;
		// Marca el evento como finalizado
		EVENT.active = false;
		EVENT.id = 255;

	}

}



// Funcion Event07();
void Event07(void) {

	// Registra la localizacion del evento
	if (EVENT.new_event) {
		EVENT.pos_x = HWALL[1].hwall_x, EVENT.pos_y = HWALL[1].hwall_y;
		EVENT.stage = GetStage(EVENT.pos_x, EVENT.pos_y);
		EVENT.new_event = false;
	}

	// Fase 1, cierra el muro nº02
	if (HWALL[2].pos_x > 4064) {

		// Desplaza la puerta de X:4128 a X:4064
		HWALL[2].pos_fx -= 64;
		HWALL[2].pos_x = (HWALL[2].pos_fx >> 8);

	} else {

		// Fase 2, abre el muro nº01
		if (HWALL[1].pos_y < 1504) {

			// Desplaza la puerta de Y:1440 a Y:1504
			HWALL[1].pos_fy += 64;
			HWALL[1].pos_y = (HWALL[1].pos_fy >> 8);

		} else {	// Si ya se ha abierto

			// Ajusta la posicion
			HWALL[2].pos_x = 4064;
			HWALL[1].pos_y = 1504;
			// Marca la puerta como abierta
			HWALL[2].activated = true;
			HWALL[1].activated = true;
			// Marca el evento como finalizado
			EVENT.active = false;
			EVENT.id = 255;

		}

		// Modifica, si es necesario, el mapa
		if ((HWALL[1].pos_y % 8) == 0) EventOpenHwallUp(1);

	}

}


// Funcion Event08();
void Event08(void) {

	// Registra la localizacion del evento
	if (EVENT.new_event) {
		EVENT.pos_x = DOOR[6].door_x, EVENT.pos_y = DOOR[6].door_y;
		EVENT.stage = GetStage(EVENT.pos_x, EVENT.pos_y);
		EVENT.new_event = false;
	}

	// Si la puerta no esta abierta
	if (DOOR[6].pos_y > 1568) {

		// Desplaza la puerta de Y:1632 a Y:1568
		DOOR[6].pos_fy -= 64;
		DOOR[6].pos_y = (DOOR[6].pos_fy >> 8);

	} else {	// Si ya se ha abierto

		// Ajusta la posicion
		DOOR[6].pos_y = 1568;
		// Marca la puerta como abierta
		DOOR[6].activated = true;
		// Marca el evento como finalizado
		EVENT.active = false;
		EVENT.id = 255;

	}

	// Modifica, si es necesario, el mapa
	if ((DOOR[6].pos_y % 8) == 0) EventOpenDoor(6);

}



// Funcion Event09();
void Event09(void) {

	// Registra la localizacion del evento
	if (EVENT.new_event) {
		EVENT.pos_x = HWALL[3].hwall_x, EVENT.pos_y = HWALL[3].hwall_y;
		EVENT.stage = GetStage(EVENT.pos_x, EVENT.pos_y);
		EVENT.new_event = false;
	}

	// Si la puerta no esta abierta
	if (HWALL[3].pos_x > 3056) {

		// Desplaza la puerta de X:3120 a X:3056
		HWALL[3].pos_fx -= 512;
		HWALL[3].pos_x = (HWALL[3].pos_fx >> 8);

	} else {	// Si ya se ha abierto

		// Ajusta la posicion
		HWALL[3].pos_x = 3056;
		// Marca la puerta como abierta
		HWALL[3].activated = true;
		// Marca el evento como finalizado
		EVENT.active = false;
		EVENT.id = 255;

	}

	// Modifica, si es necesario, el mapa
	if ((HWALL[3].pos_x % 8) == 0) EventOpenHwallRight(3);

}



// Funcion Event10();
void Event10(void) {

	// Variables
	u8 id = 0;

	// Calcula la velocidad de desplazamiento
	s32 speed = ((TRAP[1].pos_fy - (TRAP[1].trap_y << 8)) >> 3);
	if (speed < 256) speed = 256;

	// Registra la localizacion del evento
	if (EVENT.new_event) {
		EVENT.pos_x = TRAP[1].trap_x, EVENT.pos_y = TRAP[1].trap_y;
		EVENT.stage = GetStage(EVENT.pos_x, EVENT.pos_y);
		EVENT.new_event = false;
	}

	// Si la trampa no ha alcanzado al posicion deseada
	if (TRAP[1].pos_y < 1631) {

		// Desplaza la trampa de Y:1551 a Y:1631
		TRAP[1].pos_fy += speed;
		TRAP[1].pos_y = (TRAP[1].pos_fy >> 8);

		// Desplaza los interruptores anexados
		for (id =9; id <= 10; id ++) {
			SWITCH[id].pos_y = (TRAP[1].pos_y + 55);
		}

	} else {	// Si ya se ha abierto

		// Ajusta la posicion
		TRAP[1].pos_y = 1631;
		// Desplaza los interruptores anexados
		for (id = 9; id <= 10; id ++) {
			SWITCH[id].pos_y = (TRAP[1].pos_y + 48 + 7);
		}
		// Marca la puerta como abierta
		TRAP[1].activated = true;
		// Marca el evento como finalizado
		EVENT.active = false;
		EVENT.id = 255;

	}

}

