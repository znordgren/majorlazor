#include "game.h"

int waitCount;

void gInit(Game* g) {
	g->status = 0;
	waitCount = 0;
} 

void joinGame(Game* g) {
	g->status = 1;
	
	//handle sending info to app via bluetooth here
}

void updateList() {
	LCD_PutText(100, 45, (uint8_t *) "Games", Black, White);
	LCD_draw_box(40, 40, 160, 240, Black);
	LCD_draw_line(40, 60, 200, 60, Black);
}

void waiting() {
	LCD_Clear(White);
	
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
