#include <stdio.h>
#include <time.h>

#include "artdmx.h"
#include "dmxmain.h"

#define numDrops 1
#define tailLen 5

/*149- for one direction and nothing for the other*/
#define direction   

void set_led(int ch, int r, int g, int b, unsigned char *universe)
{
	int c = direction-ch;
	universe[3*c]   = r;
	universe[3*c+1] = g;
	universe[3*c+2] = b;
}

int i = 1;
int pos = 0;
int width = 7;

struct Drop 
{
	int pos;
	int line;
	int tail[tailLen];
}drop[numDrops];

void init_pattern(char *dmx_universe)
{
	memset(dmx_universe, 0, 450);
	srand(time(0));
	
	for(i = 0;i<numDrops;i++)
	{
		drop[i].pos = 0;
		drop[i].line = rand()%7;
		memset(drop[i].tail, 0, tailLen);
	}
}

void generate_pattern(char *dmx_universe)
{
	drop[0].pos++;
	if(drop[0].pos >21)
	{
		drop[0].pos -= 21;
	}
	set_led((int)(drop[0].pos+width-drop[0].line), 30,30,60, dmx_universe);
	usleep(100000);
}

