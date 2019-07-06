/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de los enemigos

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



// Funcion EnemyMain();
void EnemyMain(void) {

	// IA de los enemigos, si el personaje esta vivo
	if (MAINGAME.player_alive) {
		GoulAi();			// Gouls
		PhantomAi();		// Fantasmas
		WolfAi();			// Hombres lobo
	}

	// Mueve los enemigos
	GoulMove();			// Gouls
	PhantomMove();		// Fantasmas
	WolfMove();			// Hombres lobo

}



// Funcion GoulAi();
void GoulAi(void) {

	// Variables
	u8 n = 0;			// Bucle
	s32 dist = 0;		// Distancia entre Personaje <> Enemigo

	for (n = 0; n < ENEMY_NUM_GOUL; n ++) {
		// Si esta despierto y en la pantalla principal
		if ((GOUL[n].sleep == 0) && (GOUL[n].ignore > 0) && GOUL[n].on_screen[0]) {
			// Calcula la distancia
			dist = CHARACTER.pos_x - GOUL[n].pos_x;
			if (dist < 0) dist = -dist;
			// Si esta dentro del rango...
			if ((dist > ENEMY_AI_RANGE) && (dist < 256) && (GOUL[n].delay == 0)) {
				// Si esta a la derecha y anda hacia a la derecha, cambio de sentido
				if ((GOUL[n].pos_x > CHARACTER.pos_x) && !GOUL[n].flip) {
					GOUL[n].speed = -GOUL[n].speed;
					GOUL[n].flip = true;
					GOUL[n].ignore --;
					GOUL[n].delay = ENEMY_AI_DELAY;
				}
				// Si esta a la izquierda y anda hacia a la izquierda, cambio de sentido
				if ((GOUL[n].pos_x < CHARACTER.pos_x) && GOUL[n].flip) {
					GOUL[n].speed = -GOUL[n].speed;
					GOUL[n].flip = false;
					GOUL[n].ignore --;
					GOUL[n].delay = ENEMY_AI_DELAY;
				}
			}
			if (GOUL[n].delay > 0) GOUL[n].delay --;
		} else {
			// Reinicia el contador de IGNORE si estas fuera de la pantalla
			if (!GOUL[n].on_screen[0] || (GOUL[n].sleep != 0)) GOUL[n].ignore = ENEMY_AI_IGNORE;
		}
	}

}



// Funcion PhantomAi();
void PhantomAi(void) {

// Variables
	u8 n = 0;			// Bucle
	s32 dist = 0;		// Distancia entre Personaje <> Enemigo

	for (n = 0; n < ENEMY_NUM_PHANTOM; n ++) {
		// Si esta despierto y en la pantalla principal
		if ((PHANTOM[n].sleep == 0) && (PHANTOM[n].ignore > 0) && PHANTOM[n].on_screen[0]) {
			// Calcula la distancia
			dist = CHARACTER.pos_x - PHANTOM[n].pos_x;
			if (dist < 0) dist = -dist;
			// Si esta dentro del rango...
			if ((dist > ENEMY_AI_RANGE) && (dist < 256) && (PHANTOM[n].delay == 0)) {
				// Si esta a la derecha y anda hacia a la derecha, cambio de sentido
				if ((PHANTOM[n].pos_x > CHARACTER.pos_x) && !PHANTOM[n].flip) {
					PHANTOM[n].speed = -PHANTOM[n].speed;
					PHANTOM[n].flip = true;
					PHANTOM[n].ignore --;
					PHANTOM[n].delay = ENEMY_AI_DELAY;
				}
				// Si esta a la izquierda y anda hacia a la izquierda, cambio de sentido
				if ((PHANTOM[n].pos_x < CHARACTER.pos_x) && PHANTOM[n].flip) {
					PHANTOM[n].speed = -PHANTOM[n].speed;
					PHANTOM[n].flip = false;
					PHANTOM[n].ignore --;
					PHANTOM[n].delay = ENEMY_AI_DELAY;
				}
			}
			if (PHANTOM[n].delay > 0) PHANTOM[n].delay --;
		} else {
			// Reinicia el contador de IGNORE si estas fuera de la pantalla
			if (!PHANTOM[n].on_screen[0] || (PHANTOM[n].sleep != 0)) PHANTOM[n].ignore = ENEMY_AI_IGNORE;
		}
	}

}



// Funcion WolfAi();
void WolfAi(void) {

	// Variables
	u8 n = 0;			// Bucle
	s32 dist = 0;		// Distancia entre Personaje <> Enemigo

	for (n = 0; n < ENEMY_NUM_WOLF; n ++) {
		// Si esta despierto y en la pantalla principal
		if ((WOLF[n].sleep == 0) && (WOLF[n].ignore > 0) && WOLF[n].on_screen[0]) {
			// Calcula la distancia
			dist = CHARACTER.pos_x - WOLF[n].pos_x;
			if (dist < 0) dist = -dist;
			// Si esta dentro del rango...
			if ((dist > ENEMY_AI_RANGE) && (dist < 256) && (WOLF[n].delay == 0)) {
				// Si esta a la derecha y anda hacia a la derecha, cambio de sentido
				if ((WOLF[n].pos_x > CHARACTER.pos_x) && !WOLF[n].flip) {
					WOLF[n].speed = -WOLF[n].speed;
					WOLF[n].flip = true;
					WOLF[n].ignore --;
					WOLF[n].delay = ENEMY_AI_DELAY;
				}
				// Si esta a la izquierda y anda hacia a la izquierda, cambio de sentido
				if ((WOLF[n].pos_x < CHARACTER.pos_x) && WOLF[n].flip) {
					WOLF[n].speed = -WOLF[n].speed;
					WOLF[n].flip = false;
					WOLF[n].ignore --;
					WOLF[n].delay = ENEMY_AI_DELAY;
				}
			}
			if (WOLF[n].delay > 0) WOLF[n].delay --;
		} else {
			// Reinicia el contador de IGNORE si estas fuera de la pantalla
			if (!WOLF[n].on_screen[0] || (WOLF[n].sleep != 0)) WOLF[n].ignore = ENEMY_AI_IGNORE;
		}
	}

}



// Funcion GoulMove();
void GoulMove(void) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 x, y;			// Posicion de donde leer el tile
	s32 fx, fy;			// Posicion del goul
	s32 start, end;		// Rango del analisis de tiles
	s16 tile;			// Tiles obtenidos
	bool collision;		// Colision detectada
	u8 n = 0;			// Uso general


	/*
	-------------------------------------------------
		Calcula el movimiento de cada goul
	-------------------------------------------------
	*/

	for (n = 0; n < ENEMY_NUM_GOUL; n ++) {

		// Si esta despierto...
		if (GOUL[n].sleep == 0) {

			// Variables de posicion
			fx = (GOUL[n].pos_fx >> 8);
			fy = (GOUL[n].pos_fy >> 8);

			// Rango de analisis
			start = (fy - GOUL[n].up);
			end = (fy + GOUL[n].down);
			collision = false;

			// Lee los tiles dependiendo de la direccion
			if (GOUL[n].speed > 0) {
				// A la derecha
				for (y = start; y <= end; y += 8) {
					x = (fx + GOUL[n].right + 1);
					tile = NF_GetTile(MAINMAP_SLOT, x, y);
					if (tile == T_WALL) {
						collision = true;
						y = end;
					}
				}
				// A la derecha, abajo
				x = (fx + GOUL[n].right + 1);
				y = (fy + GOUL[n].down + 1);
				tile = NF_GetTile(MAINMAP_SLOT, x, y);
				// Si algun tile no deja continuar al goul, cambio de direccion
				if (collision || (tile == T_AIR)) {
					GOUL[n].speed = -GOUL[n].speed;
					GOUL[n].flip = true;
				}
			} else {
				// A la Izquierda
				for (y = start; y <= end; y += 8) {
					x = (fx - GOUL[n].left - 1);
					tile = NF_GetTile(MAINMAP_SLOT, x, y);
					if (tile == T_WALL) {
						collision = true;
						y = end;
					}
				}
				// A la izquierda, abajo
				x = (fx - GOUL[n].left - 1);
				y = (fy + GOUL[n].down + 1);
				tile = NF_GetTile(MAINMAP_SLOT, x, y);
				// Si algun tile no deja continuar al goul, cambio de direccion
				if (collision || (tile == T_AIR)) {
					GOUL[n].speed = -GOUL[n].speed;
					GOUL[n].flip = false;
				}
			}

			// Actualiza la animacion del Goul
			GOUL[n].frame_cnt ++;
			if (GOUL[n].frame_cnt > 7) {
				GOUL[n].frame_cnt = 0;
				GOUL[n].frame ++;
				if (GOUL[n].frame > 3) GOUL[n].frame = 0;
			}

			// Actualiza la posicion del Goul
			GOUL[n].pos_fx += GOUL[n].speed;
			GOUL[n].pos_x = (GOUL[n].pos_fx >> 8);
			GOUL[n].stage = GetStage(GOUL[n].pos_x, GOUL[n].pos_y);

		} else {

			// Si esta dormido...
			GOUL[n].sleep --;
			if (GOUL[n].sleep <= 0) GOUL[n].sleep = 0;

		}

	}

}



// Funcion PhantomMove();
void PhantomMove(void) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 x, y;			// Posicion de donde leer el tile
	s32 fx, fy;			// Posicion del goul
	s32 start, end;		// Rango del analisis de tiles
	s16 tile;			// Tiles obtenidos
	bool collision;		// Colision detectada
	u8 n = 0;			// Uso general


	/*
	-------------------------------------------------
		Calcula el movimiento de cada phantom
	-------------------------------------------------
	*/

	for (n = 0; n < ENEMY_NUM_PHANTOM; n ++) {

		// Si esta despierto...
		if (PHANTOM[n].sleep == 0) {

			// Variables de posicion
			fx = (PHANTOM[n].pos_fx >> 8);
			fy = (PHANTOM[n].pos_fy >> 8);

			// Rango de analisis
			start = (fy - PHANTOM[n].up);
			end = (fy + PHANTOM[n].down);
			collision = false;

			// Lee los tiles dependiendo de la direccion
			if (PHANTOM[n].speed > 0) {
				// A la derecha
				for (y = start; y <= end; y += 8) {
					x = (fx + PHANTOM[n].right + 1);
					tile = NF_GetTile(MAINMAP_SLOT, x, y);
					if (tile == T_WALL) {
						collision = true;
						y = end;
					}
				}
				// Si algun tile no deja continuar al phantom, cambio de direccion
				if (collision) {
					PHANTOM[n].speed = -PHANTOM[n].speed;
					PHANTOM[n].flip = true;
				}
			} else {
				// A la Izquierda
				for (y = start; y <= end; y += 8) {
					x = (fx - PHANTOM[n].left - 1);
					tile = NF_GetTile(MAINMAP_SLOT, x, y);
					if (tile == T_WALL) {
						collision = true;
						y = end;
					}
				}
				// Si algun tile no deja continuar al phantom, cambio de direccion
				if (collision) {
					PHANTOM[n].speed = -PHANTOM[n].speed;
					PHANTOM[n].flip = false;
				}
			}

			// Actualiza la animacion del Phantom
			PHANTOM[n].frame_cnt ++;
			if (PHANTOM[n].frame_cnt > 9) {
				PHANTOM[n].frame_cnt = 0;
				PHANTOM[n].frame ++;
				if (PHANTOM[n].frame > 3) PHANTOM[n].frame = 0;
			}

			// Actualiza la posicion del Phantom
			PHANTOM[n].pos_fx += PHANTOM[n].speed;
			PHANTOM[n].pos_x = (PHANTOM[n].pos_fx >> 8);
			PHANTOM[n].stage = GetStage(PHANTOM[n].pos_x, PHANTOM[n].pos_y);

		} else {

			// Si esta dormido...
			PHANTOM[n].sleep --;
			if (PHANTOM[n].sleep <= 0) PHANTOM[n].sleep = 0;

		}

	}

}



// Funcion WolfMove();
void WolfMove(void) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 x, y;		// Posicion de donde leer el tile
	s32 fx, fy;		// Posicion del wolf
	s16 tile[2];	// Tiles obtenidos
	u8 n = 0;		// Uso general


	/*
	-------------------------------------------------
		Calcula el movimiento de cada wolf
	-------------------------------------------------
	*/

	for (n = 0; n < ENEMY_NUM_WOLF; n ++) {

		// Si esta despierto...
		if (WOLF[n].sleep == 0) {

			// Variables de posicion
			fx = (WOLF[n].pos_fx >> 8);
			fy = (WOLF[n].pos_fy >> 8);

			// Lee los tiles dependiendo de la direccion
			if (WOLF[n].speed > 0) {
				// A la derecha
				x = (fx + WOLF[n].right + 1);
				y = (fy + WOLF[n].down);
				tile[0] = NF_GetTile(MAINMAP_SLOT, x, y);
				// A la derecha, abajo
				x = (fx + WOLF[n].right + 1);
				y = (fy + WOLF[n].down + 1);
				tile[1] = NF_GetTile(MAINMAP_SLOT, x, y);
				// Si algun tile no deja continuar al wolf, cambio de direccion
				if ((tile[0] == T_WALL) || (tile[1] == T_AIR)) {
					WOLF[n].speed = -WOLF[n].speed;
					WOLF[n].flip = true;
				}
			} else {
				// A la Izquierda
				x = (fx - WOLF[n].left - 1);
				y = (fy + WOLF[n].down);
				tile[0] = NF_GetTile(MAINMAP_SLOT, x, y);
				// A la derecha, abajo
				x = (fx - WOLF[n].left - 1);
				y = (fy + WOLF[n].down + 1);
				tile[1] = NF_GetTile(MAINMAP_SLOT, x, y);
				// Si algun tile no deja continuar al wolf, cambio de direccion
				if ((tile[0] == T_WALL) || (tile[1] == T_AIR)) {
					WOLF[n].speed = -WOLF[n].speed;
					WOLF[n].flip = false;
				}
			}

			// Actualiza la animacion del Wolf
			WOLF[n].frame_cnt ++;
			if (WOLF[n].frame_cnt > 6) {
				WOLF[n].frame_cnt = 0;
				WOLF[n].frame ++;
				if (WOLF[n].frame > 3) WOLF[n].frame = 0;
			}

			// Actualiza la posicion del Wolf
			WOLF[n].pos_fx += WOLF[n].speed;
			WOLF[n].pos_x = (WOLF[n].pos_fx >> 8);
			WOLF[n].stage = GetStage(WOLF[n].pos_x, WOLF[n].pos_y);

		} else {

			// Si esta dormido...
			WOLF[n].sleep --;
			if (WOLF[n].sleep <= 0) WOLF[n].sleep = 0;

		}

	}

}



// Funcion EnemyGetSpriteId();
u16 EnemyGetSpriteId(u8 screen) {

	// Variables
	u8 n = 0;
	u8 id = 255;

	// Busca una Id libre y asignala
	for (n = 0; n < ENEMY_SPR_NUM; n ++) {
		if (!ENEMY_SPR[screen].in_use[n]) {
			id = n;
			ENEMY_SPR[screen].in_use[id] = true;
			n = ENEMY_SPR_NUM;
		}
	}

	// Devuelve la ID
	return ENEMY_SPR[screen].id[id];

}



// Funcion EnemyFreeSpriteId();
void EnemyFreeSpriteId(u8 screen, u16 id) {

	// Variables
	u8 n = 0;

	// Busca una Id libre y asignala
	for (n = 0; n < ENEMY_SPR_NUM; n ++) {
		if (ENEMY_SPR[screen].id[n] == id) {
			ENEMY_SPR[screen].in_use[n] = false;
			n = ENEMY_SPR_NUM;
		}
	}

}


// Funcion CameraGoulHide();
void CameraGoulHide(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;
	u8 n = 0;


	/*
	-------------------------------------------------
		Gestion de los gouls
	-------------------------------------------------
	*/

	for (n = 0; n < ENEMY_NUM_GOUL; n ++) {
		// Calcula la posicion del sprite en la pantalla
		spr_x = (GOUL[n].pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
		spr_y = (GOUL[n].pos_y - STAGE[stage].stg_top);
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
			GOUL[n].on_screen[screen] = false;
			GOUL[n].scr_x[screen] = -64;
			GOUL[n].scr_y[screen] = -64;
			// Destruye el sprite
			if (GOUL[n].created[screen]) {
				GOUL[n].created[screen] = false;
				NF_DeleteSprite(screen, GOUL[n].spr_id[screen]);
				NF_FreeSpriteGfx(screen, GOUL[n].vram_gfx[screen]);
				EnemyFreeSpriteId(screen, GOUL[n].spr_id[screen]);
				GOUL[n].spr_id[screen] = 255, GOUL[n].vram_gfx[screen] = 255;
			}
		}
	}

}



// Funcion CameraGoulShow();
void CameraGoulShow(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;
	u8 n = 0;
	u16 id = 0;


	/*
	-------------------------------------------------
		Gestion de los gouls
	-------------------------------------------------
	*/

	for (n = 0; n < ENEMY_NUM_GOUL; n ++) {
		// Calcula la posicion del sprite en la pantalla
		spr_x = (GOUL[n].pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
		spr_y = (GOUL[n].pos_y - STAGE[stage].stg_top);
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
			GOUL[n].on_screen[screen] = true;
			GOUL[n].scr_x[screen] = spr_x;
			GOUL[n].scr_y[screen] = spr_y;
			// Si no esta creado, crealo
			if (!GOUL[n].created[screen]) {
				id = EnemyGetSpriteId(screen);
				GOUL[n].spr_id[screen] = id, GOUL[n].vram_gfx[screen] = id;
				GOUL[n].created[screen] = true;
				NF_VramSpriteGfx(screen, GOUL[n].ram_gfx, GOUL[n].vram_gfx[screen], true);
				NF_CreateSprite(screen, GOUL[n].spr_id[screen], GOUL[n].vram_gfx[screen], SPRGFX[ID_GOUL].pal, (GOUL[n].scr_x[screen] - GOUL[n].spr_left), (GOUL[n].scr_y[screen] - GOUL[n].spr_up));
				NF_SpriteLayer(screen, GOUL[n].spr_id[screen], SPRITES_LAYER);
			}
			// Actualiza el sprite
			NF_MoveSprite(screen, GOUL[n].spr_id[screen], (GOUL[n].scr_x[screen] - GOUL[n].spr_left), (GOUL[n].scr_y[screen] - GOUL[n].spr_up));
			NF_SpriteFrame(screen, GOUL[n].spr_id[screen], GOUL[n].frame);
			NF_HflipSprite(screen, GOUL[n].spr_id[screen], GOUL[n].flip);
		}
	}

}



// Funcion CameraPhantomHide();
void CameraPhantomHide(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;
	u8 n = 0;


	/*
	-------------------------------------------------
		Gestion de los phantoms
	-------------------------------------------------
	*/

	for (n = 0; n < ENEMY_NUM_PHANTOM; n ++) {
		// Calcula la posicion del sprite en la pantalla
		spr_x = (PHANTOM[n].pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
		spr_y = (PHANTOM[n].pos_y - STAGE[stage].stg_top);
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
			PHANTOM[n].on_screen[screen] = false;
			PHANTOM[n].scr_x[screen] = -64;
			PHANTOM[n].scr_y[screen] = -64;
			// Destruye el sprite
			if (PHANTOM[n].created[screen]) {
				PHANTOM[n].created[screen] = false;
				NF_DeleteSprite(screen, PHANTOM[n].spr_id[screen]);
				NF_FreeSpriteGfx(screen, PHANTOM[n].vram_gfx[screen]);
				EnemyFreeSpriteId(screen, PHANTOM[n].spr_id[screen]);
				PHANTOM[n].spr_id[screen] = 255, PHANTOM[n].vram_gfx[screen] = 255;
			}
		}
	}

}



// Funcion CameraPhantomShow();
void CameraPhantomShow(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;
	u8 n = 0;
	u16 id = 0;


	/*
	-------------------------------------------------
		Gestion de los phantoms
	-------------------------------------------------
	*/

	for (n = 0; n < ENEMY_NUM_PHANTOM; n ++) {
		// Calcula la posicion del sprite en la pantalla
		spr_x = (PHANTOM[n].pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
		spr_y = (PHANTOM[n].pos_y - STAGE[stage].stg_top);
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
			PHANTOM[n].on_screen[screen] = true;
			PHANTOM[n].scr_x[screen] = spr_x;
			PHANTOM[n].scr_y[screen] = spr_y;
			// Si no esta creado, crealo
			if (!PHANTOM[n].created[screen]) {
				id = EnemyGetSpriteId(screen);
				PHANTOM[n].spr_id[screen] = id, PHANTOM[n].vram_gfx[screen] = id;
				PHANTOM[n].created[screen] = true;
				NF_VramSpriteGfx(screen, PHANTOM[n].ram_gfx, PHANTOM[n].vram_gfx[screen], true);
				NF_CreateSprite(screen, PHANTOM[n].spr_id[screen], PHANTOM[n].vram_gfx[screen], SPRGFX[ID_PHANTOM].pal, (PHANTOM[n].scr_x[screen] - PHANTOM[n].spr_left), (PHANTOM[n].scr_y[screen] - PHANTOM[n].spr_up));
				NF_SpriteLayer(screen, PHANTOM[n].spr_id[screen], SPRITES_LAYER);
			}
			// Actualiza el sprite
			NF_MoveSprite(screen, PHANTOM[n].spr_id[screen], (PHANTOM[n].scr_x[screen] - PHANTOM[n].spr_left), (PHANTOM[n].scr_y[screen] - PHANTOM[n].spr_up));
			NF_SpriteFrame(screen, PHANTOM[n].spr_id[screen], PHANTOM[n].frame);
			NF_HflipSprite(screen, PHANTOM[n].spr_id[screen], PHANTOM[n].flip);
		}
	}

}



// Funcion CameraWolfHide();
void CameraWolfHide(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;
	u8 n = 0;


	/*
	-------------------------------------------------
		Gestion de los wolfs
	-------------------------------------------------
	*/

	for (n = 0; n < ENEMY_NUM_WOLF; n ++) {
		// Calcula la posicion del sprite en la pantalla
		spr_x = (WOLF[n].pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
		spr_y = (WOLF[n].pos_y - STAGE[stage].stg_top);
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
			WOLF[n].on_screen[screen] = false;
			WOLF[n].scr_x[screen] = -64;
			WOLF[n].scr_y[screen] = -64;
			// Destruye el sprite
			if (WOLF[n].created[screen]) {
				WOLF[n].created[screen] = false;
				NF_DeleteSprite(screen, WOLF[n].spr_id[screen]);
				NF_FreeSpriteGfx(screen, WOLF[n].vram_gfx[screen]);
				EnemyFreeSpriteId(screen, WOLF[n].spr_id[screen]);
				WOLF[n].spr_id[screen] = 255, WOLF[n].vram_gfx[screen] = 255;
			}
		}
	}

}



// Funcion CameraWolfShow();
void CameraWolfShow(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;
	u8 n = 0;
	u16 id = 0;


	/*
	-------------------------------------------------
		Gestion de los wolfs
	-------------------------------------------------
	*/

	for (n = 0; n < ENEMY_NUM_WOLF; n ++) {
		// Calcula la posicion del sprite en la pantalla
		spr_x = (WOLF[n].pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
		spr_y = (WOLF[n].pos_y - STAGE[stage].stg_top);
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
			WOLF[n].on_screen[screen] = true;
			WOLF[n].scr_x[screen] = spr_x;
			WOLF[n].scr_y[screen] = spr_y;
			// Si no esta creado, crealo
			if (!WOLF[n].created[screen]) {
				id = EnemyGetSpriteId(screen);
				WOLF[n].spr_id[screen] = id, WOLF[n].vram_gfx[screen] = id;
				WOLF[n].created[screen] = true;
				NF_VramSpriteGfx(screen, WOLF[n].ram_gfx, WOLF[n].vram_gfx[screen], true);
				NF_CreateSprite(screen, WOLF[n].spr_id[screen], WOLF[n].vram_gfx[screen], SPRGFX[ID_WOLF].pal, (WOLF[n].scr_x[screen] - WOLF[n].spr_left), (WOLF[n].scr_y[screen] - WOLF[n].spr_up));
				NF_SpriteLayer(screen, WOLF[n].spr_id[screen], SPRITES_LAYER);
			}
			// Actualiza el sprite
			NF_MoveSprite(screen, WOLF[n].spr_id[screen], (WOLF[n].scr_x[screen] - WOLF[n].spr_left), (WOLF[n].scr_y[screen] - WOLF[n].spr_up));
			NF_SpriteFrame(screen, WOLF[n].spr_id[screen], WOLF[n].frame);
			NF_HflipSprite(screen, WOLF[n].spr_id[screen], WOLF[n].flip);
		}
	}

}
