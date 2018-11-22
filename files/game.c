#include "game.h"

int waitCount;
int gameCount;
GameInfo list[4];

void gInit(Game* g, Player* p) {
	int i;
	g->status = 0;
	waitCount = 0;
	gameCount = 0;
	for(i = 0; i < 4; i++) {
		list[i].name = "No game found";
		list[i].players = "0/8";
	}
	pInit(p);
} 

void joinGame(Game* g) {
	g->status = 1;
	//handle sending info to app via bluetooth here
}

void addGame(char* name, char* players) {
	GameInfo gi;
	gi.name = name;
	gi.players = players;
	list[gameCount] = gi;
	gameCount++;
}

void updateList() {
	int i;
	int y;
	
	//code to handle checking for update from app
	
	LCD_PutText(100, 45, (uint8_t *) "Games", Black, White);
	LCD_draw_box(40, 40, 160, 240, Black);
	LCD_draw_line(40, 60, 200, 60, Black);
	LCD_draw_line(40, 115, 200, 115, Black);
	LCD_draw_line(40, 170, 200, 170, Black);
	LCD_draw_line(40, 225, 200, 225, Black);
	
	for(i = 0; i < 4; i++) {
		y = 70 + (i * 55);
		LCD_PutText(50, y, (uint8_t *) list[i].name, Black, White);
		LCD_PutText(50, y + 20, (uint8_t *) list[i].players, Black, White);
	}
}

void waiting() {
	LCD_Clear(White);
	
	//code to handling checking for update from app
	
	switch(waitCount) {
		case 0:
			LCD_PutText(80, 140, (uint8_t *) "Waiting.", Black, White);
			break;
		case 1:
			LCD_PutText(80, 140, (uint8_t *) "Waiting..", Black, White);
			break;
		case 2:
			LCD_PutText(80, 140, (uint8_t *) "Waiting...", Black, White);
			break;
	}
	waitCount++;
	if(waitCount == 3)
		waitCount = 0;
}
