/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de gestion de los NPC
	(Armadura)

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




// Funcion ArmorCamHide();
void ArmorCamHide(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;


	/*
	-------------------------------------------------
		Gestion de las visibilidad de
		la Armadura
	-------------------------------------------------
	*/

	// Calcula la posicion del sprite en la pantalla
	spr_x = (ARMOR.pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
	spr_y = (ARMOR.pos_y - STAGE[stage].stg_top);
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
		!ARMOR.show
		) {
		// No lo esta
		ARMOR.on_screen[screen] = false;
		ARMOR.scr_x[screen] = -64;
		ARMOR.scr_y[screen] = -64;
		// Destruye el sprite
		if (ARMOR.created[screen]) {
			ARMOR.created[screen] = false;
			NF_DeleteSprite(screen, ARMOR_SPR_ID);
			NF_FreeSpriteGfx(screen, ARMOR_SPR_ID);
		}
	}

}



// Funcion ArmorCamShow();
void ArmorCamShow(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;


	/*
	-------------------------------------------------
		Gestion de las visibilidad de
		la Armadura
	-------------------------------------------------
	*/

	// Calcula la posicion del sprite en la pantalla
	spr_x = (ARMOR.pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
	spr_y = (ARMOR.pos_y - STAGE[stage].stg_top);
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
		ARMOR.show
		) {
		// Esta en pantalla
		ARMOR.on_screen[screen] = true;
		ARMOR.scr_x[screen] = spr_x;
		ARMOR.scr_y[screen] = spr_y;
		// Si no esta creado, crealo
		if (!ARMOR.created[screen]) {
			ARMOR.created[screen] = true;
			NF_VramSpriteGfx(screen, ID_ARMOR, ARMOR_SPR_ID, true);
			NF_CreateSprite(screen, ARMOR_SPR_ID, ARMOR_SPR_ID, NPC_SPR_PAL, spr_x, spr_y);
			NF_SpriteLayer(screen, ARMOR_SPR_ID, SPRITES_LAYER);
		}
		// Actualiza el sprite
		NF_MoveSprite(screen, ARMOR_SPR_ID, (spr_x - ARMOR.spr_left), (spr_y - ARMOR.spr_up));
		NF_SpriteFrame(screen, ARMOR_SPR_ID, ARMOR.frame);
		NF_HflipSprite(screen, ARMOR_SPR_ID, ARMOR.flip);
	}

}



// Funcion ArmorCheckRight();
u16 ArmorCheckRight(s8 add) {

	// Variables
	s32 x, y;
	s32 fx, fy;
	s32 start, end;
	s16 tile = 0;
	s16 result = T_AIR;

	// Variables de posicion
	fx = (ARMOR.pos_fx >> 8);
	fy = (ARMOR.pos_fy >> 8);

	// Calcula el rango de tiles a analizar
	x = (fx + ARMOR.right + add);
	start = (fy - ARMOR.up);
	end = (fy + ARMOR.down);

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



// Funcion ArmorCheckLeft();
u16 ArmorCheckLeft(s8 add) {

	// Variables
	s32 x, y;
	s32 fx, fy;
	s32 start, end;
	s16 tile = 0;
	s16 result = T_AIR;

	// Variables de posicion
	fx = (ARMOR.pos_fx >> 8);
	fy = (ARMOR.pos_fy >> 8);

	// Calcula el rango de tiles a analizar
	x = (fx - ARMOR.left - add);
	start = (fy - ARMOR.up);
	end = (fy + ARMOR.down);

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



// Funcion ArmorCheckUp();
u16 ArmorCheckUp(s8 add) {

	// Variables
	s32 x, y;
	s32 fx, fy;
	s32 start, end;
	s16 tile = 0;
	s16 result = T_AIR;
	s16 air = 0, stair = 0;

	// Variables de posicion
	fx = (ARMOR.pos_fx >> 8);
	fy = (ARMOR.pos_fy >> 8);

	// Calcula el rango de tiles a analizar
	y = (fy - ARMOR.up - add);
	start = (fx - ARMOR.left);
	end = (fx + ARMOR.right);

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



// Funcion ArmorCheckDown();
u16 ArmorCheckDown(s8 add) {

	// Variables
	s32 x, y;
	s32 fx, fy;
	s32 start, end;
	s16 tile = 0;
	s16 result = T_AIR;
	s16 air = 0, stair = 0;

	// Variables de posicion
	fx = (ARMOR.pos_fx >> 8);
	fy = (ARMOR.pos_fy >> 8);

	// Calcula el rango de tiles a analizar
	y = (fy + ARMOR.down + add);
	start = (fx - ARMOR.left);
	end = (fx + ARMOR.right);

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



// Funcion ArmorFall();
void ArmorFall(void) {

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
	t_down = ArmorCheckDown(1);

	// Calcula si te vas a caer
	if (((t_down == T_AIR) && !ARMOR.is_jump) || ((t_down == T_STEEP) && ARMOR.force_down)) {
		// Se va a caer
		ARMOR.fall = true;
		// Aceleracion inicial de la caida
		if (ARMOR.air_speed == 0) {
			ARMOR.air_speed = ARMOR_AIR_MIN_SPEED;
		}
	} else {
		ARMOR.fall = false;
	}


	/*
	-------------------------------------------------
		Aplica las acciones
	-------------------------------------------------
	*/

	// la armadura se cae
	if (ARMOR.fall) {
		// Nueva posicion
		ARMOR.pos_fy += ARMOR.air_speed;
		// Calcula si te sales de los limites...
		t_down = ArmorCheckDown(1);
		if ((t_down == T_WALL) || (t_down == T_STEEP)) {
			// Si encuentras un muro
			if (t_down == T_WALL) {
				// Deten la caida
				ARMOR.fall = false;
				ARMOR.air_speed = 0;
				// Ajusta la armadura al nivel del suelo/escalon
				t_inside = ArmorCheckDown(0);
				while (t_inside == T_WALL) {
					// Ajusta la posicion
					ARMOR.pos_fy -= 64;
					// Verifica de nuevo
					t_inside = ArmorCheckDown(0);
				}
			}
			// Si encuentras un escalon
			if (t_down == T_STEEP) {
				// Si no estas en un forzado de caida, ajustalo
				if (!ARMOR.force_down) {
					// Deten la caida
					ARMOR.fall = false;
					ARMOR.air_speed = 0;
					// Ajusta la armadura al nivel del suelo/escalon
					t_inside = ArmorCheckDown(0);
					while (t_inside == T_STEEP) {
						// Ajusta la posicion
						ARMOR.pos_fy -= 64;
						// Verifica de nuevo
						t_inside = ArmorCheckDown(0);
					}
				} else {
					// Aceleracion de la caida
					if (ARMOR.air_speed < ARMOR_AIR_MAX_SPEED) {
						ARMOR.air_speed += (ARMOR.air_speed >> 4);
						if (ARMOR.air_speed > ARMOR_AIR_MAX_SPEED) ARMOR.air_speed = ARMOR_AIR_MAX_SPEED;
					}
				}
			}
		} else {
			// Aceleracion de la caida
			if (ARMOR.air_speed < ARMOR_AIR_MAX_SPEED) {
				ARMOR.air_speed += (ARMOR.air_speed >> 4);
				if (ARMOR.air_speed > ARMOR_AIR_MAX_SPEED) ARMOR.air_speed = ARMOR_AIR_MAX_SPEED;
			}
		}
		// Debes cancelar el forzado de caida?
		if (ARMOR.force_down && (t_down != T_STEEP)) ARMOR.force_down = false;
	}

}


// Funcion ArmorStairs();
void ArmorStairs(void) {

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
	t_up = ArmorCheckUp(1);
	t_down = ArmorCheckDown(1);

	// Calcula si puedes subir la escalera
	if (t_up == T_STAIR) {
		ARMOR.stair_up = true;
	} else {
		ARMOR.stair_up = false;
	}

	// Calcula si puedes bajar la escalera
	if (t_down == T_STAIR) {
		ARMOR.stair_down = true;
	} else {
		ARMOR.stair_down = false;
	}

	// Calcula si estas colgado de una escalera
	if ((t_up == T_STAIR) && (t_down == T_STAIR)) {
		ARMOR.in_stair = true;
	} else {
		ARMOR.in_stair = false;
	}


	/*
	-------------------------------------------------
		Aplica las acciones
	-------------------------------------------------
	*/

	// Si no estas saltando o cayendo...
	if (!ARMOR.is_jump && !ARMOR.fall) {

		// Subir por la escalera
		if (ARMOR.stair_up && ARMOR.ai_up) {
			// Nueva posicion
			ARMOR.pos_fy -= ARMOR_WALK_SPEED;
			// Resetea aceleracion en el aire
			ARMOR.air_speed = 0;
		}

		// Bajar por la escalera
		if (ARMOR.stair_down && ARMOR.ai_down) {
			// Nueva posicion
			ARMOR.pos_fy += ARMOR_WALK_SPEED;
			// Resetea aceleracion en el aire
			ARMOR.air_speed = 0;
		}

	}

}



// Funcion ArmorJump();
void ArmorJump(void) {

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
	if (!ARMOR.is_jump && !ARMOR.fall && !ARMOR.in_stair && !ARMOR.stair_down) {
		ARMOR.can_jump = true;
	} else {
		ARMOR.can_jump = false;
	}


	/*
	-------------------------------------------------
		Se solicita que saltes con B?
	-------------------------------------------------
	*/

	if (ARMOR.can_jump && ARMOR.ai_jump) {
		// Salta recto
		if (!ARMOR.ai_left && !ARMOR.ai_right) {
			ARMOR.jump_direction = 0;
		} else {
			// Salta a la derecha
			if (ARMOR.ai_right) ARMOR.jump_direction = ARMOR_JUMP_SIDE_SPEED;
			// Salta a la izquierda
			if (ARMOR.ai_left) ARMOR.jump_direction = -ARMOR_JUMP_SIDE_SPEED;
		}
		// Registra el salto
		ARMOR.can_jump = false;
		ARMOR.is_jump = true;
		ARMOR.jump_up = true;
		ARMOR.air_speed = ARMOR_AIR_MAX_SPEED;
		ARMOR.jump_height = 0;
	}


	/*
	-------------------------------------------------
		Ejecuta el salto
	-------------------------------------------------
	*/

	if (ARMOR.is_jump) {

		// Si hay movimiento lateral...
		if (ARMOR.jump_direction != 0) {
			// Calculos de posicion lateral y altura del salto
			ARMOR.pos_fx += ARMOR.jump_direction;
			if (ARMOR.jump_direction > 0) {
				// Ajusta el limite derecho
				t_right = ArmorCheckRight(0);
				while (t_right == T_WALL) {
					ARMOR.pos_fx -= 64;
					t_right = ArmorCheckRight(0);
				}
			} else {
				// Ajusta el limite izquierdo
				t_left = ArmorCheckLeft(0);
				while (t_left == T_WALL) {
					ARMOR.pos_fx += 64;
					t_left = ArmorCheckLeft(0);
				}
			}
		}
		
		// Salto ascendente?
		if (ARMOR.jump_up) {

			// Calcula la nueva posicion
			ARMOR.pos_fy -= ARMOR.air_speed;
			ARMOR.jump_height += ARMOR.air_speed;
			// Y verifica las colisiones
			t_up = ArmorCheckUp(1);
			// Y si has terminado de ascender
			if ((ARMOR.jump_height >= ARMOR_JUMP_MAX_HEIGHT) || !ARMOR.ai_jump || (t_up == T_WALL)) {
				// Indicalo
				ARMOR.jump_up = false;
				// Marca que estas a medio escalon
				t_inside = ArmorCheckDown(0);
				if (t_inside == T_STEEP) ARMOR.force_down = true;
				// Ajusta la posicion de la armadura
				t_up = ArmorCheckUp(0);
				while (t_up == T_WALL) {
					ARMOR.pos_fy += 64;
					t_up = ArmorCheckUp(0);
				}
			} else {
				// Si no, calcula la nueva aceleracion
				if (ARMOR.air_speed > ARMOR_AIR_MIN_SPEED) {
					ARMOR.air_speed -= (ARMOR.air_speed >> 4);
					if (ARMOR.air_speed < ARMOR_AIR_MIN_SPEED) ARMOR.air_speed = ARMOR_AIR_MIN_SPEED;
				}
			}

		} else {

			// Calcula la nueva posicion
			ARMOR.pos_fy += ARMOR.air_speed;
			ARMOR.jump_height -= ARMOR.air_speed;
			// Y verifica las colisiones
			t_up = ArmorCheckUp(1);
			t_down = ArmorCheckDown(1);
			// Y si has terminado de descender
			if ((t_down == T_WALL) || (t_down == T_STEEP) || ((t_up == T_STAIR) && (t_down == T_STAIR) && ARMOR.ai_up)) {
				// Tocas un muro
				if (t_down == T_WALL) {
					// Cancela el salto
					ARMOR.is_jump = false;
					// Borra la aceleracion en el aire si has tocado el suelo
					ARMOR.air_speed = 0;
					// Ajusta la posicion de la armadura
					t_inside = ArmorCheckDown(0);
					while (t_inside == T_WALL) {
						ARMOR.pos_fy -= 64;
						t_inside = ArmorCheckDown(0);
					}
				}
				// Estas en una escalera
				if (((t_up == T_STAIR) && (t_down == T_STAIR) && ARMOR.ai_up)) {
					// Cancela el salto
					ARMOR.is_jump = false;
					// Borra la aceleracion en el aire si has tocado el suelo
					ARMOR.air_speed = 0;
				}
				// Tocas un escalon
				if (t_down == T_STEEP) {
					// Si no estas en un forzado de caida, ajustalo
					if (!ARMOR.force_down) {
						// Deten la caida
						ARMOR.is_jump = false;
						ARMOR.air_speed = 0;
						// Ajusta la armadura al nivel del suelo/escalon
						t_inside = ArmorCheckDown(0);
						while (t_inside == T_STEEP) {
							// Ajusta la posicion
							ARMOR.pos_fy -= 64;
							// Verifica de nuevo
							t_inside = ArmorCheckDown(0);
						}
					} else {
						// Si no, calcula la nueva aceleracion
						if (ARMOR.air_speed < ARMOR_AIR_MAX_SPEED) {
							ARMOR.air_speed += (ARMOR.air_speed >> 4);
							if (ARMOR.air_speed > ARMOR_AIR_MAX_SPEED) ARMOR.air_speed = ARMOR_AIR_MAX_SPEED;
						}
					}
				}
			} else {
				// Si no, calcula la nueva aceleracion
				if (ARMOR.air_speed < ARMOR_AIR_MAX_SPEED) {
					ARMOR.air_speed += (ARMOR.air_speed >> 4);
					if (ARMOR.air_speed > ARMOR_AIR_MAX_SPEED) ARMOR.air_speed = ARMOR_AIR_MAX_SPEED;
				}
			}

			// Debes cancelar el forzado de caida?
			if (ARMOR.force_down && (t_down != T_STEEP)) ARMOR.force_down = false;

		}

	}

}



// Funcion ArmorWalk();
void ArmorWalk(void) {

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
	t_left = ArmorCheckLeft(1);
	t_right = ArmorCheckRight(1);

	// Calcula si puedes ir a la derecha
	if ((t_right != T_WALL) && !ARMOR.fall && !ARMOR.is_jump) { 
		ARMOR.mov_right = true;
	} else {
		ARMOR.mov_right = false;
	}

	// Calcula si puedes ir a la izquierda
	if ((t_left != T_WALL) && !ARMOR.fall && !ARMOR.is_jump) {
		ARMOR.mov_left = true;
	} else {
		ARMOR.mov_left = false;
	}


	/*
	-------------------------------------------------
		Aplica las acciones
	-------------------------------------------------
	*/

	// Si no estas presionando arriba/abajo
	if (!ARMOR.ai_up && !ARMOR.ai_down) {

		// Andar a la derecha
		if (ARMOR.ai_right && ARMOR.mov_right) {
			// Nueva posicion
			ARMOR.pos_fx += ARMOR_WALK_SPEED;
			// Resetea aceleracion en el aire
			ARMOR.air_speed = 0;
		}

		// Andar a la izquierda
		if (ARMOR.ai_left && ARMOR.mov_left) {
			// Nueva posicion
			ARMOR.pos_fx -= ARMOR_WALK_SPEED;
			// Resetea aceleracion en el aire
			ARMOR.air_speed = 0;
		}

	}

}



// Funcion ArmorAdjustPosition();
void ArmorAdjustPosition(void) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	u16 t_left = T_AIR, t_right = T_AIR, t_down = T_AIR;	// Almacena los tiles


	/*
	-------------------------------------------------
		Ajusta la armadura a derecha e izquierda
	-------------------------------------------------
	*/

	// Ajusta el limite derecho
	t_right = ArmorCheckRight(0);
	// Si estavas a medio salto, cancela el desplazamiento lateral
	if (ARMOR.is_jump && (ARMOR.jump_direction > 0) && (t_right == T_WALL)) ARMOR.jump_direction = 0;
	// Ajusta la posicion a la derecha
	while (t_right == T_WALL) {
		ARMOR.pos_fx -= 64;
		t_right = ArmorCheckRight(0);
	}

	// Ajusta el limite izquierdo
	t_left = ArmorCheckLeft(0);
	// Si estavas a medio salto, cancela el desplazamiento lateral
	if (ARMOR.is_jump && (ARMOR.jump_direction < 0) && (t_left == T_WALL)) ARMOR.jump_direction = 0;
	// Ajusta la posicion de la izquierda
	while (t_left == T_WALL) {
		ARMOR.pos_fx += 64;
		t_left = ArmorCheckLeft(0);
	}


	/*
	-------------------------------------------------
		Ajusta el nivel del suelo de la armadura
	-------------------------------------------------
	*/
	t_down = ArmorCheckDown(0);
	while (t_down == T_WALL) {
		ARMOR.pos_fy -= 64;
		t_down = ArmorCheckDown(0);
	}

}



// Funcion ArmorAnimation();
void ArmorAnimation(void) {

	/*
	-------------------------------------------------
		Acciones
	-------------------------------------------------
	*/

	// Juego de animaciones cayendo
	if (ARMOR.fall) {
		// Si entras en esta animacion
		if (ARMOR.anim != ARMOR_ANIM_FALL) {
			ARMOR.anim = ARMOR_ANIM_FALL;
			ARMOR.frame = 0;
			ARMOR.frame_cnt = 0;
		}
		// Animacion caerse (Frames 0 al 3)
		ARMOR.frame_cnt ++;
		if (ARMOR.frame_cnt > 6) {
			ARMOR.frame_cnt = 0;
			ARMOR.frame ++;
			if (ARMOR.frame > 3) {
				ARMOR.frame = 0;
			}
		}
	}


	// Juego de animaciones saltando
	if (ARMOR.is_jump) {

		// Salto hacia arriba
		if (ARMOR.jump_up) {

			// Registra la animacion
			if (ARMOR.anim != ARMOR_ANIM_JUMP) {
				ARMOR.anim = ARMOR_ANIM_JUMP;
				ARMOR.frame_cnt = 0;
			}
			// Salto arriba (Frame 3)
			ARMOR.frame = 3;

		} else {	// Salto hacia abajo

			// Si aun estas en la altura del salto normal
			if (ARMOR.jump_height >= 0) {

				// Salto abajo (Frame 1)
				ARMOR.frame = 1;

			} else {	// Si estas cayendote...

				// Si entras en esta animacion
				if (ARMOR.anim != ARMOR_ANIM_FALL) {
					ARMOR.anim = ARMOR_ANIM_FALL;
					ARMOR.frame = 0;
					ARMOR.frame_cnt = 0;
				}
				// Animacion caerse (Frames 0 al 3)
				ARMOR.frame_cnt ++;
				if (ARMOR.frame_cnt > 6) {
					ARMOR.frame_cnt = 0;
					ARMOR.frame ++;
					if (ARMOR.frame > 3) {
						ARMOR.frame = 0;
					}
				}

			}

		}

	}


	// Juego de animaciones en la escalera
	if ((ARMOR.in_stair || ARMOR.stair_down) && !ARMOR.is_jump && !ARMOR.fall) {
		// Si entras en esta animacion
		if (ARMOR.anim != ARMOR_ANIM_STAIRS) {
			ARMOR.anim = ARMOR_ANIM_STAIRS;
			ARMOR.frame = 4;
			ARMOR.frame_cnt = 0;
		}
		// Animacion si puedes moverte
		if (
			(ARMOR.stair_up && ARMOR.ai_up)
			||
			(ARMOR.stair_down && ARMOR.ai_down)
			||
			(ARMOR.mov_right && ARMOR.ai_right && !ARMOR.ai_up)
			||
			(ARMOR.mov_left && ARMOR.ai_left && !ARMOR.ai_up)
			) {
			// Animacion moviendose por la escalera (Frames 4 a 5)
			ARMOR.frame_cnt ++;
			if (ARMOR.frame_cnt > 10) {
				ARMOR.frame_cnt = 0;
				ARMOR.frame ++;
				if (ARMOR.frame > 5) ARMOR.frame = 4;
			}
		}
	}

	// Juego de animaciones en el suelo (Quieto, andar, agacharse, lanzar hechizo)
	if (!ARMOR.fall && !ARMOR.in_stair && !ARMOR.stair_down && !ARMOR.is_jump) {

		// Si no estas presionando arriba/abajo...
		if (!ARMOR.ai_up && !ARMOR.ai_down) {
		
			// Andar
			if ((ARMOR.mov_right && ARMOR.ai_right) || (ARMOR.mov_left && ARMOR.ai_left)) {
				// Si entras en esta animacion
				if (ARMOR.anim != ARMOR_ANIM_WALK) {
					ARMOR.anim = ARMOR_ANIM_WALK;
					ARMOR.frame = 0;
					ARMOR.frame_cnt = 0;
				}
				// Animacion andando (Frames 0 a 3)
				ARMOR.frame_cnt ++;
				if (ARMOR.frame_cnt > 7) {
					ARMOR.frame_cnt = 0;
					ARMOR.frame ++;
					if (ARMOR.frame > 3) ARMOR.frame = 0;
				}
			} else {
				// Quieto (Frame 0)
				ARMOR.anim = ARMOR_ANIM_STANDBY;
				ARMOR.frame = 0;
				ARMOR.frame_cnt = 0;
			}

		} else {

			// Por defecto, quieta
			ARMOR.anim = ARMOR_ANIM_STANDBY;
			ARMOR.frame = 0;
			ARMOR.frame_cnt = 0;

		}

	}

	// Calcula y marca la direccion a la que miras
	if (
		(ARMOR.anim != ARMOR_ANIM_FALL)
		&&
		(ARMOR.anim != ARMOR_ANIM_JUMP)
		) {
		if (ARMOR.ai_right && ARMOR.flip) ARMOR.flip = false;
		if (ARMOR.ai_left && !ARMOR.flip) ARMOR.flip = true;
	}
	
}



// Funcion ArmorMove();
void ArmorMove(void) {

	/*
	-------------------------------------------------
		Movimiento de la armadura
	-------------------------------------------------
	*/

	// Procesa si se cae
	ArmorFall();

	// Procesa el salto
	ArmorJump();

	// Procesa moverte por las escaleras
	ArmorStairs();

	// Procesa el andar
	ArmorWalk();

	// Ajusta la posicion de la armadura, para que no atraviese ningun limite
	ArmorAdjustPosition();

	// Animacion de la armadura
	ArmorAnimation();


	/*
	-------------------------------------------------
		Ajustes de posicion
	-------------------------------------------------
	*/

	ARMOR.pos_x = (ARMOR.pos_fx >> 8);
	ARMOR.pos_y = (ARMOR.pos_fy >> 8);
	ARMOR.stage = GetStage(ARMOR.pos_x, ARMOR.pos_y);

}
