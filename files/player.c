#include <LPC17xx.H>                            /* LPC17xx definitions */
#include <stdio.h>
#include <string.h>
#include "uart.h"
#include "player.h"

char stats[100];

void takeDamage(Player* p) {
	p->health -= 5;
	
	if(p->health <= 0) 
		p->lives--;
}

void fire(Player* p) {
	if(p->ammo > 0) {
		p->ammo--;
		//send out IR signal
	}
	//otherwise produce a "click" sound to indicate a reload is needed
}

void reload(Player *p) {
	p->ammo = 10;
}

void pInit(Player *p) {
	p->health = 100;
	p->lives = 1;
	p->ammo = 10;
}

void sendStats(Player *p) {
	sprintf(stats, "Health: %d\nLives: %d\n Ammo: %d\n", p->health, p->lives, p->ammo);
	UARTSend(0, (uint8_t *) stats, 100);
}
