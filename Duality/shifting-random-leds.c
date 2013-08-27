/* 
 * Based on random-leds.c
 * Made by Duality
 *  */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "artdmx.h"
#include "dmxmain.h"

#define SET_LED(ch, r, g, b) do {               \
                int c = 149-ch;                 \
                dmx_universe[3*c] = r;          \
                dmx_universe[3*c+1] = g;        \
                dmx_universe[3*c+2] = b;        \
        } while (0)

#define FIELDSIZE 150
bool field[FIELDSIZE];

void makeRandomField(bool *field, int *rBright, int *gBright, int *bBright, int maxBright)
{
	int i = 0;
	
	*rBright = rand()%maxBright;
	*gBright = rand()%maxBright;
	*bBright = rand()%maxBright;
	
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
			SET_LED(i, *rBright, *gBright, *bBright);
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
	memset(field, 0, FIELDSIZE);
	
	srand(time(0));
}

void generate_pattern(char *dmx_universe)
{
	int *rBrightness, *bBrightness, *gBrightness;
	int maxBrightness = 100;
	
	//halve a second. 1000000 = 1 sec
	int interval = 1.5e5;
	
	makeRandomField(field, &rBrightness, &gBrightness, &bBrightness, maxBrightness);
	displayField(field, &rBrightness, &gBrightness, &bBrightness);
	usleep(interval);
}

