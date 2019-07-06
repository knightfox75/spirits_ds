/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de colisiones
	entre Sprites

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





// Funcion CollisionsMain();
void CollisionsMain(void) {

	// Si el personaje no es inmune,
	// verifica las colisiones entre el personaje y...
	if (CHARACTER.immunity == 0) {
		CollisionCharacterEnemy();		// Enemigos
		CollisionCharacterEagle();		// Aguila
		CollisionCharacterLamp();		// Lamparas cayendo
		CollisionCharacterTrap();		// Trampas activadas
		CollisionCharacterFiretrap();	// Trampas de fuego
		CollisionCharacterCat();		// Gato
		CollisionCharacterDevil();		// Diablo
		CollisionCharacterArrow();		// Flecha
	}

	// Si se ha lanzado el hechizo...
	if (SPELL.active) {
		CollisionSpellEnemy();		// Le has dado a algun enemigo activo?
		CollisionSpellNpc();		// Le has dado a algun NPC?
	}

}



// Funcion CheckRectCollision();
bool CheckRectCollision(s32 xa1, s32 ya1, s32 xb1, s32 yb1, s32 xa2, s32 ya2, s32 xb2, s32 yb2) {

	// Calcula anchos
	s32 width1 = (xa1 - xb1);
	if (width1 < 0) width1 = -width1;
	s32 width2 = (xa2 - xb2);
	if (width2 < 0) width2 = -width2;

	// Calcula alturas
	s32 height1 = (ya1 - yb1);
	if (height1 < 0) height1 = -height1;
	s32 height2 = (ya2 - yb2);
	if (height2 < 0) height2 = -height2;

	// Variables para el calculo
	s32 small_xa, small_xb, small_ya, small_yb;
	s32 big_xa, big_xb, big_ya, big_yb;

	// Asigna anchos
	if (width1 >= width2) {
		big_xa = xa1, big_xb = xb1;
		small_xa = xa2, small_xb = xb2;
	} else {
		big_xa = xa2, big_xb = xb2;
		small_xa = xa1, small_xb = xb1;
	}

	// Asigna altos
	if (height1 >= height2) {
		big_ya = ya1, big_yb = yb1;
		small_ya = ya2, small_yb = yb2;
	} else {
		big_ya = ya2, big_yb = yb2;
		small_ya = ya1, small_yb = yb1;
	}

	// Verifica si hay colision
	bool collision = false;
	if (
		(
		((small_xa >= big_xa) && (small_xa <= big_xb))		// Rango horizontal
		||
		((small_xb >= big_xa) && (small_xb <= big_xb))
		)
		&&
		(
		((small_ya >= big_ya) && (small_ya <= big_yb))		// Rango vertical
		||
		((small_yb >= big_ya) && (small_yb <= big_yb))
		)
		) {
		// Si hay colision, devuelve verdadero
		collision = true;
	}

	// Revuelve la colision
	return collision;

}



// Funcion CollisionCharacterEnemy();
void CollisionCharacterEnemy(void) {

	// Variables
	u8 count = 0;
	u8 n = 0;
	s32 pj_xa, pj_xb, pj_ya, pj_yb;
	s32 e_xa, e_xb, e_ya, e_yb;

	// Calcula los vertices del personaje
	pj_xa = (CHARACTER.pos_x - CHARACTER.left);
	pj_xb = (CHARACTER.pos_x + CHARACTER.right);
	pj_ya = (CHARACTER.pos_y - CHARACTER.up[CHARACTER.duck]);
	pj_yb = (CHARACTER.pos_y + CHARACTER.down);

	// Colision con los Gouls
	for (n = 0; n < ENEMY_NUM_GOUL; n ++) {
		// Si estan en el mismo stage
		if (CHARACTER.stage == GOUL[n].stage) {
			// Y esta despierto
			if (GOUL[n].sleep == 0) {
				// Calcula las coordenadas
				e_xa = (GOUL[n].pos_x - GOUL[n].left);
				e_xb = (GOUL[n].pos_x + GOUL[n].right);
				e_ya = (GOUL[n].pos_y - GOUL[n].up);
				e_yb = (GOUL[n].pos_y + GOUL[n].down);
				// Si hay colision entre ellos
				if (CheckRectCollision(pj_xa, pj_ya, pj_xb, pj_yb, e_xa, e_ya, e_xb, e_yb)) {
					// Suma un punto de colision
					count ++;
				}
			}
		}
	}

	// Colision con los Phantoms
	for (n = 0; n < ENEMY_NUM_PHANTOM; n ++) {
		// Si estan en el mismo stage
		if (CHARACTER.stage == PHANTOM[n].stage) {
			// Y esta despierto
			if (PHANTOM[n].sleep == 0) {
				// Calcula las coordenadas
				e_xa = (PHANTOM[n].pos_x - PHANTOM[n].left);
				e_xb = (PHANTOM[n].pos_x + PHANTOM[n].right);
				e_ya = (PHANTOM[n].pos_y - PHANTOM[n].up);
				e_yb = (PHANTOM[n].pos_y + PHANTOM[n].down);
				// Si hay colision entre ellos
				if (CheckRectCollision(pj_xa, pj_ya, pj_xb, pj_yb, e_xa, e_ya, e_xb, e_yb)) {
					// Suma un punto de colision
					count ++;
				}
			}
		}
	}

	// Colision con los Wolfs
	for (n = 0; n < ENEMY_NUM_WOLF; n ++) {
		// Si estan en el mismo stage
		if (CHARACTER.stage == WOLF[n].stage) {
			// Y esta despierto
			if (WOLF[n].sleep == 0) {
				// Calcula las coordenadas
				e_xa = (WOLF[n].pos_x - WOLF[n].left);
				e_xb = (WOLF[n].pos_x + WOLF[n].right);
				e_ya = (WOLF[n].pos_y - WOLF[n].up);
				e_yb = (WOLF[n].pos_y + WOLF[n].down);
				// Si hay colision entre ellos
				if (CheckRectCollision(pj_xa, pj_ya, pj_xb, pj_yb, e_xa, e_ya, e_xb, e_yb)) {
					// Suma un punto de colision
					count ++;
				}
			}
		}
	}

	// Aplica el daño recibido
	if (count > 0) {
		CHARACTER.energy -= count;
		if (CHARACTER.energy < 0) CHARACTER.energy = 0;
		// Actualiza la barra de vida
		GUI.update_energy_bar = true;
		// Efecto de sonido
		if (SOUND_EFFECT[SFX_ID_DAMAGE].can_play) SOUND_EFFECT[SFX_ID_DAMAGE].timer = SOUND_EFFECT[SFX_ID_DAMAGE].delay;
	}

}



// Funcion CollisionCharacterEagle();
void CollisionCharacterEagle(void) {

	// Variables
	s32 pj_xa, pj_xb, pj_ya, pj_yb;
	s32 e_xa, e_xb, e_ya, e_yb;

	/*
	Colision con la aguila
	*/
	// Si estan en el mismo stage
	if (CHARACTER.stage == EAGLE.stage) {
		// Esta visible y en activa
		if (EAGLE.show && !EAGLE.done) {
			// Calcula los vertices del personaje
			pj_xa = (CHARACTER.pos_x - CHARACTER.left);
			pj_xb = (CHARACTER.pos_x + CHARACTER.right);
			pj_ya = (CHARACTER.pos_y - CHARACTER.up[CHARACTER.duck]);
			pj_yb = (CHARACTER.pos_y + CHARACTER.down);
			// Calcula los vertices del aguila
			e_xa = (EAGLE.pos_x - EAGLE.left);
			e_xb = (EAGLE.pos_x + EAGLE.right);
			e_ya = (EAGLE.pos_y - EAGLE.up);
			e_yb = (EAGLE.pos_y + EAGLE.down);
			// Si hay colision entre ellos
			if (CheckRectCollision(pj_xa, pj_ya, pj_xb, pj_yb, e_xa, e_ya, e_xb, e_yb)) {
				// Mata al personaje
				CHARACTER.energy = 0;
				// Actualiza la barra de vida
				GUI.update_energy_bar = true;
			}
		}
	}

}



// Funcion CollisionCharacterLamp();
void CollisionCharacterLamp(void) {

	// Variables
	u8 count = 0;
	u8 n = 0;
	s32 pj_xa, pj_xb, pj_ya, pj_yb;
	s32 e_xa, e_xb, e_ya, e_yb;

	// Calcula los vertices del personaje
	pj_xa = (CHARACTER.pos_x - CHARACTER.left);
	pj_xb = (CHARACTER.pos_x + CHARACTER.right);
	pj_ya = (CHARACTER.pos_y - CHARACTER.up[CHARACTER.duck]);
	pj_yb = (CHARACTER.pos_y + CHARACTER.down);

	// Colision con las lamparas
	for (n = 0; n < LAMP_NUM; n ++) {
		// Si esta cayendose la lampara...
		if (LAMP[n].fall) {
			// Calcula las coordenadas
			e_xa = LAMP[n].pos_x;
			e_xb = (LAMP[n].pos_x + 64);
			e_ya = LAMP[n].pos_y;
			e_yb = (LAMP[n].pos_y + 48);
			// Si hay colision entre ellos
			if (CheckRectCollision(pj_xa, pj_ya, pj_xb, pj_yb, e_xa, e_ya, e_xb, e_yb)) {
				// Suma un punto de colision
				count ++;
			}
		}
	}

	// Aplica el daño recibido
	if (count > 0) {
		// Mata al personaje
		CHARACTER.energy = 0;
		// Actualiza la barra de vida
		GUI.update_energy_bar = true;
	}

}



// Funcion CollisionCharacterTrap();
void CollisionCharacterTrap(void) {

	// Variables
	u8 count = 0;
	s32 pj_xa, pj_xb, pj_ya, pj_yb;
	s32 e_xa, e_xb, e_ya, e_yb;

	// Si hay alguna trampa activa...
	if (EVENT.active) {

		// Calcula los vertices del personaje
		pj_xa = (CHARACTER.pos_x - CHARACTER.left);
		pj_xb = (CHARACTER.pos_x + CHARACTER.right);
		pj_ya = (CHARACTER.pos_y - CHARACTER.up[CHARACTER.duck]);
		pj_yb = (CHARACTER.pos_y + CHARACTER.down);

		// Esta activa la trampa nº00 y estas en ese stage?
		if ((EVENT.id == 6) && (CHARACTER.stage == 16)) {
			// Calcula las coordenadas
			e_xa = TRAP[0].pos_x;
			e_xb = (TRAP[0].pos_x + 96);
			e_ya = TRAP[0].pos_y;
			e_yb = (TRAP[0].pos_y + 48);
			// Si hay colision entre ellos
			if (CheckRectCollision(pj_xa, pj_ya, pj_xb, pj_yb, e_xa, e_ya, e_xb, e_yb)) {
				// Suma un punto de colision
				count ++;
			}
		}

		// Esta activa la trampa nº01 y estas en ese stage?
		if ((EVENT.id == 10) && (CHARACTER.stage == 17)) {
			// Calcula las coordenadas
			e_xa = TRAP[1].pos_x;
			e_xb = (TRAP[1].pos_x + 96);
			e_ya = TRAP[1].pos_y;
			e_yb = (TRAP[1].pos_y + 48);
			// Si hay colision entre ellos
			if (CheckRectCollision(pj_xa, pj_ya, pj_xb, pj_yb, e_xa, e_ya, e_xb, e_yb)) {
				// Suma un punto de colision
				count ++;
			}
		}

	}

	// Aplica el daño recibido
	if (count > 0) {
		// Mata al personaje
		CHARACTER.energy = 0;
		// Actualiza la barra de vida
		GUI.update_energy_bar = true;
	}

}



// Funcion CollisionCharacterFiretrap();
void CollisionCharacterFiretrap(void) {

	// Variables
	u8 count = 0;
	u8 n = 0;
	s32 pj_xa, pj_xb, pj_ya, pj_yb;
	s32 e_xa, e_xb, e_ya, e_yb;

	// Calcula los vertices del personaje
	pj_xa = (CHARACTER.pos_x - CHARACTER.left);
	pj_xb = (CHARACTER.pos_x + CHARACTER.right);
	pj_ya = (CHARACTER.pos_y - CHARACTER.up[CHARACTER.duck]);
	pj_yb = (CHARACTER.pos_y + CHARACTER.down);

	// Colision con las trampas de fuego
	for (n = 0; n < FIRETRAP_NUM; n ++) {
		// Si esta en el mismo stage...
		if (CHARACTER.stage == FIRETRAP[n].stage) {
			// Calcula las coordenadas
			e_xa = FIRETRAP[n].pos_x;
			e_xb = (FIRETRAP[n].pos_x + FIRETRAP[n].size_x);
			e_ya = FIRETRAP[n].pos_y;
			e_yb = (FIRETRAP[n].pos_y + FIRETRAP[n].size_y);
			// Si hay colision entre ellos
			if (CheckRectCollision(pj_xa, pj_ya, pj_xb, pj_yb, e_xa, e_ya, e_xb, e_yb)) {
				// Suma un punto de colision
				count ++;
			}
		}
	}

	// Aplica el daño recibido
	if (count > 0) {
		CHARACTER.energy -= 2;
		if (CHARACTER.energy < 0) CHARACTER.energy = 0;
		// Actualiza la barra de vida
		GUI.update_energy_bar = true;
		// Efecto de sonido
		if (SOUND_EFFECT[SFX_ID_DAMAGE].can_play) SOUND_EFFECT[SFX_ID_DAMAGE].timer = SOUND_EFFECT[SFX_ID_DAMAGE].delay;
	}

}



// Funcion CollisionCharacterCat();
void CollisionCharacterCat(void) {

	// Variables
	s32 pj_xa, pj_xb, pj_ya, pj_yb;
	s32 e_xa, e_xb, e_ya, e_yb;

	// Si el gato esta activo
	if (CAT.activated) {

		// Calcula los vertices del personaje
		pj_xa = (CHARACTER.pos_x - CHARACTER.left);
		pj_xb = (CHARACTER.pos_x + CHARACTER.right);
		pj_ya = (CHARACTER.pos_y - CHARACTER.up[CHARACTER.duck]);
		pj_yb = (CHARACTER.pos_y + CHARACTER.down);

		// Calcula las coordenadas
		e_xa = (CAT.pos_x - CAT.left);
		e_xb = (CAT.pos_x + CAT.right);
		e_ya = (CAT.pos_y - CAT.up);
		e_yb = (CAT.pos_y + CAT.down);

		// Si hay colision entre ellos
		if (CheckRectCollision(pj_xa, pj_ya, pj_xb, pj_yb, e_xa, e_ya, e_xb, e_yb)) {
			// Aplica el daño recibido
			CHARACTER.energy -= 2;
			// Actualiza la barra de vida
			GUI.update_energy_bar = true;
			// Efecto de sonido
			if (SOUND_EFFECT[SFX_ID_DAMAGE].can_play) SOUND_EFFECT[SFX_ID_DAMAGE].timer = SOUND_EFFECT[SFX_ID_DAMAGE].delay;
		}

	}

}



// Funcion CollisionCharacterDevil();
void CollisionCharacterDevil(void) {

	// Variables
	s32 pj_xa, pj_xb, pj_ya, pj_yb;
	s32 e_xa, e_xb, e_ya, e_yb;

	// Si el diablo esta activo
	if (DEVIL.activated) {

		// Y en el frame correcto...
		if (DEVIL.frame == 3) {

			// Calcula los vertices del personaje
			pj_xa = (CHARACTER.pos_x - CHARACTER.left);
			pj_xb = (CHARACTER.pos_x + CHARACTER.right);
			pj_ya = (CHARACTER.pos_y - CHARACTER.up[CHARACTER.duck]);
			pj_yb = (CHARACTER.pos_y + CHARACTER.down);

			// Calcula las coordenadas
			e_xa = (DEVIL.pos_x - DEVIL.left);
			e_xb = (DEVIL.pos_x + DEVIL.right);
			e_ya = (DEVIL.pos_y - DEVIL.up);
			e_yb = (DEVIL.pos_y + DEVIL.down);

			// Si hay colision entre ellos
			if (CheckRectCollision(pj_xa, pj_ya, pj_xb, pj_yb, e_xa, e_ya, e_xb, e_yb)) {
				// Aplica el daño recibido
				CHARACTER.energy --;
				// Actualiza la barra de vida
				GUI.update_energy_bar = true;
				// Efecto de sonido
				if (SOUND_EFFECT[SFX_ID_DAMAGE].can_play) SOUND_EFFECT[SFX_ID_DAMAGE].timer = SOUND_EFFECT[SFX_ID_DAMAGE].delay;
			}

		}

	}

}



// Funcion CollisionCharacterArrow();
void CollisionCharacterArrow(void) {

	// Variables
	s32 pj_xa, pj_xb, pj_ya, pj_yb;
	s32 e_xa, e_xb, e_ya, e_yb;

	// Si la flecha esta siendo disparada
	if (ARROW.shot) {

		// Calcula los vertices del personaje
		pj_xa = (CHARACTER.pos_x - CHARACTER.left);
		pj_xb = (CHARACTER.pos_x + CHARACTER.right);
		pj_ya = (CHARACTER.pos_y - CHARACTER.up[CHARACTER.duck]);
		pj_yb = (CHARACTER.pos_y + CHARACTER.down);

		// Calcula las coordenadas
		e_xa = (ARROW.pos_x - ARROW.left);
		e_xb = (ARROW.pos_x + ARROW.right);
		e_ya = (ARROW.pos_y - ARROW.up);
		e_yb = (ARROW.pos_y + ARROW.down);

		// Si hay colision entre ellos
		if (CheckRectCollision(pj_xa, pj_ya, pj_xb, pj_yb, e_xa, e_ya, e_xb, e_yb)) {
			// Aplica el daño recibido
			CHARACTER.energy -= 8;
			// Actualiza la barra de vida
			GUI.update_energy_bar = true;
			// Efecto de sonido
			if (SOUND_EFFECT[SFX_ID_DAMAGE].can_play) SOUND_EFFECT[SFX_ID_DAMAGE].timer = SOUND_EFFECT[SFX_ID_DAMAGE].delay;
		}

	}

}



// Funcion CollisionSpellEnemy();
void CollisionSpellEnemy(void) {

	// Variables
	u8 count = 0;
	u8 n = 0;
	s32 spell_xa, spell_xb, spell_ya, spell_yb;
	s32 e_xa, e_xb, e_ya, e_yb;

	// Calcula los vertices del hechizo
	spell_xa = (SPELL.pos_x - SPELL.left);
	spell_xb = (SPELL.pos_x + SPELL.right);
	spell_ya = (SPELL.pos_y - SPELL.up);
	spell_yb = (SPELL.pos_y + SPELL.down);

	// Colision con los Gouls
	for (n = 0; n < ENEMY_NUM_GOUL; n ++) {
		// Si estan en el mismo stage
		if (SPELL.stage == GOUL[n].stage) {
			// Y esta despierto
			if (GOUL[n].sleep == 0) {
				// Calcula las coordenadas
				e_xa = (GOUL[n].pos_x - GOUL[n].left);
				e_xb = (GOUL[n].pos_x + GOUL[n].right);
				e_ya = (GOUL[n].pos_y - GOUL[n].up);
				e_yb = (GOUL[n].pos_y + GOUL[n].down);
				// Si hay colision entre ellos
				if (CheckRectCollision(spell_xa, spell_ya, spell_xb, spell_yb, e_xa, e_ya, e_xb, e_yb)) {
					// Suma un punto de colision
					count ++;
					// Duerme al goul
					GOUL[n].sleep = ENEMY_SLEEP;
				}
			}
		}
	}

	// Colision con los Phantoms
	for (n = 0; n < ENEMY_NUM_PHANTOM; n ++) {
		// Si estan en el mismo stage
		if (SPELL.stage == PHANTOM[n].stage) {
			// Y esta despierto
			if (PHANTOM[n].sleep == 0) {
				// Calcula las coordenadas
				e_xa = (PHANTOM[n].pos_x - PHANTOM[n].left);
				e_xb = (PHANTOM[n].pos_x + PHANTOM[n].right);
				e_ya = (PHANTOM[n].pos_y - PHANTOM[n].up);
				e_yb = (PHANTOM[n].pos_y + PHANTOM[n].down);
				// Si hay colision entre ellos
				if (CheckRectCollision(spell_xa, spell_ya, spell_xb, spell_yb, e_xa, e_ya, e_xb, e_yb)) {
					// Suma un punto de colision
					count ++;
					// Duerme al fantasma
					PHANTOM[n].sleep = ENEMY_SLEEP;
				}
			}
		}
	}

	// Colision con los Wolfs
	for (n = 0; n < ENEMY_NUM_WOLF; n ++) {
		// Si estan en el mismo stage
		if (SPELL.stage == WOLF[n].stage) {
			// Y esta despierto
			if (WOLF[n].sleep == 0) {
				// Calcula las coordenadas
				e_xa = (WOLF[n].pos_x - WOLF[n].left);
				e_xb = (WOLF[n].pos_x + WOLF[n].right);
				e_ya = (WOLF[n].pos_y - WOLF[n].up);
				e_yb = (WOLF[n].pos_y + WOLF[n].down);
				// Si hay colision entre ellos
				if (CheckRectCollision(spell_xa, spell_ya, spell_xb, spell_yb, e_xa, e_ya, e_xb, e_yb)) {
					// Suma un punto de colision
					count ++;
					// Duerme al lobo
					WOLF[n].sleep = ENEMY_SLEEP;
				}
			}
		}
	}

	// Si ha habido algun impacto, cancela el hechizo
	if (count > 0) {
		SPELL.cancel = true;
	}

}



// Funcion CollisionSpellNpc();
void CollisionSpellNpc(void) {

	// Variables
	u8 count = 0;
	s32 spell_xa, spell_xb, spell_ya, spell_yb;
	s32 e_xa, e_xb, e_ya, e_yb;

	// Calcula los vertices del hechizo
	spell_xa = (SPELL.pos_x - SPELL.left);
	spell_xb = (SPELL.pos_x + SPELL.right);
	spell_ya = (SPELL.pos_y - SPELL.up);
	spell_yb = (SPELL.pos_y + SPELL.down);

	/*
	Colision con la armadura
	*/
	// Si estan en el mismo stage
	if (SPELL.stage == ARMOR.stage) {
		// Esta visible y en activo, ademas de tener el libro de hechizos y la bola de cristal...
		if (ARMOR.show && !ARMOR.done && SPELLBOOK.done && MAGICWAND.done) {
			// Calcula las coordenadas
			e_xa = (ARMOR.pos_x - ARMOR.left);
			e_xb = (ARMOR.pos_x + ARMOR.right);
			e_ya = (ARMOR.pos_y - ARMOR.up);
			e_yb = (ARMOR.pos_y + ARMOR.down);
			// Si hay colision entre ellos
			if (CheckRectCollision(spell_xa, spell_ya, spell_xb, spell_yb, e_xa, e_ya, e_xb, e_yb)) {
				// Suma un punto de colision
				count ++;
				// Desencanta a la armadura
				ARMOR.done = true;
				// Actualiza la GUI
				if (PRINCESS.done) {
					NF_SpriteFrame(1, GUI_SPRITE_MASTERSPELL, 3);
					// Si has desencantado tambien a la princesa, cambio de BGM
					BGM.next = MOD_ANCIENT_EMPIRES;
				} else {
					NF_SpriteFrame(1, GUI_SPRITE_MASTERSPELL, 1);
				}
				// Y recupera algo de vida (8 puntos)
				CHARACTER.energy += (8 << 3);
				if (CHARACTER.energy > (40 << 3)) CHARACTER.energy = (40 << 3);
				GUI.update_energy_bar = true;
				// Cambia la subcamara al siguiente slot disponible
				SUBCAM.available[3] = false;
				while (!SUBCAM.available[SUBCAM.slot]) {
					SUBCAM.slot ++;
					if (SUBCAM.slot > 5) SUBCAM.slot = 1;
				}
				// Voz (Efecto desencantar)
				if (VOICE.can_play) {
					VOICE.id = VOICE_DISENCHANT;
					VOICE.play = true;
				}
			}
		}
	}


	/*
	Colision con la princesa
	*/
	// Si estan en el mismo stage
	if (SPELL.stage == PRINCESS.stage) {
		// Esta visible y en activo, ademas de tener el libro de hechizos y la bola de cristal...
		if (PRINCESS.show && !PRINCESS.done && SPELLBOOK.done && MAGICWAND.done) {
			// Calcula las coordenadas
			e_xa = (PRINCESS.pos_x - PRINCESS.left);
			e_xb = (PRINCESS.pos_x + PRINCESS.right);
			e_ya = (PRINCESS.pos_y - PRINCESS.up);
			e_yb = (PRINCESS.pos_y + PRINCESS.down);
			// Si hay colision entre ellos
			if (CheckRectCollision(spell_xa, spell_ya, spell_xb, spell_yb, e_xa, e_ya, e_xb, e_yb)) {
				// Suma un punto de colision
				count ++;
				// Desencanta a la princesa
				PRINCESS.done = true;
				PRINCESS.frame = 6;
				PRINCESS.frame_cnt = 0;
				// Actualiza la GUI
				if (ARMOR.done) {
					NF_SpriteFrame(1, GUI_SPRITE_MASTERSPELL, 3);
					// Si has desencantado tambien a la armadura, cambio de BGM
					BGM.next = MOD_ANCIENT_EMPIRES;
				} else {
					NF_SpriteFrame(1, GUI_SPRITE_MASTERSPELL, 2);
				}
				// Y recupera algo de vida (8 puntos)
				CHARACTER.energy += (8 << 3);
				if (CHARACTER.energy > (40 << 3)) CHARACTER.energy = (40 << 3);
				GUI.update_energy_bar = true;
				// Cambia la subcamara al siguiente slot disponible
				SUBCAM.available[4] = false;
				while (!SUBCAM.available[SUBCAM.slot]) {
					SUBCAM.slot ++;
					if (SUBCAM.slot > 5) SUBCAM.slot = 1;
				}
				// Voz (Efecto desencantar)
				if (VOICE.can_play) {
					VOICE.id = VOICE_DISENCHANT;
					VOICE.play = true;
				}
			}
		}
	}


	/*
	Colision con la aguila
	*/
	// Si estan en el mismo stage
	if (SPELL.stage == EAGLE.stage) {
		// Esta visible y en activo, ademas de tener desencatadas a la armadura y la princesa...
		if (EAGLE.show && !EAGLE.done && ARMOR.done && PRINCESS.done) {
			// Calcula las coordenadas
			e_xa = (EAGLE.pos_x - EAGLE.left);
			e_xb = (EAGLE.pos_x + EAGLE.right);
			e_ya = (EAGLE.pos_y - EAGLE.up);
			e_yb = (EAGLE.pos_y + EAGLE.down);
			// Si hay colision entre ellos
			if (CheckRectCollision(spell_xa, spell_ya, spell_xb, spell_yb, e_xa, e_ya, e_xb, e_yb)) {
				// Suma un punto de colision
				count ++;
				// Aniquila a la aguila
				EAGLE.done = true;
			}
		}
	}


	// Si ha habido algun impacto, cancela el hechizo
	if (count > 0) {
		SPELL.cancel = true;
	}

}
