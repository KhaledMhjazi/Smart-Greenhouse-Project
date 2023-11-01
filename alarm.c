#include "at91sam3x8.h"
#include "system_sam3x.h"
#include "stdio.h"
#include "stdlib.h"
#include "temp.h"
#include "keypad.h"
#include "sun.h"
#include "calendar.h"
#include "display.h"

unsigned int Low, High ,counter = 0,vall =0;



int SetLowTemp(){

  
  for(int i = 10 ; i>0; i /=10){
           Delay(2000);
    while(readKeypad() ==0 );
    
        if (readKeypad() != 11)
       vall += readKeypad()*i;

         counter++;
         printCalendar(vall, 2,8,0);
       
         while(readKeypad() !=0 );
  }
  
     Low = vall;
   vall = 0;
     
  return Low;
}




int SetHighTemp(){

  for(int i = 10 ; i>0; i /=10){
            Delay(2000);
    while(readKeypad() ==0 );
    
        if (readKeypad() != 11)
       vall += readKeypad()*i;

         counter++;
        printCalendar(vall, 2,9,2);
         while(readKeypad() !=0 );
  }
  
    High= vall;
   vall = 0;
     
  return High;
}





void SetLowHigh(){

  while ( counter < 4){
  
    if(readKeypad() == 0 && counter <2 )
      
      SetLowTemp();
    
    if(counter >=2 && counter <4)
      
      SetHighTemp();}
  
  
  
}



void SetAlarm(){

  if(temperature < Low || temperature > High){
    
    
     Set_Led1(1);
       }
  
  if(readKeypad() == 7){
       Set_Led1(0);}
 
}