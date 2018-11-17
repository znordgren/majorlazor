#include "game.h"

void joinGame (Game* g) {
	g->status = 1;
	
	//handle sending info to app via bluetooth here
}

void updateList() {
	LCD_PutText(100, 45, (uint8_t *) "Games", Black, White);
	LCD_draw_box(40, 40, 160, 240, Black);
	LCD_draw_line(40, 60, 200, 60, Black);
}
