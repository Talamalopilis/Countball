#pragma once

#include <avr\pgmspace.h>

#ifdef _MSC_VER		//IntelliSense override
#define PROGMEM
#endif

struct numbers {
	//digit display, 24x20 pixels, 8 pixels per column, width compressed to 10
	const unsigned char *zero; //[30] 3*10
	const unsigned char *one;
	const unsigned char *two;
	const unsigned char *three;
	const unsigned char *four;
	const unsigned char *five;
	const unsigned char *six;
	const unsigned char *seven;
	const unsigned char *eight;
	const unsigned char *nine;
};

const unsigned char zeroM[30] PROGMEM = {
	0x00, 0xf0, 0xfc, 0x3c, 0x3c, 0x3c, 0x3c, 0xfc, 0xf0, 0x00,
	0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00,
	0x00, 0x0f, 0x3f, 0x3c, 0x3c, 0x3c, 0x3c, 0x3f, 0x0f, 0x00
};

const unsigned char oneM[30] PROGMEM = {
	0x00, 0x00, 0x3c, 0x3c, 0xfc, 0xfc, 0x3c, 0x3c, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x03, 0x0f, 0x3f, 0x3f, 0x00, 0x00, 0x00, 0x00
};

const unsigned char twoM[30] PROGMEM = {
	0x00, 0x3c, 0xfc, 0xfc, 0xfc, 0x3c, 0x3c, 0x3c, 0x3c, 0x00,
	0x00, 0x00, 0x00, 0x03, 0x0f, 0x3f, 0xfc, 0xf0, 0xc0, 0x00,
	0x00, 0x0f, 0x3f, 0x3c, 0x3c, 0x3c, 0x3c, 0x3f, 0x0f, 0x00
};

const unsigned char threeM[30] PROGMEM = {
	0x00, 0xf0, 0xfc, 0x3c, 0x3c, 0x3c, 0x3c, 0xfc, 0xf0, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x3c, 0x3c, 0x3c, 0xff, 0xc3, 0x00,
	0x00, 0x0f, 0x3f, 0x3c, 0x3c, 0x3c, 0x3c, 0x3f, 0x0f, 0x00
};

const unsigned char fourM[30] PROGMEM = {
	0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xfc, 0xc0, 0x00,
	0x00, 0x3f, 0xff, 0xf3, 0xc3, 0x03, 0xff, 0xff, 0x03, 0x00
	0x00, 0x00, 0x00, 0x03, 0x0f, 0x3f, 0x3f, 0x3f, 0x00, 0x00
};

const unsigned char fiveM[30] PROGMEM = {
	0x00, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0xfc, 0xf0, 0x00,
	0x00, 0xfc, 0xfc, 0x3c, 0x3c, 0x3c, 0x3c, 0x3f, 0x0f, 0x00,
	0x00, 0x3f, 0x3f, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x00
};

const unsigned char sixM[30] PROGMEM = {
	0x00, 0xf0, 0xfc, 0x3c, 0x3c, 0x3c, 0x3c, 0xfc, 0xf0, 0x00,
	0x00, 0xff, 0xff, 0x3c, 0x3c, 0x3c, 0x3c, 0x3f, 0x0f, 0x00,
	0x00, 0x0f, 0x3f, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x00
};

const unsigned char sevenM[30] PROGMEM = {
	0x00, 0x3c, 0xfc, 0xf0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x03, 0x0f, 0x3f, 0xfc, 0xf0, 0xc0, 0x00,
	0x00, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3f, 0x3f, 0x00
};

const unsigned char eightM[30] PROGMEM = {
	0x00, 0xf0, 0xfc, 0x3c, 0x3c, 0x3c, 0x3c, 0xfc, 0xf0, 0x00,
	0x00, 0xc3, 0xff, 0x3c, 0x3c, 0x3c, 0x3c, 0xff, 0xc3, 0x00,
	0x00, 0x0f, 0x3f, 0x3c, 0x3c, 0x3c, 0x3c, 0x3f, 0x0f, 0x00
};

const unsigned char nineM[30] PROGMEM = {
	0x00, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0xfc, 0xf0, 0x00,
	0x00, 0xf0, 0xfc, 0x3c, 0x3c, 0x3c, 0x3c, 0xff, 0xff, 0x00,
	0x00, 0x0f, 0x3f, 0x3c, 0x3c, 0x3c, 0x3c, 0x3f, 0x0f, 0x00
};