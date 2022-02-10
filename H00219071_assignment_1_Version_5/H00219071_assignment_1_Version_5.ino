
//Charles Birdsall H00219071//
//B32DG Embedded Systems Assignment1//
//Aduino sequence version 5: simple with switch one input (enable/disable pulses) delays not quite right//
//Please note that this version of the code uses milliseconds instead of micro seconds//

#include <time.h>


//Establish pins as variables
const int red_led = 15;
const int green_led = 21;
const int push_switch1 = 23;
const int push_switch2 = 22;
//Establish variables
const int a=20;
const int b=90;
const int c=14;
const int d=200;
const int setmode=1;
int s1=0;
//int flag1;
void setup() {
//Establish pins as inputs or outputs  
pinMode(green_led, OUTPUT);
pinMode(red_led, OUTPUT);
pinMode(push_switch1, INPUT);
pinMode(push_switch2, INPUT);

}
void delay2(int nosecs){
  clock_t start_time= clock();
  while (clock() < start_time + nosecs);
}



void loop() {
//Establish 2x variables to read in from the pushswitches
int ps1s = digitalRead(push_switch1);
int ps2s = digitalRead(push_switch2);  
int i;  //i counts the number of loops
int j;


  
if(ps1s==HIGH){
      s1=1;
      //digitalWrite(green_led,LOW);
    }  
    
//if(s1==1 && flag1==1){
  if(ps1s==1||s1==1 ){
 
  for (j=0; j<c; j=j+1){  //This for loop counts as long as i is below the value of c and incrementally increases it by unity
    delay2((a+(j*50))+b); //create a delay that increases by 50ms with each loop    
  if(j==c){
    delay2(d+50);}
  
  if (ps1s==HIGH){  //if switch 1 is still high set s1 marker to high
    s1=1;
  }
  else if (ps1s==LOW){ //if switch 1 is low set s1 marker to low
    s1=2;
    //flag1=0;
    }}}
else if (s1!=1 && ps1s==LOW){
  //flag1=0;
  for (i=0; i<c; i=i+1){  //This for loop counts as long as i is below the value of c and incrementally increases it by unity
    digitalWrite(red_led,HIGH); // turn red led on
    delay2(a+(i*50)); //create a delay that increases by 50ms with each loop
    digitalWrite(red_led,LOW); //Turn red led off
    delay2(b);// wait the length of B between individual pulses
  
     if (digitalRead(push_switch1)==HIGH){
      s1=1;
       } 
      } 
      
    if (digitalRead(push_switch1)==HIGH){
      s1=1;
      }  
 
    
    
  if (i==c){ //when i reaches the value of c
    delay2 (d); //wait for length d
    digitalWrite(green_led,HIGH);  //turn green led on
    delay2 (50); //leave green led on for 50ms
    digitalWrite(green_led,LOW);   //turn green led off
    if (s1==2 && ps1s==LOW){
      s1=0;}
    //flag1=1;  
 
  }
  }}

  


    
