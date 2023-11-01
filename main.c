#include "at91sam3x8.h"
#include "system_sam3x.h"
#include <stdio.h>
#include "stdlib.h"
#include "stdbool.h"
#include "servo.h"
#include "light.h"
#include "temp.h"
#include "keypad.h"
#include "display.h"
#include "calendar.h"
#include "LinkedList.h"
#include "sun.h"
#include "alarm.h"
#include "plot.h"


void Menu();


unsigned int timer = 0 , time = 0, menuFlag = 0;
unsigned int updateFlag, fastflag = 0, press2flag = 0,press1flag=0 ,press3flag = 0, press4flag = 0;


int main(){

  
  SystemInit();
 SysTick_Config((SystemCoreClock/1000)); //1ms
 displayConfig();
  keypadConfig();
  LedConfig();
 Init_Display();
  ClearDisplay();
 
  lightConfig();
  servoConfig();
  Init_PWM();
  
   ADC_Config();
   
    tempComfig();
  init_Temp();
  start_mesurement();
  
  printMenu();
  
   while(1){
     
        if(flag==1){
         Delay(100);
          readTemp();
          flag=0;
        }else if (time%500==0){
        
        start_mesurement();
        }
       
       
    if(minuteFlag == 1)
       put_temp();
       
   
      readKeypad(); 
       
       
     
   if(Aflag==1)
    ADC_Config();
   
    
      sun_led();
      
     
     if(counter == 4)
     SetAlarm();
     
     
      Menu();

   // rotate the servo every 10 minute in the fast mode.
    
   if ((minute % 10 == 0 && fastflag ==1) && (sun >= val2 || sun >= val1)  ){
     
        differntvalue();

        rotateServo(resultval);
    }
  
    // rotate the servo every seconed in normal mode.
   
   if ((updateFlag == 1 && fastflag == 0)&& (sun >= val2 || sun >= val1) ){
     
         differntvalue();
        rotateServo(resultval);
        updateFlag =0;
    }
  

     
    
   }
  
  
     
   return 0;}   
     

      


  
 
       
   


void Menu(){

   //pressing 1
  
  if(readKeypad()==1 && menuFlag == 0){
  
   
   ClearDisplay();
   press1flag=1;
    menuFlag = 1;
    
    plot(0,0,10,"DD/MM/YYYY");
       plot(0,2,8,"hh:mm:ss");
      SetDateTime();
       
  }

  
 if(press1flag==1 && readKeypad()==5){
    plot(0,0,10,"DD/MM/YYYY");
       plot(0,2,8,"hh:mm:ss");
             count = 0;
              SetDateTime();}
      
  
  // print the date and time every seconed in normal mode and every 10 ms in fast mode. 
  if ((press1flag==1 && timer%1000==0) || press1flag==1 && time % 10 ==0 ){
  
    DatePlot(); }
  
  
  
  //pressing 2
  
  if(readKeypad()==2 && menuFlag == 0){
    
     ClearDisplay();
     press2flag = 1;
      menuFlag = 1;
     
      printDayView();
      Print_Min_Max_Day();
      
     
  }
 
  
 
  if ( press2flag == 1 && dayflag == 1){
  
     Print_Min_Max_Day();
     
      dayflag = 0;
  }
  
  
  
   //pressing 3
  
  if(readKeypad()==3 && menuFlag == 0){
    
      ClearDisplay();
      press3flag = 1;
      menuFlag = 1;
      
      printLightSystem();
     
      }
  
  // print every 0.5s for update sun position on the screen.
  if(  press3flag == 1   && time % 500==0){
        
    printLightSystem();}
   
   
  
  //pressing 4
  
   if(readKeypad()==4 && menuFlag == 0){
   
     ClearDisplay();
       menuFlag = 1;
       press4flag = 1;
 
      plot(0,0,10,"Set Low:LL");
      plot(0,2,11,"Set High:HH");
      
       
      SetLowHigh();  
    AlarmPlot();}
       
       
             
  if(press4flag == 1 && readKeypad()==6 ){
      
      plot(0,0,10,"Set Low:LL");
      plot(0,2,11,"Set High:HH"); 
    counter = 0;    
    SetLowHigh();       
  }
        
       
 
             
             
             
// Fast Mode  
   
   if(readKeypad() ==11){
      fastflag =0; }
  

  if(readKeypad() ==12){
    fastflag =1;}
  

  
  // return to menu by pressing *
  if(readKeypad() == 10 && menuFlag == 1){
     
    ClearDisplay();
    press2flag = 0;
    press1flag=0;
    press3flag = 0;
    press4flag = 0;
    printMenu();
      menuFlag = 0;
  
  }
  
        


   }


 





void SysTick_Handler(void){
 
    time++; 
    
// update every 1ms.
    
  if (fastflag == 1){
   update();
  }
   
 else{
 
     timer++;
     
     // update every 1s.
     
    if (timer%1000==0) {
      update();
      updateFlag =1;
     }
      }
   
  
     
 //temperture 
  if(TempFlag ==1)
    countt++;
  if(countt == 15){
    countt =0;
    TempFlag =0;
  }
  
  }
 
  
 

  
