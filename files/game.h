#include <LPC17xx.H>                            /* LPC17xx definitions */
#include <stdio.h>
#include <string.h>
#include "uart.h"
#include "GLCD.h"
#include "type.h"
#include "player.h"

typedef struct Game {
	int status;
} Game;

typedef struct GameInfo {
	char* name;
	char* players;
} GameInfo;
/* 

	status
	0 = nothing
	1 = polling
	2 = ingame

*/

void gInit(Game* g, Player* p);

void joinGame(Game* g);

void addGame(char* name, char* players);

void updateList(void);

void updateDisplay(Player* p);

void waiting(void);
