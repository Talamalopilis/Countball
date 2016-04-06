#ifdef _MSC_VER			//IntelliSense override
#define __AVR_ATtiny13__	
#define pgm_read_byte
#endif

#define A0 PINB1
#define lcdpower PINB3
#define sck PINB2
#define mosi PINB0
#define lcdreset PINB4
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/portpins.h>
#include "NumbersLibrary.h"

void init_LCD();
void data_out(unsigned char);
void comm_out(unsigned char);
void paint_frame();
void paint_count(unsigned int, struct numbers*);
void paint_digit(struct digit*, unsigned char);
void init_numbers(struct numbers*);

int main(void)
{
	unsigned int count = 0;
	DDRB |= _BV(lcdpower);
	DDRB |= _BV(A0);
	DDRB |= _BV(sck);
	DDRB |= _BV(mosi);
	DDRB |= _BV(lcdreset);

	PORTB |= _BV(lcdpower);
	_delay_ms(1);
	PORTB |= _BV(lcdreset);
	_delay_ms(1);
	init_LCD();

	struct numbers numbers;
	init_numbers(&numbers);

	while (1)
	{
		paint_digit(&(numbers.zero), 4);
		paint_digit(&(numbers.zero), 24);
		paint_digit(&(numbers.zero), 44);
		/*count++;
		if (count % 10 == 0)
			comm_out(0xB0);
		_delay_ms(1500);*/
		/*PORTB = _BV(PINB3);
		_delay_ms(1500);
		PORTB = 0;
		_delay_ms(1500);
		count++;
		if (count > 10) {
			set_sleep_mode(SLEEP_MODE_PWR_DOWN);
			sleep_enable();
			sleep_cpu();
		}*/


	}
	return 0;
}

void data_out(unsigned char i) //Data Output Serial Interface
{
	unsigned int n;
	unsigned char t;
	PORTB |= _BV(A0); // A0 = 1
	for (n = 0; n<8; n++) {
		PORTB &= ~_BV(sck);// SCL = 0;
		t = i >> 7;
		if (t == 1)
			PORTB |= _BV(mosi);
		else
			PORTB &= ~_BV(mosi);
		i <<= 1;
		_delay_ms(1);
		PORTB |= _BV(sck); //SCL = 1;
		_delay_ms(1);
	}
}
void comm_out(unsigned char i) //Command Output Serial Interface
{
	unsigned int n;
	unsigned char t;
	PORTB &= ~_BV(A0); // A0 = 0
	for (n = 0; n<8; n++) {
		PORTB &= ~_BV(sck);// SCL = 0;
		t = i >> 7;
		if (t == 1)
			PORTB |= _BV(mosi);
		else
			PORTB &= ~_BV(mosi);
		i <<= 1;
		_delay_ms(1);
		PORTB |= _BV(sck); //SCL = 1;
		_delay_ms(1);
	}
}

void paint_frame()
{
}

void paint_count(unsigned int count, struct numbers *numbers)
{
}

void paint_digit(struct digit *digit, unsigned char column)
{
	int i, j;
	for (i = 0; i < 3; i++) {
		comm_out(0xB0 + i+1); //start at row 1
		comm_out(0x10 + (column >> 4)); //column (upper bits)
		comm_out(0x00 + (column & 0x0f)); //column (lower bits)
		for (j = 0; j < 10; j++) {
			data_out(pgm_read_byte(digit->bitmap + (i * 10 + j)));
			data_out(pgm_read_byte(digit->bitmap + (i * 10 + j)));
			_delay_ms(1500);
		}
	}
}

void init_numbers(struct numbers *n)
{
	//data_out(0xFF);

	n->zero.bitmap = zeroM;
}

void init_LCD()
{
	comm_out(0xA0); //internal power and resistor settings (default)
	comm_out(0xAE);
	comm_out(0xC0);
	comm_out(0xA2);
	comm_out(0x2F);
	comm_out(0x21);
	comm_out(0x81);
	comm_out(0x3F);

	comm_out(0x40); //start line 0
	comm_out(0xB0); //page 0
	comm_out(0x10); //column 0 (upper bits)
	comm_out(0x00); //column 0 (lower bits)
	comm_out(0xAF); //display on
}
