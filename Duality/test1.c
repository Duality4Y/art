/* test */

#include <stdio.h>
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
#define fieldHeight 20 //22
#define FIELDSIZE fieldWidth*fieldHeight
#define fieldSize FIELDSIZE
#define byte_type unsigned int

byte_type field[fieldSize+1] = {0};
unsigned int Position = 0;

inline int checkUpper()
{
	if(Position-fieldWidth>0)
	{
		if(field[Position-fieldWidth])
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}
 
inline int checkLower()
{
	if(Position+fieldWidth<fieldSize)
	{
		if(field[Position+fieldWidth])
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}
 
inline int checkLeft()
{
	if(Position-1>0)
	{
		if(field[Position-1])
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}
 
inline int checkRight()
{
	if(Position+1<fieldSize)
	{
		if(field[Position+1])
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}
 
inline int checkUpperLeft()
{
	if(Position-(fieldWidth+1)>0)
	{
		if(field[Position-(fieldWidth+1)])
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}
 
inline int checkUpperRight()
{
	if(Position-(fieldWidth-1)>0)
	{
		if(field[Position-(fieldWidth-1)])
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}
 
inline int checkLowerLeft()
{
	if(Position+(fieldWidth-1)<fieldSize)
	{
		if(field[Position+(fieldWidth-1)])
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}
 
inline int checkLowerRight()
{
	if(Position+(fieldWidth+1)<fieldSize)
	{
		if(field[Position+(fieldWidth+1)])
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

inline int totalAround()
{
	unsigned int around = checkUpper()+checkLower()+checkLeft()+checkRight()+checkUpperLeft()+checkUpperRight()+checkLowerLeft()+checkLowerRight();
	return around;
}

void makeRandomField(byte_type *field, int *rBright, int *gBright, int *bBright, int maxBright)
{
	int i = 0;
	int printWidth = 4;
	
	*rBright = rand()%maxBright;
	*gBright = rand()%maxBright;
	*bBright = rand()%maxBright;
	
	printf("max brightness %d \n", maxBright);
	printf("brightnes: %d %d %d\n",*rBright, *gBright, *bBright);
	
	while(i < FIELDSIZE)
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

inline void displayField(byte_type *field,int *rBright,int *gBright,int *bBright)
{
	int i;
	for(i = 0;i<FIELDSIZE;i++)
	{
		if(field[i])
			SET_LED(i, *rBright, *gBright, *bBright);
		else
			SET_LED(i, 0,0,0);
	}
	//int i=0;
	//while(i<FIELDSIZE)
	//{
		//if(field[i])
		//{
			//SET_LED(i, *rBright, *gBright, *bBright);
		//}
		//else
		//{
			//SET_LED(i, 0, 0, 0);
		//}
		//i++;
	//}
}

inline void DisplayField(byte_type *field,int position, int *rBright,int *gBright,int *bBright)
{
	if(field[position])
	{
		SET_LED(position, *rBright, *gBright, *bBright);
	}
	else
	{
		SET_LED(position, 0,0,0);
	}
}

inline void evolve(byte_type *field)
{
	if(field[Position])
	{
		if(totalAround() == surviveAbility || totalAround == surviveAbility+1)
		{
			field[Position] = 1;
		}
		else
		{
			field[Position] = 0;
		}
	}
	else
	{
		if(totalAround() == reproductiveNumber)
		{
			field[Position] = 1;
		}
	}
	Position++;
	if(Position==FIELDSIZE)
	{
		Position=0;
	}
}
unsigned int *rBrightness, *bBrightness, *gBrightness;
unsigned int maxBrightness = 40;

void init_pattern(char *dmx_universe)
{
	memset(dmx_universe, 0, 450);
	memset(field, 0, FIELDSIZE);
	
	makeRandomField(field, &rBrightness, &gBrightness, &bBrightness, maxBrightness);
	
}

void generate_pattern(char *dmx_universe)
{
	evolve(field);
	displayField(field, &rBrightness, &gBrightness, &bBrightness);
	//DisplayField(field,Position, &rBrightness, &gBrightness, &bBrightness);
}

