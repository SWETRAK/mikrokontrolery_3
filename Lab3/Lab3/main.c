#include <avr/io.h>
#include <util/delay.h>

void timer10ms();
void czas_1s();

int main(void){
	
	TCCR0 |= (1<<CS02)|(1<<WGM01); // Ustawienie licznika w tryb pracy CTC, oraz preskalera w tryb pracy 1/256 
	OCR0 = 39; // ustalenie liczby do poruwnania tak aby odliczal czas 10ms
	
	DDRA = 0x01; // Ustawienie portu PA0 jako wyjscie 
	PORTA = 0x00; // Zgaszenie wszytskich diod 
	
    while (1) 
    {
		
		PORTA ^= (1<<PA0); // Zmiana stanu diody na przeciwny (zykliczne zapalanie i gaszenie )
		czas_1s(); // odpierzanie czasu 1s za pomoca autorskiej funkcji 
		
    }
}

// Funkcja odliczajaca 10ms z wykozystaniem timera T/C0 
void timer10ms() {
	while(!(TIFR & (1<<OCF0))); // odczekiwanie do momentu gdy lilcznik zruwna sie z zadana wartoscia 
	TCNT0 = 0; // zerowanie licznika timera 0
	TIFR |= (1<<OCF0); // wyzerowanie flagi zrownania sie licznika z zadana wartoscią 
}


void czas_1s() {
	// 100 krotne wywolanie funkcji timer10ms 
	// 100 * 10ms = 1000ms = 1s
	for(uint8_t i = 0; i<100; i++) {
		timer10ms(); 
	}
	
}


