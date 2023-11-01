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


// print in the screen

void plot (int x, int y , int size, char * value ){
        
       
   Write_Data_2_Display((unsigned short)  x + y*30);
    Write_Data_2_Display(((unsigned short)  x + y*30) >> 8);

     Write_Command_2_Display(0x24);// set address pointer
     
     
       
   for (int i =0 ;i<size;i++){

       Write_Data_2_Display(value[i] - 0x20);// 0x20 is the ASCII value for the space character ''.

       
     Write_Command_2_Display(0xC0);// data write and increment ADP
       
     }
 
  }



// print the menu that contains all data that we need.
void printMenu(){
  
  
        
     plot(0,0,6,"Khaled");
     plot(13,2,4,"Menu");
     plot(26,0,4,"Hind");
     
  plot(0,6,20,"1.Set Date And Time.");
  plot(0,8,21,"2.Temperature System.");
  plot(0,10,18,"3.Lighting System.");
   plot(0,12,12,"4.Set Alarm.");
  
   
   plot(0,14,14,"0.Normal Mode.");
    plot(18,14,12,"#.Fast Mode.");
   
 


}


// print light System and sun position and if shades on or off.
void printLightSystem(){

 char s [30] ;

    
     if(resultval >= 100){
      plot(0,0,13,"Sun Position:");
       sprintf(s,"%d",resultval);
       plot(13,0,3,s);}
 
     else{
      plot(0,0,14,"Sun Position: ");
       sprintf(s,"%d",resultval);
       plot(14,0,2,s);}
     
       plot(17,0,7,"Degrees");
        
         if (sunTime >= 10){
        
           plot(0,2,9,"Sun time:");
       sprintf(s,"%d",sunTime);
       plot(9,2,2,s);}
       
         else{ 
        plot(0,2,10,"Sun time: ");
       sprintf(s,"%d",sunTime);
       plot(10,2,1,s);}
       
        
        if (ledTime >= 10){
       plot(0,4,9,"Led time:");
      sprintf(s,"%d",ledTime);
      plot(9,4,2,s);}
      
      else {
          plot(0,4,10,"Led time: ");
          sprintf(s,"%d",ledTime);
          plot(10,4,1,s);}
        

      
       plot(0,6,9,"Darkness:");
      sprintf(s,"%d",darkness);
      plot(9,6,1,s);
      
           
      if ( shadOnflag ==1){
    
         plot(0,10,19,"Turn on the shades.");
       
        }
    
     if( shadOffFlag==1){
        plot(0,10,20,"Turn off the shades.");
     }
    
      

     plot(0,14,15,"*.Back To Menu.");


}

      
// plot date and time.

 void DatePlot(){
     
  printCalendar(day,2,0,0);
  printCalendar(month,2,3,0);
  printCalendar(year,4,6,0);
  printCalendar(hour,2,0,2);
  printCalendar(minute,2,3,2);
  printCalendar(second,2,6,2);
  
    plot(0,12,23,"5.Change Date And Time.");

 plot(0,14,15,"*.Back To Menu.");
}
       
 // plot the low and high temerature. 
void AlarmPlot(){

 printCalendar(Low,2,8,0);
  printCalendar(High,2,9,2);
   
     plot(0,10,14,"6.Change Alarm");
   plot(0,12,8,"7.Reset.");
   plot(0,14,15,"*.Back To Menu.");




}

// print the general format of temperature.
void printDayView(){


  plot(0,0,10,"DD/MM/YYYY");
  plot(11,0,4,"Min:");
  plot(20,0,2,"T:");
  plot(22,0,8,"hh:mm:ss");

  plot(0,1,4,"Avg:");
  
   plot(11,1,4,"Max:");
  plot(20,1,2,"T:");
  plot(22,1,8,"hh:mm:ss");
  
 
plot(0,2,10,"DD/MM/YYYY");
  plot(11,2,4,"Min:");
  plot(20,2,2,"T:");
  plot(22,2,8,"hh:mm:ss");

  plot(0,3,4,"Avg:");
  
   plot(11,3,4,"Max:");
  plot(20,3,2,"T:");
  plot(22,3,8,"hh:mm:ss");


 plot(0,5,10,"DD/MM/YYYY");
  plot(11,5,4,"Min:");
  plot(20,5,2,"T:");
  plot(22,5,8,"hh:mm:ss");

  plot(0,6,4,"Avg:");
  
   plot(11,6,4,"Max:");
  plot(20,6,2,"T:");
  plot(22,6,8,"hh:mm:ss");


  plot(0,7,10,"DD/MM/YYYY");
  plot(11,7,4,"Min:");
  plot(20,7,2,"T:");
  plot(22,7,8,"hh:mm:ss");

  plot(0,8,4,"Avg:");
  
   plot(11,8,4,"Max:");
  plot(20,8,2,"T:");
  plot(22,8,8,"hh:mm:ss");

  
   
   plot(0,10,10,"DD/MM/YYYY");
  plot(11,10,4,"Min:");
  plot(20,10,2,"T:");
  plot(22,10,8,"hh:mm:ss");

  plot(0,11,4,"Avg:");
  
   plot(11,11,4,"Max:");
  plot(20,11,2,"T:");
  plot(22,11,8,"hh:mm:ss");
   
   
   plot(0,12,10,"DD/MM/YYYY");
  plot(11,12,4,"Min:");
  plot(20,12,2,"T:");
  plot(22,12,8,"hh:mm:ss");

  plot(0,13,4,"Avg:");
  
   plot(11,13,4,"Max:");
  plot(20,13,2,"T:");
  plot(22,13,8,"hh:mm:ss");
   
plot(0,14,10,"DD/MM/YYYY");
  plot(11,14,4,"Min:");
  plot(20,14,2,"T:");
  plot(22,14,8,"hh:mm:ss");

  plot(0,15,4,"Avg:");
  
   plot(11,15,4,"Max:");
  plot(20,15,2,"T:");
  plot(22,15,8,"hh:mm:ss");

  
  

}

  //print min and max value for temperature with the date and time for every day.

  void Print_Min_Max_Day(){
//DAY1
  printCalendar(dayArray[0].days,2,0,0);
  printCalendar(dayArray[0].months,2,3,0);
  printCalendar(dayArray[0].years,4,6,0);
  
  printCalendar(dayArray[0].MinHours,2,22,0);
  printCalendar(dayArray[0].MinMinutes,2,25,0);
  printCalendar(dayArray[0].MinSeconds,2,28,0);
  
  printCalendar(dayArray[0].MaxHours,2,22,1);
  printCalendar(dayArray[0].MaxMinutes,2,25,1);
  printCalendar(dayArray[0].MaxSeconds,2,28,1);
 
  char s[30];
  
  sprintf(s,"%f",minArray[0]);
       plot(15,0,4,s);
  
  
 sprintf(s,"%f",maxArray[0]);
       plot(15,1,4,s);
       
        sprintf(s,"%f",Avg[0]);
       plot(5,1,4,s);
       
//DAY2
       
  printCalendar(dayArray[1].days,2,0,2);
  printCalendar(dayArray[1].months,2,3,2);
  printCalendar(dayArray[1].years,4,6,2);
  
  printCalendar(dayArray[1].MinHours,2,22,2);
  printCalendar(dayArray[1].MinMinutes,2,25,2);
  printCalendar(dayArray[1].MinSeconds,2,28,2);
  
  printCalendar(dayArray[1].MaxHours,2,22,3);
  printCalendar(dayArray[1].MaxMinutes,2,25,3);
  printCalendar(dayArray[1].MaxSeconds,2,28,3);
 
  
  sprintf(s,"%f",minArray[1]);
       plot(15,2,4,s);
  
  
 sprintf(s,"%f",maxArray[1]);
       plot(15,3,4,s);
       
        sprintf(s,"%f",Avg[1]);
       plot(5,3,4,s);
       
//DAY3
   printCalendar(dayArray[2].days,2,0,5);
  printCalendar(dayArray[2].months,2,3,5);
  printCalendar(dayArray[2].years,4,6,5);
  
  printCalendar(dayArray[2].MinHours,2,22,5);
  printCalendar(dayArray[2].MinMinutes,2,25,5);
  printCalendar(dayArray[2].MinSeconds,2,28,5);
  
  printCalendar(dayArray[2].MaxHours,2,22,6);
  printCalendar(dayArray[2].MaxMinutes,2,25,6);
  printCalendar(dayArray[2].MaxSeconds,2,28,6);
 
  
  sprintf(s,"%f",minArray[2]);
       plot(15,5,4,s);
  
  
 sprintf(s,"%f",maxArray[2]);
       plot(15,6,4,s);
       
        sprintf(s,"%f",Avg[2]);
       plot(5,6,4,s);
       
  //DAY4
        
  printCalendar(dayArray[3].days,2,0,7);
  printCalendar(dayArray[3].months,2,3,7);
  printCalendar(dayArray[3].years,4,6,7);
  
  printCalendar(dayArray[3].MinHours,2,22,7);
  printCalendar(dayArray[3].MinMinutes,2,25,7);
  printCalendar(dayArray[3].MinSeconds,2,28,7);
  
  printCalendar(dayArray[3].MaxHours,2,22,8);
  printCalendar(dayArray[3].MaxMinutes,2,25,8);
  printCalendar(dayArray[3].MaxSeconds,2,28,8);
 
 
  
  sprintf(s,"%f",minArray[3]);
       plot(15,7,4,s);
  
  
 sprintf(s,"%f",maxArray[3]);
       plot(15,8,4,s);
       
        sprintf(s,"%f",Avg[3]);
       plot(5,8,4,s); 

       
       
   //DAY5
       
  printCalendar(dayArray[4].days,2,0,10);
  printCalendar(dayArray[4].months,2,3,10);
  printCalendar(dayArray[4].years,4,6,10);
  
  printCalendar(dayArray[4].MinHours,2,22,10);
  printCalendar(dayArray[4].MinMinutes,2,25,10);
  printCalendar(dayArray[4].MinSeconds,2,28,10);
  
  printCalendar(dayArray[4].MaxHours,2,22,11);
  printCalendar(dayArray[4].MaxMinutes,2,25,11);
  printCalendar(dayArray[4].MaxSeconds,2,28,11);
 

  
  sprintf(s,"%f",minArray[4]);
       plot(15,10,4,s);
  
  
 sprintf(s,"%f",maxArray[4]);
       plot(15,11,4,s);
       
        sprintf(s,"%f",Avg[4]);
       plot(5,11,4,s); 
       
 //DAY6
  printCalendar(dayArray[5].days,2,0,12);
  printCalendar(dayArray[5].months,2,3,12);
  printCalendar(dayArray[5].years,4,6,12);
  
  printCalendar(dayArray[5].MinHours,2,22,12);
  printCalendar(dayArray[5].MinMinutes,2,25,12);
  printCalendar(dayArray[5].MinSeconds,2,28,12);
  
  printCalendar(dayArray[5].MaxHours,2,22,13);
  printCalendar(dayArray[5].MaxMinutes,2,25,13);
  printCalendar(dayArray[5].MaxSeconds,2,28,13);
 

  
  sprintf(s,"%f",minArray[5]);
       plot(15,12,4,s);
  
  
 sprintf(s,"%f",maxArray[5]);
       plot(15,13,4,s);
       
        sprintf(s,"%f",Avg[5]);
       plot(5,13,4,s);  
       
   //DAY7
   printCalendar(dayArray[6].days,2,0,14);
  printCalendar(dayArray[6].months,2,3,14);
  printCalendar(dayArray[6].years,4,6,14);
  
  printCalendar(dayArray[6].MinHours,2,22,14);
  printCalendar(dayArray[6].MinMinutes,2,25,14);
  printCalendar(dayArray[6].MinSeconds,2,28,14);
  
  printCalendar(dayArray[6].MaxHours,2,22,15);
  printCalendar(dayArray[6].MaxMinutes,2,25,15);
  printCalendar(dayArray[6].MaxSeconds,2,28,15);
 

  
  sprintf(s,"%f",minArray[6]);
       plot(15,14,4,s);
  
  
 sprintf(s,"%f",maxArray[6]);
       plot(15,15,4,s);
       
        sprintf(s,"%f",Avg[6]);
       plot(5,15,4,s);      
       
}

     
   
