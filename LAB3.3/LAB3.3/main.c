/*
 * LAB3.3.c
 *
 * Created: 05.05.2022 13:07:33
 * Author : Student_PL
 */ 

#include <avr/io.h>


int main(void) {
	
	TCCR0 |= (1<<WGM01)|(1<<CS02)|(1<<CS00); // Właczemnie licznika w trybie CTC i ustawienie prescalera 1/1024

	DDRA = 0x01; // Ustawienie PA0 jako wyjscie
	PORTA = 0x00; // Zgaszenie diod 
   
    while (1) 
    {
		//GENEROWANIE STANU WYSOKIEGO 
		OCR0 = 146; // ustawienie licznika do odmierzania 150ms dla stanu wysokiego
		TIFR |= (1<<OCF0); // zerowanie flagi zrownania licznika
		PORTA |= (1<<PA0); // zapalenie diody na porcie PA0
		while(!(TIFR & (1<<OCF0))); // odczekiwanie 150 ms (stanu wysokiego )
		TCNT0 = 0; // zerowanie licznika 
		
		// GENEROWANIE STANU NISKIEGO 
		OCR0 = 48; // ustawienie licznika do odmierzania 50ms dla stanu wysokiego
		TIFR |= (1<<OCF0); // zerowanie flagi zrownania licznika
		PORTA &= ~(1<<PA0); // gasenie diody na porcie PA0
		while(!(TIFR & (1<<OCF0))); // odczekiwanie 50 ms (stanu wysokiego )
		TCNT0 = 0; // zerowanie licznika 
    }
}

