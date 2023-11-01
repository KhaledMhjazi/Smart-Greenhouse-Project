#ifndef _CALENDAR_H
#define _CALENDAR_H



int SetDay();
int SetMonth();
int SetYear();

int SetHour();
int SetMinute();
int SetSecond();
void SetDateTime();

void update();

void printCalendar(int printvalue, int places,int x, int y);

extern  unsigned int second, minute , hour,day ,month,  year,  daysnumber ; 
extern unsigned int printValue, DaysCounter, minuteFlag, DayFlag,hourFlag, count, dayflag;

#endif