# Makefile

CFLAGS=-Wall -pedantic

all: artpoll artdmxtest white-colour multi-midi stars police artmonitor test colour-stars random-leds shifting-random-leds

artpoll: artpoll.c
artmonitor: artmonitor.c
artdmxtest: artdmxtest.c

white-colour: white-colour.c artdmx.c dmxmain.c
stars: stars.c artdmx.c dmxmain.c
multi-midi: multi-midi.c artdmx.c dmxmain.c -lasound
police: police.c artdmx.c dmxmain.c

#duality
test: test.c artdmx.c dmxmain.c
colour-stars: colour-stars.c artdmx.c dmxmain.c
random-leds: random-leds.c artdmx.c dmxmain.c
shifting-random-leds: shifting-random-leds.c artdmx.c dmxmain.c
#---------------

clean:
	rm -f artpoll artmonitor artdmxtest white-colour stars multi-midi police test colour-stars random-leds shifting-random-leds
