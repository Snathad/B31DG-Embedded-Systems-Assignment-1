
//Charles Birdsall H00219071 10.2.22//
//B32DG Embedded Systems Assignment1//
//Aduino sequence version 7: Complete and refined//
//The system operates through two LED's and a pair of push buttons. When the circuit is in its normal mode of operation the red light blinks in a particular sequence, with the green blinking to mark the end//
//points of each sequence. Pressing button one results in no output for the next loop of the sequence. Pressing button two alters the next loop of the sequence, in this case reducing its length by three.// 
//This version uses milliseconds (at a scale of one tenth for speed) for the sake of testing//

//The time library used
#include <time.h>


//Establish pins as variables
const int red_led = 15;
const int green_led = 21;
const int push_switch1 = 23;
const int push_switch2 = 22;

//Establish variables. a,b,c & d are used to define the lengths of pulses. Setmode means that three pulses can be subtracted form the totla when buttopn 2 is pressed//
const int a=20;
const int b=90;
int c=14;
const int d=200;
const int setmode=1;
//S1 and s2 are used as flags for if respective switches were pressed during a cycle
int s1=0;
int s2=0;


void setup() {
  //Establish pins as inputs or outputs  
  pinMode(green_led, OUTPUT);
  pinMode(red_led, OUTPUT);
  pinMode(push_switch1, INPUT);
  pinMode(push_switch2, INPUT);
}

//this subfunction creates a delay based on the clock in the time library. A traditional delay was found to pause the whole code and prevent the button inputs form registering//
void delay2(int nosecs){
  clock_t start_time= clock(); //define the start time of the clock
  while (clock() < start_time + nosecs);  //adds the number of elapsed milliseconds on to the clock so timing can be calculated
}



void loop() {
  
  //Establish 2x variables to read in from the pushswitches
  int ps1s = digitalRead(push_switch1);
  int ps2s = digitalRead(push_switch2);  
  int i;  //i counts the number of loops in the regular operation loop
  int j;  //j counts the number of loops in the suspended operation loop
  
  
  //If the switch1 read is high set the switch 1 flag to be 1  
  if(ps1s==HIGH){
        s1=1;
      }
      
  //If the switch2 read is high set the switch 2 flag to be 1 
  if(ps2s==HIGH){
        s2=1; 
        }     

////////////////////////////////////////////////////////////////////////////////
//The part of the code for the inactive state loop//      
  //If switch one reads as high or flag one reads as high then:
    if(digitalRead(push_switch1)||s1==1 ){
    
      if (s2==1){  //If switch 2 flag =1 then set c to its reduced form
        c=10;
      }
      
      else if (s2!=1){   //If switch 2 flag is not equal to one set to c to its regular form
        c=13;
        }
      
      for (j=0; j<c; j=j+1){  //This for loop counts as long as i is below the value of c and incrementally increases it by unity
        delay2((a+(j*50))+b); //create a delay that increases by 50ms with each loop  
          
        if(j==c){  //the final part of the delay
          delay2(d+50);}

        //If the switch is still high set switch flag 1 to be 1 or else set it to 2 (represents that switch is not pressed but was previous loop)
        if (digitalRead(push_switch1)==HIGH){  //if switch 1 is still high set s1 marker to high
          s1=1;
        }
        
        else if (digitalRead(push_switch1)==LOW){ //if switch 1 is low set s1 marker to low
          s1=2;
          }
          
        //If the switch is still high set switch flag 2 to be 1 or else set it to 2 (represents that switch is not pressed but was previous loop  
        if (digitalRead(push_switch2)==HIGH){  //if switch 1 is still high set s2 marker to high
          s2=1;
        }
        
        else if (digitalRead(push_switch2)==LOW){ //if switch 1 is low set s1 marker to low
          s2=2;
        }
        }
        }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //The part of code for the active loop
  //If switch flag one is not equal to one and the first switch is low    
  else if (s1!=1 && digitalRead(push_switch1)==LOW){
    
    if (s2==1){//If switch flag 2 is 1 reduce c
      c=10;
    }
    
    else if (s2!=1){  //If switch 2 flag is not 1 leave c as its default value
      c=13;
      }
      
    for (i=0; i<c; i=i+1){  //This for loop counts as long as i is below the value of c and incrementally increases it by unity
      digitalWrite(red_led,HIGH); // turn red led on
      delay2(a+(i*50)); //create a delay that increases by 50ms with each loop
      digitalWrite(red_led,LOW); //Turn red led off
      delay2(b);// wait the length of B between individual pulses
    
       if (digitalRead(push_switch1)==HIGH){   //detect if switch 1 is pressed inside of the for loop
        s1=1;
         }
         
       if (digitalRead(push_switch2)==HIGH){  //detect if switch 2 is pressed inside of the for loop
        s2=1;
         } 
        } 
        
   if (digitalRead(push_switch1)==HIGH){ //detect if switch one is pressed outside of the main loop
        s1=1;
        }  
   if (digitalRead(push_switch2)==HIGH){  //detect if switch two is pressed outside of the main loop
        s2=1;
         }
      
      
    if (i==c){ //when i reaches the value of c
      delay2 (d); //wait for length d
      digitalWrite(green_led,HIGH);  //turn green led on
      delay2 (50); //leave green led on for 50ms
      digitalWrite(green_led,LOW);   //turn green led off
      //reset the two switch flags if the switches are not pressed and have gone through a cycle following having beeen in their activated state.
      if (s1==2 && digitalRead(push_switch1)==LOW){
        s1=0;
        }
        
      if (s2==2 && digitalRead(push_switch2)==LOW){
        s2=0;  
        }
      }
    }
  }
  
    
  
  
      
