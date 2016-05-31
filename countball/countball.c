#ifdef _MSC_VER			//IntelliSense override
#define __AVR_ATtiny13__	
#endif

#define A0 PINB1
#define lcdpower PINB3
#define sck PINB2
#define mosi PINB0
#define lcdreset PINB4
#define F_CPU 1000000UL
#define MAXDIGITS 6
#define STARTCOLUMN 104
#define DIGITSIZE 20
#define COUNTEEADDRESS 0
#define DELAYQSECONDS 20
#define LCDCOMMAND 1
#define LCDDATA 0
#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/portpins.h>
#include <avr/eeprom.h>
#include "NumbersLibrary.h"

static void init_LCD();
void data_out(unsigned char, unsigned char);
static void paint_frame();
static void paint_count(unsigned int, struct numbers*);
static void paint_digit(const unsigned char*, unsigned char);
static void init_numbers(struct numbers*);

int main(void)
{
	unsigned int count;
	//TODO: implement eeprom wear leveling
	if (eeprom_read_byte(COUNTEEADDRESS) == 0xff) { //if first time boot
		count = 0;
		eeprom_write_word(COUNTEEADDRESS, count);
	}
	else {
		count = eeprom_read_word(COUNTEEADDRESS);
		count++;
		eeprom_write_word(COUNTEEADDRESS, count);
	}

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
	paint_count(count, &numbers);
	
	unsigned char s;
	for (s = DELAYQSECONDS*10; s; s--){
		_delay_ms(250);
	}

	PORTB = 0;	//turn all outputs off
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	sleep_enable();
	sleep_cpu();

	return 0;
}

void data_out(unsigned char datain, unsigned char comm) //Data Output Serial Interface
{
	unsigned char n;
	unsigned char t;

	if (comm)
		PORTB &= ~_BV(A0); // A0 = 0
	else
		PORTB |= _BV(A0); // A0 = 1

	for (n = 0; n<8; n++) {
		PORTB &= ~_BV(sck);// SCL = 0;
		t = datain >> 7;
		if (t == 1)
			PORTB |= _BV(mosi);
		else
			PORTB &= ~_BV(mosi);
		datain <<= 1;
		_delay_ms(1);
		PORTB |= _BV(sck); //SCL = 1;
		_delay_ms(1);
	}
}

void paint_frame()
{
	//frame graphics for the lcd.
	//cant do, ran out of code space. :(
}

void paint_count(unsigned int count, struct numbers *numbers)
{
	unsigned char column = STARTCOLUMN; // start at least significant digit
	unsigned int digitnum;
	const unsigned char *digitdraw;
	char i;

	for (i = 0; i < MAXDIGITS && count; i++, column-=DIGITSIZE) {
		// paint until max digits or until out of inputed digits.
		// increment digit count, shift column back one digit
		digitnum = count % 10;
		count /= 10;

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
		data_out(0xB0 + i+1, LCDCOMMAND); //start at row 1
		data_out(0x10 + (column >> 4), LCDCOMMAND); //column (upper bits)
		data_out(0x00 + (column & 0x0f), LCDCOMMAND); //column (lower bits)
		for (j = 0; j < 10; j++) {
			data_out(pgm_read_byte(digit + (i * 10 + j)), LCDDATA);
			data_out(pgm_read_byte(digit + (i * 10 + j)), LCDDATA);
		}
	}
}

void init_numbers(struct numbers *n)
{
	n->zero = zeroM;
	n->one = oneM;
	n->two = twoM;
	n->three = threeM;
	n->four = fourM;
	n->five = fiveM;
	n->six = sixM;
	n->seven = sevenM;
	n->eight = eightM;
	n->nine = nineM;
}

void init_LCD()
{
	data_out(0xA0, LCDCOMMAND); //internal power and resistor settings (default)
	data_out(0xAE, LCDCOMMAND);
	data_out(0xC0, LCDCOMMAND);
	data_out(0xA2, LCDCOMMAND);
	data_out(0x2F, LCDCOMMAND);
	data_out(0x21, LCDCOMMAND);
	data_out(0x81, LCDCOMMAND);
	data_out(0x3F, LCDCOMMAND);

	data_out(0x40, LCDCOMMAND); //start line 0
	data_out(0xB0, LCDCOMMAND); //page 0
	data_out(0x10, LCDCOMMAND); //column 0 (upper bits)
	data_out(0x00, LCDCOMMAND); //column 0 (lower bits)
	data_out(0xAF, LCDCOMMAND); //display on
}
