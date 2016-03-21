avrdude -p attiny13 -c arduino -P com3 -b 19200 -q -U flash:w:countball.hex
pause
