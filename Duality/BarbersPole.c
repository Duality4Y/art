/* police.c */

#include <string.h>
#include <math.h>

#include "artdmx.h"
#include "dmxmain.h"

#define min(a, b) ((a)<(b)?(a):(b))

#define backwards
#ifndef backwards
	#define DIRECTION 
#else
	#define DIRECTION 149-
#endif

void set_led(int ch, int r, int g, int b, unsigned char *universe)
{
	int c = DIRECTION ch;
	universe[c*3] = r;
	universe[c*3+1] = g;
	universe[c*3+2] = b;
}

int pos, val;
int i;
int fadeVal = 30;

void init_pattern(char *dmx_universe)
{
	memset(dmx_universe, 0, 450);
	pos = 0.0;
}

void generate_pattern(char *dmx_universe)
{	
	for(i = 0;i<153;i++)
	{
		if(!(i%6))
		{
			set_led(i+pos, fadeVal,fadeVal,fadeVal,dmx_universe);
			set_led(i+pos-3, fadeVal,0,0, dmx_universe);
		}
	}
	pos+=1;
	if(pos >= 6)
	{
		pos -= 6;
	}
	usleep(100000);
}

