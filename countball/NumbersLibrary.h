#pragma once

#include <avr\pgmspace.h>

#ifdef _MSC_VER		//IntelliSense override
#define PROGMEM
#endif

struct digit {
	const unsigned char *bitmap;	//[30] 3*10
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

const unsigned char zeroM[30] PROGMEM = {
	0x00, 0xf0, 0xfc, 0x3c, 0x3c, 0x3c, 0x3c, 0xfc, 0xf0, 0x00,
	0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00,
	0x00, 0x0f, 0x3f, 0x3c, 0x3c, 0x3c, 0x3c, 0x3f, 0x0f, 0x00
};