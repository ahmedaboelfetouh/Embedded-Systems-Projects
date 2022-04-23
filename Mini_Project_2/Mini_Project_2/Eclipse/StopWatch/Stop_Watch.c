/*
 * Mini_Project_2.c
 *
 *  Created on: Sep 21, 2021
 *      Author: am614
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned char seccounter1=0;
unsigned char seccounter2=0;
unsigned char mincounter1=0;
unsigned char mincounter2=0;
unsigned char hourcounter1=0;
unsigned char hourcounter2=0;
unsigned char flag=0;
unsigned char flagpause=0;
unsigned char flagresume=0;

ISR(TIMER1_COMPA_vect)
{

	flag=1;
}

void Timer1_Init_CTC_Mode(void)
{
	TCNT1 = 0;
	OCR1A=15625;               //setting top value
	TIMSK |= (1<<OCIE1A);
	TCCR1A = (1<<FOC1A) | (1<<FOC1B); // Non PWM
	TCCR1B |= (1 << CS11); //prescalar=64, this prescalar and top value gives a perfect 1 sec with frequency 1MHz
	TCCR1B |= (1 << CS10);
	TCCR1B |= (1<<WGM12);
}

ISR(INT0_vect)
{
	seccounter1=0;
	seccounter2=0;
	mincounter1=0;
	mincounter2=0;
	hourcounter1=0;
	hourcounter2=0;
}
ISR(INT1_vect)
{
	flagpause=1;
}
ISR(INT2_vect)
{
	flagresume=1;
}
void INT0_Init(void)
{
	SREG  &= ~(1<<7);                   // Disable interrupts by clearing I-bit
	DDRD  &= (~(1<<PD2));               // Configure INT0/PD2 as input pin
	PORTD |= 0x04;                      //internalresist
	MCUCR &= (~(1<<ISC00));
	MCUCR |= (1<<ISC01);      			// Trigger INT0 with the falling edge
	GICR  |= (1<<INT0);                 // Enable external interrupt pin INT0
	SREG  |= (1<<7);                    // Enable interrupts by setting I-bit
}
void INT1_Init(void)
{
	SREG  &= ~(1<<7);                   // Disable interrupts by clearing I-bit
	DDRD  &= (~(1<<PD3));               // Configure INT0/PD2 as input pin
	MCUCR |= (1<<ISC10);
	MCUCR |= (1<<ISC11);                // Trigger INT0 with the falling edge
	GICR  |= (1<<INT1);                 // Enable external interrupt pin INT1
	SREG  |= (1<<7);                    // Enable interrupts by setting I-bit
}
void INT2_Init(void)
{
	SREG  &= ~(1<<7);                   // Disable interrupts by clearing I-bit
	DDRB  &= (~(1<<PB2));               // Configure INT0/PD2 as input pin
	PORTB |= 0x04; 						//internalresist
	GICR  |= (1<<INT2);                 // Enable external interrupt pin INT2
	MCUCSR &= (~(1<<ISC2));             // Trigger INT0 with the falling edge
	SREG  |= (1<<7);                    // Enable interrupts by setting I-bit
}
int main(void)
{
	DDRA |= 0x3F; /////////////portA_output
	DDRC |= 0x0F;////////////////////portC_output
	//////////////////////////
	PORTA = 0x3F;
	PORTC &= 0xF0;
	///////////////////////////
	SREG |= (1<<7);


	INT0_Init();
	INT1_Init();
	INT2_Init();
	Timer1_Init_CTC_Mode();

    while(1)
    {

    	if(flag==1)
    	{
    			seccounter1++;
    			if(seccounter1==10)
    			{
    				seccounter1=0;
    				seccounter2++;
    			}
    			if(seccounter2==6)
    			{
    				seccounter2=0;
    				mincounter1++;
    			}
    			if(mincounter1==10)
    			{
    				mincounter1=0;
    				mincounter2++;
    			}
    			if(mincounter2==6)
    			{
    				mincounter2=0;
    				hourcounter1++;
    			}
    			if(hourcounter1==9)
    			{
    				hourcounter1=0;
    				hourcounter2++;
    			}
    			if(hourcounter1==4 && hourcounter2==2 && mincounter1==10 && mincounter2==6 && seccounter2==6 && seccounter1==10)
    			{
    				hourcounter1=2;
    				hourcounter2=1;
    			}
    			flag=0;
    	}
    	else
    	{
    			PORTA=0x01;
    			PORTC=seccounter1;
    		   	_delay_ms(1);
    		   	PORTA=0x02;
    		   	PORTC=seccounter2;
    		   	_delay_ms(1);
    	       	PORTA=0x04;
    	       	PORTC=mincounter1;
   		      	_delay_ms(1);
   		    	PORTA=0x08;
   		    	PORTC=mincounter2;
   		    	_delay_ms(1);
   		    	PORTA=0x10;
   		    	PORTC=hourcounter1;
   		    	_delay_ms(1);
   		    	PORTA=0x20;
   		    	PORTC=hourcounter2;
   		    	_delay_ms(1);
    	}

    	while (flagpause==1)
    	{
    			PORTA=0x01;
    		    PORTC=seccounter1;
    		   	_delay_ms(1);
      		   	PORTA=0x02;
      		   	PORTC=seccounter2;
    		   	_delay_ms(1);
    		   	PORTA=0x04;
    		    PORTC=mincounter1;
    	      	_delay_ms(1);
    	      	PORTA=0x08;
    	    	PORTC=mincounter2;
    	    	_delay_ms(1);
    	    	PORTA=0x10;
    	    	PORTC=hourcounter1;
    	    	_delay_ms(1);
    	    	PORTA=0x20;
     	    	PORTC=hourcounter2;
     	    	_delay_ms(1);
     	    	if(flagresume==1)
     	    	{
     	    		flagpause=0;
     	    		flagresume=0;
     	    	}
    	}



    }
}

