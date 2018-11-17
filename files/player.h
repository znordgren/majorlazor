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
