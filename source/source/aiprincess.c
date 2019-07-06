/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de la IA de la Princesa

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





// Funcion PrincessAi();
void PrincessAi(void) {

	// Detecta si estas cayendo y toma el control de la IA
	PrincessAiDetectFall();


	// Ejecuta el comando de la IA seleccionado
	switch (PRINCESS.ai_command) {
		
		//Caida libre
		case AI_FALL:
			PrincessAiFall();
			break;

		// Andar a la derecha
		case AI_WALK_RIGHT:
			PrincessAiWalkRight();
			break;

		// Andar a la izquierda
		case AI_WALK_LEFT:
			PrincessAiWalkLeft();
			break;

		// Saltar
		case AI_JUMP:
			PrincessAiJump();
			break;

		// Bajar las escaleras
		case AI_STAIRS_DOWN:
			PrincessAiDownStairs();
			break;

		// Subir las escaleras
		case AI_STAIRS_UP:
			PrincessAiUpStairs();
			break;

		// Subir los escalones a la derecha
		case AI_STEEPS_UP_RIGHT:
			PrincessAiUpSteepsRight();
			break;

		// Subir los escalones a la izquierda
		case AI_STEEPS_UP_LEFT:
			PrincessAiUpSteepsLeft();
			break;

		// Bajar escalones
		case AI_STEEPS_DOWN:
			PrincessAiDownSteeps();
			break;

		// Evento especial en el Stage 7
		case AI_STAGE7:
			PrincessAiStage7();
			break;

		// Nada, error trap
		default:
			break;

	}

}



// Funcion PrincessAiDetectFall();
void PrincessAiDetectFall(void) {

	// Detecta si estas cayendo y toma el control de la IA
	if ((PRINCESS.ai_command != AI_STEEPS_DOWN) && PRINCESS.fall) {
		// Bloquea la IA
		PRINCESS.ai_command = AI_FALL;
		PRINCESS.ai_ready = false;
		PRINCESS.ai_timer = AI_TIMER;
		// Bloquea el teclado
		PRINCESS.ai_jump = false;
		PRINCESS.ai_right = false;
		PRINCESS.ai_left = false;
	}

}



// Funcion PrincessAiFall();
void PrincessAiFall(void) {

	// Si ya no estas cayendo...
	if (!PRINCESS.fall) {
		// Restaura la IA
		PRINCESS.ai_ready = true;
		PRINCESS.ai_timer = 0;
		// Y el movimiento por defecto
		if (PRINCESS.flip) {
			PRINCESS.ai_command = AI_WALK_LEFT;
			PRINCESS.ai_left = true;
		} else {
			PRINCESS.ai_command = AI_WALK_RIGHT;
			PRINCESS.ai_right = true;
		}
	}

}



// Funcion PrincessAiWalkRight();
void PrincessAiWalkRight(void) {

	// Variables
	u8 right = 0;
	u8 ceil = 0;
	u8 floor = 0;

	// IA, analiza tu derecha
	right = AiCheckRight(PRINCESS.pos_x, PRINCESS.pos_y, PRINCESS.right);

	// Segun lo que tengas delante
	switch (right) {

		// Tienes un muro delante
		case AI_CWALL:
			// Cambia el sentido
			PRINCESS.ai_right = false;
			PRINCESS.ai_left = true;
			PRINCESS.ai_command = AI_WALK_LEFT;
			break;

		// Tienes un semimuro delante
		case AI_CHALFWALL:
			// Si puedes saltar
			if (PRINCESS.can_jump) {	// Salta
				PRINCESS.ai_command = AI_JUMP;
				PRINCESS.ai_jump = true;
			} else {				// Cambia de sentido
				PRINCESS.ai_right = false;
				PRINCESS.ai_left = true;
				PRINCESS.ai_command = AI_WALK_LEFT;
			}
			break;


		// Por defecto, mira si hay alguna escalera, precipicio, etc.
		default:

			// Lee el suelo
			floor = AiCheckBottom(PRINCESS.pos_x, PRINCESS.pos_y, PRINCESS.down);
			// y el techo
			ceil = AiCheckTop(PRINCESS.pos_x, PRINCESS.pos_y, PRINCESS.up);

			// Si la IA esta bloqueada, pero estas andando normalmente, desbloqueala
			if (PRINCESS.ai_timer > 0) {
				PRINCESS.ai_timer --;
			}
			if (!PRINCESS.ai_ready && (floor == AI_CFLOOR) && (ceil == AI_CAIR) && (PRINCESS.ai_timer == 0)) {
				PRINCESS.ai_ready = true;
			}

			// Salto de precipicios
			if (PRINCESS.ai_ready) {
				// Si hay un precipicio, decide si saltarlo o caerse
				if (floor == AI_CLEFTFLOOR) {
					// Bloquea la IA
					PRINCESS.ai_ready = false;
					PRINCESS.ai_timer = AI_TIMER;
					// Decide si saltar (50%), darse la vuelta (25%) o caerse (25%)
					if ((rand() % 100) >= 50) {
						// Saltalo
						PRINCESS.ai_command = AI_JUMP;
						PRINCESS.ai_jump = true;
					} else {
						if ((rand() % 100) >= 50) {
							// Date la vuelta
							PRINCESS.ai_right = false;
							PRINCESS.ai_left = true;
							PRINCESS.ai_command = AI_WALK_LEFT;
						}
					}
				}
			}

			// Subir escalones
			if (PRINCESS.ai_ready) {
				// Si delante tienes un escalon, subelo
				if (right == AI_CSTEEP) {
					// Bloquea la IA
					PRINCESS.ai_ready = false;
					PRINCESS.ai_timer = AI_TIMER;
					// Decide si subirlos
					if ((rand() % 100) >= 25) {
						// Comando
						PRINCESS.ai_command = AI_STEEPS_UP_RIGHT;
					}
				}
			}

			// Escaleras y bajada de escalones
			PrincessAiCheckStairs(floor, ceil);

			break;
	}

}



// Funcion PrincessAiWalkLeft();
void PrincessAiWalkLeft(void) {

	// Variables
	u8 left = 0;
	u8 ceil = 0;
	u8 floor = 0;

	// IA, analiza tu izquierda
	left = AiCheckLeft(PRINCESS.pos_x, PRINCESS.pos_y, PRINCESS.left);

	// Segun lo que tengas delante
	switch (left) {

		// Tienes un muro delante
		case AI_CWALL:
			// Cambia el sentido
			PRINCESS.ai_right = true;
			PRINCESS.ai_left = false;
			PRINCESS.ai_command = AI_WALK_RIGHT;
			break;

		// Tienes un semimuro delante
		case AI_CHALFWALL:
			// Si puedes saltar
			if (PRINCESS.can_jump) {	// Salta
				PRINCESS.ai_command = AI_JUMP;
				PRINCESS.ai_jump = true;
			} else {				// Cambia de sentido
				PRINCESS.ai_right = true;
				PRINCESS.ai_left = false;
				PRINCESS.ai_command = AI_WALK_RIGHT;
			}
			break;


		// Por defecto, mira si hay alguna escalera, precipicio, etc.
		default:

			// Lee el suelo
			floor = AiCheckBottom(PRINCESS.pos_x, PRINCESS.pos_y, PRINCESS.down);
			// y el techo
			ceil = AiCheckTop(PRINCESS.pos_x, PRINCESS.pos_y, PRINCESS.up);

			// Si la IA esta bloqueada, pero estas andando normalmente, desbloqueala
			if (PRINCESS.ai_timer > 0) {
				PRINCESS.ai_timer --;
			}
			if (!PRINCESS.ai_ready && (floor == AI_CFLOOR) && (ceil == AI_CAIR) && (PRINCESS.ai_timer == 0)) {
				PRINCESS.ai_ready = true;
			}

			// Salto de precipicios
			if (PRINCESS.ai_ready) {
				// Si hay un precipicio, decide si saltarlo o caerse
				if (floor == AI_CRIGHTFLOOR) {
					// Bloquea la IA
					PRINCESS.ai_ready = false;
					PRINCESS.ai_timer = AI_TIMER;
					// Decide si saltar (50%), darse la vuelta (25%) o caerse (25%)
					if ((rand() % 100) >= 50) {
						/*
						Lista de excepciones
						Stage 18 - Escalera del dragon
						*/
						if (PRINCESS.stage != 18) {
						/*
						Fin de la lista de excepciones
						*/
							// Saltalo
							PRINCESS.ai_command = AI_JUMP;
							PRINCESS.ai_jump = true;
						}
					} else {
						if ((rand() % 100) >= 50) {
							// Date la vuelta
							PRINCESS.ai_right = true;
							PRINCESS.ai_left = false;
							PRINCESS.ai_command = AI_WALK_RIGHT;
						}
					}
				}
			}

			// Subir escalones
			if (PRINCESS.ai_ready) {
				// Si delante tienes un escalon, subelo
				if (left == AI_CSTEEP) {
					// Bloquea la IA
					PRINCESS.ai_ready = false;
					PRINCESS.ai_timer = AI_TIMER;
					// Decide si subirlos
					if ((rand() % 100) >= 25) {
						// Comando
						PRINCESS.ai_command = AI_STEEPS_UP_LEFT;
					}
				}
			}

			// Escaleras y bajada de escalones
			PrincessAiCheckStairs(floor, ceil);

			/*
			Evento especial - Saltos del Stage 7 al 6
			Si estas en la caldera, subete en ella
			*/
			if (PRINCESS.ai_ready) {
				if (PRINCESS.stage == 7) {
					if (PRINCESS.pos_x == 120) {
						PRINCESS.ai_command = AI_STAGE7;
						PRINCESS.ai_sub = 0;
					}
				}
			}

			break;

	}

}



// Funcion PrincessAiCheckStairs();
void PrincessAiCheckStairs(u8 floor, u8 ceil) {

	// Bajar la escalera
	if (PRINCESS.ai_ready) {
		/*
		Lista de excepciones
		Stage 18 - Escalera del dragon
		*/
		if (PRINCESS.stage != 18) {
		/*
		Fin de la lista de excepciones
		*/
			// Si estas en unas escaleras, decide si bajarlas
			if (
				PRINCESS.stair_down
				&&
				(floor == AI_CSTAIR)
				&&
				(NF_GetTile(MAINMAP_SLOT, (PRINCESS.pos_x - 23), PRINCESS.pos_y) == T_STAIR)
				&&
				(NF_GetTile(MAINMAP_SLOT, (PRINCESS.pos_x + 24), PRINCESS.pos_y) == T_STAIR)
				) {
				// Bloquea la IA
				PRINCESS.ai_ready = false;
				PRINCESS.ai_timer = AI_TIMER;
				// Decide si bajarla...
				if ((rand() % 100) >= 50) {
					PRINCESS.ai_command = AI_STAIRS_DOWN;
					PRINCESS.ai_down = true;
				}
			}
		}
	}

	// Subir la escalera
	if (PRINCESS.ai_ready) {
		// Si estas en unas escaleras, decide si bajarlas
		if (
			PRINCESS.stair_up
			&&
			(ceil == AI_CSTAIR)
			&&
			(NF_GetTile(MAINMAP_SLOT, (PRINCESS.pos_x - 23), PRINCESS.pos_y) == T_STAIR)
			&&
			(NF_GetTile(MAINMAP_SLOT, (PRINCESS.pos_x + 24), PRINCESS.pos_y) == T_STAIR)
			) {
			// Bloquea la IA
			PRINCESS.ai_ready = false;
			PRINCESS.ai_timer = AI_TIMER;
			// Decide si bajarla...
			if ((rand() % 100) >= 50) {
				PRINCESS.ai_command = AI_STAIRS_UP;
				PRINCESS.ai_up = true;
			}
		}
	}

	// Bajar escalones
	if (PRINCESS.ai_ready) {
		// Si estas pisando un escalon
		if (floor == AI_CSTEEP) {
			// Comando
			PRINCESS.ai_command = AI_STEEPS_DOWN;
		}
	}

}



// Funcion PrincessAiJump();
void PrincessAiJump(void) {

	// Si se ha alcanzado la altura maxima del salto, o has tocado techo...
	if (!PRINCESS.jump_up) PRINCESS.ai_jump = false;

	// Si ya se ha realizado el salto
	if (!PRINCESS.is_jump) {
		// Y restablece la direccion
		if (PRINCESS.flip) {
			PRINCESS.ai_command = AI_WALK_LEFT;
		} else {
			PRINCESS.ai_command = AI_WALK_RIGHT;
		}
	}

}



// Funcion PrincessAiDownStairs();
void PrincessAiDownStairs(void) {

	// Si se ha alcanzado la altura maxima del salto, o has tocado techo...
	if (!PRINCESS.stair_down) {
		// Cancela la bajada
		PRINCESS.ai_down = false;
		// Y restablece la direccion
		if (PRINCESS.flip) {
			PRINCESS.ai_command = AI_WALK_LEFT;
		} else {
			PRINCESS.ai_command = AI_WALK_RIGHT;
		}
	}

}



// Funcion PrincessAiUpStairs();
void PrincessAiUpStairs(void) {

	// Si se ha alcanzado la altura maxima del salto, o has tocado techo...
	if (!PRINCESS.stair_up) {
		// Cancela la subida
		PRINCESS.ai_up = false;
		// Y restablece la direccion
		if (PRINCESS.flip) {
			PRINCESS.ai_command = AI_WALK_LEFT;
		} else {
			PRINCESS.ai_command = AI_WALK_RIGHT;
		}
	}

}



// Funcion PrincessAiUpSteepsRight();
void PrincessAiUpSteepsRight(void) {

	// Variables
	u8 right = 0;
	u8 floor = 0;
	u8 ceil = 0;

	// Lee el entorno
	right = AiCheckRight(PRINCESS.pos_x, PRINCESS.pos_y, PRINCESS.right);
	floor = AiCheckBottom(PRINCESS.pos_x, PRINCESS.pos_y, PRINCESS.down);
	ceil = AiCheckTop(PRINCESS.pos_x, PRINCESS.pos_y, PRINCESS.up);

	// Si tienes un escalon delante o debajo, y puedes saltar, hazlo
	if (!PRINCESS.is_jump) {
		if ((right == AI_CSTEEP) || (floor == AI_CSTEEP) || (floor == AI_CHALFSTEEP)) {
			PRINCESS.ai_jump = true;
			if (right == AI_CSTEEP) {
				PRINCESS.ai_shortjump = true;
			} else {
				PRINCESS.ai_shortjump = false;
			}
		} else {
			// Si no estas saltando y tocas algo que no es un escalon ni aire
			if ((floor != AI_CAIR) || (right != AI_CAIR)) {
				// Cancela el salto
				PRINCESS.ai_jump = false;
				// Y restablece la direccion
				if (PRINCESS.flip) {
					PRINCESS.ai_command = AI_WALK_LEFT;
				} else {
					PRINCESS.ai_command = AI_WALK_RIGHT;
				}
			}
		}
	} else {
		// Limita la altura del salto para subir los escalones sin problemas
		if (
			(PRINCESS.ai_shortjump && (PRINCESS.jump_height >= AI_JUMP_HEIGHT))
			||
			!PRINCESS.jump_up
			) {
			PRINCESS.ai_jump = false;
		}
	}

	// Si estas saltando y has tocado techo con la cabeza... cancela el salto
	if (PRINCESS.is_jump && (ceil == AI_CWALL)) {
		PRINCESS.ai_jump = false;
		// Y restablece la direccion
		if (right == AI_CWALL) {
			if (PRINCESS.flip) {
				PRINCESS.ai_command = AI_WALK_LEFT;
			} else {
				PRINCESS.ai_command = AI_WALK_RIGHT;
			}
		}
	}

}



// Funcion PrincessAiUpSteepsLeft();
void PrincessAiUpSteepsLeft(void) {

	// Variables
	u8 left = 0;
	u8 floor = 0;
	u8 ceil = 0;

	// Lee el entorno
	left = AiCheckLeft(PRINCESS.pos_x, PRINCESS.pos_y, PRINCESS.left);
	floor = AiCheckBottom(PRINCESS.pos_x, PRINCESS.pos_y, PRINCESS.down);
	ceil = AiCheckTop(PRINCESS.pos_x, PRINCESS.pos_y, PRINCESS.up);

	// Si tienes un escalon delante o debajo, y puedes saltar, hazlo
	if (!PRINCESS.is_jump) {
		if ((left == AI_CSTEEP) || (floor == AI_CSTEEP) || (floor == AI_CHALFSTEEP)) {
			PRINCESS.ai_jump = true;
			if (left == AI_CSTEEP) {
				PRINCESS.ai_shortjump = true;
			} else {
				PRINCESS.ai_shortjump = false;
			}
		} else {
			// Si no estas saltando y tocas algo que no es un escalon ni aire
			if ((floor != AI_CAIR) || (left != AI_CAIR)) {
				// Cancela el salto
				PRINCESS.ai_jump = false;
				// Y restablece la direccion
				if (PRINCESS.flip) {
					PRINCESS.ai_command = AI_WALK_LEFT;
				} else {
					PRINCESS.ai_command = AI_WALK_RIGHT;
				}
			}
		}
	} else {
		// Limita la altura del salto para subir los escalones sin problemas
		if (
			(PRINCESS.ai_shortjump && (PRINCESS.jump_height >= AI_JUMP_HEIGHT))
			||
			!PRINCESS.jump_up
			) {
			PRINCESS.ai_jump = false;
		}
	}

	// Si estas saltando y has tocado techo con la cabeza... cancela el salto
	if (PRINCESS.is_jump && (ceil == AI_CWALL)) {
		PRINCESS.ai_jump = false;
		// Y restablece la direccion si es necesario
		if (left == AI_CWALL) {
			if (PRINCESS.flip) {
				PRINCESS.ai_command = AI_WALK_LEFT;
			} else {
				PRINCESS.ai_command = AI_WALK_RIGHT;
			}
		}
	}

}



// Funcion PrincessAiDownSteeps();
void PrincessAiDownSteeps(void) {

	// Variables
	u8 right = 0;
	u8 left = 0;
	u8 floor = 0;
	u8 ceil = 0;

	// Lee el entorno
	right = AiCheckRight(PRINCESS.pos_x, PRINCESS.pos_y, PRINCESS.right);
	left = AiCheckLeft(PRINCESS.pos_x, PRINCESS.pos_y, PRINCESS.left);
	floor = AiCheckBottom(PRINCESS.pos_x, PRINCESS.pos_y, PRINCESS.down);
	ceil = AiCheckTop(PRINCESS.pos_x, PRINCESS.pos_y, PRINCESS.up);

	// Si estas a medio escalon y la IA esta disponible...
	if ((floor == AI_CHALFSTEEP) && (PRINCESS.ai_ready)) {
		// Bloquea la IA
		PRINCESS.ai_ready = false;
		PRINCESS.ai_timer = AI_TIMER;
		// Decide si saltar o no el escalon
		if ((rand() % 100) >= 25) {
			PRINCESS.ai_command = AI_JUMP;
			PRINCESS.ai_jump = true;
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
		if (PRINCESS.flip) {
			PRINCESS.ai_command = AI_WALK_LEFT;
		} else {
			PRINCESS.ai_command = AI_WALK_RIGHT;
		}
	}

}



// Funcion PrincessAiStage7();
void PrincessAiStage7(void) {

	// Nucleo
	switch (PRINCESS.ai_sub) {

		// Realiza el salto vertical
		case 0:
			PRINCESS.ai_left = false;
			PRINCESS.ai_jump = true;
			PRINCESS.ai_sub = 1;
			break;

		// Espera a finalizar el salto y camina a la izquierda
		case 1:
			if (!PRINCESS.jump_up) {
				PRINCESS.ai_left = true;
				PRINCESS.ai_jump = false;
				PRINCESS.ai_sub = 2;
			}
			break;

		// Anda a la izquierda hasta el borde y salta al peldaño
		case 2:
			if (PRINCESS.pos_x == 88) {
				PRINCESS.ai_jump = true;
				PRINCESS.ai_timer = 0;		// Error trap, deteccion si ha fallado el salto
				PRINCESS.ai_sub = 3;
			}
			break;

		// Espera a completar el salto y salta en vertical
		case 3:
			if (!PRINCESS.jump_up) {
				PRINCESS.ai_left = false;
				PRINCESS.ai_sub = 4;
			}
			break;

		// Salta en vertical hasta el siguiente stage
		case 4:
			if (PRINCESS.stage == 6) {
				PRINCESS.ai_right = true;
				PRINCESS.ai_jump = false;
				PRINCESS.ai_sub = 5;
			} else {
				// Error trap, detecta si ha fallado el salto
				PRINCESS.ai_timer ++;
				if (PRINCESS.ai_timer >= 120) {
					// Date la vuelta a la derecha y cancela la secuencia
					PRINCESS.ai_left = false;
					PRINCESS.ai_right = true;
					PRINCESS.ai_jump = false;
					PRINCESS.ai_timer = 0;
					PRINCESS.ai_command = AI_WALK_RIGHT;
					PRINCESS.ai_sub = 255;
				}
			}
			break;

		// Espera a llegar al borde y salta
		case 5:
			if (PRINCESS.pos_x == 50) {
				PRINCESS.ai_jump = true;
				PRINCESS.ai_sub = 6;
			}
			break;

		// Espera a terminar el salto y anda a la derecha
		case 6:
			if (!PRINCESS.is_jump) {
				PRINCESS.ai_jump = false;
				PRINCESS.ai_command = AI_WALK_RIGHT;
			}
			break;

		// Nada, error trap
		default:
			break;

	}

}
