/*
 * LAB3.2.c
 *
 * Created: 05.05.2022 12:49:42
 * Author : Student_PL
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
 
	TCCR0 |= (1<<CS02)|(1<<CS01); // Uruchomienie licznika i ustawienie prescalera w tryb syganlow zewnetrznych 
	PORTB |= (1<<PB0); // Podpiecie pinu do VCC (wewnetrzny rezystor)
	
	DDRA = 0xFF; // Caly port A jako wyjscie
	PORTA = 0x00; // Zgaszenie wszytskich diod
	
 
    while (1) 
    {
		
		while(!(TIFR & (1<<TOV0))) { // Jezeli licznik sie nie przepelnil wyswietlaj na diodach bitowo wartosc licznika 
			PORTA = TCNT0; // wyswietlanie na diodach bitowo wartosci licznika
			_delay_ms(200); // odczekiwanie 200 ms 
		}
		TCCR0 &= ~((1<<CS02)|(1<<CS01)|(1<<CS00)); // wylaczenie licznika gdy wartosc licznika osiagnie wartosc 255

    }
}
