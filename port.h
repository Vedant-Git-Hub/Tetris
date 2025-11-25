#ifndef H_PORT_H
#define H_PORT_H





void signalInit(void);
void signalHandle(int signal);

void termDisableEcho(void);
void termClearScrn(void);
void termSetCursorHome(void);

void drawDisplayBuffer(void);









#endif
