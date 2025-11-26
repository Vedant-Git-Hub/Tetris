#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "buff_op.h"
#include "port.h"
#include "game_intro.h"



#define B(b7,b6,b5,b4,b3,b2,b1,b0)		(128*b7 + 64*b6 + 32*b5 + 16*b4 + 8*b + 4*b2 + 2*b1 + 1*b0)

#define OUTLINE_X               		0
#define OUTLINE_Y               		0
#define OUTLINE_WIDTH           		40
#define OUTLINE_HEIGHT          		45

#define ARENA_X     				(OUTLINE_X + 1)
#define ARENA_Y					(OUTLINE_Y + 1)
#define ARENA_WIDTH             		(OUTLINE_WIDTH - 1)
#define ARENA_HEIGHT            		(OUTLINE_HEIGHT - 1)





void gameBorder(void);



int main()
{

    signalInit();
    termDisableEcho();
    termClearScrn();
    termSetCursorHome();
    
    introAnimation();
    
    while(1);
    
    if( !drawBuffInit(OUTLINE_WIDTH, OUTLINE_HEIGHT) )
    	return 0;
    
    gameBorder();

    while(1)
    {
        drawDisplayBuffer();
    }
    
    drawBuffDeinit();
    
    return 0;
}


void gameBorder()
{
    drawLine(OUTLINE_X, OUTLINE_Y, OUTLINE_WIDTH, HOR, ON);
    drawLine(OUTLINE_X, OUTLINE_Y, OUTLINE_HEIGHT, VER, ON);
    drawLine(OUTLINE_WIDTH - 1, OUTLINE_Y, OUTLINE_HEIGHT, VER, ON);
    drawLine(OUTLINE_X, OUTLINE_HEIGHT - 1, OUTLINE_WIDTH, HOR, ON);
}





