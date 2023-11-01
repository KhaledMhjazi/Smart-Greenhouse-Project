#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "calendar.h"
#include "temp.h"
#include "LinkedList.h"


float min = 0, max = 0, average, SumTempInsert = 0;

unsigned int  min_max_day, min_max_month, min_max_year, insertCount, full = 0;
unsigned int  min_hour, min_minute, min_second, max_hour,max_minute, max_second,tempo;

float minArray[7],maxArray[7],Avg[7];


LinkedListt *List;
LinkedListt *temp;

DaysList dayArray[7]; // evrey index in this array save 9 values.





bool isFull(){
  
  if (full == 1){
    
    return true;}
     
       return false;}









void insertfirst (LinkedListt **first,float t,int ho,int mi,int se){


 temp = (LinkedListt *)malloc(sizeof(LinkedListt));


 if(temp == NULL){
   full = 1;

 } else {
  
   tempo++;

   temp-> hourss = ho;
  temp -> minutess = mi;
 temp-> secondss = se;
  temp->tempee = t;
  
  if (*first == NULL){
    
   temp-> next = NULL;
   *first = temp;
   }
 
  else {

 temp-> next = *first;
 *first = temp;}
 
 }
 
 
}



void RemoveLast (LinkedListt **first){
   
      
      LinkedListt *current = *first;
      LinkedListt *prev = NULL;
      
      
      while (current != NULL){
      
      
        if(current->next==NULL){
        
        prev->next=NULL;
    
         free(current);
    
        }
      
        prev = current;
        
       current = current->next;   
      }
      
   
          full = 0;
  }



  void put_temp(){

      

     if (DaysCounter < 7) {

          
             insertfirst(&List,temperature,hour, minute,second);
           
             if (isFull()){
               
              RemoveLast(&List);
              insertfirst(&List,temperature,hour, minute,second);
             }
              
              
             
              Min_Max_Average();
              
              minuteFlag =0;
            }

          }
        



  void Min_Max_Average(){

              insertCount++;
          SumTempInsert += temp->tempee;


       if (min == 0 && max == 0){

              min = temp->tempee;
              max = temp->tempee;

            min_max_day = day;
            min_max_month= month;
             min_max_year = year;
             
 
             max_hour = min_hour = temp-> hourss;
             max_minute = min_minute = temp->minutess; 
             max_second = min_second = temp-> secondss;
              
             
            }


            if (temp->tempee < min ) {
              
              min = temp->tempee;
              min_hour = temp-> hourss;
              min_minute = temp->minutess;
              min_second = temp-> secondss;

              }

            if (temp->tempee > max )  {
               
              max = temp->tempee;
             
              max_hour = temp-> hourss;
              max_minute= temp->minutess;
              max_second = temp-> secondss;}
       
                    
        if ( hour == 23 && minute == 59){


          average = SumTempInsert / insertCount;
          
           PutMinMaxAvg();
               
         
          SumTempInsert = 0;
          insertCount = 0;
          min = 0;
          max = 0;
          
        

       }

     }
   




void PutMinMaxAvg(){

  
 
  
    minArray[DaysCounter]= min;
    
    
    maxArray[DaysCounter]= max;
    
     Avg[DaysCounter]= average;
    
  
   dayArray[DaysCounter].days= min_max_day;
    dayArray[DaysCounter].months = min_max_month; 
     dayArray[DaysCounter].years= min_max_year;
     
      dayArray[DaysCounter].MaxHours= max_hour;
       dayArray[DaysCounter].MaxMinutes= max_minute;
         dayArray[DaysCounter].MaxSeconds= max_second;
         
      dayArray[DaysCounter].MinHours= min_hour;  
       dayArray[DaysCounter].MinMinutes= min_minute;
        dayArray[DaysCounter].MinSeconds= min_second;
  

}


 
