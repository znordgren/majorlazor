#include <lpc17xx.h>
#include <stdio.h>
#include <math.h>
#include "Serial.h"
#include "GLCD.h"
#include "uart.h"

int receive(void);

extern unsigned short getColor(char c);

extern volatile uint32_t UART0_Count;
extern volatile uint8_t UART0_Buffer[BUFSIZE];
extern volatile uint32_t UART2_Count;
extern volatile uint8_t UART2_Buffer[BUFSIZE];

char response;
int delay;
int myChar;
int mode;
unsigned short color;


int main(void)
{	
	SystemInit();
	GLCD_Init();
  LPC_SC->PCONP |= 1 << 1; // Power up Timer 0 
  LPC_SC->PCLKSEL0 |= 1 << 2; // Clock for timer = CCLK, i.e., CPU Clock
  LPC_TIM0->MR0 = 1 << 24; // 24: give a value suitable for the LED blinking 
                           // frequency based on the clock frequency 
  LPC_TIM0->MCR |= 1 << 0; // Interrupt on Match 0 compare 
  LPC_TIM0->MCR |= 1 << 1; // Reset timer on Match 0    
  LPC_TIM0->TCR |= 1 << 1; // Manually Reset Timer 0 (forced) 
  LPC_TIM0->TCR &= ~(1 << 1); // Stop resetting the timer 

  NVIC_EnableIRQ(TIMER0_IRQn);

  LPC_TIM0->TCR |= 1 << 0; // Start timer
	
	GLCD_Clear(Purple);
	
	SER_init(0,115200); // Initialize Serial
	UARTInit(2, 115200);// Initialize UART2 for debugging
	
	UARTSend( 2, (uint8_t *)("\r\n\r\nSetting up ESP8266...\r\n"), 27);

	SER_putString(0,"AT+RST\r\n"); // reset module
	receive(); // receive output
	SER_putString(0,"AT+CWMODE=2\r\n"); // set wifi mode to access point
	receive(); // receive output
	SER_putString(0,"AT+CIFSR\r\n"); // get IP address
	receive(); // receive output
	SER_putString(0,"AT+CIPMODE=0\r\n"); // set transfer mode to normal
	receive(); // receive output
	SER_putString(0,"AT+CIPMUX=1\r\n"); // multiple connections
	receive(); // receive output
	SER_putString(0,"AT+CIPSERVER=1,80\r\n"); // turn on server on port 80
	receive(); // receive output

            // Pin P0.2 used as TXD0 (Com0) 
						// Pin P0.3 used as RXD0 (Com0) 
//while(1)
//{
//		response = SER_getChar(0); // gets data from the wifi chip
//		if(response == '0') // if the response is 1, team color is red
//		{
//			GLCD_Clear(Red);
//			break;
//		}
//		else if(response == '1') // if the response is 2, team color is blue
//		{
//			GLCD_Clear(Blue);
//			break;
//		}
//}
	response = SER_getChar(0);
	color = getColor(response);
	while(color == DarkGrey)
	{
		response = SER_getChar(0); // gets data from the wifi chip
		color = getColor(response); // translates data from wifi chip into team color
	}
	GLCD_Clear(color); // set Team Color as background
}

void TIMER0_IRQHandler(void)
{
  if ( (LPC_TIM0->IR & 0x01) == 0x01 ) // if MR0 interrupt (this is a sanity check);
  {
    LPC_TIM0->IR |= 1 << 0; // Clear MR0 interrupt flag
		response = SER_getChar(0); // gets data from the wifi chip
		delay++;
  }
}

int receive()
{
	delay = 0;
	UART2_Count = 0;
	
	while ((delay < 5) && (UART2_Count < BUFSIZE))
	{
		while ((myChar = SER_getChar_nb(2)) != 0)
			UART2_Buffer[UART2_Count++] = myChar;
	}
	
	if(UART2_Count > 0)
	{
		UARTSend(2, (uint8_t *)("\r\n+---------------------+\r\n"), 27);
		UARTSend(2, (uint8_t *)(UART2_Buffer), UART2_Count);
		return 1;
	}
	return 0;
}



