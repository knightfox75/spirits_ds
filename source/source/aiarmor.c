/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de la IA de la Armadura

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





// Funcion ArmorAi();
void ArmorAi(void) {

	// Detecta si estas cayendo y toma el control de la IA
	ArmorAiDetectFall();


	// Ejecuta el comando de la IA seleccionado
	switch (ARMOR.ai_command) {
		
		//Caida libre
		case AI_FALL:
			ArmorAiFall();
			break;

		// Andar a la derecha
		case AI_WALK_RIGHT:
			ArmorAiWalkRight();
			break;

		// Andar a la izquierda
		case AI_WALK_LEFT:
			ArmorAiWalkLeft();
			break;

		// Saltar
		case AI_JUMP:
			ArmorAiJump();
			break;

		// Bajar las escaleras
		case AI_STAIRS_DOWN:
			ArmorAiDownStairs();
			break;

		// Subir las escaleras
		case AI_STAIRS_UP:
			ArmorAiUpStairs();
			break;

		// Subir los escalones a la derecha
		case AI_STEEPS_UP_RIGHT:
			ArmorAiUpSteepsRight();
			break;

		// Subir los escalones a la izquierda
		case AI_STEEPS_UP_LEFT:
			ArmorAiUpSteepsLeft();
			break;

		// Bajar escalones
		case AI_STEEPS_DOWN:
			ArmorAiDownSteeps();
			break;

		// Evento especial en el Stage 7
		case AI_STAGE7:
			ArmorAiStage7();
			break;

		// Nada, error trap
		default:
			break;

	}

}



// Funcion ArmorAiDetectFall();
void ArmorAiDetectFall(void) {

	// Detecta si estas cayendo y toma el control de la IA
	if ((ARMOR.ai_command != AI_STEEPS_DOWN) && ARMOR.fall) {
		// Bloquea la IA
		ARMOR.ai_command = AI_FALL;
		ARMOR.ai_ready = false;
		ARMOR.ai_timer = AI_TIMER;
		// Bloquea el teclado
		ARMOR.ai_jump = false;
		ARMOR.ai_right = false;
		ARMOR.ai_left = false;
	}

}



// Funcion ArmorAiFall();
void ArmorAiFall(void) {

	// Si ya no estas cayendo...
	if (!ARMOR.fall) {
		// Restaura la IA
		ARMOR.ai_ready = true;
		ARMOR.ai_timer = 0;
		// Y el movimiento por defecto
		if (ARMOR.flip) {
			ARMOR.ai_command = AI_WALK_LEFT;
			ARMOR.ai_left = true;
		} else {
			ARMOR.ai_command = AI_WALK_RIGHT;
			ARMOR.ai_right = true;
		}
	}

}



// Funcion ArmorAiWalkRight();
void ArmorAiWalkRight(void) {

	// Variables
	u8 right = 0;
	u8 ceil = 0;
	u8 floor = 0;

	// IA, analiza tu derecha
	right = AiCheckRight(ARMOR.pos_x, ARMOR.pos_y, ARMOR.right);

	// Segun lo que tengas delante
	switch (right) {

		// Tienes un muro delante
		case AI_CWALL:
			// Cambia el sentido
			ARMOR.ai_right = false;
			ARMOR.ai_left = true;
			ARMOR.ai_command = AI_WALK_LEFT;
			break;

		// Tienes un semimuro delante
		case AI_CHALFWALL:
			// Si puedes saltar
			if (ARMOR.can_jump) {	// Salta
				ARMOR.ai_command = AI_JUMP;
				ARMOR.ai_jump = true;
			} else {				// Cambia de sentido
				ARMOR.ai_right = false;
				ARMOR.ai_left = true;
				ARMOR.ai_command = AI_WALK_LEFT;
			}
			break;


		// Por defecto, mira si hay alguna escalera, precipicio, etc.
		default:

			// Lee el suelo
			floor = AiCheckBottom(ARMOR.pos_x, ARMOR.pos_y, ARMOR.down);
			// y el techo
			ceil = AiCheckTop(ARMOR.pos_x, ARMOR.pos_y, ARMOR.up);

			// Si la IA esta bloqueada, pero estas andando normalmente, desbloqueala
			if (ARMOR.ai_timer > 0) {
				ARMOR.ai_timer --;
			}
			if (!ARMOR.ai_ready && (floor == AI_CFLOOR) && (ceil == AI_CAIR) && (ARMOR.ai_timer == 0)) {
				ARMOR.ai_ready = true;
			}

			// Salto de precipicios
			if (ARMOR.ai_ready) {
				// Si hay un precipicio, decide si saltarlo o caerse
				if (floor == AI_CLEFTFLOOR) {
					// Bloquea la IA
					ARMOR.ai_ready = false;
					ARMOR.ai_timer = AI_TIMER;
					// Decide si saltar (50%), darse la vuelta (25%) o caerse (25%)
					if ((rand() % 100) >= 50) {
						// Saltalo
						ARMOR.ai_command = AI_JUMP;
						ARMOR.ai_jump = true;
					} else {
						if ((rand() % 100) >= 50) {
							// Date la vuelta
							ARMOR.ai_right = false;
							ARMOR.ai_left = true;
							ARMOR.ai_command = AI_WALK_LEFT;
						}
					}
				}
			}

			// Subir escalones
			if (ARMOR.ai_ready) {
				// Si delante tienes un escalon, subelo
				if (right == AI_CSTEEP) {
					// Bloquea la IA
					ARMOR.ai_ready = false;
					ARMOR.ai_timer = AI_TIMER;
					// Decide si subirlos
					if ((rand() % 100) >= 25) {
						// Comando
						ARMOR.ai_command = AI_STEEPS_UP_RIGHT;
					}
				}
			}

			// Escaleras y bajada de escalones
			ArmorAiCheckStairs(floor, ceil);

			break;
	}

}



// Funcion ArmorAiWalkLeft();
void ArmorAiWalkLeft(void) {

	// Variables
	u8 left = 0;
	u8 ceil = 0;
	u8 floor = 0;

	// IA, analiza tu izquierda
	left = AiCheckLeft(ARMOR.pos_x, ARMOR.pos_y, ARMOR.left);

	// Segun lo que tengas delante
	switch (left) {

		// Tienes un muro delante
		case AI_CWALL:
			// Cambia el sentido
			ARMOR.ai_right = true;
			ARMOR.ai_left = false;
			ARMOR.ai_command = AI_WALK_RIGHT;
			break;

		// Tienes un semimuro delante
		case AI_CHALFWALL:
			// Si puedes saltar
			if (ARMOR.can_jump) {	// Salta
				ARMOR.ai_command = AI_JUMP;
				ARMOR.ai_jump = true;
			} else {				// Cambia de sentido
				ARMOR.ai_right = true;
				ARMOR.ai_left = false;
				ARMOR.ai_command = AI_WALK_RIGHT;
			}
			break;


		// Por defecto, mira si hay alguna escalera, precipicio, etc.
		default:

			// Lee el suelo
			floor = AiCheckBottom(ARMOR.pos_x, ARMOR.pos_y, ARMOR.down);
			// y el techo
			ceil = AiCheckTop(ARMOR.pos_x, ARMOR.pos_y, ARMOR.up);

			// Si la IA esta bloqueada, pero estas andando normalmente, desbloqueala
			if (ARMOR.ai_timer > 0) {
				ARMOR.ai_timer --;
			}
			if (!ARMOR.ai_ready && (floor == AI_CFLOOR) && (ceil == AI_CAIR) && (ARMOR.ai_timer == 0)) {
				ARMOR.ai_ready = true;
			}

			// Salto de precipicios
			if (ARMOR.ai_ready) {
				// Si hay un precipicio, decide si saltarlo o caerse
				if (floor == AI_CRIGHTFLOOR) {
					// Bloquea la IA
					ARMOR.ai_ready = false;
					ARMOR.ai_timer = AI_TIMER;
					// Decide si saltar (50%), darse la vuelta (25%) o caerse (25%)
					if ((rand() % 100) >= 50) {
						/*
						Lista de excepciones
						Stage 18 - Escalera del dragon
						*/
						if (ARMOR.stage != 18) {
						/*
						Fin de la lista de excepciones
						*/
							// Saltalo
							ARMOR.ai_command = AI_JUMP;
							ARMOR.ai_jump = true;
						}
					} else {
						if ((rand() % 100) >= 50) {
							// Date la vuelta
							ARMOR.ai_right = true;
							ARMOR.ai_left = false;
							ARMOR.ai_command = AI_WALK_RIGHT;
						}
					}
				}
			}

			// Subir escalones
			if (ARMOR.ai_ready) {
				// Si delante tienes un escalon, subelo
				if (left == AI_CSTEEP) {
					// Bloquea la IA
					ARMOR.ai_ready = false;
					ARMOR.ai_timer = AI_TIMER;
					// Decide si subirlos
					if ((rand() % 100) >= 25) {
						// Comando
						ARMOR.ai_command = AI_STEEPS_UP_LEFT;
					}
				}
			}

			// Escaleras y bajada de escalones
			ArmorAiCheckStairs(floor, ceil);

			/*
			Evento especial - Saltos del Stage 7 al 6
			Si estas en la caldera, subete en ella
			*/
			if (ARMOR.ai_ready) {
				if (ARMOR.stage == 7) {
					if (ARMOR.pos_x == 120) {
						ARMOR.ai_command = AI_STAGE7;
						ARMOR.ai_sub = 0;
					}
				}
			}

			break;

	}

}



// Funcion ArmorAiCheckStairs();
void ArmorAiCheckStairs(u8 floor, u8 ceil) {

	// Bajar la escalera
	if (ARMOR.ai_ready) {
		/*
		Lista de excepciones
		Stage 18 - Escalera del dragon
		*/
		if (ARMOR.stage != 18) {
		/*
		Fin de la lista de excepciones
		*/
			// Si estas en unas escaleras, decide si bajarlas
			if (
				ARMOR.stair_down
				&&
				(floor == AI_CSTAIR)
				&&
				(NF_GetTile(MAINMAP_SLOT, (ARMOR.pos_x - 23), ARMOR.pos_y) == T_STAIR)
				&&
				(NF_GetTile(MAINMAP_SLOT, (ARMOR.pos_x + 24), ARMOR.pos_y) == T_STAIR)
				) {
				// Bloquea la IA
				ARMOR.ai_ready = false;
				ARMOR.ai_timer = AI_TIMER;
				// Decide si bajarla...
				if ((rand() % 100) >= 50) {
					ARMOR.ai_command = AI_STAIRS_DOWN;
					ARMOR.ai_down = true;
				}
			}
		}
	}

	// Subir la escalera
	if (ARMOR.ai_ready) {
		// Si estas en unas escaleras, decide si bajarlas
		if (
			ARMOR.stair_up
			&&
			(ceil == AI_CSTAIR)
			&&
			(NF_GetTile(MAINMAP_SLOT, (ARMOR.pos_x - 23), ARMOR.pos_y) == T_STAIR)
			&&
			(NF_GetTile(MAINMAP_SLOT, (ARMOR.pos_x + 24), ARMOR.pos_y) == T_STAIR)
			) {
			// Bloquea la IA
			ARMOR.ai_ready = false;
			ARMOR.ai_timer = AI_TIMER;
			// Decide si bajarla...
			if ((rand() % 100) >= 50) {
				ARMOR.ai_command = AI_STAIRS_UP;
				ARMOR.ai_up = true;
			}
		}
	}

	// Bajar escalones
	if (ARMOR.ai_ready) {
		// Si estas pisando un escalon
		if (floor == AI_CSTEEP) {
			// Comando
			ARMOR.ai_command = AI_STEEPS_DOWN;
		}
	}

}



// Funcion ArmorAiJump();
void ArmorAiJump(void) {

	// Si se ha alcanzado la altura maxima del salto, o has tocado techo...
	if (!ARMOR.jump_up) ARMOR.ai_jump = false;

	// Si ya se ha realizado el salto
	if (!ARMOR.is_jump) {
		// Y restablece la direccion
		if (ARMOR.flip) {
			ARMOR.ai_command = AI_WALK_LEFT;
		} else {
			ARMOR.ai_command = AI_WALK_RIGHT;
		}
	}

}



// Funcion ArmorAiDownStairs();
void ArmorAiDownStairs(void) {

	// Si se ha alcanzado la altura maxima del salto, o has tocado techo...
	if (!ARMOR.stair_down) {
		// Cancela la bajada
		ARMOR.ai_down = false;
		// Y restablece la direccion
		if (ARMOR.flip) {
			ARMOR.ai_command = AI_WALK_LEFT;
		} else {
			ARMOR.ai_command = AI_WALK_RIGHT;
		}
	}

}



// Funcion ArmorAiUpStairs();
void ArmorAiUpStairs(void) {

	// Si se ha alcanzado la altura maxima del salto, o has tocado techo...
	if (!ARMOR.stair_up) {
		// Cancela la subida
		ARMOR.ai_up = false;
		// Y restablece la direccion
		if (ARMOR.flip) {
			ARMOR.ai_command = AI_WALK_LEFT;
		} else {
			ARMOR.ai_command = AI_WALK_RIGHT;
		}
	}

}



// Funcion ArmorAiUpSteepsRight();
void ArmorAiUpSteepsRight(void) {

	// Variables
	u8 right = 0;
	u8 floor = 0;
	u8 ceil = 0;

	// Lee el entorno
	right = AiCheckRight(ARMOR.pos_x, ARMOR.pos_y, ARMOR.right);
	floor = AiCheckBottom(ARMOR.pos_x, ARMOR.pos_y, ARMOR.down);
	ceil = AiCheckTop(ARMOR.pos_x, ARMOR.pos_y, ARMOR.up);

	// Si tienes un escalon delante o debajo, y puedes saltar, hazlo
	if (!ARMOR.is_jump) {
		if ((right == AI_CSTEEP) || (floor == AI_CSTEEP) || (floor == AI_CHALFSTEEP)) {
			ARMOR.ai_jump = true;
			if (right == AI_CSTEEP) {
				ARMOR.ai_shortjump = true;
			} else {
				ARMOR.ai_shortjump = false;
			}
		} else {
			// Si no estas saltando y tocas algo que no es un escalon ni aire
			if ((floor != AI_CAIR) || (right != AI_CAIR)) {
				// Cancela el salto
				ARMOR.ai_jump = false;
				// Y restablece la direccion
				if (ARMOR.flip) {
					ARMOR.ai_command = AI_WALK_LEFT;
				} else {
					ARMOR.ai_command = AI_WALK_RIGHT;
				}
			}
		}
	} else {
		// Limita la altura del salto para subir los escalones sin problemas
		if (
			(ARMOR.ai_shortjump && (ARMOR.jump_height >= AI_JUMP_HEIGHT))
			||
			!ARMOR.jump_up
			) {
			ARMOR.ai_jump = false;
		}
	}

	// Si estas saltando y has tocado techo con la cabeza... cancela el salto
	if (ARMOR.is_jump && (ceil == AI_CWALL)) {
		ARMOR.ai_jump = false;
		// Y restablece la direccion
		if (right == AI_CWALL) {
			if (ARMOR.flip) {
				ARMOR.ai_command = AI_WALK_LEFT;
			} else {
				ARMOR.ai_command = AI_WALK_RIGHT;
			}
		}
	}

}



// Funcion ArmorAiUpSteepsLeft();
void ArmorAiUpSteepsLeft(void) {

	// Variables
	u8 left = 0;
	u8 floor = 0;
	u8 ceil = 0;

	// Lee el entorno
	left = AiCheckLeft(ARMOR.pos_x, ARMOR.pos_y, ARMOR.left);
	floor = AiCheckBottom(ARMOR.pos_x, ARMOR.pos_y, ARMOR.down);
	ceil = AiCheckTop(ARMOR.pos_x, ARMOR.pos_y, ARMOR.up);

	// Si tienes un escalon delante o debajo, y puedes saltar, hazlo
	if (!ARMOR.is_jump) {
		if ((left == AI_CSTEEP) || (floor == AI_CSTEEP) || (floor == AI_CHALFSTEEP)) {
			ARMOR.ai_jump = true;
			if (left == AI_CSTEEP) {
				ARMOR.ai_shortjump = true;
			} else {
				ARMOR.ai_shortjump = false;
			}
		} else {
			// Si no estas saltando y tocas algo que no es un escalon ni aire
			if ((floor != AI_CAIR) || (left != AI_CAIR)) {
				// Cancela el salto
				ARMOR.ai_jump = false;
				// Y restablece la direccion
				if (ARMOR.flip) {
					ARMOR.ai_command = AI_WALK_LEFT;
				} else {
					ARMOR.ai_command = AI_WALK_RIGHT;
				}
			}
		}
	} else {
		// Limita la altura del salto para subir los escalones sin problemas
		if (
			(ARMOR.ai_shortjump && (ARMOR.jump_height >= AI_JUMP_HEIGHT))
			||
			!ARMOR.jump_up
			) {
			ARMOR.ai_jump = false;
		}
	}

	// Si estas saltando y has tocado techo con la cabeza... cancela el salto
	if (ARMOR.is_jump && (ceil == AI_CWALL)) {
		ARMOR.ai_jump = false;
		// Y restablece la direccion si es necesario
		if (left == AI_CWALL) {
			if (ARMOR.flip) {
				ARMOR.ai_command = AI_WALK_LEFT;
			} else {
				ARMOR.ai_command = AI_WALK_RIGHT;
			}
		}
	}

}



// Funcion ArmorAiDownSteeps();
void ArmorAiDownSteeps(void) {

	// Variables
	u8 right = 0;
	u8 left = 0;
	u8 floor = 0;
	u8 ceil = 0;

	// Lee el entorno
	right = AiCheckRight(ARMOR.pos_x, ARMOR.pos_y, ARMOR.right);
	left = AiCheckLeft(ARMOR.pos_x, ARMOR.pos_y, ARMOR.left);
	floor = AiCheckBottom(ARMOR.pos_x, ARMOR.pos_y, ARMOR.down);
	ceil = AiCheckTop(ARMOR.pos_x, ARMOR.pos_y, ARMOR.up);

	// Si estas a medio escalon y la IA esta disponible...
	if ((floor == AI_CHALFSTEEP) && (ARMOR.ai_ready)) {
		// Bloquea la IA
		ARMOR.ai_ready = false;
		ARMOR.ai_timer = AI_TIMER;
		// Decide si saltar o no el escalon
		if ((rand() % 100) >= 25) {
			ARMOR.ai_command = AI_JUMP;
			ARMOR.ai_jump = true;
		}
	}

	// Si ya tocas de pies en el suelo o bloqueado en un lateral, pon la IA en modo normal
	if (
		((floor == AI_CFLOOR) && (ceil == AI_CAIR))
		||
		(right != AI_CAIR)
		||
		(left != AI_CAIR)
		) {
		if (ARMOR.flip) {
			ARMOR.ai_command = AI_WALK_LEFT;
		} else {
			ARMOR.ai_command = AI_WALK_RIGHT;
		}
	}

}



// Funcion ArmorAiStage7();
void ArmorAiStage7(void) {

	// Nucleo
	switch (ARMOR.ai_sub) {

		// Realiza el salto vertical
		case 0:
			ARMOR.ai_left = false;
			ARMOR.ai_jump = true;
			ARMOR.ai_sub = 1;
			break;

		// Espera a finalizar el salto y camina a la izquierda
		case 1:
			if (!ARMOR.jump_up) {
				ARMOR.ai_left = true;
				ARMOR.ai_jump = false;
				ARMOR.ai_sub = 2;
			}
			break;

		// Anda a la izquierda hasta el borde y salta al peldaño
		case 2:
			if (ARMOR.pos_x == 88) {
				ARMOR.ai_jump = true;
				ARMOR.ai_timer = 0;		// Error trap, deteccion si ha fallado el salto
				ARMOR.ai_sub = 3;
			}
			break;

		// Espera a completar el salto y salta en vertical
		case 3:
			if (!ARMOR.jump_up) {
				ARMOR.ai_left = false;
				ARMOR.ai_sub = 4;
			}
			break;

		// Salta en vertical hasta el siguiente stage
		case 4:
			if (ARMOR.stage == 6) {
				ARMOR.ai_right = true;
				ARMOR.ai_jump = false;
				ARMOR.ai_sub = 5;
			} else {
				// Error trap, detecta si ha fallado el salto
				ARMOR.ai_timer ++;
				if (ARMOR.ai_timer >= 120) {
					// Date la vuelta a la derecha y cancela la secuencia
					ARMOR.ai_left = false;
					ARMOR.ai_right = true;
					ARMOR.ai_jump = false;
					ARMOR.ai_timer = 0;
					ARMOR.ai_command = AI_WALK_RIGHT;
					ARMOR.ai_sub = 255;
				}
			}
			break;

		// Espera a llegar al borde y salta
		case 5:
			if (ARMOR.pos_x == 50) {
				ARMOR.ai_jump = true;
				ARMOR.ai_sub = 6;
			}
			break;

		// Espera a terminar el salto y anda a la derecha
		case 6:
			if (!ARMOR.is_jump) {
				ARMOR.ai_jump = false;
				ARMOR.ai_command = AI_WALK_RIGHT;
			}
			break;

		// Nada, error trap
		default:
			break;

	}

}
