#ifndef _DISPLAY_H
#define _DISPLAY_H


void displayConfig();
void Init_Display(void);
void Delay(int Value);
unsigned char Read_Status_Display(void);
void Write_Command_2_Display(unsigned char Command);
void Write_Data_2_Display(unsigned char Data);
void ClearDisplay();
void print(unsigned char key );



#endif
