/* stars.c */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "artdmx.h"
#include "dmxmain.h"

#define SET_LED(ch, r, g, b) do {               \
                int c = 149-ch;                 \
                dmx_universe[3*c] = r;          \
                dmx_universe[3*c+1] = g;        \
                dmx_universe[3*c+2] = b;        \
        } while (0)

#define FIELDSIZE 120
bool field[FIELDSIZE+1];
int maxBright = 10;
int *rBright, *bBright, *gBright = 10;

void makeRandomField(bool *field, int *rBright, int *gBright, int *bBright)
{
	rBright = rand()%maxBright;
	gBright = rand()%maxBright;
	bBright = rand()%maxBright;
	
	memset(field, 0, FIELDSIZE);
	
	int i=0;
	while(i<FIELDSIZE)
	{
		field[i] = rand()%2;
		i++;
	}
}

void displayField(bool *field,int *rBright,int *gBright,int *bBright)
{
	int i=0;	
	while(i<FIELDSIZE)
	{
		if(field[i])
		{
			SET_LED(i, &rBright, &gBright, &bBright);
		}
		else
		{
			SET_LED(i, 0, 0, 0);
		}
		i++;
	}
}

void init_pattern(char *dmx_universe)
{
	memset(dmx_universe, 0, 450);
	makeRandomField(field, rBright, gBright, bBright);
}
void generate_pattern(char *dmx_universe)
{
	displayField(field, rBright, gBright, bBright);
}

