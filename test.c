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

#define FIELDSIZE 150
bool field[FIELDSIZE];

void makeRandomField(bool *field, int *rBright, int *gBright, int *bBright, int maxBright)
{
	int i = 0;
	int printWidth = 4;
	
	srand(time(0));
	
	*rBright = rand()%maxBright;
	*gBright = rand()%maxBright;
	*bBright = rand()%maxBright;
	
	printf("max brightness %d \n", maxBright);
	printf("brightnes: %d %d %d\n",*rBright, *gBright, *bBright);
	
	while(i<FIELDSIZE)
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
	
	//makeRandomField(field, &rBright, &gBright, &bBright, maxBright);
	//displayField(field, &rBright, &gBright, &bBright);
}
void generate_pattern(char *dmx_universe)
{
	int *rBright, *bBright, *gBright;
	
	int maxBright = 100;
	
	int interval = 10;
	static int count;
	
	if(count++ >= interval)
	{
		count = 0;
		makeRandomField(field, &rBright, &gBright, &bBright, maxBright);
		displayField(field, &rBright, &gBright, &bBright);
	}
}

