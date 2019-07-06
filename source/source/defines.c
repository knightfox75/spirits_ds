/*
-------------------------------------------------

	Spirits DS

	Archivo de definiciones

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



/*
-------------------------------------------------
	Gestion de dispositivos de entrada
-------------------------------------------------
*/

// Array para almacenar las teclas "HELD"
keypad_info KEYHELD;

// Array para almacenar las teclas "DOWN"
keypad_info KEYPRESS;

// Array para almacenar las teclas "UP"
keypad_info KEYUP;

// Array para almacenar la info de la pantalla tactil
touchscreen_info TOUCHPAD;



/*
-------------------------------------------------
	Gestion del sonido
-------------------------------------------------
*/

// Escructura de control de la musica
soundtrack_info SOUNDTRACK;		// BGM que esta sonando

// Escructura de control de los sonidos
sfx_info SFX[SFX_MAXNUM];		// Control de los SFX

// Escructura de control de la reproduccion de los efectos de sonido
sound_effect_info SOUND_EFFECT[SOUND_EFFECT_MAXNUM];

// Escructura de control de la reproduccion de las voces
voice_info VOICE;

// Escructura de control de la reproduccion de la musica de fondo
bgm_info BGM;



/*
-------------------------------------------------
	Datos del Archivo de guardado
-------------------------------------------------
*/

char SAVEFILEPATH[256];		// Guarda el PATH del savegame
bool IS_EMULATOR;			// Guarda si es la consola o un emulador

// Checksum del savedata
checksum_info CHECKSUM[1];				// Checksum del savedata

// Estructura de las opciones del juego
gameoptions_info GAMEOPTIONS[1];		// Opciones del juego



/*
-------------------------------------------------
	Gestion del curso de la partida
-------------------------------------------------
*/

maingame_info MAINGAME;



/*
-------------------------------------------------
	Datos de los tipos de Sprite
-------------------------------------------------
*/

sprgfx_info SPRGFX[TOTAL_SPRITE_GFX];



/*
-------------------------------------------------
	Datos del personaje
-------------------------------------------------
*/

character_info CHARACTER;
revive_info REVIVE;



/*
-------------------------------------------------
	Datos del hechizo
-------------------------------------------------
*/

spell_info SPELL;



/*
-------------------------------------------------
	Datos de los ITEMS y NPC
-------------------------------------------------
*/

// Posiciones aleatorias
random_pos_info RANDOM_POS[MAX_ITEM_POS];

// Control de los items
item_info PEDESTAL[2];
item_info CRISTALLBALL;
item_info SPELLBOOK;
item_info MAGICWAND;

// Control de los NPC
npc_info ARMOR;
npc_info PRINCESS;
npc_info EAGLE;



/*
-------------------------------------------------
	Datos de los enemigos
-------------------------------------------------
*/

enemy_info GOUL[ENEMY_NUM_GOUL];
enemy_info PHANTOM[ENEMY_NUM_PHANTOM];
enemy_info WOLF[ENEMY_NUM_WOLF];
enemy_spr_info ENEMY_SPR[2];


/*
-------------------------------------------------
	Datos de los enemigos especiales
	(Gato, diablo arquero, dragon)
-------------------------------------------------
*/

// Datos de los graficos los enemigos aleatorios
sprgfx_info DEVILGFX[TOTAL_DEVIL_GFX];

// Datos de los sprites
cat_info CAT;
devil_info DEVIL;
arrow_info ARROW;
dragon_info DRAGONEYE;



/*
-------------------------------------------------
	Datos de las pantallas
-------------------------------------------------
*/

stage_info STAGE[20];


/*
-------------------------------------------------
	Datos de las camaras
-------------------------------------------------
*/

// Control general de las camaras
camera_info CAMERA[2];

// Camara inferior, seguimiento de objetivos
subcam_info SUBCAM;



/*
-------------------------------------------------
	Datos de la gestion de eventos
-------------------------------------------------
*/

// Datos de los graficos de las puertas
sprgfx_info DOORGFX[TOTAL_DOOR_GFX];

// Datos de los graficos de los muros ocultos
sprgfx_info HWALLGFX[TOTAL_HWALL_GFX];

// Datos de los graficos de las trampas
sprgfx_info TRAPGFX[TOTAL_TRAP_GFX];


// Gestion de eventos
event_info EVENT;

// Gestion de interruptores
switch_info SWITCH[SWITCH_NUM];

// Gestion de Sprites de los interruptores
switch_spr_info SWITCH_SPR[2];

// Gestion de las puertas
door_info DOOR[DOOR_NUM];

// Gestion de Sprites de las puertas
door_spr_info DOOR_SPR[2];

// Gestion de muros ocultos
hwall_info HWALL[HWALL_NUM];

// Gestion de Sprites de muros ocultos
hwall_spr_info HWALL_SPR[2];

// Gestion de trampas
trap_info TRAP[TRAP_NUM];

// Gestion de Sprites de las trampas
trap_spr_info TRAP_SPR[2];

// Gestion de lamparas
lamp_info LAMP[LAMP_NUM];



/*
-------------------------------------------------
	Datos de la gestion de fuego animado
-------------------------------------------------
*/

firetrap_info FIRETRAP[FIRETRAP_NUM];
torch_info TORCH[TORCH_NUM];
torch_spr_info TORCH_SPR[2];



/*
-------------------------------------------------
	Datos de la GUI
-------------------------------------------------
*/

// Datos de los graficos de la GUI
sprgfx_info GUIGFX[(TOTAL_GUI_GFX + 2)];

// Gestion del GUI
gui_info GUI;



/*
-------------------------------------------------
	Datos del minimapa
-------------------------------------------------
*/

// Gestion del minimapa
minimap_info MINIMAP;



/*
-------------------------------------------------
	Control del tutorial
-------------------------------------------------
*/

// Gestion del tutorial
tutorial_info TUTORIAL;



/*
-------------------------------------------------
	Pantalla de carga
-------------------------------------------------
*/

// Gestion de la pantalla de carga
loading_info LOADING;



/*
-------------------------------------------------
	Cheats in-game
-------------------------------------------------
*/

cheats_info CHEATS;