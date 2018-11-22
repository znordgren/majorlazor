#include <LPC17xx.H>                            /* LPC17xx definitions */
#include <stdio.h>
#include <string.h>
#include "GLCD.h"                               /* GLCD function prototypes */
#include "LED.h"                                /* LED function prototypes */
#include "uart.h"
#include "game.h"

Player thisPlayer;
Game thisGame;

extern volatile uint32_t UART0_Count;
extern volatile uint8_t UART0_Buffer[BUFSIZE];
extern volatile uint32_t UART2_Count;
extern volatile uint8_t UART2_Buffer[BUFSIZE];

volatile uint32_t temp;
void delay( uint32_t del)
{
  uint32_t i;
  for ( i=0; i<del; i++)
    temp = i;
}

/*
void displayResponse() {
	if(UART2_Count != 0) {
			LPC_UART2->IER = IER_THRE | IER_RLS; // Disable RBR
			UARTSend(0, (uint8_t *)(UART2_Buffer), UART2_Count );
			UART2_Count = 0;
			LPC_UART2->IER = IER_THRE | IER_RLS | IER_RBR; // Re-enable RBR
	}
} */

/*void search(char *msg, int size) {
	int i;
	char mg[3];
	mk = 0;
	
	for(i = 0; i < size; i++) {
		if(msg[i] == '+')
		else if(msg[i] == '=') {
			if(msg[i+1] == '1')
				mk = 1;
			else if(msg[i+1] == '2')
				mk = 2;
		}
	}
	
	sprintf(mg, "r:%d", mk);
	GLCD_DisplayString(3, 0, mg);
} */

/*----------------------------------------------------------------------------
  SysTick IRQ: Executed periodically
 *----------------------------------------------------------------------------*/
void SysTick_Handler (void) // SysTick Interrupt Handler (10ms);
{           
  static unsigned long ticks;

  // (1) Set clock_1s to 1 every 1 second;
  if (ticks++ >= 99) { 
    ticks    = 0;
		switch(thisGame.status) {
			case 0:
				updateList();
				break;
			case 1:
				waiting();
				break;
		}
  }

} 

int main (void) {
	//char test[12];
	
	UARTInit(0, 9600);
	LCD_Initialization();
	LCD_Clear(White);
	SysTick_Config(SystemCoreClock/100);
	gInit(&thisGame, &thisPlayer);
	addGame("test game", "1/8");
	addGame("test game2", "2/8");
	addGame("test game3", "3/8");
	addGame("test game4", "4/8");

	while(1) {
		if(thisGame.status == 0) {
			/* display list of games on screen
				 waiting for app user to press "New Game"
				 when that happens, update list of games on screen 
				 wait for user input to select a game and move to status == 1 */
		} else if(thisGame.status == 1) {
			/* read in from bluetooth
				 looking to receive info that the game has started 
				 when it has, update thisGame.status to 2 */
		} else /* status == 2 */ {
			/* handle game logic unrelated to IR interrupts */
		}
	}
}
