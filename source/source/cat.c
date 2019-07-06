/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de control y
	de visualizacion del gato

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





// Funcion CatMain();
void CatMain(void) {

	CatTimer();			// Temporazador de actuacion
	CatMove();			// Mueve al gato

}



// Funcion CatTimer
void CatTimer(void) {

	// Si estas inactivo y con tiempo en el contador...
	if (!CAT.activated && (CAT.timer > 0)) {
		// Actualiza el temporizador
		CAT.timer --;
		// Si has llegado a 0, activacion del evento
		if (CAT.timer == 0) {
			if (CatGetPos()) {
				// Exito en colocar al gato, activa el evento
				CAT.activated = true;
			} else {
				// Fallo, intentalo de nuevo en 5 segundos
				CAT.timer = 300;
			}
		}
	}

}



// Funcion CatGetPos();
bool CatGetPos(void) {

	// Variables
	bool result = false;				// Resultado
	u8 stage = 0;						// Stage del suceso

	s32 pos_xl, pos_xr;					// Posiciones iniciales
	s32 pos_yl, pos_yr;

	bool left = false, right = false;	// Disponibilidad de la ubicacion
	s32 cam_left, cam_right;			// Limites de la camara inferior

	s32 y = 0;			// Uso general

	// Stage del evento
	stage = GetStage(CHARACTER.pos_x, CHARACTER.pos_y);

	// Calcula las posiciones
	pos_xl = (CHARACTER.pos_x - 160);
	pos_xr = (CHARACTER.pos_x + 160);

	// Calcula si estan en rango
	if (pos_xl > (STAGE[stage].stg_left + 32)) left = true;
	if (pos_xr < (STAGE[stage].stg_right - 32)) right = true;

	// Calcula si no estan en un precipicio
	pos_yl = (STAGE[stage].stg_bottom - 4);
	pos_yr = pos_yl;
	if (left) {
		if (NF_GetTile(MAINMAP_SLOT, pos_xl, pos_yl) != T_WALL) left = false;
	}
	if (right) {
		if (NF_GetTile(MAINMAP_SLOT, pos_xr, pos_yr) != T_WALL) right = false;
	}

	// Calcula de ser validas las posiciones, las alturas de inicio
	// Izquierda
	if (left) {
		// Resetea el flag
		left = false;
		// Busca la altura valida
		for (y = STAGE[stage].stg_bottom; y > STAGE[stage].stg_top; y -= 8) {
			if (NF_GetTile(MAINMAP_SLOT, pos_xl, y) == T_AIR) {
				// Posicion valida
				left = true;
				pos_yl = (y - 16);
				y = STAGE[stage].stg_top;
			}
		}
	}
	// Derecha
	if (right) {
		// Resetea el flag
		right = false;
		// Busca la altura valida
		for (y = STAGE[stage].stg_bottom; y > STAGE[stage].stg_top; y -= 8) {
			if (NF_GetTile(MAINMAP_SLOT, pos_xr, y) == T_AIR) {
				// Posicion valida
				right = true;
				pos_yr = (y - 16);
				y = STAGE[stage].stg_top;
			}
		}
	}

	// Vigila que no este en el campo de vision de la sub-cam
	cam_left = (CAMERA[1].cam_x - 192);
	cam_right = (CAMERA[1].cam_x +  192);
	// Mira la posicion izquierda
	if (left) {
		if (
			(pos_xl >= cam_left)
			&&
			(pos_xl <= cam_right)
			&&
			(stage == CAMERA[1].current_stage)
			) {
			left = false;
		}
	}
	// Mira la posicion derecha
	if (right) {
		if (
			(pos_xr >= cam_left)
			&&
			(pos_xr <= cam_right)
			&&
			(stage == CAMERA[1].current_stage)
			) {
			right = false;
		}
	}

	// Escoge una de las posiciones
	if (left && right) {
		if ((rand() % 100) > 50) {
			left = false;
		} else {
			right = false;
		}
	}

	// Valida solo la izquierda
	if (left) {
		// Posicion
		CAT.pos_x = pos_xl, CAT.pos_fx = (pos_xl << 8);
		CAT.pos_y = pos_yl, CAT.pos_fy = (pos_yl << 8);
		// Direccion
		CAT.flip = false;
		CAT.speed = CAT_WALK_SPEED;
		// Correcto
		result = true;
	}
	// Valida solo la derecha
	if (right) {
		// Posicion
		CAT.pos_x = pos_xr, CAT.pos_fx = (pos_xr << 8);
		CAT.pos_y = pos_yr, CAT.pos_fy = (pos_yr << 8);
		// Direccion
		CAT.flip = true;
		CAT.speed = -CAT_WALK_SPEED;
		// Correcto
		result = true;
	}
	// Inicializa parametros adicionales
	if (result) {
		CAT.frame = 0, CAT.frame_cnt = 0;
		CAT.fall = false; CAT.air_speed = 0;
		CAT.counter = 0;
	}

	// Devuelve el resultado
	return result;

}



// Funcion CatMove();
void CatMove(void) {

	// Si el gato esta activo
	if (CAT.activated) {
		CatFall();					// El gato se cae?
		if (!CAT.fall) {
			if (CAT.counter > 4) {
				CatVanish();	// El gato desaparece
			} else {
				CatWalk();		// Si no se cae y no desaparece, corretea
			}
		}
		CatAdjustPosition();		// Ajusta la posicion del gato
	}

}



// Funcion CatWalk();
void CatWalk(void) {

	// Variables
	s32 dist_x = 0, dist_y = 0;

	// Animacion del gato corriendo
	CAT.frame_cnt ++;
	if (CAT.frame_cnt > 6) {
		CAT.frame_cnt = 0;
		CAT.frame ++;
		if (CAT.frame > 2) CAT.frame = 0;
	}

	// Mueve al gato
	CAT.pos_fx += CAT.speed;

	// Limites de desplazamiento
	if (CAT.flip) {
		if (CatCheckLeft(4) == T_WALL) {
			CAT.counter ++;
			if (CAT.counter > 4) {
				CAT.frame = 3;
				CAT.frame_cnt = 0;
			} else {
				CAT.speed = -CAT.speed;
				CAT.flip = false;
			}
		}
	} else {
		if (CatCheckRight(4) == T_WALL) {
			CAT.counter ++;
			if (CAT.counter > 4) {
				CAT.frame = 3;
				CAT.frame_cnt = 0;
			} else {
				CAT.speed = -CAT.speed;
				CAT.flip = true;
			}
		}
	}

	// Calcula si el gato esta fuera del campo de accion y debe ser desactivado
	dist_x = (CHARACTER.pos_x - CAT.pos_x);
	if (dist_x < 0) dist_x = -dist_x;
	dist_y = (CHARACTER.pos_y - CAT.pos_y);
	if (dist_y < 0) dist_y = -dist_y;
	if (((dist_x > 192) || (dist_y > 128)) && !CAT.on_screen[0] && !CAT.on_screen[1]) {
		CAT.cancel = true;
		CAT.timer = ((rand() % CAT_RAND_TIME) + CAT_MIN_TIME);
	}

}



// Funcion CatVanish();
void CatVanish(void) {

	// Animacion del efecto
	CAT.frame_cnt ++;
	if (CAT.frame_cnt > 5) {
		CAT.frame_cnt = 0;
		// Fin del efecto?
		if (CAT.frame > 3) {
			CAT.frame = 3;
			// Desactiva el gato y actualiza el contador
			CAT.cancel = true;
			CAT.timer = ((rand() % CAT_RAND_TIME) + CAT_MIN_TIME);
		}
		// Siguiente frame
		CAT.frame ++;
	}

}



// Funcion CatFall();
void CatFall(void) {

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
	t_down = CatCheckDown(1);

	// Calcula si te vas a caer
	if (t_down == T_AIR) {
		// Se va a caer
		CAT.fall = true;
		// Frame de la caida
		CAT.frame = 2;
		// Aceleracion inicial de la caida
		if (CAT.air_speed == 0) {
			CAT.air_speed = CAT_AIR_MIN_SPEED;
		}
	} else {
		CAT.fall = false;
	}


	/*
	-------------------------------------------------
		Aplica las acciones
	-------------------------------------------------
	*/

	// el gato se cae
	if (CAT.fall) {
		// Nueva posicion
		CAT.pos_fy += CAT.air_speed;
		// Calcula si te sales de los limites...
		t_down = CatCheckDown(1);
		if ((t_down == T_WALL) || (t_down == T_STEEP)) {
			// Si encuentras un muro
			if (t_down == T_WALL) {
				// Deten la caida
				CAT.fall = false;
				CAT.air_speed = 0;
				// Ajusta el gato al nivel del suelo/escalon
				t_inside = CatCheckDown(0);
				while (t_inside == T_WALL) {
					// Ajusta la posicion
					CAT.pos_fy -= 64;
					// Verifica de nuevo
					t_inside = CatCheckDown(0);
				}
			}
			// Si encuentras un escalon
			if (t_down == T_STEEP) {
				// Deten la caida
				CAT.fall = false;
				CAT.air_speed = 0;
				// Ajusta el gato al nivel del suelo/escalon
				t_inside = CatCheckDown(0);
				while (t_inside == T_STEEP) {
					// Ajusta la posicion
					CAT.pos_fy -= 64;
					// Verifica de nuevo
					t_inside = CatCheckDown(0);
				}
			}
		} else {
			// Aceleracion de la caida
			if (CAT.air_speed < CAT_AIR_MAX_SPEED) {
				CAT.air_speed += (CAT.air_speed >> 4);
				if (CAT.air_speed > CAT_AIR_MAX_SPEED) CAT.air_speed = CAT_AIR_MAX_SPEED;
			}
		}
	}

}



// CatAdjustPosition();
void CatAdjustPosition(void) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	u16 t_left = T_AIR, t_right = T_AIR, t_down = T_AIR;	// Almacena los tiles


	/*
	-------------------------------------------------
		Ajusta el gato a derecha e izquierda
	-------------------------------------------------
	*/

	// Ajusta el limite derecho
	t_right = CatCheckRight(0);
	while (t_right == T_WALL) {
		CAT.pos_fx -= 64;
		t_right = CatCheckRight(0);
	}

	// Ajusta el limite izquierdo
	t_left = CatCheckLeft(0);
	while (t_left == T_WALL) {
		CAT.pos_fx += 64;
		t_left = CatCheckLeft(0);
	}


	/*
	-------------------------------------------------
		Ajusta el nivel del suelo del gato
	-------------------------------------------------
	*/
	t_down = CatCheckDown(0);
	while (t_down == T_WALL) {
		CAT.pos_fy -= 64;
		t_down = CatCheckDown(0);
	}

	/*
	-------------------------------------------------
		Actualiza las coordenadas
	-------------------------------------------------
	*/
	CAT.pos_x = (CAT.pos_fx >> 8);
	CAT.pos_y = (CAT.pos_fy >> 8);
	
}



// Funcion CatCheckRight();
u16 CatCheckRight(s8 add) {

	// Variables
	s32 x, y;
	s32 fx, fy;
	s32 start, end;
	s16 tile = 0;
	s16 result = T_AIR;

	// Variables de posicion
	fx = (CAT.pos_fx >> 8);
	fy = (CAT.pos_fy >> 8);

	// Calcula el rango de tiles a analizar
	x = (fx + CAT.right + add);
	start = (fy - CAT.up);
	end = (fy + CAT.down);

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



// Funcion CatCheckLeft();
u16 CatCheckLeft(s8 add) {

	// Variables
	s32 x, y;
	s32 fx, fy;
	s32 start, end;
	s16 tile = 0;
	s16 result = T_AIR;

	// Variables de posicion
	fx = (CAT.pos_fx >> 8);
	fy = (CAT.pos_fy >> 8);

	// Calcula el rango de tiles a analizar
	x = (fx - CAT.left - add);
	start = (fy - CAT.up);
	end = (fy + CAT.down);

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



// Funcion CatCheckDown();
u16 CatCheckDown(s8 add) {

	// Variables
	s32 x, y;
	s32 fx, fy;
	s32 start, end;
	s16 tile = 0;
	s16 result = T_AIR;
	s16 air = 0, stair = 0;

	// Variables de posicion
	fx = (CAT.pos_fx >> 8);
	fy = (CAT.pos_fy >> 8);

	// Calcula el rango de tiles a analizar
	y = (fy + CAT.down + add);
	start = (fx - CAT.left);
	end = (fx + CAT.right);

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



// Funcion CatCamHide();
void CatCamHide(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;


	/*
	-------------------------------------------------
		Gestion de las visibilidad de
		el Gato
	-------------------------------------------------
	*/

	// Calcula la posicion del sprite en la pantalla
	spr_x = (CAT.pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
	spr_y = (CAT.pos_y - STAGE[stage].stg_top);
	// Calcula si esta en pantalla
	if (
		(spr_x < -32)
		||
		(spr_x > 287)
		||
		(spr_y < -16)
		||
		(spr_y > 207)
		||
		!CAT.activated
		) {
		// No lo esta
		CAT.on_screen[screen] = false;
		CAT.scr_x[screen] = -64;
		CAT.scr_y[screen] = -64;
		// Destruye el sprite
		if (CAT.created[screen]) {
			CAT.created[screen] = false;
			NF_DeleteSprite(screen, CAT_SPR_ID);
			NF_FreeSpriteGfx(screen, CAT_SPR_ID);
		}
	}

}



// Funcion CatCamShow();
void CatCamShow(u8 screen, u8 stage) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s32 spr_x, spr_y;


	/*
	-------------------------------------------------
		Gestion de las visibilidad de
		el Gato
	-------------------------------------------------
	*/

	// Calcula la posicion del sprite en la pantalla
	spr_x = (CAT.pos_x - STAGE[stage].stg_left - CAMERA[screen].bg_x);
	spr_y = (CAT.pos_y - STAGE[stage].stg_top);
	// Calcula si esta en pantalla
	if (
		(spr_x >= -32)
		&&
		(spr_x <= 287)
		&&
		(spr_y >= -16)
		&&
		(spr_y <= 207)
		&&
		CAT.activated
		) {
		// Esta en pantalla
		CAT.on_screen[screen] = true;
		CAT.scr_x[screen] = spr_x;
		CAT.scr_y[screen] = spr_y;
		// Si no esta creado, crealo
		if (!CAT.created[screen]) {
			CAT.created[screen] = true;
			NF_VramSpriteGfx(screen, ID_CAT, CAT_SPR_ID, true);
			NF_CreateSprite(screen, CAT_SPR_ID, CAT_SPR_ID, CAT_SPR_PAL, spr_x, spr_y);
			NF_SpriteLayer(screen, CAT_SPR_ID, SPRITES_LAYER);
		}
		// Actualiza el sprite
		NF_MoveSprite(screen, CAT_SPR_ID, (spr_x - CAT.spr_left), (spr_y - CAT.spr_up));
		NF_SpriteFrame(screen, CAT_SPR_ID, CAT.frame);
		NF_HflipSprite(screen, CAT_SPR_ID, CAT.flip);
	}

}
