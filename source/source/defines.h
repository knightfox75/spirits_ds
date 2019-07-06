#ifndef __DEFINES_H__
#define __DEFINES_H__



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

// Includes propietarios NDS
#include <nds.h>



/*
-------------------------------------------------
	Defines generales
-------------------------------------------------
*/

// Obtiene via registro la linea actual del dibujado
#define VLINE *(vu16*)0x04000006



/*
-------------------------------------------------
	Gestion de dispositivos de entrada
-------------------------------------------------
*/

// Define la estructura de lectura del KeyPad
typedef struct {
	bool up;
	bool down;
	bool left;
	bool right;
	bool a;
	bool b;
	bool x;
	bool y;
	bool l;
	bool r;
	bool start;
	bool select;
} keypad_info;

// Array para almacenar las teclas "HELD"
extern keypad_info KEYHELD;

// Array para almacenar las teclas "DOWN"
extern keypad_info KEYPRESS;

// Array para almacenar las teclas "UP"
extern keypad_info KEYUP;

// Define la estructura de lectura del Touchscreen
typedef struct {
	u16 pos_x;
	u16 pos_y;
	u16 raw_x;
	u16 raw_y;
	u16 press_a;
	u16 press_b;
	bool held;
} touchscreen_info;

// Array para almacenar la info de la pantalla tactil
extern touchscreen_info TOUCHPAD;



/*
-------------------------------------------------
	Gestion del sonido
-------------------------------------------------
*/

// Escructura de control de la musica
typedef struct {
	bool playback;	// Flag de si se esta reproduciendo
	s16 track_id;	// ID de la musica que esta cargada
	s16 volume;		// Volumen de la musica
} soundtrack_info;
extern soundtrack_info SOUNDTRACK;		// BGM que esta sonando

// Escructura de control de los sonidos
#define SFX_MAXNUM 10
typedef struct {
	u16 sfx_id;		// ID del SFX
	u16 handle;		// ID asignado al reproducir este SFX
	s16 volume;		// Volumen del SFX
	s16 freq;		// Frecuencia del SFX
} sfx_info;
extern sfx_info SFX[SFX_MAXNUM];		// Control de los SFX

// Escructura de control de la reproduccion de los efectos de sonido
#define SOUND_EFFECT_MAXNUM 6	// Numero de efectos de sonido
#define SFX_ID_TACK 0			// ID del sonido al andar (Tack)
#define SFX_ID_TICK 1			// ID del sonido al andar (Tick)
#define SFX_ID_SPELL 2			// ID del sonido de disparo de hechizo
#define SFX_ID_FALL 3			// ID del sonido de caer al suelo
#define SFX_ID_DAMAGE 4			// ID del sonido de recibir daño
#define SFX_ID_DEAD 5			// ID del sonido de muerte
typedef struct {
	bool can_play;
	s16 timer;
	s16 delay;
} sound_effect_info;
extern sound_effect_info SOUND_EFFECT[SOUND_EFFECT_MAXNUM];

// Escructura de control de la reproduccion de las voces
#define VOICE_NUM 4
#define VOICE_CRISTALLBALL 0
#define VOICE_SPELLBOOK 1
#define VOICE_MAGICWAND 2
#define VOICE_DISENCHANT 3
typedef struct {
	bool can_play;				// Se puede reproducir la voz
	bool play;					// Reproducela
	s16 timer;					// Control de duracion	
	s16 id;						// ID de voz a reproducir
	s16 length[VOICE_NUM];		// Longitud de cada voz
	s16 voice[VOICE_NUM];		// Id de voz asociada
} voice_info;
extern voice_info VOICE;

// Escructura de control de la reproduccion de la musica de fondo
typedef struct {
	s16 current;			// Track actual
	s16 next;				// Track a reproducir
	s16 volume;				// Volumen
	bool play;				// Fuerza el comando PLAY
	bool stop;				// Fuerza el comando STOP
	s16 status;				// Flag de estado
} bgm_info;
extern bgm_info BGM;



/*
-------------------------------------------------
	Datos del Archivo de guardado
-------------------------------------------------
*/

#define SAVEGAMEVERSION 20120908	// Version del savegame
#define USE_SRAM 1					// (0) No usar SRAM, (1) Usar SRAM

extern char SAVEFILEPATH[256];		// Guarda el PATH del savegame
extern bool IS_EMULATOR;			// Guarda si es la consola o un emulador

// Checksum del savedata
typedef struct {
	u32 value;			// Valor Checksum
	u32 version;
	char magic[12];		// SPIRITSDS
} checksum_info;
extern checksum_info CHECKSUM[1];	// Checksum del savedata

// Estructura de las opciones del juego
typedef struct {
	bool remake;	// Flag de si esta en modo clasico (8 bits) o remake
	u8 language;	// ID de idioma
	u8 scanlines;	// Nivel de scanlines
} gameoptions_info;
extern gameoptions_info GAMEOPTIONS[1];		// Opciones del juego



/*
-------------------------------------------------
	Gestion del curso de la partida
-------------------------------------------------
*/

typedef struct {
	u8 thread;				// Thread de ejecucion dle juego
	bool player_alive;		// El jugador esta vivo?
	s16 player_dead;		// Control de la animacion de la muerte
	bool fade_in;			// Efecto fade in
	bool fade_out;			// Efecto fade out
	s16 brightness;			// Brillo
} maingame_info;
extern maingame_info MAINGAME;

#define GAMETHREAD_PLAYGAME 0
#define GAMETHREAD_PLAYERDEAD 1
#define GAMETHREAD_GAMEOVER 2
#define GAMETHREAD_GAMEEND 3
#define GAMETHREAD_DRAGONSLAIR 4
#define GAMETHREAD_GAMEEXIT 5



/*
-------------------------------------------------
	Informacion de los graficos de los Sprites
	principales

	Personaje
	Enemigos
	Items
	NPC
-------------------------------------------------
*/


// Id's de los graficos de los sprites (RAM)
#define TOTAL_SPRITE_GFX 13
#define SPRITE_8BITS_PAL 0
#define ID_CHARACTER 0
#define ID_GOUL 1
#define ID_PHANTOM 2
#define ID_WOLF 3
#define ID_ARMOR 4
#define ID_PRINCESS 5
#define ID_BASE 6
#define ID_BALL 7
#define ID_BOOK 8
#define ID_WAND 9
#define ID_EAGLE 10
#define ID_SPELL 11
#define ID_SWITCH 12



/*
-------------------------------------------------
	Datos de los tipos de Sprite
-------------------------------------------------
*/

typedef struct {
	u16 width;		// Tamaño del grafico
	u16 height;
	u8 pal;			// Paleta
} sprgfx_info;
extern sprgfx_info SPRGFX[TOTAL_SPRITE_GFX];



/*
-------------------------------------------------
	Datos del personaje
-------------------------------------------------
*/

#define CHARACTER_START_X 64	// 64	4600	3164	3250
#define CHARACTER_START_Y 128	// 128	1432	1632	1650

#define CHARACTER_WALK_SPEED 256				// Velocidad al andar
#define CHARACTER_AIR_MAX_SPEED 1024			// Velocidad de salto
#define CHARACTER_AIR_MIN_SPEED 256
#define CHARACTER_JUMP_SIDE_SPEED 256
#define CHARACTER_JUMP_MAX_HEIGHT (56 << 8)		// Altura maxima del salto

#define CHARACTER_ANIM_STANDBY 0		// Animacion, quieto
#define CHARACTER_ANIM_WALK 1			// Animacion, andar
#define CHARACTER_ANIM_DUCK 2			// Animacion, agacharse
#define CHARACTER_ANIM_JUMP 3			// Animacion, saltar
#define CHARACTER_ANIM_FALL 4			// Animacion, caer
#define CHARACTER_ANIM_STAIRS 5			// Animacion, escaleras
#define CHARACTER_ANIM_SPELL 6			// Animacion, disparo de hechizo

#define CHARACTER_IMMUNITY 180			// Tiempo de inmunidad despues de resucitar

#define CHARACTER_SPR_ID 40				// Datos del sprite del Personaje (VRAM)
#define CHARACTER_SPR_PAL 0


typedef struct {

	// Ubicacion del Personaje
	u8 stage;			// Stage en el que estas
	s32 pos_x;			// Posicion del personaje (Centro)
	s32 pos_y;
	s32 pos_fx;			// Posicion del personaje (Fixed point) (Centro)
	s32 pos_fy;
	s32 old_x;			// Guarda la posicion anterior
	s32 old_y;
	s32 fall_y;			// Guarda la posicion Y en el momento de la caida
	s32 scr_x[2];		// Posicion del personaje en pantalla
	s32 scr_y[2];
	bool flip;			// Direccion a la que miras

	// Parametros del Sprite del personaje
	s16 spr_up;			// Distancia desde el centro al borde del Gfx (Tamaño REAL del sprite)
	s16 spr_left;
	s16 left;			// Limites del Sprite
	s16 right;
	s16 up[2];
	s16 down;
	bool on_screen[2];	// Flag de si esta visible en alguna pantalla
	bool created[2];

	// Animacion del personaje
	u8 anim;			// nº de animacion
	u8 frame;			// Frame de la animacion
	u16 frame_cnt;		// Temporizador para el cambio de frame
	bool spell;			// Esta realizando la animacion de lanzar el hechizo?

	// Control del personaje
	s32 air_speed;		// Aceleracion en el aire
	bool mov_left;		// Flags de movimiento (Direcciones en las que puedes moverte)
	bool mov_right;
	bool can_jump;		// Puede saltar?
	bool is_jump;		// Esta saltando
	bool jump_up;		// Saltando arriba
	s32 jump_height;	// Altura del salto
	s32 jump_direction;	// Direccion del salto
	bool fall;			// El personaje debe caerse
	bool force_down;	// El personaje puede descolgarse?
	bool stair_up;		// Puede moverse en la escalera?
	bool stair_down;	
	bool in_stair;		// Esta en la escalera
	u8 duck;			// Esta agachado (0 no, 1 si)

	// Vida, energia, etc
	s16 energy;			// Vida del personaje
	s16 damage;			// Calculo de daño
	s8 lives;			// Vidas del personaje
	s16 immunity;		// Invulnerable despues de resucitar
	bool show;			// Flag para el efecto inmune

} character_info;
extern character_info CHARACTER;

typedef struct {

	// Ubicacion del Personaje
	u8 stage;			// Stage en el que estas
	s32 pos_x;			// Posicion del personaje (Centro)
	s32 pos_y;
	s32 pos_fx;			// Posicion del personaje (Fixed point) (Centro)
	s32 pos_fy;
	bool flip;			// Direccion a la que miras

	// Animacion del personaje
	u8 anim;			// nº de animacion
	u8 frame;			// Frame de la animacion
	u16 frame_cnt;		// Temporizador para el cambio de frame
	bool spell;			// Esta realizando la animacion de lanzar el hechizo?

	// Control del personaje
	s32 air_speed;		// Aceleracion en el aire
	bool mov_left;		// Flags de movimiento (Direcciones en las que puedes moverte)
	bool mov_right;
	bool can_jump;		// Puede saltar?
	bool is_jump;		// Esta saltando
	bool jump_up;		// Saltando arriba
	s32 jump_height;	// Altura del salto
	s32 jump_direction;	// Direccion del salto
	bool fall;			// El personaje debe caerse
	bool force_down;	// El personaje puede descolgarse?
	bool stair_up;		// Puede moverse en la escalera?
	bool stair_down;	
	bool in_stair;		// Esta en la escalera
	u8 duck;			// Esta agachado (0 no, 1 si)

} revive_info;
extern revive_info REVIVE;



/*
-------------------------------------------------
	Datos del hechizo
-------------------------------------------------
*/

#define SPELL_SPR_ID 39				// Datos del sprite del Hechizo (VRAM)
#define SPELL_SPR_PAL 0
#define SPELL_SPEED 512				// Velocidad del hechizo

typedef struct {

	// Ubicacion del hechizo
	u8 stage;			// Stage en el que estas
	s32 pos_x;			// Posicion del hechizo (Centro)
	s32 pos_y;
	s32 pos_fx;			// Posicion del hechizo (Fixed point) (Centro)
	s32 pos_fy;
	s32 scr_x[2];		// Posicion del hechizo en pantalla
	s32 scr_y[2];
	bool flip;			// Direccion a la que miras

	// Parametros del Sprite del hechizo
	s16 spr_up;			// Distancia desde el centro al borde del Gfx (Tamaño REAL del sprite)
	s16 spr_left;
	s16 left;			// Limites del Sprite
	s16 right;
	s16 up;
	s16 down;
	bool on_screen[2];	// Flag de si esta visible en alguna pantalla
	bool created[2];

	// Animacion del hechizo
	u8 frame;			// Frame de la animacion
	u16 frame_cnt;		// Temporizador para el cambio de frame

	// Contol del hechizo
	bool active;		// Esta activo?
	bool cancel;		// Flag de desactivacion
	bool shot;			// En proceso de ser lanzado
	s16 speed;			// Velocidad y direccion del hechizo

} spell_info;
extern spell_info SPELL;





/*
-------------------------------------------------
	Datos de los ITEMS y NPC
-------------------------------------------------
*/

#define EAGLE_SPR_ID 41				// Datos del sprite del Aguila (VRAM)
#define ARMOR_SPR_ID 42				// Datos del sprite de la Armadura (VRAM)
#define PRINCESS_SPR_ID 43			// Datos del sprite de la Princesa (VRAM)
#define NPC_SPR_PAL 1				// Paleta para los NPC

#define PEDESTAL_0_SPR_ID 44		// Datos del sprite del pedestal 1 (VRAM)
#define PEDESTAL_1_SPR_ID 45		// Datos del sprite del pedestal 2 (VRAM)
#define CRISTALLBALL_SPR_ID 46		// Datos del sprite de la bola de cristal (VRAM)
#define SPELLBOOK_SPR_ID 47			// Datos del sprite del libro de hechizos (VRAM)
#define MAGICWAND_SPR_ID 48			// Datos del sprite la vara de hechizos	(VRAM)
#define ITEM_SPR_PAL 2				// Paleta para los Items

#define MAX_ITEM_POS 29				// Maximo numero de posiciones para los los Items


/*
-------------------------------------------------
	Parametros para la armadura
-------------------------------------------------
*/
#define ARMOR_WALK_SPEED 256				// Velocidad al andar
#define ARMOR_AIR_MAX_SPEED 1024			// Velocidad de salto
#define ARMOR_AIR_MIN_SPEED 256
#define ARMOR_JUMP_SIDE_SPEED 300
#define ARMOR_JUMP_MAX_HEIGHT (56 << 8)		// Altura maxima del salto
// --
#define ARMOR_ANIM_STANDBY 0		// Animacion, quieto
#define ARMOR_ANIM_WALK 1			// Animacion, andar
#define ARMOR_ANIM_JUMP 2			// Animacion, saltar
#define ARMOR_ANIM_FALL 3			// Animacion, caer
#define ARMOR_ANIM_STAIRS 4			// Animacion, escaleras

/*
-------------------------------------------------
	Parametros para la princesa
-------------------------------------------------
*/
#define PRINCESS_WALK_SPEED 256				// Velocidad al andar
#define PRINCESS_AIR_MAX_SPEED 1024			// Velocidad de salto
#define PRINCESS_AIR_MIN_SPEED 256
#define PRINCESS_JUMP_SIDE_SPEED 300
#define PRINCESS_JUMP_MAX_HEIGHT (56 << 8)		// Altura maxima del salto
// --
#define PRINCESS_ANIM_STANDBY 0			// Animacion, quieto
#define PRINCESS_ANIM_WALK 1			// Animacion, andar
#define PRINCESS_ANIM_JUMP 2			// Animacion, saltar
#define PRINCESS_ANIM_FALL 3			// Animacion, caer
#define PRINCESS_ANIM_STAIRS 4			// Animacion, escaleras

/*
-------------------------------------------------
	Parametros para la aguila
-------------------------------------------------
*/
#define EAGLE_FLY_SPEED 192			// Velocidad al volar
// --
#define EAGLE_ANIM_FLY 0			// Animacion, volar


/*
-------------------------------------------------
	Parametros de la IA
-------------------------------------------------
*/

#define AI_WALK_RIGHT 0			// IA andar a la derecha
#define AI_WALK_LEFT 1			// IA andar a la izquierda
#define AI_JUMP 2				// IA saltar
#define AI_STAIRS_DOWN 3		// IA bajar las escaleras
#define AI_STAIRS_UP 4			// IA subir las escaleras
#define AI_FALL 5				// IA, indica que estas cayendo
#define AI_STEEPS_UP_RIGHT 6	// IA, sube los escalones a la derecha
#define AI_STEEPS_UP_LEFT 7		// IA, sube los escalones a la izquierda
#define AI_STEEPS_DOWN 8		// IA, baja los escalones
#define AI_STAGE7 9				// IA, evento especial del stage 7
#define AI_MOVE_RIGHT 10		// IA Aguila, moverse a la derecha
#define AI_MOVE_LEFT 11			// IA Aguila, moverse a la derecha
#define AI_MOVE_UP 12			// IA Aguila, moverse a la derecha
#define AI_MOVE_DOWN 13			// IA Aguila, moverse a la derecha

#define AI_CAIR 0				// Colision de la IA, aire
#define AI_CWALL 1				// Colision de la IA, muro
#define AI_CHALFWALL 2			// Colision de la IA, semi-muro
#define AI_CSTEEP 3				// Colision de la IA, escalon
#define AI_CHALFSTEEP 4			// Colision de la IA, medio escalon
#define AI_CFLOOR 5				// Colision de la IA, suelo
#define AI_CRIGHTFLOOR 6		// Colision de la IA, suelo a la derecha
#define AI_CLEFTFLOOR 7			// Colision de la IA, suelo a la izquierda
#define AI_CSTAIR 8				// Colision de la IA, en la escalera

#define AI_TIMER 64					// Frames de rearme de la IA
#define AI_JUMP_HEIGHT (40 << 8)	// Altura maxima del salto al subir escalones


// Posiciones aleatorias
typedef struct {

	s32 x;			// Coordenadas
	s32 y;
	u8 stage;		// Stage

	bool npc;		// Posicion valida para un NPC?
	bool in_use;	// Posicion en uso?

} random_pos_info;

extern random_pos_info RANDOM_POS[MAX_ITEM_POS];


// Control de los items
typedef struct {

	s32 pos_x;			// Posicion del item (Esquina superior/izquierda)
	s32 pos_y;

	s32 cam_x;			// Posicion del item para la camara (referencia original)
	s32 cam_y;	

	u8 width;			// Tamaño del Sprite
	u8 height;

	u8 mov_x;			// Distancia entre el hotspot y el borde del sprite
	u8 mov_y;

	u8 stage;			// Pantalla en la que te encuentras

	bool show;			// Debe mostrarse este Item?
	bool on_screen[2];	// Flag de si esta visible en alguna pantalla
	bool created[2];

	bool done;			// El item se ha conseguido?

} item_info;

extern item_info PEDESTAL[2];
extern item_info CRISTALLBALL;
extern item_info SPELLBOOK;
extern item_info MAGICWAND;


// Control de los NPC
typedef struct {

	// Ubicacion del NPC
	u8 stage;			// Stage en el que estas
	s32 pos_x;			// Posicion del NPC (Centro)
	s32 pos_y;
	s32 old_x;			// Posicion anterior al movimiento
	s32 old_y;
	s32 pos_fx;			// Posicion del NPC (Fixed point) (Centro)
	s32 pos_fy;
	s32 scr_x[2];		// Posicion del personaje en pantalla
	s32 scr_y[2];
	bool flip;			// Direccion a la que miras

	// Variacion para el posicionamiento aleatorio
	u8 mov_y;			// Distancia entre el hotspot y el centro del sprite

	// Parametros del Sprite del NPC
	s16 spr_up;			// Distancia desde el centro al borde del Gfx (Tamaño REAL del sprite)
	s16 spr_left;
	s16 left;			// Limites del Sprite
	s16 right;
	s16 up;
	s16 down;
	bool on_screen[2];	// Flag de si esta visible en alguna pantalla
	bool created[2];

	// Animacion del NPC
	u8 anim;			// nº de animacion
	u8 frame;			// Frame de la animacion
	u16 frame_cnt;		// Temporizador para el cambio de frame

	// Control del NPC
	s32 air_speed;		// Aceleracion en el aire
	bool mov_left;		// Flags de movimiento (Direcciones en las que puedes moverte)
	bool mov_right;
	bool mov_up;
	bool mov_down;
	bool can_jump;		// Puede saltar?
	bool is_jump;		// Esta saltando
	bool jump_up;		// Saltando arriba
	s32 jump_height;	// Altura del salto
	s32 jump_direction;	// Direccion del salto
	bool fall;			// El NPC debe caerse
	bool force_down;	// El NPC puede descolgarse?
	bool stair_up;		// Puede moverse en la escalera?
	bool stair_down;	
	bool in_stair;		// Esta en la escalera

	// IA del NPC
	bool ai_up;			// Moverse arriba
	bool ai_down;		// Moverse abajo
	bool ai_right;		// Moverse a la derecha
	bool ai_left;		// Moverse a la izquierda
	bool ai_jump;		// Saltar
	bool ai_shortjump;	// Marca el salto corto
	u8 ai_command;		// Comando actual
	u8 ai_sub;			// Subcomando
	bool ai_ready;		// IA lista para un nuevo comando
	s16 ai_timer;		// Temporizador de rearme de la IA
	u8 ai_stage;		// Flag de stage para la IA
	bool ai_error;		// Flag de error en la IA

	// Datos de partida del NPC
	bool show;			// El NPC esta activo y debe mostrarse?
	bool done;			// El NPC se ha desencantado?

} npc_info;

extern npc_info ARMOR;
extern npc_info PRINCESS;
extern npc_info EAGLE;



/*
-------------------------------------------------
	Datos de los enemigos
-------------------------------------------------
*/

#define ENEMY_NUM_GOUL 6		// 6
#define ENEMY_NUM_PHANTOM 10	// 10
#define ENEMY_NUM_WOLF 4		// 4

#define ENEMY_SPR_ID 30			// FIFO de los Sprites de los enemigos
#define ENEMY_SPR_PAL 3
#define ENEMY_SPR_NUM 3

#define ENEMY_AI_RANGE 32		// Rango de la IA para dar la vuelta
#define ENEMY_AI_IGNORE 20		// Numero de pasos para que el enemigo te ignore
#define ENEMY_AI_DELAY 32		// Retardo de la IA en reaccionar

#define ENEMY_SLEEP	300			// Tiempo que estaras dormido

// Control de los enemigos
typedef struct {

	// Ubicacion del enemigo
	s32 pos_x;			// Posicion del enemigo (Centro)
	s32 pos_y;
	s32 pos_fx;			// Posicion del enemigo (Fixed point) (Centro)
	s32 pos_fy;
	s32 scr_x[2];		// Posicion del enemigo en pantalla
	s32 scr_y[2];
	bool flip;			// Direccion a la que mira
	u8 stage;			// Stage en la que se encuentra

	// Parametros del Sprite del enemigo
	u8 ram_gfx;			// Id's del grafico que usa
	u8 vram_gfx[2];
	u8 spr_id[2];
	s16 spr_up;			// Distancia desde el centro al borde del Gfx (Tamaño REAL del sprite)
	s16 spr_left;
	s16 left;			// Limites del Sprite
	s16 right;
	s16 up;
	s16 down;
	bool on_screen[2];	// Flag de si esta visible en alguna pantalla
	bool created[2];

	// Animacion del enemigo
	u8 frame;			// Frame de la animacion
	u16 frame_cnt;		// Temporizador para el cambio de frame

	// Control del enemigo
	s16 speed;			// Velocidad y direccion
	s16 sleep;			// Contador de inactividad
	s16 ignore;			// Ignorar al jugador pasado un tiempo
	s16 delay;			// Retardo al cambio de direccion 

} enemy_info;
extern enemy_info GOUL[ENEMY_NUM_GOUL];
extern enemy_info PHANTOM[ENEMY_NUM_PHANTOM];
extern enemy_info WOLF[ENEMY_NUM_WOLF];

// Gestion de Sprites de los enemigos
typedef struct {
	u8 id[ENEMY_SPR_NUM];			// Id de Sprite a usar en el FIFO
	bool in_use[ENEMY_SPR_NUM];		// Flag de Id disponible
} enemy_spr_info;
extern enemy_spr_info ENEMY_SPR[2];



/*
-------------------------------------------------
	Datos de los enemigos especiales
	(Gato, diablo arquero, dragon)
-------------------------------------------------
*/

// RAM ID de los Sprites
#define ID_CAT 13
#define ID_DEVIL 14
#define ID_ARROW 15
#define ID_DRAGONEYE 16
// VRAM ID de los Sprites
#define CAT_SPR_ID 33
#define CAT_SPR_PAL 5
#define DEVIL_SPR_ID 34
#define DEVIL_SPR_PAL 5
#define ARROW_SPR_ID 35
#define ARROW_SPR_PAL 5
#define DRAGONEYE_SPR_ID 36
#define DRAGONEYE_SPR_PAL 5
// Parametros Gato
#define CAT_WALK_SPEED 512			// Velocidad al correr
#define CAT_AIR_MAX_SPEED 1024		// Velocidad de salto
#define CAT_AIR_MIN_SPEED 256
#define CAT_MIN_TIME 1800			// Tiempo de aparicion (1800/3600)
#define CAT_RAND_TIME 3600
// Parametros Diablo
#define DEVIL_MIN_TIME 1800			// Tiempo de aparicion (1800/3600)
#define DEVIL_RAND_TIME 3600
// Parametros de la flecha
#define ARROW_MIN_SPEED 256			// Velocidad de disparo
#define ARROW_MAX_SPEED 1536

// Datos de los graficos los enemigos aleatorios
#define TOTAL_DEVIL_GFX 4
extern sprgfx_info DEVILGFX[TOTAL_DEVIL_GFX];

// Datos del gato
typedef struct {

	bool activated;			// Flag de si esta activo
	bool cancel;			// Flag de desactivacion
	s32 timer;              // Temporizador

	s32 pos_x;				// Posicion (Centro del Sprite)
	s32 pos_y;
	s32 pos_fx;
	s32 pos_fy;
	s32 scr_x[2];			// Posicion del enemigo en pantalla
	s32 scr_y[2];
	bool flip;				// Direccion a la que mira
	s16 speed;				// Velocidad
	u8 stage;				// Stage en la que se encuentra

	bool fall;				// Caida
	s32 air_speed;

	s16 spr_up;				// Distancia desde el centro al borde del Gfx (Tamaño REAL del sprite)
	s16 spr_left;
	s16 left;				// Limites del Sprite
	s16 right;
	s16 up;
	s16 down;

	u8 frame;				// Control de la animacion
	u8 frame_cnt;

	s16 counter;			// Contador de cambios de sentido

	bool on_screen[2];		// Flag de si esta visible en alguna pantalla
	bool created[2];

} cat_info;
extern cat_info CAT;

// Datos del diablo
typedef struct {

	bool activated;			// Flag de si esta activo
	s32 timer;              // Temporizador

	s32 pos_x;				// Posicion (Centro del Sprite)
	s32 pos_y;
	s32 pos_fx;
	s32 pos_fy;
	s32 scr_x[2];			// Posicion del enemigo en pantalla
	s32 scr_y[2];
	bool flip;				// Direccion a la que mira
	u8 stage;				// Stage en la que se encuentra

	s16 spr_up;				// Distancia desde el centro al borde del Gfx (Tamaño REAL del sprite)
	s16 spr_left;
	s16 left;				// Limites del Sprite
	s16 right;
	s16 up;
	s16 down;

	s8 frame;				// Control de la animacion
	u8 frame_cnt;
	u8 animation;

	bool on_screen[2];		// Flag de si esta visible en alguna pantalla
	bool created[2];

} devil_info;
extern devil_info DEVIL;

// Datos de la flecha
typedef struct {

	bool activated;			// Flag de si esta activo
	bool cancel;			// Flag de desactivacion
	bool shot;
	s16 timer;				// Tiempo de espera clavada en la pared

	s32 pos_x;				// Posicion (Centro del Sprite)
	s32 pos_y;
	s32 pos_fx;
	s32 pos_fy;
	s32 scr_x[2];			// Posicion del enemigo en pantalla
	s32 scr_y[2];
	bool flip;				// Direccion a la que mira
	s16 speed;				// Velocidad
	u8 stage;				// Stage en la que se encuentra

	s16 spr_up;				// Distancia desde el centro al borde del Gfx (Tamaño REAL del sprite)
	s16 spr_left;
	s16 left;				// Limites del Sprite
	s16 right;
	s16 up;
	s16 down;

	bool on_screen[2];		// Flag de si esta visible en alguna pantalla
	bool created[2];

} arrow_info;
extern arrow_info ARROW;

// Datos del dragon
typedef struct {

	bool on_screen[2];		// Flag de si esta visible en alguna pantalla
	bool created[2];

	s8 frame;				// Control de la animacion
	u8 frame_cnt;
	u8 animation;

	bool active;			// Evento esta activo

} dragon_info;
extern dragon_info DRAGONEYE;



/*
-------------------------------------------------
	Datos de las pantallas
-------------------------------------------------
*/

// Color de los tiles del mapa de colisiones
#define T_AIR 0			// MAGENTA
#define T_STAIR 1		// RED			
#define T_WALL 2		// GREEN
#define T_STEEP	3		// BLUE

#define T_SWITCH_0 10	// Interruptores (0 / F)
#define T_SWITCH_1 11	
#define T_SWITCH_2 12	
#define T_SWITCH_3 13	
#define T_SWITCH_4 14
#define T_SWITCH_5 15	
#define T_SWITCH_6 16	
#define T_SWITCH_7 17	
#define T_SWITCH_8 18	
#define T_SWITCH_9 19
#define T_SWITCH_A 20	
#define T_SWITCH_B 21	
#define T_SWITCH_C 22	
#define T_SWITCH_D 23	
#define T_SWITCH_E 24

#define T_OUTOFMAP 255	// Fuera del mapa


// Datos del mapa de colisiones
#define MAINMAP_SLOT 0
#define MAINMAP_WIDTH 4992
#define MAINMAP_HEIGHT 2000

// Capa destinada a los sprites
#define SPRITES_LAYER 1

// Capa para cada fondo en modo HQ
#define BG_MAIN_LAYER 1
#define BG_SUB_LAYER 2
#define BG_SCENE_LAYER 3

typedef struct {
	u32 bg_width[4];	// Tamaño del fondo (fisico)
	u32 bg_height[4];
	u8 bg_speed[4];		// Velocidad de la capa
	u32 stg_width;		// Tamaño de la pantalla
	u32 stg_height;
	s32 stg_top;		// Limites de la pantalla en el mundo
	s32 stg_bottom;
	s32 stg_left;
	s32 stg_right;
	char bg3name[16];	// Nombre del fondo que se usara como decorado de fondo
} stage_info;
extern stage_info STAGE[20];


/*
-------------------------------------------------
	Datos de las camaras
-------------------------------------------------
*/

// Control general de las camaras
typedef struct {
	u8 current_stage;	// Stage a la que enfoca la camara
	u8 new_stage;
	s32 bg_x;			// Posicion del fondo (en el stage)
	s32 cam_x;			// Posicion de la camara (en el mundo)
	s32 cam_y;
} camera_info;
extern camera_info CAMERA[2];

// Camara inferior, seguimiento de objetivos
typedef struct {
	bool available[6];		// Marcador de camara disponible
	s8 slot;				// Camara seleccionada
} subcam_info;
extern subcam_info SUBCAM;


/*
-------------------------------------------------
	Datos de la gestion de eventos
-------------------------------------------------
*/

#define EVENT_NUM 11		// Numero de eventos
#define SWITCH_NUM 11		// Numero de interruptores
#define DOOR_NUM 7			// Numero de puertas
#define HWALL_NUM 4			// Numero de muros ocultos
#define TRAP_NUM 2			// Numero de trampas
#define LAMP_NUM 6			// Numero de lamparas

#define TOTAL_DOOR_GFX 7	// Numero total de gfx de puertas
#define ID_DOOR 30			// Primer GFX de las puertas

#define TOTAL_HWALL_GFX 6	// Numero total de gfx de los muros ocultos
#define ID_HWALL 37			// Primer GFX de los muros ocultos

#define TOTAL_TRAP_GFX 1	// Numero total de gfx de las trampas
#define ID_TRAP 43			// Primer GFX de las trampas

#define TOTAL_LAMP_GFX 1	// Numero total de gfx de las lamparas
#define ID_LAMP 44			// Primer GFX de las lamparas

#define SWITCH_SPR_NUM 3	// Numero de interruptores en pantalla
#define SWITCH_SPR_ID 60	// Primer ID de sprites de interruptores
#define SWITCH_SPR_PAL 10	// y la paleta

#define DOOR_SPR_NUM 4		// Numero de sprites de puerta en pantalla
#define DOOR_SPR_ID 63		// Primer ID de sprites de puertas
#define DOOR_SPR_PAL 11		// y la paleta
#define DOOR_PARTS_NUM 4	// Numero maximo de partes de la puerta

#define HWALL_SPR_NUM 6		// Numero de sprites de muros en pantalla
#define HWALL_SPR_ID 67		// Primer ID de sprites de muros 
#define HWALL_SPR_PAL 12	// y la paleta
#define HWALL_PARTS_NUM 2	// Numero maximo de partes del muro

#define TRAP_SPR_NUM 2		// Numero de sprites de trampa en pantalla
#define TRAP_SPR_ID 30		// Primer ID de sprites de muros 
#define TRAP_SPR_PAL 13		// y la paleta
#define TRAP_PARTS_NUM 2	// Numero maximo de partes del muro

#define LAMP_SPR_ID 50		// ID de sprites de lamparas 
#define LAMP_SPR_PAL 14		// y la paleta
#define LAMP_ANIM_SPEED 3	// Velocidad de animacion de la lampara

#define DOORS_LAYER 2		// Capa de dibujado de las puertas y muros
#define TRAPS_LAYER 1		// Capa de dibujado de las trampas


// Datos de los graficos de las puertas
extern sprgfx_info DOORGFX[TOTAL_DOOR_GFX];
// Datos de los graficos de los muros ocultos
extern sprgfx_info HWALLGFX[TOTAL_HWALL_GFX];
// Datos de los graficos de las trampas
extern sprgfx_info TRAPGFX[TOTAL_TRAP_GFX];


// Gestion de eventos
typedef struct {
	bool active;			// Algun evento activo?
	bool new_event;			// Se ha producido un nuevo evento
	bool on_main_screen;	// El evento es visible en la pantalla principal
	u8 id;					// Id del evento
	s32 pos_x;				// Posicion donde se ha producido el evento
	s32 pos_y;
	u8 stage;
} event_info;
extern event_info EVENT;

// Gestion de interruptores
typedef struct {

	bool activated;		// Flag de activacion

	s32 pos_x;			// Posicion
	s32 pos_y;

	u8 ram_gfx;			// Id's del grafico que usa
	u8 vram_gfx[2];
	u8 spr_id[2];
	s16 spr_up;			// Distancia desde el centro al borde del Gfx (Tamaño REAL del sprite)
	s16 spr_left;
	bool on_screen[2];	// Flag de si esta visible en alguna pantalla
	bool created[2];

} switch_info;
extern switch_info SWITCH[SWITCH_NUM];

// Gestion de Sprites de los interruptores
typedef struct {
	u8 id[SWITCH_SPR_NUM];				// Id de Sprite a usar en el FIFO
	bool in_use[SWITCH_SPR_NUM];		// Flag de Id disponible
} switch_spr_info;
extern switch_spr_info SWITCH_SPR[2];


// Gestion de puertas
typedef struct {

	bool activated;			// Flag de activacion

	s32 pos_x;				// Posicion (Esquina superior/izquierda del primer sprite)
	s32 pos_y;
	s32 pos_fx;
	s32 pos_fy;
	s32 door_x;
	s32 door_y;
	s32 size_x;				// Tamaño de la puerta (en pixeles)
	s32 size_y;

	u8 ram_gfx[DOOR_PARTS_NUM];			// Id's del grafico que usa
	u8 vram_gfx[2][DOOR_PARTS_NUM];
	u8 spr_id[2][DOOR_PARTS_NUM];
	bool on_screen[2][DOOR_PARTS_NUM];	// Flag de si esta visible en alguna pantalla
	bool created[2][DOOR_PARTS_NUM];

} door_info;
extern door_info DOOR[DOOR_NUM];

// Gestion de Sprites de las puertas
typedef struct {
	u8 id[DOOR_SPR_NUM];				// Id de Sprite a usar en el FIFO
	bool in_use[DOOR_SPR_NUM];			// Flag de Id disponible
} door_spr_info;
extern door_spr_info DOOR_SPR[2];



// Gestion de muros
typedef struct {

	bool activated;			// Flag de activacion

	s32 pos_x;				// Posicion (Esquina superior/izquierda del primer sprite)
	s32 pos_y;
	s32 pos_fx;
	s32 pos_fy;
	s32 hwall_x;
	s32 hwall_y;
	s32 size_x;				// Tamaño de la puerta (en pixeles)
	s32 size_y;

	u8 ram_gfx[HWALL_PARTS_NUM];			// Id's del grafico que usa
	u8 vram_gfx[2][HWALL_PARTS_NUM];
	u8 spr_id[2][HWALL_PARTS_NUM];
	bool on_screen[2][HWALL_PARTS_NUM];		// Flag de si esta visible en alguna pantalla
	bool created[2][HWALL_PARTS_NUM];

} hwall_info;
extern hwall_info HWALL[HWALL_NUM];

// Gestion de Sprites de las puertas
typedef struct {
	u8 id[HWALL_SPR_NUM];				// Id de Sprite a usar en el FIFO
	bool in_use[HWALL_SPR_NUM];			// Flag de Id disponible
} hwall_spr_info;
extern hwall_spr_info HWALL_SPR[2];



// Gestion de trampas
typedef struct {

	bool activated;			// Flag de activacion

	s32 pos_x;				// Posicion (Esquina superior/izquierda del primer sprite)
	s32 pos_y;
	s32 pos_fx;
	s32 pos_fy;
	s32 trap_x;
	s32 trap_y;
	s32 size_x;				// Tamaño de la trampa (en pixeles)
	s32 size_y;

	u8 ram_gfx[TRAP_PARTS_NUM];			// Id's del grafico que usa
	u8 vram_gfx[2][TRAP_PARTS_NUM];
	u8 spr_id[2][TRAP_PARTS_NUM];
	bool on_screen[2][TRAP_PARTS_NUM];	// Flag de si esta visible en alguna pantalla
	bool created[2][TRAP_PARTS_NUM];

} trap_info;
extern trap_info TRAP[TRAP_NUM];

// Gestion de Sprites de las trampas
typedef struct {
	u8 id[TRAP_SPR_NUM];				// Id de Sprite a usar en el FIFO
	bool in_use[TRAP_SPR_NUM];			// Flag de Id disponible
} trap_spr_info;
extern trap_spr_info TRAP_SPR[2];



// Gestion de lamparas
typedef struct {

	bool activated;			// Flag de activacion
	bool fall;              // Flag de caida en curso
	s32 timer;              // Temporizador caida

	s32 pos_x;				// Posicion (Esquina superior/izquierda del primer sprite)
	s32 pos_y;
	s32 pos_fx;
	s32 pos_fy;
	s32 lamp_x;
	s32 lamp_y;
	u8 stage;

	u8 frame;				// Animacion
	u8 frame_cnt;			// Velocidad de la animacion

	bool on_screen[2];		// Flag de si esta visible en alguna pantalla
	bool created[2];

} lamp_info;
extern lamp_info LAMP[LAMP_NUM];


/*
-------------------------------------------------
	Datos de la gestion de fuego animado
-------------------------------------------------
*/

#define FIRETRAP_NUM 3			// Numero de hogueras
#define TORCH_NUM 75			// Numero de antorchas/velas

#define TOTAL_FIRETRAP_GFX 1	// Numero total de gfx de las hogueras
#define ID_FIRETRAP 60			// Primer GFX de las hogueras

#define ID_TORCH 65				// Gfx de las antorchas
#define ID_FLAME 66				// Gfx de la llama de las velas

#define FIRETRAP_SPR_ID 75		// ID de sprites de la hoguera 
#define FIRETRAP_SPR_PAL 15		// y la paleta

#define TORCH_SPR_ID 76			// ID de sprites de las antorchas (GFX)
#define FLAME_SPR_ID 77			// ID de sprite de las llamas de las velas (GFX)
#define TORCH_SPR_PAL 15		// Paletas
#define FLAME_SPR_PAL 15
#define TORCH_SPRITE 80			// Primer ID de sprite
#define TORCH_SPR_NUM 5			// Numero de antorchas en pantalla
#define TORCH_SPEED 3			// Velocidad de animacion de las llamas

#define TORCH_LAYER 2			// Capa de dibujado de las antorchas



// Gestion de las Hogueras
typedef struct {

	s32 pos_x;		// Posicion
	s32 pos_y;
	u16 size_x;		// Tamaño
	u16 size_y;
	s32 spr_x;		// Posicion del sprite
	s32 spr_y;
	u8 stage;		// Stage

	u8 frame;		// Control de la animacion
	u8 frame_cnt;

	bool on_screen[2];		// Flag de si esta visible en alguna pantalla
	bool created[2];


} firetrap_info;
extern firetrap_info FIRETRAP[FIRETRAP_NUM];



// Gestion de antorchas/velas
typedef struct {

	s32 pos_x;		// Posicion
	s32 pos_y;
	u8 stage;
	u8 type;		// 0 - Antorcha // 1 - Vela

	u8 frame;		// Animacion
	u8 frame_cnt;	

	u8 spr_id[2];		// ID de sprite asignado en VRAM
	bool on_screen[2];	// Flag de si esta visible en alguna pantalla
	bool created[2];	// Flag de creacion

} torch_info;
extern torch_info TORCH[TORCH_NUM];

// Gestion de Sprites de las antorchas/velas
typedef struct {
	u8 id[TORCH_SPR_NUM];				// Id de Sprite a usar en el FIFO
	bool in_use[TORCH_SPR_NUM];			// Flag de Id disponible
} torch_spr_info;
extern torch_spr_info TORCH_SPR[2];



/*
-------------------------------------------------
	Datos de la GUI
-------------------------------------------------
*/


#define TOTAL_GUI_GFX 8		// Numero total de gfx de la GUI
#define ID_GUI 50			// Primer GFX de la GUI

#define GUI_SPR_ID 10		// Primer ID de sprites de la GUI
#define GUI_SPR_PAL 4		// y la paleta
#define GUI_TOTAL_ITEMS 12	// Numero de items que componen la GUI

#define GUI_SPRITE_CRISTALLBALL 10		// ID de sprite de la bola de cristal
#define GUI_SPRITE_SPELLBOOK 11			// ID de sprite del libro de hechizos
#define GUI_SPRITE_MAGICWAND 12			// ID de sprite de la varita magica
#define GUI_SPRITE_MASTERSPELL 13		// ID de sprite del hechizo maestro
#define GUI_SPRITE_LIVE1 14				// ID de sprite del contador de vidas (1)
#define GUI_SPRITE_LIVE2 15				// ID de sprite del contador de vidas (2)
#define GUI_SPRITE_LIVE3 16				// ID de sprite del contador de vidas (3)
#define GUI_SPRITE_LB_RED 17			// ID de sprite de la barra de vida (rojo)
#define GUI_SPRITE_LB_YELLOW1 18		// ID de sprite de la barra de vida (amarillo)(1)
#define GUI_SPRITE_LB_YELLOW2 19		// ID de sprite de la barra de vida (amarillo)(2)
#define GUI_SPRITE_LB_GREEN1 20			// ID de sprite de la barra de vida (verde)(1)
#define GUI_SPRITE_LB_GREEN2 21			// ID de sprite de la barra de vida (verde)(2)

#define GUI_SPRITE_LAYER 1		// Capa de dibujado de la GUI

#define ID_PAUSE 90				// GFX del cartel de pausa
#define PAUSE_SPR_PAL 9			// y la paleta
#define PAUSE_SPRITE 0			// ID de sprite del cartel de pausa (+1, son dos botones)

// Datos de los graficos de la GUI
extern sprgfx_info GUIGFX[(TOTAL_GUI_GFX + 2)];

// Gestion del GUI
typedef struct {
	bool update_energy_bar;		// Flag para actualizar la barra de energia
	bool update_lives_counter;	// Flag para actualizar el contador de vidas
} gui_info;
extern gui_info GUI;




/*
-------------------------------------------------
	Datos del minimapa
-------------------------------------------------
*/

#define TOTAL_MINIMAP_GFX 4		// Numero total de gfx del Minimapa
#define ID_MINIMAP 61			// Primer GFX del Minimapa

#define MINIMAP_SPR_ID 22		// Primer ID de sprites del Minimapa
#define MINIMAP_SPR_PAL 6		// y la paleta
#define MINIMAP_TOTAL_ITEMS 7	// Numero de items que componen el Minimapa

#define MINIMAP_SPRITE_CHARACTER 22			// Sprite marca Personaje
#define MINIMAP_SPRITE_CRISTALLBALL 23		// Sprite marca Bola de cristal
#define MINIMAP_SPRITE_SPELLBOOK 24			// Sprite marca Libro de hechizos
#define MINIMAP_SPRITE_MAGICWAND 25			// Sprite marca Varita magica
#define MINIMAP_SPRITE_ARMOR 26				// Sprite marca Armadura
#define MINIMAP_SPRITE_PRINCESS 27			// Sprite marca Princesa
#define MINIMAP_SPRITE_EAGLE 28				// Sprite marca Aguila

#define MINIMAP_LAYER 2			// Capa del mapa
#define MINIMAP_FOG_LAYER 1		// Capa de la niebla de guerra del mapa

// Gestion del minimapa
typedef struct {
	bool active;		// El minimapa ha sido activado
	s32 bg_x;			// Coordenadas del mapa
	s32 bg_y;
	s16 frame;			// Control de la animacion
	s16 frame_cnt;
	u8 rambuffer;		// ID del buffer que contiene el mapa
	bool vram_update;	// El mapa debe ser actualizado en VRAM
} minimap_info;
extern minimap_info MINIMAP;


/*
-------------------------------------------------
	Control del tutorial
-------------------------------------------------
*/

// Gestion del tutorial
typedef struct {
	char* text_buffer;		// Buffer para almacenar el archivo con los textos del tutorial
	u32 text_size;			// Tamaño del archivo de texto
	u32 text_pos;			// Posicion del puntero de lectura
	char page[12][34];		// Almacena la pagina actual 12 lineas / 32 columnas + \n + seguridad
	u16 lines;				// Numero de lineas de la pagina
	u16 characters;			// Numero de letras en la linea actual
	s16 pos_x;				// Posicion del texto en pantalla
	s16 pos_y;
	s16 char_x;				// Idx del caracter a escribir
	s16 char_y;	
	bool page_active;		// Pagina en escritura
	bool eof;				// Final de archivo
} tutorial_info;
extern tutorial_info TUTORIAL;



/*
-------------------------------------------------
	Pantalla de carga
-------------------------------------------------
*/

// Gestion de la pantalla de carga
typedef struct {
	u8 frame;		// Frame al andar
	u8 timer;		// Velocidad animacion
	s32 bg_x;		// Coordenada X del fondo
} loading_info;
extern loading_info LOADING;



/*
-------------------------------------------------
	Cheats in-game
-------------------------------------------------
*/

typedef struct {
	bool enabled;
	s16 steep;
	bool map;
} cheats_info;
extern cheats_info CHEATS;



#endif