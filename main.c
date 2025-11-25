#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <termios.h>


#define B(b7,b6,b5,b4,b3,b2,b1,b0)		(128*b7 + \
                						 64*b6  + \
				                		 32*b5  + \
					 	                 16*b4  + \
						                  8*b3	+ \
						                  4*b2  + \
						                  2*b1  + \
						                  1*b0)


#define OUTLINE_X               0
#define OUTLINE_Y               0
#define OUTLINE_WIDTH           40
#define OUTLINE_HEIGHT          48

#define ARENA_X     			(OUTLINE_X + 1)
#define ARENA_Y				    (OUTLINE_Y + 1)
#define ARENA_WIDTH             (OUTLINE_WIDTH - 1)
#define ARENA_HEIGHT            (OUTLINE_HEIGHT - 1)



enum{
    OFF = 0,
    ON,
    TOGGLE
};

enum{
    HOR = 0,
    VER
};



static struct termios old_tio, new_tio;

static uint8_t display_buffer[OUTLINE_HEIGHT][OUTLINE_WIDTH / 8];




static void signalInit(void);
static void signalHandle(int signal);

static void termDisableEcho(void);
static void termClearScrn(void);
static void termSetCursorHome(void);

void drawDisplayBuffer(void);
void drawPixel(uint8_t x, uint8_t y, uint8_t state);
void drawLine(uint8_t x, uint8_t y, uint8_t length, uint8_t ori, uint8_t state);

void gameBorder(void);



int main()
{

    signalInit();
    termDisableEcho();
    
    gameBorder();

	while(1)
    {
        drawDisplayBuffer();
    }
	return 0;
}

void gameBorder()
{
    drawLine(OUTLINE_X, OUTLINE_Y, OUTLINE_WIDTH, HOR, ON);
    drawLine(OUTLINE_X, OUTLINE_Y, OUTLINE_HEIGHT, VER, ON);
    drawLine(OUTLINE_WIDTH - 1, OUTLINE_Y, OUTLINE_HEIGHT, VER, ON);
    drawLine(OUTLINE_X, OUTLINE_HEIGHT - 1, OUTLINE_WIDTH, HOR, ON);
}

void drawLine(uint8_t x, uint8_t y, uint8_t length, uint8_t ori, uint8_t state)
{
    for(uint8_t start = 0; start < length; start++)
    {
        switch(ori)
        {
            case HOR:
                drawPixel(x + start, y, state);
                break;

            case VER:
                drawPixel(x, y + start, state);
                break;
        }
    }
}


void drawPixel(uint8_t x, uint8_t y, uint8_t state)
{
    switch( state )
    {
        case ON:
            display_buffer[ y ][ (uint8_t)(x / 8) ] |= (1 << (7 - (x & 0x07)));
            break;

        case OFF:
            display_buffer[ y ][ (uint8_t)(x / 8) ] &= ~(1 << (7 - (x & 0x07)));
            break;

        case TOGGLE:
            display_buffer[ y ][ (uint8_t)(x / 8) ] ^= (1 << (7 - (x & 0x07)));
            break;
    }
}


void drawDisplayBuffer()
{
    termSetCursorHome();

    for(uint8_t row = 0; row < OUTLINE_HEIGHT; row++)
    {
        for(uint8_t col = 0; col < (OUTLINE_WIDTH / 8); col++)
        {
            uint8_t temp = display_buffer[row][col];
            
            for(int8_t shift = 7; shift >= 0; shift--)
            {
                if( (temp >> shift) & 0x01)
                {
                    printf("#");
                }
                else
                {
                    printf(" ");
                }
            }
        }

        printf("\n");
    }
}


void termDisableEchoHandle() 
{
    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
}

void termDisableEcho()
{
    tcgetattr(STDIN_FILENO, &old_tio);    
    new_tio = old_tio;

    new_tio.c_lflag &= ~(ECHO);         
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);

    atexit(termDisableEchoHandle);
}

static void termSetCursorHome()
{
    printf("\033[H");
}

static void termClearScrn()
{
    printf("\033[2J");
}

static void signalInit(void)
{
    signal(SIGINT, signalHandle);
}

static void signalHandle(int signal)
{
    termClearScrn();
    termSetCursorHome();
    exit(0);
}
