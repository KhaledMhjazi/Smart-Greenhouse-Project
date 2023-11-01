#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H


typedef struct DaysList {

unsigned int days:5;
unsigned int months:4;
unsigned int years:12;

unsigned int MaxHours:5;
unsigned int MaxMinutes:6;
unsigned int MaxSeconds:6;


unsigned int MinHours:5;
unsigned int MinMinutes:6;
unsigned int MinSeconds:6;

struct DaysList *next; } DaysList;




typedef struct LinkedListt {

float tempee;

unsigned int hourss:5;
unsigned int minutess:6;
unsigned int secondss:6;

struct LinkedListt *next; } LinkedListt;



void PutMinMaxAvg();
void RemoveLast (LinkedListt **first);
bool isFull();

void insertfirst (LinkedListt **first,float t,int ho,int mi,int se);

void put_temp();
void Min_Max_Average();

extern float min, max, average,minArray[7],maxArray[7],Avg[7];
extern unsigned int  min_max_day, min_max_month, min_max_year;
extern unsigned int  min_hour, min_minute, min_second, max_hour,max_minute, max_second;
extern DaysList dayArray[7];
#endif
