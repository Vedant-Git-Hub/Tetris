#ifndef H_BUFF_OP_H
#define H_BUFF_OP_H

typedef enum{
    OFF = 0,
    ON,
    TOGGLE
}E_PIX_STATE;

typedef enum{
    HOR = 0,
    VER
}E_LINE_TYPE;





bool drawBuffInit(uint8_t pixel_x, uint8_t pixel_y);
uint8_t getDrawBuffWidth(void);
uint8_t getDrawBuffHeight(void);
uint8_t *getDrawBuffer(void);
void drawPixel(uint8_t x, uint8_t y, uint8_t state);
void drawLine(uint8_t x, uint8_t y, uint8_t length, E_LINE_TYPE ori, E_PIX_STATE state);
void drawBuffDeinit(void);


#endif
