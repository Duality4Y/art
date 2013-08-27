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

#define CELL(I,J) (field[size*(I)+(J)])
#define ALIVE(I,J) t[size*(I)+(J)] = 1
#define DEAD(I,J)  t[size*(I)+(J)] = 0
 
int count_alive(const char *field, int i, int j, int size)
{
	int x, y, a=0;
	for(x=i-1; x <= (i+1) ; x++)
	{
		for(y=j-1; y <= (j+1) ; y++)
		{
			if ( (x==i) && (y==j) ) continue;
			if ( (y<size) && (x<size) &&
				(x>=0)   && (y>=0) )
			{
				a += CELL(x,y);
			}
		}
	}
	return a;
}
 
void evolve(const char *field, char *t, int size)
{
	int i, j, alive, cs;
	for(i=0; i < size; i++)
	{
		for(j=0; j < size; j++)
		{
			alive = count_alive(field, i, j, size);
			cs = CELL(i,j);
			if ( cs )
			{
				if ( (alive > 3) || ( alive < 2 ) )
					DEAD(i,j);
				else
					ALIVE(i,j);
			} else {
				if ( alive == 3 )
					ALIVE(i,j);
				else
					DEAD(i,j);
			}
		}
	}
}

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
	int *rBrightness, *bBrightness, *gBrightness;
	
	int maxBrightness = 100;
	
	//makeRandomField(field, &rBrightness, &gBrightness, &bBrightness, maxBrightness);
	displayField(field, &rBrightness, &gBrightness, &bBrightness);
}

