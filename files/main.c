//CHANGE THE thisGame.status == 2 LINE TO CHANGE/SEE THE DIFFERENT GAME STATES
// 0 : LOBBY
// 1 : WAITING FOR GAME TO START
// 2 : GAME IN PROGRESS

#include <LPC17xx.H>                            /* LPC17xx definitions */
#include "LPC17xx.H"
#include <stdio.h>
#include <string.h>
#include "GLCD.h"                               /* GLCD function prototypes */
#include "LED.h"                                /* LED function prototypes */
#include "uart.h"
#include "game.h"


#define CYCLE_TIME 445
#define SBIT_CNTEN 0 
#define SBIT_PWMEN 2

Player thisPlayer;
Game thisGame;
int toFire;
int toReload;
int toDamage;

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
char displayResponse0() {
	char rtn = 'o';	
	if(UART0_Count != 0) {
			LPC_UART0->IER = IER_THRE | IER_RLS; // Disable RBR
			rtn = UART0_Buffer[0];
			UART0_Count = 0;
			LPC_UART0->IER = IER_THRE | IER_RLS | IER_RBR; // Re-enable RBR
	}
	return rtn;
} 

char displayResponse2() {
	char rtn = 'o';	
	if(UART2_Count != 0) {
			LPC_UART2->IER = IER_THRE | IER_RLS; // Disable RBR
			rtn = UART2_Buffer[0];
			UART2_Count = 0;
			LPC_UART2->IER = IER_THRE | IER_RLS | IER_RBR; // Re-enable RBR
	}
	return rtn;
} 
*/
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
/*
void testIRQ(void) {
	char in0, in2;
		//temp way of handling input
		in0 = displayResponse0();
		in2 = displayResponse2();
		
		if(thisGame.status == 2) {
			//code to check if Fire button pressed
			//sets toFire flag to 1
			if(in2 == 'a') 
				toFire = 1;
			
			//code to check if Reload button pressed
			//sets toReload flag to 1
			//maybe introduce a delay between reloading and firing?
			if(in2 == 's')
				toReload = 1;
			
			//code to check if Receiving IR Info
			//sets toDamage flag to 1
			if(in0 == 'd')
				toDamage = 1;
		
	  }
		
		if(in0 == 'q') {
			thisGame.status = 0;
			LCD_Clear(White);
		}
		
		if(in0 == 'w') {
			thisGame.status = 1;
		}
		
		if(in0 == 'e') {
			pInit(&thisPlayer);
			thisGame.status = 2;
			updateDisplay(&thisPlayer);
		}
		
		//fire / reload should be if else if so as to only allow one at a time
}
*/
/*----------------------------------------------------------------------------
  SysTick IRQ: Executed periodically
 *----------------------------------------------------------------------------*/
void SysTick_Handler (void) // SysTick Interrupt Handler (10ms);
{           
  static unsigned long ticks;

  // (1) Set clock_1s to 1 every 1 second;
  if (ticks++ >= 30) { 
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
	
	//testIRQ();
} 

int main (void) {
	//char test[12];
	
	SystemInit();
	
	LCD_Initialization();
	LCD_Clear(White);
	SysTick_Config(SystemCoreClock/100);
	UARTInit(0, 9600);
	UARTInit(2, 9600);
	UARTSend(2, (uint8_t *) "Made it here", 12);
	
	gInit(&thisGame);
	addGame("test game", "1/8");
	addGame("test game2", "2/8");
	addGame("test game3", "3/8");
	addGame("test game4", "4/8");
	thisGame.status = 0;
	
	// (2) Timer 0 configuration;
  LPC_SC->PCONP |= 1 << 1; // Power up Timer 0 
  LPC_SC->PCLKSEL0 |= 1 << 2; // Clock for timer = CCLK, i.e., CPU Clock
  LPC_TIM0->MR0 = 1 << 12; // 24: give a value suitable for the LED blinking 
                           // frequency based on the clock frequency 
  LPC_TIM0->MCR |= 1 << 0; // Interrupt on Match 0 compare 
  LPC_TIM0->MCR |= 1 << 1; // Reset timer on Match 0    
  LPC_TIM0->TCR |= 1 << 1; // Manually Reset Timer 0 (forced) 
  LPC_TIM0->TCR &= ~(1 << 1); // Stop resetting the timer 
	
	LPC_TIM0->TCR |= 1 << 0; 
	
	UARTSend(2, (uint8_t *) "Made it update", 13);
	
	//Enable PWM
	LPC_PINCON->PINSEL3 |= ( 1 << 5 );  // Bit 5 P1.18 set for PWM1.1
	LPC_PWM1->PR = 0x0;        // count frequency:Fpclk
	LPC_PWM1->MCR = 3;         // interrupt on PWMMR0, reset on PWMMR0, reset TC if PWM matches
	LPC_PWM1->TCR = (1<<SBIT_CNTEN) | (1<<SBIT_PWMEN);  // Enable Counters,PWM module
	LPC_PWM1->MR0 = CYCLE_TIME;                // set PWM cycle(Ton+Toff)=100)
	LPC_PWM1->MR1 = CYCLE_TIME/3;              //
	LPC_PWM1->LER = 1;
	LPC_PWM1->PCR = 1<<9;
	
	//LPC_PWM1->MR0 = 50;
	//LPC_PWM1->MR1 = 30;
	//LPC_PWM1->PCR |= (1 << 9); //Bit 9 enables PWM1
	
	
  //NVIC_EnableIRQ(TIMER0_IRQn);

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
		
			if(toFire) {
				if(thisPlayer.ammo > 0) {
					
					UARTSend(0, (uint8_t *)('d'), 1 );
					// IR send here
					thisPlayer.ammo--;
					updateDisplay(&thisPlayer);
				}
				toFire = 0;
			}
			
			if(toReload) {
				thisPlayer.ammo = 10;
				toReload = 0;
				updateDisplay(&thisPlayer);
			}
			
			if(toDamage) {
				thisPlayer.health -= 5;
				toDamage = 0;
				updateDisplay(&thisPlayer);
			}
			
			if(thisPlayer.health == 0) {
				/* handle death logic here
					 might want to just end this player's game */
				thisPlayer.lives--;
				if(thisPlayer.lives == 0) {
					thisGame.status = 0;
					LCD_Clear(White);
				}
				else
					thisPlayer.health = 10;
			}
			
		}
	}
}
