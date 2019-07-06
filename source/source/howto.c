/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones del manual

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





// Funcion HowTo();
void HowTo(void) {

	/*
	-------------------------------------------------
		Inicializaciones
	-------------------------------------------------
	*/

	// Resetealo todo
	ResetAll();

	// Variables
	bool loop = true;			// Control del bucle
	u16 timer = 0;				// Temporizador
	u16 counter = 0;
	bool get_page = false;		// Flag optencion nueva pagina
	u16 thread = 0;				// Thread de ejecucion (35)
	bool next_thread = false;	// Siguiente thread
	bool flash = false;			// Muestra el Icono de "Pulsa A"
	bool key_a = false;			// Teclas de control
	bool key_start = false;
	u16 camera = 0;
	u8 screen = 3;				// Pantalla que afecta al fade (por defecto, ambas pantallas)
	bool icon_state = false;	// Control ICONO A
	s16 icon_cnt = 0;


	/*
	-------------------------------------------------
		Inicializaciones del HowTo
	-------------------------------------------------
	*/

	// Carga los archivos
	HowToLoad();

	// Inicializa la simulacion
	HowToInit();


	/*
	-------------------------------------------------
		Nucleo
	-------------------------------------------------
	*/

	while (loop) {

		// Lee el teclado
		ReadKeypad();
		key_a = KEYPRESS.a;
		key_start = KEYPRESS.start;
		HowToKeypadOverride();

		// Reset de variables
		flash = false;
		camera = 0;

		/*
		-------------------------------------------------
			Procesos del Tutorial
		-------------------------------------------------
		*/

		switch (thread) {

			// Inicio del tutorial - Espera al final del fade-in y pide la pagina de texto.
			case 0:
				if (!MAINGAME.fade_in) {
					get_page = true;
					next_thread = true;
				}
				break;

			// Espera a que se pulse A despues de mostrar el texto.
			// case 1:


			/*
			-------------------------------------------------
				Tutorial "Andar"
			-------------------------------------------------
			*/

			// Tutorial "Moverse". Anda a la derecha.
			case 2:
				if (CHARACTER.pos_x <= 688) {
					KEYHELD.right = true;
				} else {
					next_thread = true;
				}
				break;

			// Tutorial "Moverse". Anda a la Izquierda.
			case 3:
				if (CHARACTER.pos_x >= 624) {
					KEYHELD.left = true;
				} else {
					KEYHELD.right = true;
					next_thread = true;
				}
				break;

			// Espera a que se pulse A despues de esta parte del tutorial.
			// case 4:


			/*
			-------------------------------------------------
				Tutorial "Saltar"
			-------------------------------------------------
			*/

			// Saltar
			case 5:
				KEYPRESS.b = true;
				KEYHELD.b = true;
				next_thread = true;
				break;

			// Espera a que finalice el salto
			case 6:
				if (CHARACTER.can_jump) {
					next_thread = true;
				} else {
					KEYHELD.b = true;
				}
				break;

			// Salta a la derecha
			case 7:
				KEYHELD.right = true;
				KEYPRESS.b = true;
				KEYHELD.b = true;
				next_thread = true;
				break;

			// Espera a que finalice el salto
			case 8:
				if (CHARACTER.can_jump) {
					next_thread = true;
				} else {
					KEYHELD.b = true;
				}
				break;

			// Encarate a la izquierda
			case 9:
				KEYHELD.left = true;
				next_thread = true;
				break;

			// Salta a la izquierda
			case 10:
				KEYHELD.left = true;
				KEYPRESS.b = true;
				KEYHELD.b = true;
				next_thread = true;
				break;

			// Espera a que finalice el salto
			case 11:
				if (CHARACTER.can_jump) {
					next_thread = true;
				} else {
					KEYHELD.b = true;
				}
				break;

			// Espera a que se pulse A despues de esta parte del tutorial.
			// case 12:


			/*
			-------------------------------------------------
				Tutorial "Agacharse"
			-------------------------------------------------
			*/

			// Agacharse (Preparalo)
			case 13:
				timer = 0;
				next_thread = true;
				break;

			// Espera
			case 14:
				timer ++;
				if (timer >= 15) {
					timer = 0;
					next_thread = true;
				}
				break;

			// Agachate 2 segundos
			case 15:
				timer ++;
				KEYHELD.down = true;
				if (timer >= 60) {
					timer = 0;
					next_thread = true;
				}
				break;

			// Espera 1 segundo
			case 16:
				timer ++;
				if (timer >= 15) {
					timer = 0;
					next_thread = true;
				}
				break;

			// Espera a que se pulse A despues de esta parte del tutorial.
			// case 17:


			/*
			-------------------------------------------------
				Tutorial "Subir y bajar escaleras"
			-------------------------------------------------
			*/

			// Anda hasta las escaleras
			case 18:
				if (CHARACTER.pos_x >= 536) {
					KEYHELD.left = true;
				} else {
					next_thread = true;
				}
				break;

			// Baja las escaleras
			case 19:
				if (CHARACTER.stair_down) {
					KEYHELD.down = true;
				} else {
					next_thread = true;
				}
				break;

			// Sal de las escaleras
			case 20:
				if (CHARACTER.pos_x <= 576) {
					KEYHELD.right = true;
				} else {
					KEYHELD.left = true;
					next_thread = true;
				}
				break;

			// Salta hasta las escaleras
			case 21:
				KEYHELD.left = true;
				KEYPRESS.b = true;
				KEYHELD.b = true;
				next_thread = true;
				break;

			// Sigue saltando hasta alcanzar la escalera
			case 22:
				if (CHARACTER.pos_x >= 536) {
					KEYHELD.b = true;
				} else {
					KEYHELD.up = true;
					next_thread = true;
				}
				break;

			// Espera a que se pulse A para el fade out
			case 23:
				if (key_a && !TUTORIAL.page_active) {
					MAINGAME.brightness = 0;
					MAINGAME.fade_out = true;
					screen = 2;
					next_thread = true;
				}
				if (!TUTORIAL.page_active) flash = true;
				break;

			/*
			-------------------------------------------------
				Cambio de seccion del tutorial
			-------------------------------------------------
			*/

			// Espera a que termine el fade out
			case 24:
				if (!MAINGAME.fade_out) {
					CHARACTER.pos_x = 4304;
					CHARACTER.pos_fx = (CHARACTER.pos_x << 8);
					CHARACTER.pos_y = 1455;
					CHARACTER.pos_fy = (CHARACTER.pos_y << 8);
					next_thread = true;
				}
				break;

			// Fade in
			case 25:
				MAINGAME.brightness = 0;
				MAINGAME.fade_in = true;
				next_thread = true;
				break;

			// Espera a que termine el fade in
			case 26:
				if (!MAINGAME.fade_in) {
					get_page = true;
					next_thread = true;
				}
				break;


			/*
			-------------------------------------------------
				Salta para activar palancas
			-------------------------------------------------
			*/

			// Salta para activar la palanca
			case 27:
				KEYPRESS.b = true;
				KEYHELD.b = true;
				next_thread = true;
				break;

			// Espera a que termine el salto
			case 28:
				if (!CHARACTER.can_jump) {
					KEYHELD.b = true;
				} else {
					KEYHELD.right = true;
					next_thread = true;
				}
				break;

			// Anda hasta el borde de el pasadizo
			case 29:
				if (CHARACTER.pos_x <= 4368) {
					KEYHELD.right = true;
				} else {
					next_thread = true;
				}
				break;

			// Espera a que se pulse A despues de esta parte del tutorial.
			// case 30:


			/*
			-------------------------------------------------
				Disparo de hechizos
			-------------------------------------------------
			*/

			// Disparo de hechizo
			case 31:
				KEYPRESS.y = true;
				next_thread = true;
				break;

			// Espera a que termine el disparo
			case 32:
				if (!SPELL.active) next_thread = true;
				break;

			// Espera a que se pulse A despues de esta parte del tutorial.
			// Carga parte del texto.
			// case 33:

			// Espera a que se pulse A para el fade out
			case 34:
				if (key_a && !TUTORIAL.page_active) {
					MAINGAME.brightness = 0;
					MAINGAME.fade_out = true;
					screen = 2;
					next_thread = true;
				}
				if (!TUTORIAL.page_active) flash = true;
				break;


			/*
			-------------------------------------------------
				Cambio de seccion del tutorial
			-------------------------------------------------
			*/

			// Espera a que termine el fade out
			case 35:
				if (!MAINGAME.fade_out) {
					CHARACTER.pos_x = (CRISTALLBALL.cam_x - 32);
					CHARACTER.pos_fx = (CHARACTER.pos_x << 8);
					CHARACTER.pos_y = (CRISTALLBALL.cam_y - 32);
					CHARACTER.pos_fy = (CHARACTER.pos_y << 8);
					next_thread = true;
				}
				break;

			// Fade in
			case 36:
				MAINGAME.brightness = 0;
				MAINGAME.fade_in = true;
				next_thread = true;
				break;

			// Espera a que termine el fade in
			case 37:
				if (!MAINGAME.fade_in) {
					get_page = true;
					next_thread = true;
				}
				break;


			/*
			-------------------------------------------------
				Coger objetos. La bola.
			-------------------------------------------------
			*/

			// Espera a que se pulse A despues de esta parte del tutorial.
			// Carga parte del texto.
			// case 38:

			// Anda hasta la bola
			case 39:
				if (CHARACTER.pos_x <= CRISTALLBALL.cam_x) {
					KEYHELD.right = true;
				} else {
					next_thread = true;
				}
				break;

			// Coge la bola
			case 40:
				KEYPRESS.a = true;
				next_thread = true;
				timer = 0;
				counter = 1;
				break;

			// Espera a que se pulse A despues de esta parte del tutorial.
			// Carga parte del texto.
			// case 41:


			/*
			-------------------------------------------------
				Cambio de objetivo
			-------------------------------------------------
			*/

			// Muestra todos los objetivos
			case 42:
				timer ++;
				if (timer >= 60) {
					timer = 0;
					counter ++;
					if (counter == 6) {
						counter = 0;
						next_thread = true;
					}
				}
				camera = counter;
				break;

			// Espera a que se pulse A despues de esta parte del tutorial.
			// Carga parte del texto.
			// case 43:


			/*
			-------------------------------------------------
				Obtener libro y varita
			-------------------------------------------------
			*/

			// Colocate donde este el libro
			case 44:
				CHARACTER.pos_x = (SPELLBOOK.cam_x - 32);
				CHARACTER.pos_fx = (CHARACTER.pos_x << 8);
				CHARACTER.pos_y = (SPELLBOOK.cam_y - 32);
				CHARACTER.pos_fy = (CHARACTER.pos_y << 8);
				next_thread = true;
			break;

			// Anda hasta el libro
			case 45:
				if (CHARACTER.pos_x <= SPELLBOOK.cam_x) {
					KEYHELD.right = true;
				} else {
					next_thread = true;
				}
				break;

			// Coge el libro
			case 46:
				KEYPRESS.a = true;
				next_thread = true;
				timer = 0;
				break;

			// Espera a que termine la voz
			case 47:
				timer ++;
				if (timer >= 188) next_thread = true;
				break;

			// Colocate donde este el libro
			case 48:
				CHARACTER.pos_x = (MAGICWAND.cam_x - 32);
				CHARACTER.pos_fx = (CHARACTER.pos_x << 8);
				CHARACTER.pos_y = (MAGICWAND.cam_y - 32);
				CHARACTER.pos_fy = (CHARACTER.pos_y << 8);
				next_thread = true;
			break;

			// Anda hasta el libro
			case 49:
				if (CHARACTER.pos_x <= MAGICWAND.cam_x) {
					KEYHELD.right = true;
				} else {
					next_thread = true;
				}
				break;

			// Coge el libro
			case 50:
				KEYPRESS.a = true;
				next_thread = true;
				timer = 0;
				break;

			// Espera a que termine la voz
			case 51:
				timer ++;
				if (timer >= 167) next_thread = true;
				break;

			// Espera a que se pulse A despues de esta parte del tutorial.
			// Carga parte del texto.
			// case 52:
			// case 53:


			/*
			-------------------------------------------------
				Mapa
			-------------------------------------------------
			*/

			// Muestra el mapa
			case 54:
				KEYPRESS.x = true;
				next_thread = true;
				timer = 0;
				break;

			// Espera 3 segundos
			case 55:
				timer ++;
				if (timer >= 180) {
					KEYPRESS.x = true;
					next_thread = true;
				}
				break;

			// Espera a que se pulse A despues de esta parte del tutorial.
			// Carga parte del texto.
			// case 56:

			/*
			-------------------------------------------------
				Fin del tutorial
			-------------------------------------------------
			*/

			case 57:
				if (key_a && !TUTORIAL.page_active) {
					thread = 499;
					next_thread = true;
				}
				if (!TUTORIAL.page_active) flash = true;
				break;





			/*
			-------------------------------------------------
				Salida del tutorial
			-------------------------------------------------
			*/

			// Salida del tutorial
			case 500:
				MAINGAME.brightness = 0;
				MAINGAME.fade_out = true;
				screen = 3;
				next_thread = true;
				break;

			// Fade out de la musica
			case 501:
				if (GAMEOPTIONS[0].remake) BgmVolume(((4096 - MAINGAME.brightness) >> 2));
				if (!MAINGAME.fade_out) next_thread = true;
				break;

			// Para la musica y sal
			case 502:
				if (GAMEOPTIONS[0].remake) StopBgm();
				loop = false;
				break;


			/*
			-------------------------------------------------
				Tutorial "Espera a que se pulse A"
			-------------------------------------------------
			*/

			// Espera a que se presione A, cambia de thread y pide una pagina de texto nueva
			default:
				if (!TUTORIAL.page_active && key_a) {
					get_page = true;
					next_thread = true;
				}
				if (!TUTORIAL.page_active) flash = true;
				break;

		}

		if (next_thread) {
			thread ++;
			next_thread = false;
		}

		/*
		-------------------------------------------------
			Fin de los procesos del Tutorial
		-------------------------------------------------
		*/


		// Efecto Fade In
		if (MAINGAME.fade_in) {
			MAINGAME.brightness += 64;
			if (MAINGAME.brightness >= (16 << 8)) {
				MAINGAME.brightness = (16 << 8);
				MAINGAME.fade_in = false;
			}
			setBrightness(screen, ((MAINGAME.brightness >> 8) - 16));
		}

		// Efecto Fade Out
		if (MAINGAME.fade_out) {
			MAINGAME.brightness += 64;
			if (MAINGAME.brightness >= (16 << 8)) {
				MAINGAME.brightness = (16 << 8);
				MAINGAME.fade_out = false;
			}
			setBrightness(screen, -(MAINGAME.brightness >> 8));
		}

		// Sal de la simulacion si se presiona START
		if (key_start) {
			if (!MAINGAME.fade_in && !MAINGAME.fade_out && (thread < 500)) thread = 500;
		}

		// Control del ICONO A
		if (flash) {
			NF_ShowSprite(0, 0, true);
			icon_cnt ++;
			if (icon_cnt >= 15) {
				icon_cnt = 0;
				icon_state = !icon_state;
				if (icon_state) {
					NF_SpriteFrame(0, 0, 1);
				} else {
					NF_SpriteFrame(0, 0, 0);
				}
			}
		} else {
			NF_ShowSprite(0, 0, false);
			NF_SpriteFrame(0, 0 , 0);
			icon_state = false;
			icon_cnt = 0;
		}

		// Engine grafico y sonoro del HowTo
		HowToEngine(camera);

		// Control del texto
		if (get_page) {
			TutorialGetTextPage();
			get_page = false;
		}
		if (!MAINGAME.fade_in && !MAINGAME.fade_out) TutorialWritePage();

	}

	// Deten y limpia el sonido
	SoundSfxCleanUp();
	SoundBgmCleanUp();

	// Limpia los buffers de texto
	free(TUTORIAL.text_buffer);
	TUTORIAL.text_buffer = NULL;

}






