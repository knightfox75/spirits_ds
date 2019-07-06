/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de SFX

	Requiere DevkitARM
	Requiere NightFox's Lib

	Codigo por NightFox
	http://www.nightfoxandco.com
	Inicio 02 de Septiembre del 2011

	(c)2008 - 2012 NightFox & Co.

-------------------------------------------------
*/



// Includes C
#include <stdio.h>

// Includes propietarios NDS
#include <nds.h>
#include <maxmod9.h>

// Includes NightFox's Lib
#include <nf_lib.h>

//Incluye las librerias del juego
#include "includes.h"





// Funcion SoundInitSfx();
void SoundInitSfx(void) {

	// Variables
	u8 n = 0;
	
	// Inicia las estructuras
	for (n = 0; n < SOUND_EFFECT_MAXNUM; n ++) {
		SOUND_EFFECT[n].can_play = true;
		SOUND_EFFECT[n].timer = 0;
		SOUND_EFFECT[n].delay = 0;
	}

	// Excepciones
	SOUND_EFFECT[SFX_ID_FALL].can_play = false;		// Tocar el suelo

	// Parametros de duracion de los efectos
	if (GAMEOPTIONS[0].remake) {
		SOUND_EFFECT[SFX_ID_DAMAGE].delay = 30;		// Sonido del daño
	} else {
		SOUND_EFFECT[SFX_ID_DAMAGE].delay = 5;		// Sonido del daño
	}

	// Inicializacion de las voces
	if (GAMEOPTIONS[0].remake) {
		VOICE.can_play = true;
		VOICE.play = false;
		VOICE.timer = 0;
		if (GAMEOPTIONS[0].language == 0) {
			VOICE.length[VOICE_CRISTALLBALL] = 176;		// Bola de cristal
			VOICE.length[VOICE_SPELLBOOK] = 188;		// Libro de hechizos
			VOICE.length[VOICE_MAGICWAND] = 167;		// Varita magica
		} else {
			VOICE.length[VOICE_CRISTALLBALL] = 120;		// Cristall Ball
			VOICE.length[VOICE_SPELLBOOK] = 107;		// Spellbook
			VOICE.length[VOICE_MAGICWAND] = 118;		// Magic Wand
		}
		VOICE.length[VOICE_DISENCHANT] = 96;			// Desencantar
	}

}



// Funcion SoundSfxPlay8bits();
void SoundSfxPlay8bits(void) {

	// Efecto de sonido "tack" al andar
	if (SOUND_EFFECT[SFX_ID_TACK].can_play) {
		if (CHARACTER.frame == 1) {
			SOUND_EFFECT[SFX_ID_TACK].can_play = false;
			NF_PlayRawSound(SFX_ID_TACK, 127, 64, false, 0);
		}
	} else {
		if (CHARACTER.frame != 1) SOUND_EFFECT[SFX_ID_TACK].can_play = true;
	}

	// Efecto de sonido "tick" al andar
	if (SOUND_EFFECT[SFX_ID_TICK].can_play) {
		if (CHARACTER.frame == 4) {
			SOUND_EFFECT[SFX_ID_TICK].can_play = false;
			NF_PlayRawSound(SFX_ID_TICK, 127, 64, false, 0);
		}
	} else {
		if (CHARACTER.frame != 4) SOUND_EFFECT[SFX_ID_TICK].can_play = true;
	}

	// Efecto de sonido "hechizo"
	if (SOUND_EFFECT[SFX_ID_SPELL].can_play) {
		if (CHARACTER.frame == 15) {
			SOUND_EFFECT[SFX_ID_SPELL].can_play = false;
			NF_PlayRawSound(SFX_ID_SPELL, 127, 64, false, 0);
		}
	} else {
		if (CHARACTER.frame != 15) SOUND_EFFECT[SFX_ID_SPELL].can_play = true;
	}

	// Efecto de sonido "tocar el suelo"
	if (SOUND_EFFECT[SFX_ID_FALL].can_play) {
		if (CHARACTER.can_jump) {
			SOUND_EFFECT[SFX_ID_FALL].can_play = false;
			NF_PlayRawSound(SFX_ID_FALL, 127, 64, false, 0);
		}
	} else {
		if (CHARACTER.is_jump || CHARACTER.fall) SOUND_EFFECT[SFX_ID_FALL].can_play = true;
	}

	// Efecto de sonido "recibir daño"
	if (SOUND_EFFECT[SFX_ID_DAMAGE].can_play) {
		if (SOUND_EFFECT[SFX_ID_DAMAGE].timer > 0) {
			SOUND_EFFECT[SFX_ID_DAMAGE].can_play = false;
			NF_PlayRawSound(SFX_ID_DAMAGE, 127, 64, false, 0);
		}
	} else {
		SOUND_EFFECT[SFX_ID_DAMAGE].timer --;
		if (SOUND_EFFECT[SFX_ID_DAMAGE].timer == 0) SOUND_EFFECT[SFX_ID_DAMAGE].can_play = true;
	}

}



// Funcion SoundSfxPlayHq();
void SoundSfxPlayHq(void) {

	/*
	// Efecto de sonido "tack" al andar
	if (SOUND_EFFECT[SFX_ID_TACK].can_play) {
		if (CHARACTER.frame == 1) {
			SOUND_EFFECT[SFX_ID_TACK].can_play = false;
			NF_PlayRawSound(SFX_ID_TACK, 127, 64, false, 0);
		}
	} else {
		if (CHARACTER.frame != 1) SOUND_EFFECT[SFX_ID_TACK].can_play = true;
	}

	// Efecto de sonido "tick" al andar
	if (SOUND_EFFECT[SFX_ID_TICK].can_play) {
		if (CHARACTER.frame == 4) {
			SOUND_EFFECT[SFX_ID_TICK].can_play = false;
			NF_PlayRawSound(SFX_ID_TICK, 127, 64, false, 0);
		}
	} else {
		if (CHARACTER.frame != 4) SOUND_EFFECT[SFX_ID_TICK].can_play = true;
	}

	*/

	// Efecto de sonido "hechizo"
	if (SOUND_EFFECT[SFX_ID_SPELL].can_play) {
		if (CHARACTER.frame == 15) {
			SOUND_EFFECT[SFX_ID_SPELL].can_play = false;
			NF_PlayRawSound(SFX_ID_SPELL, 127, 64, false, 0);
		}
	} else {
		if (CHARACTER.frame != 15) SOUND_EFFECT[SFX_ID_SPELL].can_play = true;
	}

	/*

	// Efecto de sonido "tocar el suelo"
	if (SOUND_EFFECT[SFX_ID_FALL].can_play) {
		if (CHARACTER.can_jump) {
			SOUND_EFFECT[SFX_ID_FALL].can_play = false;
			NF_PlayRawSound(SFX_ID_FALL, 127, 64, false, 0);
		}
	} else {
		if (CHARACTER.is_jump || CHARACTER.fall) SOUND_EFFECT[SFX_ID_FALL].can_play = true;
	}

	*/

	// Efecto de sonido "recibir daño"
	if (SOUND_EFFECT[SFX_ID_DAMAGE].can_play) {
		if (SOUND_EFFECT[SFX_ID_DAMAGE].timer > 0) {
			SOUND_EFFECT[SFX_ID_DAMAGE].can_play = false;
			NF_PlayRawSound(SFX_ID_DAMAGE, 127, 64, false, 0);
		}
	} else {
		SOUND_EFFECT[SFX_ID_DAMAGE].timer --;
		if (SOUND_EFFECT[SFX_ID_DAMAGE].timer == 0) SOUND_EFFECT[SFX_ID_DAMAGE].can_play = true;
	}

}



// Funcion SoundVoicePlayback();
void SoundVoicePlayback(void) {

	// Si se puede reproducir...
	if (VOICE.can_play) {
		// Si hay orden de reproducirla
		if (VOICE.play) {
			VOICE.can_play = false;
			// Segun el idioma...
			char filename[64];
			char lang[4];
			if (GAMEOPTIONS[0].language == 0) {
				sprintf(lang, "es");
			} else {
				sprintf(lang, "en");
			}
			// Carga el archivo
			switch (VOICE.id) {
				case VOICE_CRISTALLBALL:
					sprintf(filename, "snd/raw/cristallball_%s", lang);
					NF_LoadRawSound(filename, 31, 22050, 0);
					break;
				case VOICE_SPELLBOOK:
					sprintf(filename, "snd/raw/spellbook_%s", lang);
					NF_LoadRawSound(filename , 31, 22050, 0);
					break;
				case VOICE_MAGICWAND:
					sprintf(filename, "snd/raw/magicwand_%s", lang);
					NF_LoadRawSound(filename, 31, 22050, 0);
					break;
				case VOICE_DISENCHANT:
					NF_LoadRawSound("snd/raw/disenchant", 31, 22050, 0);
					break;
			}
			// Inicia su reproduccion
			VOICE.voice[VOICE.id] = NF_PlayRawSound(31, 127, 64, false, 0);
			VOICE.timer = VOICE.length[VOICE.id];
			// Ajusta el volumen de la musica
			BgmVolume(256);
		}
	} else {
		// Si hay una reproduccion en curso...
		if (VOICE.play) {
			VOICE.timer --;
			// Si ha terminado de reproducir
			if (VOICE.timer == 0) {
				soundKill(VOICE.voice[VOICE.id]);
				NF_UnloadRawSound(31);
				VOICE.play = false;
				VOICE.can_play = true;
				if (BGM.current == BGM.next) BgmVolume(1024);
			}
		}
	}

}



// Funcion SoundSfxCleanUp();
void SoundSfxCleanUp(void) {

	/*
	-------------------------------------------------
		Elimina las voces pendientes
	-------------------------------------------------
	*/
	VOICE.play = false;
	VOICE.can_play = false;

}
