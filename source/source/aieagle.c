/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de la IA de la Aguila

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




// Funcion EagleAi();
void EagleAi(void) {

	// Toma de decisiones
	EagleAiTakeDecision();

	// Ejecuta el comando de la IA seleccionado
	switch (EAGLE.ai_command) {

		// Vuela a la derecha
		case AI_MOVE_RIGHT:
			EagleAiFlyRight();
			break;

		// Vuela a la izquierda
		case AI_MOVE_LEFT:
			EagleAiFlyLeft();
			break;

		// Vuela hacia arriba
		case AI_MOVE_UP:
			EagleAiFlyUp();
			break;

		// Vuela hacia abajo
		case AI_MOVE_DOWN:
			EagleAiFlyDown();
			break;

		// Nada, error trap
		default:
			break;

	}

}



// Funcion EagleAiTakeDecision();
void EagleAiTakeDecision(void) {

	// Variables
	s32 eagle_top = 0;				// Analisis del techo y suelo
	s32 eagle_bottom = 0;
	u16 tiles_top = AI_CAIR;		// Tiles del techo y suelo
	u16 tiles_bottom = AI_CAIR;
	u16 tiles_left = T_AIR;
	u16 tiles_right = T_AIR;

	// Calcula la coordenada del techo y del suelo
	eagle_top = (STAGE[EAGLE.stage].stg_top + 4);
	eagle_bottom = (STAGE[EAGLE.stage].stg_bottom - 4);

	// Obten los tiles del techo y suelo
	tiles_top = AiEagleCheckTop(EAGLE.pos_x, eagle_top);
	tiles_bottom = AiEagleCheckBottom(EAGLE.pos_x, eagle_bottom);

	// Y los de la derecha e izquierda
	tiles_right = NF_GetTile(MAINMAP_SLOT, (EAGLE.pos_x + EAGLE.right), EAGLE.pos_y);
	tiles_left = NF_GetTile(MAINMAP_SLOT, (EAGLE.pos_x - EAGLE.left), EAGLE.pos_y);

	// Toma de decisiones
	if (EAGLE.ai_ready) {
		// Si hay escaleras o abertura arriba...
		if ((tiles_top == AI_CAIR) || ((tiles_top == AI_CSTAIR) && (tiles_right == T_STAIR) && (tiles_left == T_STAIR))) {
			// Decide si subir o seguir recto
			if ((rand() % 100) >= 50) {
				// Marca la decision tomada
				EAGLE.ai_command = AI_MOVE_UP;
				EAGLE.ai_stage = EAGLE.stage;
				// Y cancela el desplazamiento lateral
				EAGLE.ai_right = false;
				EAGLE.ai_left = false;
			}
			// Deshabilita la IA
			EAGLE.ai_ready = false;
			EAGLE.ai_timer = 120;
		} else {
			// Si hay escaleras o abertura abajo...
			if ((tiles_bottom == AI_CAIR) || ((tiles_bottom == AI_CSTAIR) && (tiles_right == T_STAIR) && (tiles_left == T_STAIR))) {
				// Decide si bajar o seguir recto
				if ((rand() % 100) >= 50) {
					/*
					Lista de excepciones
					Stage 18 - Escalera del dragon
					*/
					if (EAGLE.stage != 18) {
					/*
					Fin de la lista de excepciones
					*/
						// Marca la decision tomada
						EAGLE.ai_command = AI_MOVE_DOWN;
						EAGLE.ai_stage = EAGLE.stage;
						// Y cancela el desplazamiento lateral
						EAGLE.ai_right = false;
						EAGLE.ai_left = false;
					}
				}
				// Deshabilita la IA
				EAGLE.ai_ready = false;
				EAGLE.ai_timer = 120;
			}
		}

	} else {

		// Si el suelo y el techo son solidos
		if ((tiles_top == AI_CWALL) && (tiles_bottom == AI_CFLOOR)) {
			if (EAGLE.ai_timer > 0) {
				EAGLE.ai_timer --;
			} else {
				EAGLE.ai_ready = true;
				EAGLE.ai_error = false;
				if (EAGLE.flip) {
					EAGLE.ai_command = AI_MOVE_LEFT;
				} else {
					EAGLE.ai_command = AI_MOVE_RIGHT;
				}
			}
		}

	}


	/*
	Lista de Excepciones de la IA, comandos forzados
	*/

	// Evita meterte en la sala cerrada del stage 16
	if (EAGLE.stage == 16) {
		if ((EAGLE.pos_x >= 4030) && (EAGLE.pos_x <= 4033) && (EAGLE.ai_command == AI_MOVE_LEFT)) {
			// Decide si subir o bajar
			if ((rand() % 100) >= 50) {
				EAGLE.ai_command = AI_MOVE_UP;
			} else {
				EAGLE.ai_command = AI_MOVE_DOWN;
			}
			EAGLE.ai_ready = false;
		}
	}


	// Verifica la integridad de la IA
	if ((EAGLE.pos_x == EAGLE.old_x) && (EAGLE.pos_y == EAGLE.old_y)) {
		EAGLE.ai_sub ++;
		if (EAGLE.ai_sub > 5) {
			EAGLE.ai_ready = false;
			EAGLE.ai_error = true;
			if (!EAGLE.flip) {
				EAGLE.ai_command = AI_MOVE_LEFT;
			} else {
				EAGLE.ai_command = AI_MOVE_RIGHT;
			}
		}
	} else {
		EAGLE.ai_sub = 0;
	}

}



// Funcion AiEagleCheckBottom();
u8 AiEagleCheckBottom(s32 x, s32 y) {

	// Variables
	s32 pos_x = 0;			// Coordenadas
	s32 pos_y = y;
	u8 n = 0;				// Uso general
	u8 wall = 0;			// Bitmask de muros
	u8 stair = 0;			// Bitmask de las escaleras
	u8 result = AI_CAIR;	// Resultado

	// Analiza los tiles (BITMASK)
	for (n = 0; n < 8; n ++) {
		pos_x = (x - (n << 3) + 32);
		switch (NF_GetTile(MAINMAP_SLOT, pos_x, pos_y)) {
			case T_WALL:
				wall |= BIT(n);
				break;
			case T_STAIR:
				stair |= BIT(n);
			default:
				break;
		}
	}

	// Calcula el resultado
	if (wall != 0) {
		result = AI_CFLOOR;
	}
	if ((stair & 0x7e) == 0x7e) {
		result = AI_CSTAIR;
	}
	
	// Devuelve el resultado
	return result;

}



// Funcion AiEagleCheckTop();
u8 AiEagleCheckTop(s32 x, s32 y) {

	// Variables
	s32 pos_x = 0;			// Coordenadas
	s32 pos_y = y;
	u8 n = 0;				// Uso general
	u8 wall = 0;			// Bitmask de muros
	u8 stair = 0;			// Bitmask de las escaleras
	u8 result = AI_CAIR;	// Resultado

	// Analiza los tiles (BITMASK)
	for (n = 0; n < 8; n ++) {
		pos_x = (x - (n << 3) + 32);
		switch (NF_GetTile(MAINMAP_SLOT, pos_x, pos_y)) {
			case T_WALL:
				wall |= BIT(n);
				break;
			case T_STAIR:
				stair |= BIT(n);
			default:
				break;
		}
	}

	// Calcula el resultado
	if (wall != 0) {
		result = AI_CWALL;
	}
	if ((stair & 0x7e) == 0x7e) {
		result = AI_CSTAIR;
	}

	// Devuelve el resultado
	return result;

}



// Funcion EagleAiFlyRight();
void EagleAiFlyRight(void) {

	// Variables
	u8 right = 0, down = 0;

	// Valor por defecto
	EAGLE.ai_right = true;
	EAGLE.ai_up = false;
	EAGLE.ai_down = false;

	// IA, analiza tu derecha
	right = AiCheckRight(EAGLE.pos_x, EAGLE.pos_y, EAGLE.right);
	down = AiCheckBottom(EAGLE.pos_x, EAGLE.pos_y, EAGLE.mov_y);

	// Si hay un muro, cambio de sentido
	if (right == AI_CWALL) {
		EAGLE.ai_right = false;
		EAGLE.ai_left = true;
		EAGLE.ai_command = AI_MOVE_LEFT;
		EAGLE.ai_ready = true;
	} else {
		// Si hay un escalon, gana altura
		if (right == AI_CHALFWALL) {
			EAGLE.ai_up = true;
		} else {
			// Ajusta la altura, estas demasiado alto?
			if (EAGLE.ai_ready || EAGLE.ai_error) {
				if ((down == AI_CAIR) || (down == AI_CSTEEP) || (down == AI_CHALFSTEEP)) {
					EAGLE.ai_down = true;
				}
			}
			// Ajusta la altura, estas demasiado bajo?
			down = AiCheckBottom(EAGLE.pos_x, EAGLE.pos_y, (EAGLE.mov_y - 1));
			if (down == AI_CFLOOR) {
				EAGLE.ai_up = true;
			}
		}
	}

}



// Funcion EagleAiFlyLeft();
void EagleAiFlyLeft(void) {

	// Variables
	u8 left = 0, down = 0;

	// Valor por defecto
	EAGLE.ai_left = true;
	EAGLE.ai_up = false;
	EAGLE.ai_down = false;

	// IA, analiza tu izquierda
	left = AiCheckLeft(EAGLE.pos_x, EAGLE.pos_y, EAGLE.left);
	down = AiCheckBottom(EAGLE.pos_x, EAGLE.pos_y, EAGLE.mov_y);

	// Si hay un muro, cambio de sentido
	if (left == AI_CWALL) {
		EAGLE.ai_right = true;
		EAGLE.ai_left = false;
		EAGLE.ai_command = AI_MOVE_RIGHT;
		EAGLE.ai_ready = true;
	} else {
		// Si hay un escalon, gana altura
		if (left == AI_CHALFWALL) {
			EAGLE.ai_up = true;
		} else {
			// Ajusta la altura, estas demasiado alto?
			if (EAGLE.ai_ready || EAGLE.ai_error) {
				if ((down == AI_CAIR) || (down == AI_CSTEEP) || (down == AI_CHALFSTEEP)) {
					EAGLE.ai_down = true;
				}
			}
			// Ajusta la altura, estas demasiado bajo?
			down = AiCheckBottom(EAGLE.pos_x, EAGLE.pos_y, (EAGLE.mov_y - 1));
			if (down == AI_CFLOOR) {
				EAGLE.ai_up = true;
			}
		}
	}

}



// Funcion EagleAiFlyDown();
void EagleAiFlyDown(void) {

	// Variables
	u8 down = 0;
	u8 bottom = 0;
	s32 y = (EAGLE.pos_y - STAGE[EAGLE.stage].stg_top);

	// Valor por defecto
	EAGLE.ai_right = false;
	EAGLE.ai_left = false;
	EAGLE.ai_down = true;

	// IA, analiza lo que tienes debajo
	down = AiEagleCheckBottom(EAGLE.pos_x, (EAGLE.pos_y + EAGLE.mov_y));
	bottom = NF_GetTile(MAINMAP_SLOT, EAGLE.pos_x, (EAGLE.pos_y + 33));

	// Si has tocado el suelo...
	if ((down == AI_CFLOOR) || (bottom == T_WALL)) {
		if (EAGLE.flip) {
			EAGLE.ai_command = AI_MOVE_LEFT;
		} else {
			EAGLE.ai_command = AI_MOVE_RIGHT;
		}
	}

	// Si has cambiado de stage...
	if (EAGLE.stage != EAGLE.ai_stage) {
		if (y > 96) {
			if ((rand() % 100) >= 50) {
				if (EAGLE.flip) {
					EAGLE.ai_command = AI_MOVE_LEFT;
				} else {
					EAGLE.ai_command = AI_MOVE_RIGHT;
				}
			} else {
				EAGLE.ai_stage = EAGLE.stage;
			}
		}
	}

}



// Funcion EagleAiFlyUp();
void EagleAiFlyUp(void) {

	// Variables
	u8 up = 0;
	u8 top = 0;
	s32 y = (EAGLE.pos_y - STAGE[EAGLE.stage].stg_top);

	// Valor por defecto
	EAGLE.ai_right = false;
	EAGLE.ai_left = false;
	EAGLE.ai_up = true;

	// IA, analiza lo que tienes encima
	up = AiEagleCheckTop(EAGLE.pos_x, (EAGLE.pos_y - 96));
	top = NF_GetTile(MAINMAP_SLOT, EAGLE.pos_x, (EAGLE.pos_y - 32));

	// Si has tocado el suelo...
	if ((up == AI_CWALL) || (top == T_WALL)) {
		if (EAGLE.flip) {
			EAGLE.ai_command = AI_MOVE_LEFT;
		} else {
			EAGLE.ai_command = AI_MOVE_RIGHT;
		}
	}

	// Si has cambiado de stage...
	if (EAGLE.stage != EAGLE.ai_stage) {
		if (y < 96) {
			if ((rand() % 100) >= 50) {
				if (EAGLE.flip) {
					EAGLE.ai_command = AI_MOVE_LEFT;
				} else {
					EAGLE.ai_command = AI_MOVE_RIGHT;
				}
			} else {
				EAGLE.ai_stage = EAGLE.stage;
			}
		}
	}

}
