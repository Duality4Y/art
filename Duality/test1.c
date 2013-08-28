/* stars.c */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "artdmx.h"
#include "dmxmain.h"

#define SET_LED(ch, r, g, b) do {               \
                int c = 149-ch;                 \
                dmx_universe[3*c] = r;          \
                dmx_universe[3*c+1] = g;        \
                dmx_universe[3*c+2] = b;        \
        } while (0)

#define surviveAbility 2
#define reproductiveNumber 3

#define fieldWidth 7
#define fieldHeight 21 //22
#define byte_type uint8_t

byte_type field[fieldSize+1] = {0};

int checkUpper()
{
	if(Position-fieldWidt > 0)
	{
		
	}
}

void makeRandomField(char *field, int *rBright, int *gBright, int *bBright, int maxBright)
{
	int i = 0;
	int printWidth = 4;
	
	*rBright = rand()%maxBright;
	*gBright = rand()%maxBright;
	*bBright = rand()%maxBright;
	
	printf("max brightness %d \n", maxBright);
	printf("brightnes: %d %d %d\n",*rBright, *gBright, *bBright);
	
	while(i<(FIELDSIZE*FIELDSIZE))
	{
		field[i] = rand()%2;
		
		//for a pretty print
		printf("i:%d\tdata:%d\t\t",(int)i, (int)field[i]);
		if(!(i%printWidth))
		{
			printf(" \n");
		}
		i++;
	}
	printf(" \n");
	
	
}

void displayField(const char *field,int *rBright,int *gBright,int *bBright)
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

int *rBrightness, *bBrightness, *gBrightness;
int maxBrightness = 40;

void init_pattern(char *dmx_universe)
{
	srand(time(0));
	memset(dmx_universe, 0, 450);
	memset(field, 0, FIELDSIZE*FIELDSIZE);
	memset(temp_field, 0, FIELDSIZE*FIELDSIZE);
	
	makeRandomField(field, &rBrightness, &gBrightness, &bBrightness, maxBrightness);
	
}

void generate_pattern(char *dmx_universe)
{
}

