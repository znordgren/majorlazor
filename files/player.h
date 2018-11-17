#include <LPC17xx.H>                            /* LPC17xx definitions */
#include <stdio.h>
#include <string.h>
#include "uart.h"

typedef struct Player {
	int health;
	int lives;
	int ammo;
} Player;

void takeDamage(Player* p);

void fire(Player* p);

void reload(Player *p);

void pInit(Player* p);

void sendStats(Player* p);
