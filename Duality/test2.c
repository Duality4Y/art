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

#define byte_type unsigned char
#define FIELDSIZE 12
byte_type field[FIELDSIZE*FIELDSIZE];
byte_type temp_field[FIELDSIZE*FIELDSIZE];

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

void makeRandomField(byte_type *field, int *rBright, int *gBright, int *bBright, int maxBright)
{
	int i = 0;
	int printWidth = 4;
	
	*rBright = rand()%maxBright;
	*gBright = rand()%maxBright;
	*bBright = rand()%maxBright;
	
	//printf("max brightness %d \n", maxBright);
	//printf("brightnes: %d %d %d\n",*rBright, *gBright, *bBright);
	
	while(i < FIELDSIZE)
	{
		field[i] = rand()%2;
		
		//for a pretty print
		//printf("i:%d\tdata:%d\t\t",(int)i, (int)field[i]);
		//if(!(i%printWidth))
		//{
			//printf(" \n");
		//}
		i++;
	}
	//printf(" \n");
}

inline void displayField(byte_type *field,int *rBright,int *gBright,int *bBright)
{
	int i;
	for(i = FIELDSIZE;i--;)
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

unsigned int *rBrightness, *bBrightness, *gBrightness;
unsigned int maxBrightness = 40;

inline void init_pattern(char *dmx_universe)
{
	memset(dmx_universe, 0, 450);
	memset(field, 0, FIELDSIZE*FIELDSIZE);
	srand(time(0));
	makeRandomField(field, &rBrightness, &gBrightness, &bBrightness, maxBrightness);
	
}

inline void generate_pattern(char *dmx_universe)
{ 
	int i;
	char *fa, *fb, *tt, op;
	fa = field;
	fb = temp_field;
	
	displayField(fa, &rBrightness, &gBrightness, &bBrightness);
	evolve(fa, fb, FIELDSIZE);
	tt = fb; fb = fa; fa = tt;
}

