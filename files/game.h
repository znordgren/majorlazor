#include <LPC17xx.H>                            /* LPC17xx definitions */
#include <stdio.h>
#include <string.h>
#include "uart.h"
#include "GLCD.h"
#include "type.h"

typedef struct Game {
	int status;
} Game;

/* 

	status
	0 = nothing
	1 = polling
	2 = ingame

*/

void gInit(Game* g);

void joinGame(Game* g);

void updateList(void);

void waiting(void);
