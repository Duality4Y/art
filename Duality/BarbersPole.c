/* police.c */

#include <string.h>
#include <math.h>

#include "artdmx.h"
#include "dmxmain.h"

#define min(a, b) ((a)<(b)?(a):(b))

#define SET_LED(ch, r, g, b) do {               \
                int c = 149-ch;                 \
                dmx_universe[3*c] = r;          \
                dmx_universe[3*c+1] = g;        \
                dmx_universe[3*c+2] = b;        \
        } while (0)

float pos;
int i = 0;
int fadeVal = 255;

void init_pattern(char *dmx_universe)
{
	memset(dmx_universe, 0, 450);
	pos = 0.0;
}

void generate_pattern(char *dmx_universe)
{	
	for(i = 0;i<155;i++)
	{
		if(!(i%6))
		{
			SET_LED(i+pos, fadeVal,fadeVal,fadeVal);
			SET_LED(i+pos-3, fadeVal,0,0);
		}
	}
	pos+=0.5;
	if(pos >= 7.0)
	{
		pos = 0.0;
	}
}

