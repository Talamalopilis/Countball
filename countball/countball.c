#define __AVR_ATtiny13__
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

struct digit {
	unsigned char* bitmap; //[3][10];
	//digit display, 24x20 pixels, 8 pixels per column, width compressed to 10
};

struct numbers {
	struct digit zero;
	struct digit one;
	struct digit two;
	struct digit three;
	struct digit four;
	struct digit five;
	struct digit six;
	struct digit seven;
	struct digit eight;
	struct digit nine;
};

void init_LCD();
void data_out(unsigned char);
void comm_out(unsigned char);
void paint_frame();
void paint_count(unsigned int, struct numbers);
void paint_digit(struct digit, unsigned char);
struct numbers init_numbers();

int main(void)
{
	struct numbers numbers = init_numbers();
	unsigned int count = 0;
	unsigned char page = 0x00;
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

	while (1)
	{
		data_out(0xFF);
		count++;
		if (count % 10 == 0)
			comm_out(0xB0);
		_delay_ms(1500);
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

void paint_count(unsigned int count, struct numbers numbers)
{
}

void paint_digit(struct digit digit, unsigned char column)
{

}

struct numbers init_numbers()
{
	struct numbers n;

	unsigned char zero[3][10] = {
		{0x00, 0xf0, 0xfc, 0x3c, 0x3c, 0x3c, 0x3c, 0xfc, 0xf0, 0x00},
		{0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00},
		{0x00, 0x0f, 0x3f, 0x3c, 0x3c, 0x3c, 0x3c, 0x3f, 0x0f, 0x00}
	};
	n.zero.bitmap = zero;
	return n;
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
