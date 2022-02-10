
//Charles Birdsall H00219071//
//B32DG Embedded Systems Assignment1//
//Aduino sequence version 3: simple with switch one input (enable/disable pulses) delays not quite right//
//Please note that this version of the code uses milliseconds instead of micro seconds//

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
const int s1=0;
void setup() {
//Establish pins as inputs or outputs  
pinMode(green_led, OUTPUT);
pinMode(red_led, OUTPUT);
pinMode(push_switch1, INPUT);
pinMode(push_switch2, INPUT);

}

void loop() {
  
int i;  //i counts the number of loops
int j;
//Establish 2x variables to read in from the pushswitches
int ps1s = digitalRead(push_switch1);
int ps2s = digitalRead(push_switch2);
if ((s1==0 || s1==2)&& ps1s==LOW){
  goto switch1inactive;}
else if (s1==1){
  goto switch1active;  
}
  

switch1inactive:
  for (i=0; i<c; i=i+1){  //This for loop counts as long as i is below the value of c and incrementally increases it by unity
    digitalWrite(red_led,HIGH); // turn red led on
    delay(a+(i*50)); //create a delay that increases by 50ms with each loop
    digitalWrite(red_led,LOW); //Turn red led off
    delay(b);} // wait the length of B between individual pulses
  
  if (ps1s==HIGH){
    digitalWrite(s1,1);
    digitalWrite(green_led,HIGH);
  }
  else if (ps1s==LOW){
    digitalWrite(s1,0);
    digitalWrite(green_led,LOW);
  }
    
  if (i==c){ //when i reaches the value of c
    delay (d); //wait for length d
    digitalWrite(green_led,HIGH);  //turn green led on
    delay (50); //leave green led on for 50ms
    digitalWrite(green_led,LOW);   //turn green led off
    if (s1==2 && ps1s==LOW){
      digitalWrite(s1,0);}
    
  }
  
switch1active:
  for (j=0; j<c; j=j+1){  //This for loop counts as long as i is below the value of c and incrementally increases it by unity
    delay((a+(j*50))+b);} //create a delay that increases by 50ms with each loop    
  if(i==c){
    delay(d+50);}
  
  if (ps1s==HIGH){  //if switch 1 is still high set s1 marker to high
    digitalWrite(s1,1);
  }
  else if (ps1s==LOW){ //if switch 1 is low set s1 marker to low
    digitalWrite(s1,2);
    }
    

    
}
