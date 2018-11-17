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
	p->health = 10;
	p->lives = 1;
	p->ammo = 10;
}

void sendStats(Player *p) {
	sprintf(stats, "Health: %d\n\rLives: %d\n\r Ammo: %d\n\r", p->health, p->lives, p->ammo);
	UARTSend(0, (uint8_t *) stats, 100);
}
