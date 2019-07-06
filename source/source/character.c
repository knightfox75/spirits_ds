/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones del personaje

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



// Funcion CharacterMain();
void CharacterMain(void) {
	
	// Mueve el personaje
	CharacterMove();
	// Obtencion de objetos
	CharacterGetItem();

}



// Funcion CharacterCheckRight();
u16 CharacterCheckRight(s8 add) {

	// Variables
	s32 x, y;
	s32 fx, fy;
	s32 start, end;
	s16 tile = 0;
	s16 result = T_AIR;

	// Variables de posicion
	fx = (CHARACTER.pos_fx >> 8);
	fy = (CHARACTER.pos_fy >> 8);

	// Calcula el rango de tiles a analizar
	x = (fx + CHARACTER.right + add);
	start = (fy - CHARACTER.up[0]);
	end = (fy + CHARACTER.down);

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



// Funcion CharacterCheckLeft();
u16 CharacterCheckLeft(s8 add) {

	// Variables
	s32 x, y;
	s32 fx, fy;
	s32 start, end;
	s16 tile = 0;
	s16 result = T_AIR;

	// Variables de posicion
	fx = (CHARACTER.pos_fx >> 8);
	fy = (CHARACTER.pos_fy >> 8);

	// Calcula el rango de tiles a analizar
	x = (fx - CHARACTER.left - add);
	start = (fy - CHARACTER.up[0]);
	end = (fy + CHARACTER.down);

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



// Funcion CharacterCheckUp();
u16 CharacterCheckUp(s8 add) {

	// Variables
	s32 x, y;
	s32 fx, fy;
	s32 start, end;
	s16 tile = 0;
	s16 result = T_AIR;
	s16 air = 0, stair = 0;

	// Variables de posicion
	fx = (CHARACTER.pos_fx >> 8);
	fy = (CHARACTER.pos_fy >> 8);

	// Calcula el rango de tiles a analizar
	y = (fy - CHARACTER.up[0] - add);
	start = (fx - CHARACTER.left);
	end = (fx + CHARACTER.right);

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
		// Verifica si se la pulsado algun interruptor
		tile = NF_GetTile(MAINMAP_SLOT, CHARACTER.pos_x, y);
		switch (tile) {
			case T_SWITCH_A:
				result = T_SWITCH_A;
				break;
			case T_SWITCH_B:
				result = T_SWITCH_B;
				break;
			case T_SWITCH_C:
				result = T_SWITCH_C;
				break;
			case T_SWITCH_D:
				result = T_SWITCH_D;
				break;
			case T_SWITCH_E:
				result = T_SWITCH_E;
				break;
			default:	// Nada
				break;
		}
	}

	// Devuelve el resultado
	return result;

}



// Funcion CharacterCheckDown();
u16 CharacterCheckDown(s8 add) {

	// Variables
	s32 x, y;
	s32 fx, fy;
	s32 start, end;
	s16 tile = 0;
	s16 result = T_AIR;
	s16 air = 0, stair = 0;

	// Variables de posicion
	fx = (CHARACTER.pos_fx >> 8);
	fy = (CHARACTER.pos_fy >> 8);

	// Calcula el rango de tiles a analizar
	y = (fy + CHARACTER.down + add);
	start = (fx - CHARACTER.left);
	end = (fx + CHARACTER.right);

	// Analiza los tiles abajo (steps de 1 pixel)
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



// Funcion CharacterFall();
void CharacterFall(void) {

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
	t_down = CharacterCheckDown(1);

	// Calcula si te vas a caer
	if (((t_down == T_AIR) && !CHARACTER.is_jump) || ((t_down == T_STEEP) && CHARACTER.force_down)) {
		// Registra la coordenada de inicio de caida
		if (!CHARACTER.fall) CHARACTER.fall_y = CHARACTER.pos_y;
		// Se va a caer
		CHARACTER.fall = true;
		// Aceleracion inicial de la caida
		if (CHARACTER.air_speed == 0) {
			CHARACTER.air_speed = CHARACTER_AIR_MIN_SPEED;
		}
	} else {
		CHARACTER.fall = false;
	}


	/*
	-------------------------------------------------
		Aplica las acciones
	-------------------------------------------------
	*/

	// El personaje se cae
	if (CHARACTER.fall) {
		// Nueva posicion
		CHARACTER.pos_fy += CHARACTER.air_speed;
		// Calcula si te sales de los limites...
		t_down = CharacterCheckDown(1);
		if ((t_down == T_WALL) || (t_down == T_STEEP)) {
			// Si encuentras un muro
			if (t_down == T_WALL) {
				// Deten la caida
				CHARACTER.fall = false;
				CHARACTER.air_speed = 0;
				// Calcula si se pierde vida con la caida
				FallDamage();
				// Ajusta el personaje al nivel del suelo/escalon
				t_inside = CharacterCheckDown(0);
				while (t_inside == T_WALL) {
					// Ajusta la posicion
					CHARACTER.pos_fy -= 64;
					// Verifica de nuevo
					t_inside = CharacterCheckDown(0);
				}
			}
			// Si encuentras un escalon
			if (t_down == T_STEEP) {
				// Si no estas en un forzado de caida, ajustalo
				if (!CHARACTER.force_down) {
					// Deten la caida
					CHARACTER.fall = false;
					CHARACTER.air_speed = 0;
					// Calcula si se pierde vida con la caida
					FallDamage();
					// Ajusta el personaje al nivel del suelo/escalon
					t_inside = CharacterCheckDown(0);
					while (t_inside == T_STEEP) {
						// Ajusta la posicion
						CHARACTER.pos_fy -= 64;
						// Verifica de nuevo
						t_inside = CharacterCheckDown(0);
					}
				} else {
					// Aceleracion de la caida
					if (CHARACTER.air_speed < CHARACTER_AIR_MAX_SPEED) {
						CHARACTER.air_speed += (CHARACTER.air_speed >> 4);
						if (CHARACTER.air_speed > CHARACTER_AIR_MAX_SPEED) CHARACTER.air_speed = CHARACTER_AIR_MAX_SPEED;
					}
				}
			}
		} else {
			// Aceleracion de la caida
			if (CHARACTER.air_speed < CHARACTER_AIR_MAX_SPEED) {
				CHARACTER.air_speed += (CHARACTER.air_speed >> 4);
				if (CHARACTER.air_speed > CHARACTER_AIR_MAX_SPEED) CHARACTER.air_speed = CHARACTER_AIR_MAX_SPEED;
			}
		}
		// Debes cancelar el forzado de caida?
		if (CHARACTER.force_down && (t_down != T_STEEP)) CHARACTER.force_down = false;
	}

}


// Funcion CharacterStairs();
void CharacterStairs(void) {

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
	t_up = CharacterCheckUp(1);
	t_down = CharacterCheckDown(1);

	// Calcula si puedes subir la escalera
	if (t_up == T_STAIR) {
		CHARACTER.stair_up = true;
	} else {
		CHARACTER.stair_up = false;
	}

	// Calcula si puedes bajar la escalera
	if (t_down == T_STAIR) {
		CHARACTER.stair_down = true;
	} else {
		CHARACTER.stair_down = false;
	}

	// Calcula si estas colgado de una escalera
	if ((t_up == T_STAIR) && (t_down == T_STAIR)) {
		CHARACTER.in_stair = true;
	} else {
		CHARACTER.in_stair = false;
	}


	/*
	-------------------------------------------------
		Aplica las acciones
	-------------------------------------------------
	*/

	// Si no estas saltando o cayendo...
	if (!CHARACTER.is_jump && !CHARACTER.fall) {

		// Subir por la escalera
		if (CHARACTER.stair_up && KEYHELD.up) {
			// Nueva posicion
			CHARACTER.pos_fy -= CHARACTER_WALK_SPEED;
			// Resetea aceleracion en el aire
			CHARACTER.air_speed = 0;
		}

		// Bajar por la escalera
		if (CHARACTER.stair_down && KEYHELD.down) {
			// Nueva posicion
			CHARACTER.pos_fy += CHARACTER_WALK_SPEED;
			// Resetea aceleracion en el aire
			CHARACTER.air_speed = 0;
		}

	}

}



// Funcion CharacterJump();
void CharacterJump(void) {

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
	if (!CHARACTER.is_jump && !CHARACTER.fall && !CHARACTER.in_stair && !CHARACTER.stair_down && !CHARACTER.spell) {
		CHARACTER.can_jump = true;
	} else {
		CHARACTER.can_jump = false;
	}


	/*
	-------------------------------------------------
		Se solicita que saltes con B?
	-------------------------------------------------
	*/

	if (CHARACTER.can_jump && KEYPRESS.b && !KEYHELD.down) {
		// Salta recto
		if (!KEYHELD.left && !KEYHELD.right) {
			CHARACTER.jump_direction = 0;
		} else {
			// Salta a la derecha
			if (KEYHELD.right) CHARACTER.jump_direction = CHARACTER_JUMP_SIDE_SPEED;
			// Salta a la izquierda
			if (KEYHELD.left) CHARACTER.jump_direction = -CHARACTER_JUMP_SIDE_SPEED;
		}
		// Registra el salto
		CHARACTER.can_jump = false;
		CHARACTER.is_jump = true;
		CHARACTER.jump_up = true;
		CHARACTER.air_speed = CHARACTER_AIR_MAX_SPEED;
		CHARACTER.jump_height = 0;
	}


	/*
	-------------------------------------------------
		Se solicita que te descuelgues con B?
	-------------------------------------------------
	*/

	if (CHARACTER.can_jump && KEYPRESS.b && KEYHELD.down) CHARACTER.force_down = true;


	/*
	-------------------------------------------------
		Ejecuta el salto
	-------------------------------------------------
	*/

	if (CHARACTER.is_jump) {

		// Si hay movimiento lateral...
		if (CHARACTER.jump_direction != 0) {
			// Calculos de posicion lateral y altura del salto
			CHARACTER.pos_fx += CHARACTER.jump_direction;
			if (CHARACTER.jump_direction > 0) {
				// Ajusta el limite derecho
				t_right = CharacterCheckRight(0);
				while (t_right == T_WALL) {
					CHARACTER.pos_fx -= 64;
					t_right = CharacterCheckRight(0);
				}
			} else {
				// Ajusta el limite izquierdo
				t_left = CharacterCheckLeft(0);
				while (t_left == T_WALL) {
					CHARACTER.pos_fx += 64;
					t_left = CharacterCheckLeft(0);
				}
			}
		}
		
		// Salto ascendente?
		if (CHARACTER.jump_up) {

			// Calcula la nueva posicion
			CHARACTER.pos_fy -= CHARACTER.air_speed;
			CHARACTER.jump_height += CHARACTER.air_speed;
			// Y verifica las colisiones
			t_up = CharacterCheckUp(1);
			// Y si has terminado de ascender
			if ((CHARACTER.jump_height >= CHARACTER_JUMP_MAX_HEIGHT) || !KEYHELD.b || (t_up == T_WALL)) {
				// Registra la altura maxima del salto
				CHARACTER.fall_y = CHARACTER.pos_y;
				// Indicalo
				CHARACTER.jump_up = false;
				// Marca que estas a medio escalon
				t_inside = CharacterCheckDown(0);
				if (t_inside == T_STEEP) CHARACTER.force_down = true;
				// Ajusta la posicion del personaje
				t_up = CharacterCheckUp(0);
				while (t_up == T_WALL) {
					CHARACTER.pos_fy += 64;
					t_up = CharacterCheckUp(0);
				}
			} else {
				// Si no, calcula la nueva aceleracion
				if (CHARACTER.air_speed > CHARACTER_AIR_MIN_SPEED) {
					CHARACTER.air_speed -= (CHARACTER.air_speed >> 4);
					if (CHARACTER.air_speed < CHARACTER_AIR_MIN_SPEED) CHARACTER.air_speed = CHARACTER_AIR_MIN_SPEED;
				}
			}

		} else {	// Descenso del salto

			// Calcula la nueva posicion
			CHARACTER.pos_fy += CHARACTER.air_speed;
			CHARACTER.jump_height -= CHARACTER.air_speed;
			// Y verifica las colisiones
			t_up = CharacterCheckUp(1);
			t_down = CharacterCheckDown(1);
			// Y si has terminado de descender
			if ((t_down == T_WALL) || (t_down == T_STEEP) || ((t_up == T_STAIR) && (t_down == T_STAIR) && KEYHELD.up)) {
				// Tocas un muro
				if (t_down == T_WALL) {
					// Cancela el salto
					CHARACTER.is_jump = false;
					// Borra la aceleracion en el aire si has tocado el suelo
					CHARACTER.air_speed = 0;
					// Ajusta la posicion del personaje
					t_inside = CharacterCheckDown(0);
					while (t_inside == T_WALL) {
						CHARACTER.pos_fy -= 64;
						t_inside = CharacterCheckDown(0);
					}
					// Calcula si se pierde vida con la caida
					FallDamage();
				}
				// Estas en una escalera
				if (((t_up == T_STAIR) && (t_down == T_STAIR) && KEYHELD.up)) {
					// Cancela el salto
					CHARACTER.is_jump = false;
					// Borra la aceleracion en el aire si has tocado el suelo
					CHARACTER.air_speed = 0;
				}
				// Tocas un escalon
				if (t_down == T_STEEP) {
					// Si no estas en un forzado de caida, ajustalo
					if (!CHARACTER.force_down) {
						// Deten la caida
						CHARACTER.is_jump = false;
						CHARACTER.air_speed = 0;
						// Ajusta el personaje al nivel del suelo/escalon
						t_inside = CharacterCheckDown(0);
						while (t_inside == T_STEEP) {
							// Ajusta la posicion
							CHARACTER.pos_fy -= 64;
							// Verifica de nuevo
							t_inside = CharacterCheckDown(0);
						}
						// Calcula si se pierde vida con la caida
						FallDamage();
					} else {
						// Si no, calcula la nueva aceleracion
						if (CHARACTER.air_speed < CHARACTER_AIR_MAX_SPEED) {
							CHARACTER.air_speed += (CHARACTER.air_speed >> 4);
							if (CHARACTER.air_speed > CHARACTER_AIR_MAX_SPEED) CHARACTER.air_speed = CHARACTER_AIR_MAX_SPEED;
						}
					}
				}
			} else {
				// Si no, calcula la nueva aceleracion
				if (CHARACTER.air_speed < CHARACTER_AIR_MAX_SPEED) {
					CHARACTER.air_speed += (CHARACTER.air_speed >> 4);
					if (CHARACTER.air_speed > CHARACTER_AIR_MAX_SPEED) CHARACTER.air_speed = CHARACTER_AIR_MAX_SPEED;
				}
			}

			// Debes cancelar el forzado de caida?
			if (CHARACTER.force_down && (t_down != T_STEEP)) CHARACTER.force_down = false;

		}

	}

}



// Funcion CharacterWalk();
void CharacterWalk(void) {

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
	t_left = CharacterCheckLeft(1);
	t_right = CharacterCheckRight(1);

	// Calcula si puedes ir a la derecha
	if ((t_right != T_WALL) && !CHARACTER.fall && !CHARACTER.is_jump) { 
		CHARACTER.mov_right = true;
	} else {
		CHARACTER.mov_right = false;
	}

	// Calcula si puedes ir a la izquierda
	if ((t_left != T_WALL) && !CHARACTER.fall && !CHARACTER.is_jump) {
		CHARACTER.mov_left = true;
	} else {
		CHARACTER.mov_left = false;
	}


	/*
	-------------------------------------------------
		Aplica las acciones
	-------------------------------------------------
	*/

	// Si no estas presionando arriba/abajo
	if (!KEYHELD.up && !KEYHELD.down) {

		// Andar a la derecha
		if (KEYHELD.right && CHARACTER.mov_right) {
			// Nueva posicion
			CHARACTER.pos_fx += CHARACTER_WALK_SPEED;
			// Resetea aceleracion en el aire
			CHARACTER.air_speed = 0;
		}

		// Andar a la izquierda
		if (KEYHELD.left && CHARACTER.mov_left) {
			// Nueva posicion
			CHARACTER.pos_fx -= CHARACTER_WALK_SPEED;
			// Resetea aceleracion en el aire
			CHARACTER.air_speed = 0;
		}

	}

}



// Funcion CharacterAdjustPosition();
void CharacterAdjustPosition(void) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	u16 t_left = T_AIR, t_right = T_AIR, t_down = T_AIR;	// Almacena los tiles


	/*
	-------------------------------------------------
		Ajusta el personaje a derecha e izquierda
	-------------------------------------------------
	*/

	// Ajusta el limite derecho
	t_right = CharacterCheckRight(0);
	// Si estavas a medio salto, cancela el desplazamiento lateral
	if (CHARACTER.is_jump && (CHARACTER.jump_direction > 0) && (t_right == T_WALL)) CHARACTER.jump_direction = 0;
	// Ajusta la posicion a la derecha
	while (t_right == T_WALL) {
		CHARACTER.pos_fx -= 64;
		t_right = CharacterCheckRight(0);
	}

	// Ajusta el limite izquierdo
	t_left = CharacterCheckLeft(0);
	// Si estavas a medio salto, cancela el desplazamiento lateral
	if (CHARACTER.is_jump && (CHARACTER.jump_direction < 0) && (t_left == T_WALL)) CHARACTER.jump_direction = 0;
	// Ajusta la posicion de la izquierda
	while (t_left == T_WALL) {
		CHARACTER.pos_fx += 64;
		t_left = CharacterCheckLeft(0);
	}

	/*
	-------------------------------------------------
		Ajusta el nivel del suelo del personaje
	-------------------------------------------------
	*/
	t_down = CharacterCheckDown(0);
	while (t_down == T_WALL) {
		CHARACTER.pos_fy -= 64;
		t_down = CharacterCheckDown(0);
	}

}



// Funcion CharacterAnimation();
void CharacterAnimation(void) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	// Por defecto, no estas agachado
	CHARACTER.duck = 0;


	/*
	-------------------------------------------------
		Acciones
	-------------------------------------------------
	*/

	// Juego de animaciones cayendo
	if (CHARACTER.fall) {
		// Si entras en esta animacion
		if (CHARACTER.anim != CHARACTER_ANIM_FALL) {
			CHARACTER.anim = CHARACTER_ANIM_FALL;
			CHARACTER.frame = 12;
			CHARACTER.frame_cnt = 0;
		}
		// Animacion caerse (Frames 12 a 13)
		CHARACTER.frame_cnt ++;
		if (CHARACTER.frame_cnt > 6) {
			CHARACTER.frame_cnt = 0;
			CHARACTER.frame ++;
			if (CHARACTER.frame > 13) CHARACTER.frame = 12;
		}
	}


	// Juego de animaciones saltando
	if (CHARACTER.is_jump) {

		// Salto hacia arriba
		if (CHARACTER.jump_up) {

			// Registra la animacion
			if (CHARACTER.anim != CHARACTER_ANIM_JUMP) {
				CHARACTER.anim = CHARACTER_ANIM_JUMP;
				CHARACTER.frame_cnt = 0;
			}
			// Salto arriba (Frame 10)
			CHARACTER.frame = 10;

		} else {	// Salto hacia abajo

			// Si aun estas en la altura del salto normal
			if (CHARACTER.jump_height >= 0) {

				// Salto abajo (Frame 11)
				CHARACTER.frame = 11;

			} else {	// Si estas cayendote...

				// Si entras en esta animacion
				if (CHARACTER.anim != CHARACTER_ANIM_FALL) {
					CHARACTER.anim = CHARACTER_ANIM_FALL;
					CHARACTER.frame = 12;
					CHARACTER.frame_cnt = 0;
				}
				// Animacion caerse (Frames 12 a 13)
				CHARACTER.frame_cnt ++;
				if (CHARACTER.frame_cnt > 6) {
					CHARACTER.frame_cnt = 0;
					CHARACTER.frame ++;
					if (CHARACTER.frame > 13) CHARACTER.frame = 12;
				}

			}

		}

	}


	// Juego de animaciones en la escalera
	if ((CHARACTER.in_stair || CHARACTER.stair_down) && !CHARACTER.is_jump && !CHARACTER.fall) {
		// Si entras en esta animacion
		if (CHARACTER.anim != CHARACTER_ANIM_STAIRS) {
			CHARACTER.anim = CHARACTER_ANIM_STAIRS;
			CHARACTER.frame = 8;
			CHARACTER.frame_cnt = 0;
		}
		// Animacion si puedes moverte
		if (
			(CHARACTER.stair_up && KEYHELD.up)
			||
			(CHARACTER.stair_down && KEYHELD.down)
			||
			(CHARACTER.mov_right && KEYHELD.right && !KEYHELD.up)
			||
			(CHARACTER.mov_left && KEYHELD.left && !KEYHELD.up)
			) {
			// Animacion moviendose por la escalera (Frames 8 a 9)
			CHARACTER.frame_cnt ++;
			if (CHARACTER.frame_cnt > 10) {
				CHARACTER.frame_cnt = 0;
				CHARACTER.frame ++;
				if (CHARACTER.frame > 9) CHARACTER.frame = 8;
			}
		}
	}

	// Juego de animaciones en el suelo (Quieto, andar, agacharse, lanzar hechizo)
	if (!CHARACTER.fall && !CHARACTER.in_stair && !CHARACTER.stair_down && !CHARACTER.is_jump) {

		// Si estas lanzando el hechizo...
		if (CHARACTER.spell) {

			// Si entras en esta animacion
			if (CHARACTER.anim != CHARACTER_ANIM_SPELL) {
				CHARACTER.anim = CHARACTER_ANIM_SPELL;
				CHARACTER.frame = 14;
				CHARACTER.frame_cnt = 0;
			}
			// Animacion andando (Frames 14 a 16)
			CHARACTER.frame_cnt ++;
			if (CHARACTER.frame_cnt > 5) {
				CHARACTER.frame_cnt = 0;
				CHARACTER.frame ++;
				// Si la animacion termina...
				if (CHARACTER.frame > 16) {
					CHARACTER.frame = 0;
					CHARACTER.spell = false;
				}
			}

		} else {	// Si no estas lanzando el hechizo

			// Si no estas presionando arriba/abajo...
			if (!KEYHELD.up && !KEYHELD.down) {
			
				// Andar
				if ((CHARACTER.mov_right && KEYHELD.right) || (CHARACTER.mov_left && KEYHELD.left)) {
					// Si entras en esta animacion
					if (CHARACTER.anim != CHARACTER_ANIM_WALK) {
						CHARACTER.anim = CHARACTER_ANIM_WALK;
						CHARACTER.frame = 1;
						CHARACTER.frame_cnt = 0;
					}
					// Animacion andando (Frames 1 a 6)
					CHARACTER.frame_cnt ++;
					if (CHARACTER.frame_cnt > 5) {
						CHARACTER.frame_cnt = 0;
						CHARACTER.frame ++;
						if (CHARACTER.frame > 6) CHARACTER.frame = 1;
					}
				} else {
					// Quieto (Frame 0)
					CHARACTER.anim = CHARACTER_ANIM_STANDBY;
					CHARACTER.frame = 0;
					CHARACTER.frame_cnt = 0;
				}

			} else {

				if (KEYHELD.down) {
					// Agachado (Frame 7)
					CHARACTER.anim = CHARACTER_ANIM_DUCK;
					CHARACTER.frame = 7;
					CHARACTER.frame_cnt = 0;
					CHARACTER.duck = 1;
				} else {
					// Quieto (Frame 0)
					CHARACTER.anim = CHARACTER_ANIM_STANDBY;
					CHARACTER.frame = 0;
					CHARACTER.frame_cnt = 0;
				}

			}

		}

	}

	// Calcula y marca la direccion a la que miras
	if (
		(CHARACTER.anim != CHARACTER_ANIM_FALL)
		&&
		(CHARACTER.anim != CHARACTER_ANIM_JUMP)
		) {
		if (KEYHELD.right && CHARACTER.flip) CHARACTER.flip = false;
		if (KEYHELD.left && !CHARACTER.flip) CHARACTER.flip = true;
	}
	
}



// Funcion CharacterMove();
void CharacterMove(void) {

	/*
	-------------------------------------------------
		Movimiento del personaje
	-------------------------------------------------
	*/

	// Procesa si se cae
	CharacterFall();

	// Procesa el salto
	CharacterJump();

	// Procesa moverte por las escaleras
	CharacterStairs();

	// Procesa el andar (si no estas disparando el hechizo)
	if (!CHARACTER.spell) CharacterWalk();

	// Ajusta la posicion del personaje, para que no atraviese ningun limite
	CharacterAdjustPosition();

	// Animacion del personaje
	CharacterAnimation();


	/*
	-------------------------------------------------
		Ajustes de posicion
	-------------------------------------------------
	*/

	CHARACTER.pos_x = (CHARACTER.pos_fx >> 8);
	CHARACTER.pos_y = (CHARACTER.pos_fy >> 8);
	CHARACTER.stage = GetStage(CHARACTER.pos_x, CHARACTER.pos_y);

	/*
	-------------------------------------------------
		Invulnerable
	-------------------------------------------------
	*/
	if (CHARACTER.immunity > 0) {
		CHARACTER.immunity --;
		CHARACTER.show = !CHARACTER.show;
		if (CHARACTER.immunity == 0) {
			CHARACTER.show = true;
		}
	}

}



// Funcion CameraCharacterHide();
void CameraCharacterHide(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Gestion del Personaje
	-------------------------------------------------
	*/

	// Calcula la posicion del sprite en la pantalla
	s32 spr_x = (CHARACTER.pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
	s32 spr_y = (CHARACTER.pos_y - STAGE[stage].stg_top);

	// Calcula si esta en pantalla
	if (
		(spr_x < -32)
		||
		(spr_x > 287)
		||
		(spr_y < -32)
		||
		(spr_y > 223)
		) {
		// No lo esta
		CHARACTER.on_screen[screen] = false;
		CHARACTER.scr_x[screen] = -64;
		CHARACTER.scr_y[screen] = -64;
		// Destruye el sprite
		if (CHARACTER.created[screen]) {
			CHARACTER.created[screen] = false;
			NF_DeleteSprite(screen, CHARACTER_SPR_ID);
			NF_FreeSpriteGfx(screen, CHARACTER_SPR_ID);
		}
	}

}



// Funcion CameraCharacterShow();
void CameraCharacterShow(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Gestion del Personaje
	-------------------------------------------------
	*/

	// Calcula la posicion del sprite en la pantalla
	s32 spr_x = (CHARACTER.pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
	s32 spr_y = (CHARACTER.pos_y - STAGE[stage].stg_top);

	// Calcula si esta en pantalla
	if (
		(spr_x >= -32)
		&&
		(spr_x <= 287)
		&&
		(spr_y >= -32)
		&&
		(spr_y <= 223)
		) {
		// Esta en pantalla
		CHARACTER.on_screen[screen] = true;
		CHARACTER.scr_x[screen] = spr_x;
		CHARACTER.scr_y[screen] = spr_y;
		// Si no esta creado, crealo
		if (!CHARACTER.created[screen]) {
			CHARACTER.created[screen] = true;
			NF_VramSpriteGfx(screen, ID_CHARACTER, CHARACTER_SPR_ID, true);
			NF_CreateSprite(screen, CHARACTER_SPR_ID, CHARACTER_SPR_ID, CHARACTER_SPR_PAL, (CHARACTER.scr_x[screen] - CHARACTER.spr_left), (CHARACTER.scr_y[screen] - CHARACTER.spr_up));
			NF_SpriteLayer(screen, CHARACTER_SPR_ID, SPRITES_LAYER);
		}
		// Frame del evento especial (fin de juego)
		if ((screen == 1) && (CHARACTER.frame == 21)) {
			NF_SpriteFrame(screen, CHARACTER_SPR_ID, 22);
		} else {
			// Frame normal
			NF_SpriteFrame(screen, CHARACTER_SPR_ID, CHARACTER.frame);
		}
		// Actualiza el Sprite
		NF_ShowSprite(screen, CHARACTER_SPR_ID, CHARACTER.show);
		NF_HflipSprite(screen, CHARACTER_SPR_ID, CHARACTER.flip);
		NF_MoveSprite(screen, CHARACTER_SPR_ID, (CHARACTER.scr_x[screen] - CHARACTER.spr_left), (CHARACTER.scr_y[screen] - CHARACTER.spr_up));
	}

}



// Funcion CharacterGetItem();
void CharacterGetItem(void) {

	// Variables
	s32 char_xa, char_xb, char_ya, char_yb;		// Limites personaje
	s32 item_xa, item_xb, item_ya, item_yb;		// Limites item
	bool checkit = false;						// Flag de verificacion

	// Si se pulsa A, verifica si se puede coger un item
	if (KEYPRESS.a) {
		// Si el personaje esta en condiciones de coger un item...
		if (
			!CHARACTER.is_jump
			&&
			!CHARACTER.fall
			&&
			!CHARACTER.in_stair
			&&
			(CHARACTER.duck == 0)
			) {
			// Verificado
			checkit = true;
		}
	}

	// Si la verificacion ha sido correcta, comprueba si se ha cogido alguno
	if (checkit) {

		// Calcula las coordenadas de referencia del personaje
		char_xa = (CHARACTER.pos_x - CHARACTER.left);
		char_xb = (CHARACTER.pos_x + CHARACTER.right);
		char_ya = (CHARACTER.pos_y - CHARACTER.up[0]);
		char_yb = (CHARACTER.pos_y + CHARACTER.down);

		// Verifica si se puede coger la Bola de cristal
		if (!CRISTALLBALL.done) {
			// Calcula las coordenadas de referencia de la bola
			item_xa = CRISTALLBALL.pos_x;
			item_xb = (CRISTALLBALL.pos_x + CRISTALLBALL.width);
			item_ya = CRISTALLBALL.pos_y;
			item_yb = (CRISTALLBALL.pos_y + CRISTALLBALL.height);
			// Verifica si se ha tocado la bola al pulsar el boton
			if (CheckRectCollision(char_xa, char_ya, char_xb, char_yb, item_xa, item_ya, item_xb, item_yb)) {
				// Coge la bola
				GetCristallball();
			}
		}

		// Verifica si se puede coger el libro de hechizos
		if (!SPELLBOOK.done) {
			// Calcula las coordenadas de referencia del libro de hechizos
			item_xa = SPELLBOOK.pos_x;
			item_xb = (SPELLBOOK.pos_x + SPELLBOOK.width);
			item_ya = SPELLBOOK.pos_y;
			item_yb = (SPELLBOOK.pos_y + SPELLBOOK.height);
			// Verifica si se ha tocado la bola al pulsar el boton
			if (CheckRectCollision(char_xa, char_ya, char_xb, char_yb, item_xa, item_ya, item_xb, item_yb)) {
				// Coge el libro
				GetSpellbook();
			}
		}

		// Verifica si se puede coger la varita magica
		if (!MAGICWAND.done) {
			// Calcula las coordenadas de referencia de la bola
			item_xa = MAGICWAND.pos_x;
			item_xb = (MAGICWAND.pos_x + MAGICWAND.width);
			item_ya = MAGICWAND.pos_y;
			item_yb = (MAGICWAND.pos_y + MAGICWAND.height);
			// Verifica si se ha tocado la bola al pulsar el boton
			if (CheckRectCollision(char_xa, char_ya, char_xb, char_yb, item_xa, item_ya, item_xb, item_yb)) {
				// Coge la varita
				GetMagicwand();
			}
		}

	}

}



// Funcion CharacterRevivePoint();
void CharacterRevivePoint(void) {

	/*
	-------------------------------------------------
		Verifica si hay que crear un
		punto de resurreccion
	-------------------------------------------------
	*/

	// Si has cambiado de stage...
	if (CHARACTER.stage != REVIVE.stage) {
		// Y el personaje no se esta cayendo ni saltando
		if (!CHARACTER.is_jump && !CHARACTER.fall && (CHARACTER.stage != 19)) {
			CharacterBackupPos();
		}
	}

	// Actualiza la posicion de referencia para la siguiente verificacion
	CHARACTER.old_x = CHARACTER.pos_x;
	CHARACTER.old_y = CHARACTER.pos_y;

}



// Funcion CharacterBackupPos();
void CharacterBackupPos(void) {

	// Variables
	s16 x = 0;

	// Calcula el desplazamiento lateral
	if (CHARACTER.pos_y == CHARACTER.old_y) {
		if (CHARACTER.pos_x > CHARACTER.old_x) {
			x = 32;
		} else {
			x = -32;
		}
	}

	// Copia los datos
	REVIVE.air_speed = CHARACTER.air_speed;
	REVIVE.anim = CHARACTER.anim;
	REVIVE.can_jump = CHARACTER.can_jump;
	REVIVE.duck = CHARACTER.duck;
	REVIVE.fall = CHARACTER.fall;
	REVIVE.flip = CHARACTER.flip;
	REVIVE.force_down = CHARACTER.force_down;
	REVIVE.frame = CHARACTER.frame;
	REVIVE.frame_cnt = CHARACTER.frame_cnt;
	REVIVE.in_stair = CHARACTER.in_stair;
	REVIVE.is_jump = CHARACTER.is_jump;
	REVIVE.jump_direction = CHARACTER.jump_direction;
	REVIVE.jump_height = CHARACTER.jump_height;
	REVIVE.jump_up = CHARACTER.jump_up;
	REVIVE.mov_left = CHARACTER.mov_left;
	REVIVE.mov_right = CHARACTER.mov_right;
	REVIVE.pos_x = (CHARACTER.pos_x + x);
	REVIVE.pos_y = CHARACTER.pos_y;
	REVIVE.pos_fx = (REVIVE.pos_x << 8);
	REVIVE.pos_fy = (REVIVE.pos_y << 8);
	REVIVE.spell = CHARACTER.spell;
	REVIVE.stage = CHARACTER.stage;
	REVIVE.stair_down = CHARACTER.stair_down;
	REVIVE.stair_up = CHARACTER.stair_up;

}



// Funcion CharacterRestorePos();
void CharacterRestorePos(void) {

	CHARACTER.air_speed = REVIVE.air_speed;
	CHARACTER.anim = REVIVE.anim;
	CHARACTER.can_jump = REVIVE.can_jump;
	CHARACTER.duck = REVIVE.duck;
	CHARACTER.fall = REVIVE.fall;
	CHARACTER.flip = REVIVE.flip;
	CHARACTER.force_down = REVIVE.force_down;
	CHARACTER.frame = REVIVE.frame;
	CHARACTER.frame_cnt = REVIVE.frame_cnt;
	CHARACTER.in_stair = REVIVE.in_stair;
	CHARACTER.is_jump = REVIVE.is_jump;
	CHARACTER.jump_direction = REVIVE.jump_direction;
	CHARACTER.jump_height = REVIVE.jump_height;
	CHARACTER.jump_up = REVIVE.jump_up;
	CHARACTER.mov_left = REVIVE.mov_left;
	CHARACTER.mov_right = REVIVE.mov_right;
	CHARACTER.pos_fx = REVIVE.pos_fx;
	CHARACTER.pos_fy = REVIVE.pos_fy;
	CHARACTER.pos_x = REVIVE.pos_x;
	CHARACTER.pos_y = REVIVE.pos_y;
	CHARACTER.spell = REVIVE.spell;
	CHARACTER.stage = REVIVE.stage;
	CHARACTER.stair_down = REVIVE.stair_down;
	CHARACTER.stair_up = REVIVE.stair_up;

}
