#include <stdio.h>
#include <time.h>

#include "artdmx.h"
#include "dmxmain.h"

#define numStars 4
#define tailLen 5

/*149- for one direction and nothing for the other*/
#define direction 149-

void set_led(int ch, int r, int g, int b, unsigned char *universe)
{
	int c = direction(ch);
	universe[c*3] = r;
	universe[c*3+1] = g;
	universe[c*3+2] = b;
}

int i = 1;
int led = 0;
int lastLed = 0;
int pos = 0;
int width = 7;

struct Star 
{
	int pos;
	int line;
	int tail[tailLen];
}fallingStars[numStars];

void init_pattern(char *dmx_universe)
{
	memset(dmx_universe, 0, 450);
	srand(time(0));
	
	//set up star attributes.
	for(i = 0;i<numStars;i++)
	{
		//for every star set pos 0
		fallingStars[i].pos = 0;
		/* for every star set it on a random line
		 * and while not the first star which is 0, 
		 * and the previous stars random line is the same as the current
		 * */
		int randomint = rand()%7;
		while(i!=0 && fallingStars[i-1].line != randomint)
		{
			randomint = rand()%7;
		}
		fallingStars[i].line = randomint;
		//Check which numbers we got (debugging)
		printf("the random int: %d \n", fallingStars[i].line);
		//clear every tail.
		memset(fallingStars[i].tail, 0, tailLen);
	}
}

void generate_pattern(char *dmx_universe)
{
	//fallingStars[0].pos++;
	//if(fallingStars[0].pos > 150)
	//{
		//fallingStars[0].pos -= 150;
	//}
	//if(!(fallingStars[0].pos%21))
		//{
			//fallingStars[0].line++;
		//if(fallingStars[0].line > 7)
		//{
			//fallingStars[0].line -= 7;
		//}
	//}
	//led = ((fallingStars[0].pos%21)*7)+fallingStars[0].line;
	//if(led < 150)
	//{
		//set_led(led-1, 0,0,0, dmx_universe);
		//set_led(led, 10,10,10, dmx_universe);
	//}
}

