#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "buff_op.h"





static uint8_t *display_buffer = NULL;
static uint8_t buff_x = 0;
static uint8_t buff_y = 0;





bool drawBuffInit(uint8_t pixel_x, uint8_t pixel_y)
{
	display_buffer = (uint8_t *)malloc((pixel_x / 8) * pixel_y);
	
	if( !display_buffer )
		return 0;
		
	buff_x = pixel_x / 8;
	buff_y = pixel_y;
		
	return 1;	
}

uint8_t *getDrawBuffer()
{
	return display_buffer;
}

uint8_t getDrawBuffWidth()
{
	return buff_x * 8;
}

uint8_t getDrawBuffHeight()
{
	return buff_y;
}

void drawLine(uint8_t x, uint8_t y, uint8_t length, E_LINE_TYPE ori, E_PIX_STATE state)
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
            display_buffer[ (y * buff_x) + (uint8_t)(x / 8) ] |= (1 << (7 - (x & 0x07)));
            break;

        case OFF:
            display_buffer[ (y * buff_x) + (uint8_t)(x / 8) ] &= ~(1 << (7 - (x & 0x07)));
            break;

        case TOGGLE:
            display_buffer[ (y * buff_x) + (uint8_t)(x / 8) ] ^= (1 << (7 - (x & 0x07)));
            break;
    }
}

void drawBuffDeinit()
{
	if(display_buffer)
	{
		free(display_buffer);
	}
}
