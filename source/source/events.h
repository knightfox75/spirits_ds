#ifndef __EVENTS_H__
#define __EVENTS_H__



/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de los eventos
	(Interruptores, puertas, trampas)

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



// Funcion EventMain();
void EventMain(void);
// Gestiona los eventos del juego



// Funcion EventCloseDoor();
void EventCloseDoor(u8 door);
// Edita el mapa de colisiones, segun el estado de la puerta


// Funcion EventOpenDoor();
void EventOpenDoor(u8 door);
// Edita el mapa de colisiones, segun el estado de la puerta



// Funcion EventCloseHwall();
void EventCloseHwall(u8 hwall);
// Edita el mapa de colisiones, segun del muro mobil



// Funcion EventOpenHwallRight();
void EventOpenHwallRight(u8 hwall);
// Edita el mapa de colisiones, segun del muro mobil (de derecha a izquierda)



// Funcion EventOpenHwallUp();
void EventOpenHwallUp(u8 hwall);
// Edita el mapa de colisiones, segun del muro mobil (de arriba a abajo)



// Funcion EventCheckSwitch();
void EventCheckSwitch(void);
// Gestiona la activacion de interruptores



// Funcion EventRun();
void EventRun(void);
// Gestiona la ejecucion de eventos



// Funcion Event00();
void Event00(void);
// Abre la puerta nº00 en el Stage 01



// Funcion Event01();
void Event01(void);
// Abre la puerta nº01 en el Stage 04



// Funcion Event02();
void Event02(void);
// Abre la puerta nº02 en el Stage 05



// Funcion Event03();
void Event03(void);
// Abre la puerta nº03 en el Stage 07



// Funcion Event04();
void Event04(void);
// Abre las puertas nº04 y nº04 en el Stage 14



// Funcion Event05();
void Event05(void);
// Abre el muro nº00 en el Stage 16



// Funcion Event06();
void Event06(void);
// Activa la trampa nº00 en el Stage 16



// Funcion Event07();
void Event07(void);
// Abre el muro nº01 y cierra el muro nº02 en el Stage 16



// Funcion Event08();
void Event08(void);
// Abre la puerta nº06 en el Stage 17



// Funcion Event09();
void Event09(void);
// Abre muro nº03 en el Stage 17



// Funcion Event10();
void Event10(void);
// Activa la trampa nº01 en el Stage 17



#endif
