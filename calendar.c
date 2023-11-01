#include "at91sam3x8.h"
#include "system_sam3x.h"
#include <stdio.h>
#include "keypad.h"
#include "display.h"
#include "calendar.h"



int unsigned second, minute, hour, day, daysnumber, month, year;
int unsigned count =0, printValue = 0 , DaysCounter = 0 , minuteFlag = 0 , DayFlag = 0,hourFlag=0, dayflag = 0;
int unsigned D, M, Y, H, m, S, valu;


int SetDay(){
  
  for(int i = 10 ; i>0; i /=10){
       Delay(2000);
       
    while(readKeypad() == 0 );
          
          
          
       if (readKeypad() != 11)
    D += readKeypad()*i;

         count++;
       
       printCalendar(D, 2,0,0);
       
      
       while(readKeypad() != 0 );
             
       
  }
      
     day = D;
     D = 0;
     
    return day;
}




int SetMonth(){
  
   
  int a[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

  for(int i = 10 ; i>0; i /=10){
 
        Delay(2000);
   
    while(readKeypad() == 0 );
  
        
       if (readKeypad() != 11)
        M += readKeypad()*i;

         count++;

         
            printCalendar(M, 2,3,0);
         
         while(readKeypad() !=0 );
  
                }
  
          month = M;
            M = 0;
        
        daysnumber = a[month-1];
    
  return month;
}




int SetYear(){

  // we discuss all number in the year which are 4 numbers
 
  for(int i = 1000 ; i>0; i /=10){
       Delay(2000);
       
    while(readKeypad() == 0 ); //not pressed
    
        if (readKeypad() != 11)
       Y += readKeypad()*i;

         count++;
         
           printCalendar(Y, 4,6,0); 
        while(readKeypad() !=0 );
        
  }
  
     year = Y;
     Y = 0;
     
  return year;
}





int SetHour(){

  for(int i = 10 ; i>0; i /=10){
    
    Delay(2000);
    while(readKeypad() ==0 );
    
        if (readKeypad() != 11)
       H += readKeypad()*i;

         count++;
         
       
       printCalendar(H, 2,0,2);
         while(readKeypad() !=0 );
  }
  
     hour = H;
    H = 0;
       
  return hour;
}




int SetMinute(){

  for(int i = 10 ; i>0; i /=10){
      Delay(2000);
    while(readKeypad() ==0 );
    
        if (readKeypad() != 11)
   m += readKeypad()*i;

         count++;
           printCalendar(m, 2,3,2);
        while(readKeypad() !=0 );
  }
  
     minute = m;
     m = 0;
 
  return minute;
}




int SetSecond(){
  
  for(int i = 10 ; i>0; i /=10){
       
        Delay(2000);
   
         while(readKeypad() ==0 );
    
        if (readKeypad() != 11)
    S+= readKeypad()*i;

         count++;
         
           printCalendar(S, 2,6,2); 
         
      while(readKeypad() !=0 );
  
  }
 
     second = S;
     S = 0;
  return second;
}





void SetDateTime(){

  while (count < 14){
  
    
    if(readKeypad() == 0 &&count <2 )
      
      SetDay();

    if(count >=2 && count <4)
      
      SetMonth();
     
    if(count >=4 && count <8)
      
      SetYear();
  
    if(count >= 8 && count < 10)
      
      SetHour();
     
    if (count >= 10 && count < 12)
      SetMinute();
    
    if (count >= 12 && count < 14)
      
      SetSecond();
  
  }
  
  
}




// if second = 60 update minute and check all conditions.

void update(){

    second++;

    if (second == 60 ) {
       minute++;
       second = 0;
        minuteFlag = 1;
    
       

       if (minute == 60){
         hour++;
         minute = 0;
         hourFlag = 1;
         }
       
      if (hour == 24){
           day++;
       DayFlag = 1;
       dayflag = 1;
        DaysCounter++;
           hour = 0;
          
        }
       
       // wait for the end of the last day in the month.
      
       if(day == daysnumber + 1){
          month++;
          day = 1;
        
        }
          
        // wait for the end of the last month in the year.
        if (month == 13){
          year ++;
          month = 1;
        
        }

        }
    
    
    if (DaysCounter == 7){
      DaysCounter = 0;}
    
    if(second > 60)
      second = 0;
    
    if (minute > 60)
      minute = 0;
    
    if (hour > 24)
      hour = 0;
    
    if(day > 31)
      day = 1;
    
    if (month > 12)
       month = 1;
     
    
    
}


//print 

void printCalendar(int printvalue, int places,int x, int y){
  
     
  // used short for dont missing any information (480d need 9 bits).
  
   Write_Data_2_Display((unsigned short)  x + y*30);
    Write_Data_2_Display(((unsigned short)  x + y*30) >> 8);

     Write_Command_2_Display(0x24);// set address pointer
     
  // Calculate 10^places
  
     valu = 1;
     for(int i = 0; i < places; i++){
     valu *= 10;
  }

  for(int i=0; i<places; i++){
  
     printValue = (printvalue%valu)/(valu/10);
      
      Write_Data_2_Display(0x10 + printValue);
     Write_Command_2_Display(0xC0);

     valu /= 10;
  
  
  
  }



}


