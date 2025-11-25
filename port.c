#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <termios.h>

#include "buff_op.h"
#include "port.h"




static struct termios old_tio, new_tio;








void drawDisplayBuffer()
{
    termSetCursorHome();
    
    uint8_t *display_buffer = getDrawBuffer();
    
    if( !display_buffer )
    	return;

    for(uint8_t row = 0; row < getDrawBuffHeight(); row++)
    {
        for(uint8_t col = 0; col < (getDrawBuffWidth() / 8); col++)
        {
            uint8_t temp = display_buffer[(row * (getDrawBuffWidth() / 8)) + col];
            
            for(int8_t shift = 7; shift >= 0; shift--)
            {
                if( (temp >> shift) & 0x01)
                {
                    printf("█");
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

void termSetCursorHome()
{
    printf("\033[H");
}

void termClearScrn()
{
    printf("\033[2J");
}

void signalInit(void)
{
    signal(SIGINT, signalHandle);
    signal(SIGTERM, signalHandle);
    signal(SIGQUIT, signalHandle);
    signal(SIGHUP, signalHandle);
}

void signalHandle(int signal)
{
    signal++;
    termClearScrn();
    termSetCursorHome();
    drawBuffDeinit();
    exit(0);
}
