/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de gestion de los NPC
	(Princesa)

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





// Funcion PrincessCamHide();
void PrincessCamHide(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;


	/*
	-------------------------------------------------
		Gestion de las visibilidad de
		la Princesa
	-------------------------------------------------
	*/

	// Calcula la posicion del sprite en la pantalla
	spr_x = (PRINCESS.pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
	spr_y = (PRINCESS.pos_y - STAGE[stage].stg_top);
	// Calcula si esta en pantalla
	if (
		(spr_x < -32)
		||
		(spr_x > 287)
		||
		(spr_y < -32)
		||
		(spr_y > 223)
		||
		!PRINCESS.show
		) {
		// No lo esta
		PRINCESS.on_screen[screen] = false;
		PRINCESS.scr_x[screen] = -64;
		PRINCESS.scr_y[screen] = -64;
		// Destruye el sprite
		if (PRINCESS.created[screen]) {
			PRINCESS.created[screen] = false;
			NF_DeleteSprite(screen, PRINCESS_SPR_ID);
			NF_FreeSpriteGfx(screen, PRINCESS_SPR_ID);
		}
	}

}



// Funcion PrincessCamShow();
void PrincessCamShow(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;


	/*
	-------------------------------------------------
		Gestion de las visibilidad de
		la Princesa
	-------------------------------------------------
	*/

	// Calcula la posicion del sprite en la pantalla
	spr_x = (PRINCESS.pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
	spr_y = (PRINCESS.pos_y - STAGE[stage].stg_top);
	// Calcula si esta en pantalla
	if (
		(spr_x >= -32)
		&&
		(spr_x <= 287)
		&&
		(spr_y >= -32)
		&&
		(spr_y <= 223)
		&&
		PRINCESS.show
		) {
		// Esta en pantalla
		PRINCESS.on_screen[screen] = true;
		PRINCESS.scr_x[screen] = spr_x;
		PRINCESS.scr_y[screen] = spr_y;
		// Si no esta creado, crealo
		if (!PRINCESS.created[screen]) {
			PRINCESS.created[screen] = true;
			NF_VramSpriteGfx(screen, ID_PRINCESS, PRINCESS_SPR_ID, true);
			NF_CreateSprite(screen, PRINCESS_SPR_ID, PRINCESS_SPR_ID, NPC_SPR_PAL, spr_x, spr_y);
			NF_SpriteLayer(screen, PRINCESS_SPR_ID, SPRITES_LAYER);
		}
		// Actualiza el sprite
		NF_MoveSprite(screen, PRINCESS_SPR_ID, (spr_x - PRINCESS.spr_left), (spr_y - PRINCESS.spr_up));
		NF_SpriteFrame(screen, PRINCESS_SPR_ID, PRINCESS.frame);
		NF_HflipSprite(screen, PRINCESS_SPR_ID, PRINCESS.flip);
	}

}



// Funcion PrincessCheckRight();
u16 PrincessCheckRight(s8 add) {

	// Variables
	s32 x, y;
	s32 fx, fy;
	s32 start, end;
	s16 tile = 0;
	s16 result = T_AIR;

	// Variables de posicion
	fx = (PRINCESS.pos_fx >> 8);
	fy = (PRINCESS.pos_fy >> 8);

	// Calcula el rango de tiles a analizar
	x = (fx + PRINCESS.right + add);
	start = (fy - PRINCESS.up);
	end = (fy + PRINCESS.down);

	// Analiza los tiles del lateral (steps de 1/2 tile)
	for (y = start; y <= end; y += 4) {
		tile = NF_GetTile(MAINMAP_SLOT, x, y);
		// Si el tile es pared...
		if (tile == T_WALL) {
			result = T_WALL;
			y = end;
		}
	}

	// Devuelve el resultado
	return result;

}



// Funcion PrincessCheckLeft();
u16 PrincessCheckLeft(s8 add) {

	// Variables
	s32 x, y;
	s32 fx, fy;
	s32 start, end;
	s16 tile = 0;
	s16 result = T_AIR;

	// Variables de posicion
	fx = (PRINCESS.pos_fx >> 8);
	fy = (PRINCESS.pos_fy >> 8);

	// Calcula el rango de tiles a analizar
	x = (fx - PRINCESS.left - add);
	start = (fy - PRINCESS.up);
	end = (fy + PRINCESS.down);

	// Analiza los tiles del lateral (steps de 1/2 tile)
	for (y = start; y <= end; y += 4) {
		tile = NF_GetTile(MAINMAP_SLOT, x, y);
		// Si el tile es pared...
		if (tile == T_WALL) {
			result = T_WALL;
			y = end;
		}
	}

	// Devuelve el resultado
	return result;

}



// Funcion PrincessCheckUp();
u16 PrincessCheckUp(s8 add) {

	// Variables
	s32 x, y;
	s32 fx, fy;
	s32 start, end;
	s16 tile = 0;
	s16 result = T_AIR;
	s16 air = 0, stair = 0;

	// Variables de posicion
	fx = (PRINCESS.pos_fx >> 8);
	fy = (PRINCESS.pos_fy >> 8);

	// Calcula el rango de tiles a analizar
	y = (fy - PRINCESS.up - add);
	start = (fx - PRINCESS.left);
	end = (fx + PRINCESS.right);

	// Analiza los tiles del lateral (steps de 1 pixel)
	for (x = start; x <= end; x ++) {
		tile = NF_GetTile(MAINMAP_SLOT, x, y);
		// Si el tile es pared o puerta cerrada...
		switch (tile) {
			case T_WALL:	// Muros
				result = T_WALL;
				x = end;
				break;
			case T_STAIR:	// Escalera
				stair ++;
				break;
			case T_AIR:		// Aire
				air ++;
				break;
			default:		// Nada
				break;
		}
	}

	// Si no hay muro, decide el resultado
	if (result != T_WALL) {
		// Decide si es aire o pared
		if (air >= stair) {
			result = T_AIR;
		} else {
			result = T_STAIR;
		}
	}

	// Devuelve el resultado
	return result;

}



// Funcion PrincessCheckDown();
u16 PrincessCheckDown(s8 add) {

	// Variables
	s32 x, y;
	s32 fx, fy;
	s32 start, end;
	s16 tile = 0;
	s16 result = T_AIR;
	s16 air = 0, stair = 0;

	// Variables de posicion
	fx = (PRINCESS.pos_fx >> 8);
	fy = (PRINCESS.pos_fy >> 8);

	// Calcula el rango de tiles a analizar
	y = (fy + PRINCESS.down + add);
	start = (fx - PRINCESS.left);
	end = (fx + PRINCESS.right);

	// Analiza los tiles del lateral (steps de 1 pixel)
	for (x = start; x <= end; x ++) {
		tile = NF_GetTile(MAINMAP_SLOT, x, y);
		// Si el tile es pared o puerta cerrada...
		switch (tile) {
			case T_WALL:	// Muros
				result = T_WALL;
				x = end;
				break;
			case T_STEEP:	// Escalon
				result = T_STEEP;
				x = end;
				break;
			case T_STAIR:	// Escaleras
				stair ++;
				break;
			case T_AIR:		// Aire
				air ++;
				break;
			default:		// Nada
				break;
		}
	}

	// Si no hay muro o escalon, decide el resultado
	if ((result != T_WALL) && (result != T_STEEP)) {
		// Decide si es aire o pared
		if (air >= stair) {
			result = T_AIR;
		} else {
			result = T_STAIR;
		}
	}

	// Devuelve el resultado
	return result;

}



// Funcion PrincessFall();
void PrincessFall(void) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	u16 t_down = T_AIR;
	u16 t_inside = T_AIR;


	/*
	-------------------------------------------------
		Analiza las posibilidades
	-------------------------------------------------
	*/

	// Obten el tile inferior
	t_down = PrincessCheckDown(1);

	// Calcula si te vas a caer
	if (((t_down == T_AIR) && !PRINCESS.is_jump) || ((t_down == T_STEEP) && PRINCESS.force_down)) {
		// Se va a caer
		PRINCESS.fall = true;
		// Aceleracion inicial de la caida
		if (PRINCESS.air_speed == 0) {
			PRINCESS.air_speed = PRINCESS_AIR_MIN_SPEED;
		}
	} else {
		PRINCESS.fall = false;
	}


	/*
	-------------------------------------------------
		Aplica las acciones
	-------------------------------------------------
	*/

	// la princesa se cae
	if (PRINCESS.fall) {
		// Nueva posicion
		PRINCESS.pos_fy += PRINCESS.air_speed;
		// Calcula si te sales de los limites...
		t_down = PrincessCheckDown(1);
		if ((t_down == T_WALL) || (t_down == T_STEEP)) {
			// Si encuentras un muro
			if (t_down == T_WALL) {
				// Deten la caida
				PRINCESS.fall = false;
				PRINCESS.air_speed = 0;
				// Ajusta la princesa al nivel del suelo/escalon
				t_inside = PrincessCheckDown(0);
				while (t_inside == T_WALL) {
					// Ajusta la posicion
					PRINCESS.pos_fy -= 64;
					// Verifica de nuevo
					t_inside = PrincessCheckDown(0);
				}
			}
			// Si encuentras un escalon
			if (t_down == T_STEEP) {
				// Si no estas en un forzado de caida, ajustalo
				if (!PRINCESS.force_down) {
					// Deten la caida
					PRINCESS.fall = false;
					PRINCESS.air_speed = 0;
					// Ajusta la princesa al nivel del suelo/escalon
					t_inside = PrincessCheckDown(0);
					while (t_inside == T_STEEP) {
						// Ajusta la posicion
						PRINCESS.pos_fy -= 64;
						// Verifica de nuevo
						t_inside = PrincessCheckDown(0);
					}
				} else {
					// Aceleracion de la caida
					if (PRINCESS.air_speed < PRINCESS_AIR_MAX_SPEED) {
						PRINCESS.air_speed += (PRINCESS.air_speed >> 4);
						if (PRINCESS.air_speed > PRINCESS_AIR_MAX_SPEED) PRINCESS.air_speed = PRINCESS_AIR_MAX_SPEED;
					}
				}
			}
		} else {
			// Aceleracion de la caida
			if (PRINCESS.air_speed < PRINCESS_AIR_MAX_SPEED) {
				PRINCESS.air_speed += (PRINCESS.air_speed >> 4);
				if (PRINCESS.air_speed > PRINCESS_AIR_MAX_SPEED) PRINCESS.air_speed = PRINCESS_AIR_MAX_SPEED;
			}
		}
		// Debes cancelar el forzado de caida?
		if (PRINCESS.force_down && (t_down != T_STEEP)) PRINCESS.force_down = false;
	}

}


// Funcion PrincessStairs();
void PrincessStairs(void) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	u16 t_up = T_AIR, t_down = T_AIR;


	/*
	-------------------------------------------------
		Analiza las posibilidades
	-------------------------------------------------
	*/

	// Opten los tiles
	t_up = PrincessCheckUp(1);
	t_down = PrincessCheckDown(1);

	// Calcula si puedes subir la escalera
	if (t_up == T_STAIR) {
		PRINCESS.stair_up = true;
	} else {
		PRINCESS.stair_up = false;
	}

	// Calcula si puedes bajar la escalera
	if (t_down == T_STAIR) {
		PRINCESS.stair_down = true;
	} else {
		PRINCESS.stair_down = false;
	}

	// Calcula si estas colgado de una escalera
	if ((t_up == T_STAIR) && (t_down == T_STAIR)) {
		PRINCESS.in_stair = true;
	} else {
		PRINCESS.in_stair = false;
	}


	/*
	-------------------------------------------------
		Aplica las acciones
	-------------------------------------------------
	*/

	// Si no estas saltando o cayendo...
	if (!PRINCESS.is_jump && !PRINCESS.fall) {

		// Subir por la escalera
		if (PRINCESS.stair_up && PRINCESS.ai_up) {
			// Nueva posicion
			PRINCESS.pos_fy -= PRINCESS_WALK_SPEED;
			// Resetea aceleracion en el aire
			PRINCESS.air_speed = 0;
		}

		// Bajar por la escalera
		if (PRINCESS.stair_down && PRINCESS.ai_down) {
			// Nueva posicion
			PRINCESS.pos_fy += PRINCESS_WALK_SPEED;
			// Resetea aceleracion en el aire
			PRINCESS.air_speed = 0;
		}

	}

}



// Funcion PrincessJump();
void PrincessJump(void) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	u16 t_up = T_AIR, t_down = T_AIR, t_left = T_AIR, t_right = T_AIR, t_inside = T_AIR;


	/*
	-------------------------------------------------
		Analiza las posibilidades
	-------------------------------------------------
	*/

	// Calcula si puedes saltar
	if (!PRINCESS.is_jump && !PRINCESS.fall && !PRINCESS.in_stair && !PRINCESS.stair_down) {
		PRINCESS.can_jump = true;
	} else {
		PRINCESS.can_jump = false;
	}


	/*
	-------------------------------------------------
		Se solicita que saltes con B?
	-------------------------------------------------
	*/

	if (PRINCESS.can_jump && PRINCESS.ai_jump) {
		// Salta recto
		if (!PRINCESS.ai_left && !PRINCESS.ai_right) {
			PRINCESS.jump_direction = 0;
		} else {
			// Salta a la derecha
			if (PRINCESS.ai_right) PRINCESS.jump_direction = PRINCESS_JUMP_SIDE_SPEED;
			// Salta a la izquierda
			if (PRINCESS.ai_left) PRINCESS.jump_direction = -PRINCESS_JUMP_SIDE_SPEED;
		}
		// Registra el salto
		PRINCESS.can_jump = false;
		PRINCESS.is_jump = true;
		PRINCESS.jump_up = true;
		PRINCESS.air_speed = PRINCESS_AIR_MAX_SPEED;
		PRINCESS.jump_height = 0;
	}


	/*
	-------------------------------------------------
		Ejecuta el salto
	-------------------------------------------------
	*/

	if (PRINCESS.is_jump) {

		// Si hay movimiento lateral...
		if (PRINCESS.jump_direction != 0) {
			// Calculos de posicion lateral y altura del salto
			PRINCESS.pos_fx += PRINCESS.jump_direction;
			if (PRINCESS.jump_direction > 0) {
				// Ajusta el limite derecho
				t_right = PrincessCheckRight(0);
				while (t_right == T_WALL) {
					PRINCESS.pos_fx -= 64;
					t_right = PrincessCheckRight(0);
				}
			} else {
				// Ajusta el limite izquierdo
				t_left = PrincessCheckLeft(0);
				while (t_left == T_WALL) {
					PRINCESS.pos_fx += 64;
					t_left = PrincessCheckLeft(0);
				}
			}
		}

		// Salto ascendente?
		if (PRINCESS.jump_up) {

			// Calcula la nueva posicion
			PRINCESS.pos_fy -= PRINCESS.air_speed;
			PRINCESS.jump_height += PRINCESS.air_speed;
			// Y verifica las colisiones
			t_up = PrincessCheckUp(1);
			// Y si has terminado de ascender
			if ((PRINCESS.jump_height >= PRINCESS_JUMP_MAX_HEIGHT) || !PRINCESS.ai_jump || (t_up == T_WALL)) {
				// Indicalo
				PRINCESS.jump_up = false;
				// Marca que estas a medio escalon
				t_inside = PrincessCheckDown(0);
				if (t_inside == T_STEEP) PRINCESS.force_down = true;
				// Ajusta la posicion de la princesa
				t_up = PrincessCheckUp(0);
				while (t_up == T_WALL) {
					PRINCESS.pos_fy += 64;
					t_up = PrincessCheckUp(0);
				}
			} else {
				// Si no, calcula la nueva aceleracion
				if (PRINCESS.air_speed > PRINCESS_AIR_MIN_SPEED) {
					PRINCESS.air_speed -= (PRINCESS.air_speed >> 4);
					if (PRINCESS.air_speed < PRINCESS_AIR_MIN_SPEED) PRINCESS.air_speed = PRINCESS_AIR_MIN_SPEED;
				}
			}

		} else {

			// Calcula la nueva posicion
			PRINCESS.pos_fy += PRINCESS.air_speed;
			PRINCESS.jump_height -= PRINCESS.air_speed;
			// Y verifica las colisiones
			t_up = PrincessCheckUp(1);
			t_down = PrincessCheckDown(1);
			// Y si has terminado de descender
			if ((t_down == T_WALL) || (t_down == T_STEEP) || ((t_up == T_STAIR) && (t_down == T_STAIR) && PRINCESS.ai_up)) {
				// Tocas un muro
				if (t_down == T_WALL) {
					// Cancela el salto
					PRINCESS.is_jump = false;
					// Borra la aceleracion en el aire si has tocado el suelo
					PRINCESS.air_speed = 0;
					// Ajusta la posicion de la princesa
					t_inside = PrincessCheckDown(0);
					while (t_inside == T_WALL) {
						PRINCESS.pos_fy -= 64;
						t_inside = PrincessCheckDown(0);
					}
				}
				// Estas en una escalera
				if (((t_up == T_STAIR) && (t_down == T_STAIR) && PRINCESS.ai_up)) {
					// Cancela el salto
					PRINCESS.is_jump = false;
					// Borra la aceleracion en el aire si has tocado el suelo
					PRINCESS.air_speed = 0;
				}
				// Tocas un escalon
				if (t_down == T_STEEP) {
					// Si no estas en un forzado de caida, ajustalo
					if (!PRINCESS.force_down) {
						// Deten la caida
						PRINCESS.is_jump = false;
						PRINCESS.air_speed = 0;
						// Ajusta la princesa al nivel del suelo/escalon
						t_inside = PrincessCheckDown(0);
						while (t_inside == T_STEEP) {
							// Ajusta la posicion
							PRINCESS.pos_fy -= 64;
							// Verifica de nuevo
							t_inside = PrincessCheckDown(0);
						}
					} else {
						// Si no, calcula la nueva aceleracion
						if (PRINCESS.air_speed < PRINCESS_AIR_MAX_SPEED) {
							PRINCESS.air_speed += (PRINCESS.air_speed >> 4);
							if (PRINCESS.air_speed > PRINCESS_AIR_MAX_SPEED) PRINCESS.air_speed = PRINCESS_AIR_MAX_SPEED;
						}
					}
				}
			} else {
				// Si no, calcula la nueva aceleracion
				if (PRINCESS.air_speed < PRINCESS_AIR_MAX_SPEED) {
					PRINCESS.air_speed += (PRINCESS.air_speed >> 4);
					if (PRINCESS.air_speed > PRINCESS_AIR_MAX_SPEED) PRINCESS.air_speed = PRINCESS_AIR_MAX_SPEED;
				}
			}

			// Debes cancelar el forzado de caida?
			if (PRINCESS.force_down && (t_down != T_STEEP)) PRINCESS.force_down = false;

		}

	}

}



// Funcion PrincessWalk();
void PrincessWalk(void) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	u16 t_left = T_AIR, t_right = T_AIR;	// Almacena los tiles


	/*
	-------------------------------------------------
		Analiza las posibilidades
	-------------------------------------------------
	*/

	// Analiza los tiles de alrededor
	t_left = PrincessCheckLeft(1);
	t_right = PrincessCheckRight(1);

	// Calcula si puedes ir a la derecha
	if ((t_right != T_WALL) && !PRINCESS.fall && !PRINCESS.is_jump) {
		PRINCESS.mov_right = true;
	} else {
		PRINCESS.mov_right = false;
	}

	// Calcula si puedes ir a la izquierda
	if ((t_left != T_WALL) && !PRINCESS.fall && !PRINCESS.is_jump) {
		PRINCESS.mov_left = true;
	} else {
		PRINCESS.mov_left = false;
	}


	/*
	-------------------------------------------------
		Aplica las acciones
	-------------------------------------------------
	*/

	// Si no estas presionando arriba/abajo
	if (!PRINCESS.ai_up && !PRINCESS.ai_down) {

		// Andar a la derecha
		if (PRINCESS.ai_right && PRINCESS.mov_right) {
			// Nueva posicion
			PRINCESS.pos_fx += PRINCESS_WALK_SPEED;
			// Resetea aceleracion en el aire
			PRINCESS.air_speed = 0;
		}

		// Andar a la izquierda
		if (PRINCESS.ai_left && PRINCESS.mov_left) {
			// Nueva posicion
			PRINCESS.pos_fx -= PRINCESS_WALK_SPEED;
			// Resetea aceleracion en el aire
			PRINCESS.air_speed = 0;
		}

	}

}



// Funcion PrincessAdjustPosition();
void PrincessAdjustPosition(void) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	u16 t_left = T_AIR, t_right = T_AIR, t_down = T_AIR;	// Almacena los tiles


	/*
	-------------------------------------------------
		Ajusta la princesa a derecha e izquierda
	-------------------------------------------------
	*/

	// Ajusta el limite derecho
	t_right = PrincessCheckRight(0);
	// Si estavas a medio salto, cancela el desplazamiento lateral
	if (PRINCESS.is_jump && (PRINCESS.jump_direction > 0) && (t_right == T_WALL)) PRINCESS.jump_direction = 0;
	// Ajusta la posicion a la derecha
	while (t_right == T_WALL) {
		PRINCESS.pos_fx -= 64;
		t_right = PrincessCheckRight(0);
	}

	// Ajusta el limite izquierdo
	t_left = PrincessCheckLeft(0);
	// Si estavas a medio salto, cancela el desplazamiento lateral
	if (PRINCESS.is_jump && (PRINCESS.jump_direction < 0) && (t_left == T_WALL)) PRINCESS.jump_direction = 0;
	// Ajusta la posicion de la izquierda
	while (t_left == T_WALL) {
		PRINCESS.pos_fx += 64;
		t_left = PrincessCheckLeft(0);
	}


	/*
	-------------------------------------------------
		Ajusta el nivel del suelo de la princesa
	-------------------------------------------------
	*/
	t_down = PrincessCheckDown(0);
	while (t_down == T_WALL) {
		PRINCESS.pos_fy -= 64;
		t_down = PrincessCheckDown(0);
	}

}



// Funcion PrincessAnimation();
void PrincessAnimation(void) {

	/*
	-------------------------------------------------
		Acciones
	-------------------------------------------------
	*/

	// Juego de animaciones cayendo
	if (PRINCESS.fall) {
		// Si entras en esta animacion
		if (PRINCESS.anim != PRINCESS_ANIM_FALL) {
			PRINCESS.anim = PRINCESS_ANIM_FALL;
			PRINCESS.frame = 0;
			PRINCESS.frame_cnt = 0;
		}
		// Animacion caerse (Frames 0 al 3)
		PRINCESS.frame_cnt ++;
		if (PRINCESS.frame_cnt > 6) {
			PRINCESS.frame_cnt = 0;
			PRINCESS.frame ++;
			if (PRINCESS.frame > 3) {
				PRINCESS.frame = 0;
			}
		}
	}


	// Juego de animaciones saltando
	if (PRINCESS.is_jump) {

		// Salto hacia arriba
		if (PRINCESS.jump_up) {

			// Registra la animacion
			if (PRINCESS.anim != PRINCESS_ANIM_JUMP) {
				PRINCESS.anim = PRINCESS_ANIM_JUMP;
				PRINCESS.frame_cnt = 0;
			}
			// Salto arriba (Frame 1)
			PRINCESS.frame = 1;

		} else {	// Salto hacia abajo

			// Si aun estas en la altura del salto normal
			if (PRINCESS.jump_height >= 0) {

				// Salto abajo (Frame 3)
				PRINCESS.frame = 3;

			} else {	// Si estas cayendote...

				// Si entras en esta animacion
				if (PRINCESS.anim != PRINCESS_ANIM_FALL) {
					PRINCESS.anim = PRINCESS_ANIM_FALL;
					PRINCESS.frame = 0;
					PRINCESS.frame_cnt = 0;
				}
				// Animacion caerse (Frames 0 al 3)
				PRINCESS.frame_cnt ++;
				if (PRINCESS.frame_cnt > 6) {
					PRINCESS.frame_cnt = 0;
					PRINCESS.frame ++;
					if (PRINCESS.frame > 3) {
						PRINCESS.frame = 0;
					}
				}

			}

		}

	}


	// Juego de animaciones en la escalera
	if ((PRINCESS.in_stair || PRINCESS.stair_down) && !PRINCESS.is_jump && !PRINCESS.fall) {
		// Si entras en esta animacion
		if (PRINCESS.anim != PRINCESS_ANIM_STAIRS) {
			PRINCESS.anim = PRINCESS_ANIM_STAIRS;
			PRINCESS.frame = 4;
			PRINCESS.frame_cnt = 0;
		}
		// Animacion si puedes moverte
		if (
			(PRINCESS.stair_up && PRINCESS.ai_up)
			||
			(PRINCESS.stair_down && PRINCESS.ai_down)
			||
			(PRINCESS.mov_right && PRINCESS.ai_right && !PRINCESS.ai_up)
			||
			(PRINCESS.mov_left && PRINCESS.ai_left && !PRINCESS.ai_up)
			) {
			// Animacion moviendose por la escalera (Frames 4 a 5)
			PRINCESS.frame_cnt ++;
			if (PRINCESS.frame_cnt > 10) {
				PRINCESS.frame_cnt = 0;
				PRINCESS.frame ++;
				if (PRINCESS.frame > 5) PRINCESS.frame = 4;
			}
		}
	}

	// Juego de animaciones en el suelo (Quieto, andar, agacharse, lanzar hechizo)
	if (!PRINCESS.fall && !PRINCESS.in_stair && !PRINCESS.stair_down && !PRINCESS.is_jump) {

		// Si no estas presionando arriba/abajo...
		if (!PRINCESS.ai_up && !PRINCESS.ai_down) {

			// Andar
			if ((PRINCESS.mov_right && PRINCESS.ai_right) || (PRINCESS.mov_left && PRINCESS.ai_left)) {
				// Si entras en esta animacion
				if (PRINCESS.anim != PRINCESS_ANIM_WALK) {
					PRINCESS.anim = PRINCESS_ANIM_WALK;
					PRINCESS.frame = 0;
					PRINCESS.frame_cnt = 0;
				}
				// Animacion andando (Frames 0 a 3)
				PRINCESS.frame_cnt ++;
				if (PRINCESS.frame_cnt > 7) {
					PRINCESS.frame_cnt = 0;
					PRINCESS.frame ++;
					if (PRINCESS.frame > 3) PRINCESS.frame = 0;
				}
			} else {
				// Quieto (Frame 0)
				PRINCESS.anim = PRINCESS_ANIM_STANDBY;
				PRINCESS.frame = 0;
				PRINCESS.frame_cnt = 0;
			}

		} else {

			// Por defecto, quieta
			PRINCESS.anim = PRINCESS_ANIM_STANDBY;
			PRINCESS.frame = 0;
			PRINCESS.frame_cnt = 0;

		}

	}

	// Calcula y marca la direccion a la que miras
	if (
		(PRINCESS.anim != PRINCESS_ANIM_FALL)
		&&
		(PRINCESS.anim != PRINCESS_ANIM_JUMP)
		) {
		if (PRINCESS.ai_right && PRINCESS.flip) PRINCESS.flip = false;
		if (PRINCESS.ai_left && !PRINCESS.flip) PRINCESS.flip = true;
	}

}



// Funcion PrincessMove();
void PrincessMove(void) {

	/*
	-------------------------------------------------
		Movimiento de la princesa
	-------------------------------------------------
	*/

	// Procesa si se cae
	PrincessFall();

	// Procesa el salto
	PrincessJump();

	// Procesa moverte por las escaleras
	PrincessStairs();

	// Procesa el andar
	PrincessWalk();

	// Ajusta la posicion de la princesa, para que no atraviese ningun limite
	PrincessAdjustPosition();

	// Animacion de la princesa
	PrincessAnimation();


	/*
	-------------------------------------------------
		Ajustes de posicion
	-------------------------------------------------
	*/

	PRINCESS.pos_x = (PRINCESS.pos_fx >> 8);
	PRINCESS.pos_y = (PRINCESS.pos_fy >> 8);
	PRINCESS.stage = GetStage(PRINCESS.pos_x, PRINCESS.pos_y);

}
