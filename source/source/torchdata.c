/*
-------------------------------------------------

	Spirits DS

	Archivo de funciones de Carga de datos de las antorchas y velas

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



// Funcion LoadDefaultTorchData();
void LoadDefaultTorchData(void) {

	// Carga los parametros estaticos de las antorchas o velas (unicos)
	// Stage 01
	TORCH[0].pos_x = 448, TORCH[0].pos_y = 48, TORCH[0].type = 0, TORCH[0].stage = 1;
	TORCH[1].pos_x = 608, TORCH[1].pos_y = 48, TORCH[1].type = 0, TORCH[1].stage = 1;
	TORCH[2].pos_x = 1232, TORCH[2].pos_y = 32, TORCH[2].type = 0, TORCH[2].stage = 1;
	TORCH[3].pos_x = 1440, TORCH[3].pos_y = 32, TORCH[3].type = 0, TORCH[3].stage = 1;
	// Stage 02
	TORCH[4].pos_x = 244, TORCH[4].pos_y = 232, TORCH[4].type = 1, TORCH[4].stage = 2;
	TORCH[5].pos_x = 448, TORCH[5].pos_y = 224, TORCH[5].type = 0, TORCH[5].stage = 2;
	TORCH[6].pos_x = 608, TORCH[6].pos_y = 224, TORCH[6].type = 0, TORCH[6].stage = 2;
	// Stage 03
	TORCH[7].pos_x = 80, TORCH[7].pos_y = 416, TORCH[7].type = 0, TORCH[7].stage = 3;
	TORCH[8].pos_x = 320, TORCH[8].pos_y = 416, TORCH[8].type = 0, TORCH[8].stage = 3;
	TORCH[9].pos_x = 800, TORCH[9].pos_y = 432, TORCH[9].type = 0, TORCH[9].stage = 3;
	TORCH[10].pos_x = 1792, TORCH[10].pos_y = 416, TORCH[10].type = 0, TORCH[10].stage = 3;
	// Stage 04
	TORCH[11].pos_x = 432, TORCH[11].pos_y = 624, TORCH[11].type = 0, TORCH[11].stage = 4;
	TORCH[12].pos_x = 948, TORCH[12].pos_y = 600, TORCH[12].type = 1, TORCH[12].stage = 4;
	// Stage 05
	TORCH[13].pos_x = 292, TORCH[13].pos_y = 792, TORCH[13].type = 1, TORCH[13].stage = 5;
	TORCH[14].pos_x = 432, TORCH[14].pos_y = 800, TORCH[14].type = 0, TORCH[14].stage = 5;
	TORCH[15].pos_x = 820, TORCH[15].pos_y = 792, TORCH[15].type = 1, TORCH[15].stage = 5;
	TORCH[16].pos_x = 1076, TORCH[16].pos_y = 792, TORCH[16].type = 1, TORCH[16].stage = 5;
	TORCH[17].pos_x = 1392, TORCH[17].pos_y = 800, TORCH[17].type = 0, TORCH[17].stage = 5;
	TORCH[18].pos_x = 1712, TORCH[18].pos_y = 800, TORCH[18].type = 0, TORCH[18].stage = 5;
	// Stage 11
	TORCH[19].pos_x = 3376, TORCH[19].pos_y = 416, TORCH[19].type = 0, TORCH[19].stage = 11;
	TORCH[20].pos_x = 4560, TORCH[20].pos_y = 416, TORCH[20].type = 0, TORCH[20].stage = 11;
	// Stage 12
	TORCH[21].pos_x = 3536, TORCH[21].pos_y = 624, TORCH[21].type = 0, TORCH[21].stage = 12;
	TORCH[22].pos_x = 3772, TORCH[22].pos_y = 616, TORCH[22].type = 1, TORCH[22].stage = 12;
	TORCH[23].pos_x = 4448, TORCH[23].pos_y = 624, TORCH[23].type = 0, TORCH[23].stage = 12;
	TORCH[24].pos_x = 4560, TORCH[24].pos_y = 624, TORCH[24].type = 0, TORCH[24].stage = 12;
	// Stage 13
	TORCH[25].pos_x = 3168, TORCH[25].pos_y = 800, TORCH[25].type = 0, TORCH[25].stage = 13;
	TORCH[26].pos_x = 3392, TORCH[26].pos_y = 800, TORCH[26].type = 0, TORCH[26].stage = 13;
	TORCH[27].pos_x = 3536, TORCH[27].pos_y = 800, TORCH[27].type = 0, TORCH[27].stage = 13;
	TORCH[28].pos_x = 3808, TORCH[28].pos_y = 800, TORCH[28].type = 0, TORCH[28].stage = 13;
	TORCH[29].pos_x = 4272, TORCH[29].pos_y = 800, TORCH[29].type = 0, TORCH[29].stage = 13;
	TORCH[30].pos_x = 4768, TORCH[30].pos_y = 800, TORCH[30].type = 0, TORCH[30].stage = 13;
	TORCH[31].pos_x = 4912, TORCH[31].pos_y = 800, TORCH[31].type = 0, TORCH[31].stage = 13;
	// Stage 6
	TORCH[32].pos_x = 816, TORCH[32].pos_y = 992, TORCH[32].type = 0, TORCH[32].stage = 6;
	TORCH[33].pos_x = 880, TORCH[33].pos_y = 992, TORCH[33].type = 0, TORCH[33].stage = 6;
	TORCH[34].pos_x = 1456, TORCH[34].pos_y = 992, TORCH[34].type = 0, TORCH[34].stage = 6;
	TORCH[35].pos_x = 1552, TORCH[35].pos_y = 992, TORCH[35].type = 0, TORCH[35].stage = 6;
	TORCH[36].pos_x = 1728, TORCH[36].pos_y = 992, TORCH[36].type = 0, TORCH[36].stage = 6;
	TORCH[37].pos_x = 1888, TORCH[37].pos_y = 992, TORCH[37].type = 0, TORCH[37].stage = 6;
	// Stage 7
	TORCH[38].pos_x = 736, TORCH[38].pos_y = 1184, TORCH[38].type = 0, TORCH[38].stage = 7;
	TORCH[39].pos_x = 1008, TORCH[39].pos_y = 1184, TORCH[39].type = 0, TORCH[39].stage = 7;
	TORCH[40].pos_x = 1300, TORCH[40].pos_y = 1192, TORCH[40].type = 1, TORCH[40].stage = 7;
	TORCH[41].pos_x = 1380, TORCH[41].pos_y = 1192, TORCH[41].type = 1, TORCH[41].stage = 7;
	TORCH[42].pos_x = 1572, TORCH[42].pos_y = 1184, TORCH[42].type = 1, TORCH[42].stage = 7;
	// Stage 8
	TORCH[43].pos_x = 512, TORCH[43].pos_y = 1376, TORCH[43].type = 0, TORCH[43].stage = 8;
	TORCH[44].pos_x = 672, TORCH[44].pos_y = 1376, TORCH[44].type = 0, TORCH[44].stage = 8;
	TORCH[45].pos_x = 1184, TORCH[45].pos_y = 1376, TORCH[45].type = 0, TORCH[45].stage = 8;
	TORCH[46].pos_x = 1648, TORCH[46].pos_y = 1376, TORCH[46].type = 0, TORCH[46].stage = 8;
	// Stage 10
	TORCH[47].pos_x = 2032, TORCH[47].pos_y = 992, TORCH[47].type = 0, TORCH[47].stage = 10;
	TORCH[48].pos_x = 2160, TORCH[48].pos_y = 992, TORCH[48].type = 0, TORCH[48].stage = 10;
	TORCH[49].pos_x = 2320, TORCH[49].pos_y = 992, TORCH[49].type = 0, TORCH[49].stage = 10;
	TORCH[50].pos_x = 2432, TORCH[50].pos_y = 992, TORCH[50].type = 0, TORCH[50].stage = 10;
	// Stage 14
	TORCH[51].pos_x = 3200, TORCH[51].pos_y = 992, TORCH[51].type = 0, TORCH[51].stage = 14;
	TORCH[52].pos_x = 3620, TORCH[52].pos_y = 984, TORCH[52].type = 1, TORCH[52].stage = 14;
	TORCH[53].pos_x = 3780, TORCH[53].pos_y = 984, TORCH[53].type = 1, TORCH[53].stage = 14;
	TORCH[54].pos_x = 4164, TORCH[54].pos_y = 1000, TORCH[54].type = 1, TORCH[54].stage = 14;
	// Stage 15
	TORCH[55].pos_x = 3712, TORCH[55].pos_y = 1184, TORCH[55].type = 0, TORCH[55].stage = 15;
	TORCH[56].pos_x = 4176, TORCH[56].pos_y = 1184, TORCH[56].type = 0, TORCH[56].stage = 15;
	TORCH[57].pos_x = 4240, TORCH[57].pos_y = 1184, TORCH[57].type = 0, TORCH[57].stage = 15;
	TORCH[58].pos_x = 4304, TORCH[58].pos_y = 1184, TORCH[58].type = 0, TORCH[58].stage = 15;
	TORCH[59].pos_x = 4368, TORCH[59].pos_y = 1184, TORCH[59].type = 0, TORCH[59].stage = 15;
	TORCH[60].pos_x = 4432, TORCH[60].pos_y = 1184, TORCH[60].type = 0, TORCH[60].stage = 15;
	TORCH[61].pos_x = 4496, TORCH[61].pos_y = 1184, TORCH[61].type = 0, TORCH[61].stage = 15;
	// Stage 16
	TORCH[62].pos_x = 4176, TORCH[62].pos_y = 1376, TORCH[62].type = 0, TORCH[62].stage = 16;
	TORCH[63].pos_x = 4484, TORCH[63].pos_y = 1368, TORCH[63].type = 1, TORCH[63].stage = 16;
	TORCH[64].pos_x = 4928, TORCH[64].pos_y = 1376, TORCH[64].type = 0, TORCH[64].stage = 16;
	// Stage 17
	TORCH[65].pos_x = 3232, TORCH[65].pos_y = 1568, TORCH[65].type = 0, TORCH[65].stage = 17;
	TORCH[66].pos_x = 3392, TORCH[66].pos_y = 1568, TORCH[66].type = 0, TORCH[66].stage = 17;
	TORCH[67].pos_x = 3492, TORCH[67].pos_y = 1576, TORCH[67].type = 1, TORCH[67].stage = 17;
	TORCH[68].pos_x = 3588, TORCH[68].pos_y = 1576, TORCH[68].type = 1, TORCH[68].stage = 17;
	TORCH[69].pos_x = 3776, TORCH[69].pos_y = 1568, TORCH[69].type = 0, TORCH[69].stage = 17;
	// Stage 18
	TORCH[70].pos_x = 3408, TORCH[70].pos_y = 1776, TORCH[70].type = 0, TORCH[70].stage = 18;
	TORCH[71].pos_x = 3504, TORCH[71].pos_y = 1760, TORCH[71].type = 0, TORCH[71].stage = 18;
	TORCH[72].pos_x = 3680, TORCH[72].pos_y = 1760, TORCH[72].type = 0, TORCH[72].stage = 18;
	TORCH[73].pos_x = 4372, TORCH[73].pos_y = 1752, TORCH[73].type = 1, TORCH[73].stage = 18;
	TORCH[74].pos_x = 4928, TORCH[74].pos_y = 1760, TORCH[74].type = 0, TORCH[74].stage = 18;

}



// Funcion LoadStartTorchData();
void LoadStartTorchData(void) {

	/*
	-------------------------------------------------
		Variables
	-------------------------------------------------
	*/

	s16 n = 0;
	u8 screen = 0;
	u8 id = 0;

	/*
	-------------------------------------------------
		Resetea el FIFO de sprites
		de las antorchas
	-------------------------------------------------
	*/

	for (screen = 0; screen < 2; screen ++) {
		for (id = 0; id < TORCH_SPR_NUM; id ++) {
			TORCH_SPR[screen].id[id] = (id + TORCH_SPRITE);
			TORCH_SPR[screen].in_use[id] = false;
		}
	}


	/*
	-------------------------------------------------
		Todas las antorchas ocultas e inicializadas
	-------------------------------------------------
	*/

	for (n = 0; n < TORCH_NUM; n ++) {
		// Parametros iniciales de las antorchas
		TORCH[n].on_screen[0] = false, TORCH[n].on_screen[1] = false;
		TORCH[n].created[0] = false, TORCH[n].created[1] = false;
		// Resetea los datos del FIFO
		TORCH[n].spr_id[0] = 255, TORCH[n].spr_id[1] = 255;
		// Animacion
		TORCH[n].frame = (int)(rand() % 4);
		TORCH[n].frame_cnt = 0;

	}

}
