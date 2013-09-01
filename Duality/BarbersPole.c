/* police.c */

#include <string.h>
#include <stdio.h>
#include <time.h>
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

void init_pattern(char *dmx_universe)
{
	memset(dmx_universe, 0, 450);
}

void generate_pattern(char *dmx_universe)
{
	static int i;
	static float pos,place;
	for(i = 0;i<153;i++)
	{
		int fadeVal = 255;
		if(!(i%6))
		{
			SET_LED(i+pos, fadeVal,fadeVal,fadeVal);
			SET_LED(i+pos-3, fadeVal/255*112,0,0);
		}
	}
	pos+=0.2;
	if(pos >= 7.0)
	{
		pos = 0.0;
	}
}

