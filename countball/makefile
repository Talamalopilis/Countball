MCU=attiny13
CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-g -mmcu=$(MCU) -Os

all: countball.hex

countball.hex : countball.o 
	$(OBJCOPY) -R .eeprom -O ihex countball.o countball.hex 
countball.o : countball.c 
	$(CC) $(CFLAGS) -Os -o countball.o countball.c
clean:
	rm -f *.hex *.o