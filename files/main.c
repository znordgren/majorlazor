#include <LPC17xx.H>                            /* LPC17xx definitions */
#include <stdio.h>
#include <string.h>
#include "GLCD.h"                               /* GLCD function prototypes */
#include "LED.h"                                /* LED function prototypes */
#include "uart.h"

//CHANGE UART2 MENTIONS TO 0 AND VICE VERSA
//USING 2 FOR MODULE, 0 FOR OUTPUTTING RESPONSES

extern volatile uint32_t UART0_Count;
extern volatile uint8_t UART0_Buffer[BUFSIZE];
extern volatile uint32_t UART2_Count;
extern volatile uint8_t UART2_Buffer[BUFSIZE];

const int DEBUG = 0;

char message[500];

const unsigned long led_mask2[] = { 1UL<<0, 1UL<<1, 1UL<<2, 1UL<<3,
                                 1UL<<4, 1UL<<5, 1UL<<6, 1UL<<7 };

int mk;
unsigned char clock_1s;

uint16_t hnum[30];

unsigned int val_Tx = 0, val_Rx = 0;

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
  Function that turns on requested LED
 *----------------------------------------------------------------------------*/
void LED_On (unsigned int num) {

  LPC_GPIO2->FIOSET |= led_mask2[num];
}

/*----------------------------------------------------------------------------
  Function that turns off requested LED
 *----------------------------------------------------------------------------*/
void LED_Off (unsigned int num) {

  LPC_GPIO2->FIOCLR |= led_mask2[num];
}
/*----------------------------------------------------------------------------
  Function that outputs value to LEDs
 *----------------------------------------------------------------------------*/
void LED_Out(unsigned int value) {
  int i;

  for (i = 0; i < LED_NUM; i++) {
    if (value == i) {
      LED_On (i);
    } else {
      LED_Off(i);
    }
  }
}
/*----------------------------------------------------------------------------
  SysTick IRQ: Executed periodically
 *----------------------------------------------------------------------------*/
/* void SysTick_Handler (void) // SysTick Interrupt Handler (10ms);
{           
  static unsigned long ticks;
  static unsigned int leds = 7;

  // (1) Set clock_1s to 1 every 1 second;
  if (ticks++ >= 99) { 
    ticks    = 0;
//		secs 		+= 1;
    clock_1s = 1;
  }

  // (2) Blink the LEDs depending on ADC_ConvertedValue;
  if (clock_1s && mk == 1) {
    if(leds == 0) leds = 7;
    LED_Out(leds);
		leds--;
		clock_1s = 0;
  } else if (clock_1s && mk == 2) {
		if(leds == 7) leds = 0;
    LED_Out(leds);
		leds++;
		clock_1s = 0;
	}
} */

int main (void) {
	//char test[12];
	char msg[30];
	uint32_t value;
	uint32_t oldVal;
	uint32_t count;
	
	SystemInit();
	LED_init();
	
	LCD_Initialization();
	LCD_Clear(White);
	UARTInit(2, 9600);
	UARTInit(0, 9600);
	
	//
		
	//sendHTTPResponse(10, test, 12);
	//sendCommand("AT\r\n", 7);
	/*sendCommand("AT+GMR\r\n", 10);
	delay( 1 << 26 );
	sendCommand("AT+CWMODE=1\r\n", 15);
	delay( 1 << 27 );
	sendCommand("AT+CWLAP\r\n", 12);*/
	
	
	while(1) {
		if(UART2_Count != 0) {
			LPC_UART2->IER = IER_THRE | IER_RLS; // Disable RBR
			UARTSend(0, (uint8_t *)(UART2_Buffer), UART2_Count );
			UART2_Count = 0;
			LPC_UART2->IER = IER_THRE | IER_RLS | IER_RBR; // Re-enable RBR
		}
	}
}
