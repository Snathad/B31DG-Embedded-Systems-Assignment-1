# B31DG-Embedded-Systems-Assignment-1B31DG Embedded Software
Assignment 1
Charles Birdsall H00219071
Robotics MSc
Due: 10.02.2022
Abstract
This assignment involved the creation of a simple circuit featuring LED’s, switches, controlled by an ESP32 microcontroller. The LED’s were to blink in a pattern determined using an existing mathematical ruleset and programmed using C code. The switches could alter the effect of the blinking pattern. This was implemented successfully both on the physical board and using the code.
Contents
Introduction	1
Methodology	2
Results	3
Conclusion	4
Appendices	4
Appendix one: Nassi-Shneiderman Diagram	4
Appendix 2: The C code	6


Introduction
The ESP32 is a system on a chip microcontroller that behaves similarly to an Arduino and can utilise C code to control circuits.
 
Figure 1: The ESP32 Microcontroller (source: me).
The desired circuit used two light-emitting diodes, two resistors to protect the diodes and two push button switches in conjunction with the ESP32. The parts were placed into a breadboard following the circuit diagram provided in figure 2.
 
Figure 2: The circuit diagram for the assignment. (Source: The assignment brief B31DG Assignment 1).
The LED’s were to flash in a particular sequence determined by a mathematical ruleset based on the participants’ names. The first five letters of the users' surname were associated with corresponding numbers between one and thirteen (A to M = 1 to 13, N to Z = 13 to 1). Five values were found, the pulse width “a” (100 μS x the value of the first letter), gap between pulses “b” (100 μS x the value of the second letter), the number of pulses “c” (The value of the third letter plus four), the gap between one cycle and the next “d” (500 μS x the value of the fourth letter), and the mode (remainder of the fifth letter divided by four all plus one). The mode altered the effects of the second switch, in this case reducing the number of pulses in the cycle by three.
Methodology
Firstly, by the use of an excel spreadsheet, the particular values for the project were calculated.
Table 1: The letters, numbers, parameters and values calculated for the project.
Numbered letter of surname	Letter	Corresponding number	Parameter	Value
1st	B	2	A	200 μS
2nd	I	9	B	900 μS
3rd	R	9	C	13
4th	D	4	D	2000 μS
5th	S	8	Mode	1

It was then possible to create a plan of the code in the form of a Nassi-Shneiderman diagram using the Structorizer software, please see appendix one. 
The circuit was wired using a circuit development breadboard as seen in figure 3.
 
Figure 3: A picture of the completed circuit (source: me).
 Using the insight of the Nassi-Shneiderman diagram an attempt was made at developing the code. For the sake of simplicity, the coding was broken up into multiple segments: the light sequence itself, the behaviour when the first switch was pressed, and the behaviour when the second switch was pressed before finally all the parts were merged. Throughout the process, versions were saved to create a version history. For ease of testing, the code was originally made with increased time frames so that the flashing of the diodes would be visible to the naked eye as well as not so slow as to delay the testing process. This was put into microsecond time frames for the final version of the code.
The whole code can be seen in appendix two.

Results
The circuit operated as follows: 
•	Most of the time the circuit would run through a linear sequence of flashing the red LED, with increasing lengths of on time before flashing the green LED and waiting for the duration of the “d” variable before starting the cycle again.
•	If at any point in a cycle, the first button was pressed, the cycle would finish and when the next started the LED’s would not illuminate for the next cycle and onwards as long as the button was pressed or held within cycles. Only when the button was released and the duration of one cycle had passed, would the lights come on again in a cycle.
•	If at any point in a cycle the second switch was pushed, after the current cycle completed the next would have three fewer pulses than the original amount, staying at three pulses less until the pushbutton was released for a cycle and the next cycle could start with the full number of pulses.
The code proved to be successful following the above pattern. Significant issues were had, however, by the initial usage of delays which prevented the button inputs from registering so long as the delays continued. This was ultimately fixed by incorporating the board’s clock facility and the time.h library into a counter-based clock that could keep track of the pulses and handle delays without pausing the system. Flag variables enabled the system to keep track of whether or not a button had been pressed in that cycle or even the previous cycle to create a buffer that ensured the button had not been pressed again.
Initially, it was found that the button had to be pressed (and often held) at the exact moment a cycle ended and another started for its desired effects to take place in the next cycle. Making the code read directly from the inputs at the start of the code, the end of each pulse and again at the end of each cycle, allowed for the code to detect button presses most of the time so long as they were longer than the shortest pulse.

Conclusion
This project saw the creation of a simple circuit and a piece of code to blink LED’s in a sequence depending on whether particular inputs had been pressed. This was ultimately successful but not without first overcoming the challenges of reading the inputs constantly and while the system was trying to delay. In future work, the code could potentially be simplified by the removal of some redundant variables or by accurately incorporating updating variables from the inputs. Additionally, the code could likely be optimised to use less memory and run smoother.







Appendices
Appendix one: Nassi-Shneiderman Diagram
(Please see next page)
 
 
   
Appendix 2: The C code
//Charles Birdsall H00219071 10.2.22//
//B32DG Embedded Software Assignment1//
//Arduino sequence version 8: Complete and refined//
//The system operates through two LED's and a pair of pushbuttons. When the circuit is in its normal mode of operation the red light blinks in a particular sequence, with the green blinking to mark the end//
//points of each sequence. Pressing button one results in no output for the next loop of the sequence. Pressing button two alters the next loop of the sequence, in this case reducing its length by three.// 
//This version uses microseconds converted into milliseconds//

//The time library used
#include <time.h>


//Establish pins as variables
const int red_led = 15;
const int green_led = 21;
const int push_switch1 = 23;
const int push_switch2 = 22;

//Establish variables. a,b,c & d are used to define the lengths of pulses. Setmode means that three pulses can be subtracted from the total when button 2 is pressed//
const int a=0.2;
const int b=0.9;
int c=14;
const int d=2;
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

//this sub-function creates a delay based on the clock in the time library. A traditional delay was found to pause the whole code and prevent the button inputs form registering//
void delay2(int nosecs){
  clock_t start_time= clock(); //define the start time of the clock
  while (clock() < start_time + nosecs);  //adds the number of elapsed milliseconds on to the clock so timing can be calculated
}



void loop() {
  
  //Establish 2x variables to read in from the push switches
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
        delay2((a+(j*0.05))+b); //create a delay that increases by 50ms with each loop  
          
        if(j==c){  //the final part of the delay
          delay2(d+0.05);}

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
      delay2(a+(i*0.05)); //create a delay that increases by 50ms with each loop
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
      delay2 (0.05); //leave green led on for 50ms
      digitalWrite(green_led,LOW);   //turn green led off
      //reset the two switch flags if the switches are not pressed and have gone through a cycle following having been in their activated state.
      if (s1==2 && digitalRead(push_switch1)==LOW){
        s1=0;
        }
        
      if (s2==2 && digitalRead(push_switch2)==LOW){
        s2=0;  
        }}}}
