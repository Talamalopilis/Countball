#ifdef _MSC_VER			//IntelliSense override
#define __AVR_ATtiny13__	
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

static const unsigned char MAXDIGITS =	6;
static unsigned char STARTCOLUMN =		104;
static const char DIGITSIZE = 20;

void init_LCD();
void data_out(unsigned char);
void comm_out(unsigned char);
void paint_frame();
void paint_count(unsigned int, struct numbers*);
void paint_digit(const unsigned char*, unsigned char);
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
	paint_count(10, &numbers);
	//_delay_ms(15000);
	//paint_count(1111, &numbers);

	while (1)
	{
		/*set_sleep_mode(SLEEP_MODE_PWR_DOWN);
		sleep_enable();
		sleep_cpu();*/
	}
	return 0;
}

void data_out(unsigned char i) //Data Output Serial Interface
{
	unsigned char n;
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
	unsigned char n;
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
	unsigned char column = STARTCOLUMN; // start at last least significant digit
	int digitnum;
	const unsigned char *digitdraw;
	char i;
	int a = 10;
	int b = 1;

	for (i = 0; i < MAXDIGITS && count > 0; i++, b=a, a*=10, column-=DIGITSIZE) {
		// paint until max digits or until out of inputed digits.
		// increment digit count, order up dividor and modulus, shift column back one digit
		digitnum = count % a;
		count -= digitnum;
		digitnum = digitnum / b;

		switch (digitnum)
		{
		case 0:
			digitdraw = numbers->zero;
			break;
		case 1:
			digitdraw = numbers->one;
			break;
		case 2:
			digitdraw = numbers->two;
			break;
		case 3:
			digitdraw = numbers->three;
			break;
		case 4:
			digitdraw = numbers->four;
			break;
		case 5:
			digitdraw = numbers->five;
			break;
		case 6:
			digitdraw = numbers->six;
			break;
		case 7:
			digitdraw = numbers->seven;
			break;
		case 8:
			digitdraw = numbers->eight;
			break;
		case 9:
			digitdraw = numbers->nine;
			break;
		default:
			digitdraw = numbers->zero;
			break;
		}
		paint_digit(digitdraw, column);
	}
}

void paint_digit(const unsigned char *digit, unsigned char column)
{
	char i, j;
	for (i = 0; i < 3; i++) {
		comm_out(0xB0 + i+1); //start at row 1
		comm_out(0x10 + (column >> 4)); //column (upper bits)
		comm_out(0x00 + (column & 0x0f)); //column (lower bits)
		for (j = 0; j < 10; j++) {
			data_out(pgm_read_byte(digit + (i * 10 + j)));
			data_out(pgm_read_byte(digit + (i * 10 + j)));
		}
	}
}

void init_numbers(struct numbers *n)
{
	n->zero = zeroM;
	n->one = oneM;
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
