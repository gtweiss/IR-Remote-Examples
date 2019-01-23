//Import IR library: https://github.com/z3t0/Arduino-IRremote
//Author: Gordon Weiss
#include <IRremote.h>

//Set recieving pin in library
const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;

//Set Global variables
bool state = LOW;
bool state2 = LOW;
bool state3 = LOW;
long sigrec = 0;
int x = 255;

void setup(){
  //Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);

  //Pin Setup
  pinMode(9,OUTPUT);
  analogWrite(9, 0);
  pinMode(5,OUTPUT);
  analogWrite(5, 0);
  pinMode(6,OUTPUT);
  analogWrite(6, 0);
}

void loop(){

  //Collect results from IR sensor
  if (irrecv.decode(&results)){
        //Serial.println(results.value, HEX);
        sigrec = results.value;
        irrecv.resume();
  }

  //Read Results and flip bits
  if(sigrec == 0xFF30CF){
    state = !state;
  }
  else if(sigrec == 0xFF18E7){
    state2 = !state2;
  }
  else if(sigrec == 0xFF7A85){
    state3 = !state3;
  }
  else if(sigrec == 0xFFA857){
    if(x>50){
      x = x-50;
    }
    else{
      x=0;
    }
  }
  else if(sigrec == 0xFF906F){
    if(x<205){
      x = x+50;
    }
    else{
      x=255;
    }
  }

  //Update RGB LED
  analogWrite(9,state*x);
  analogWrite(5,state2*x);
  analogWrite(6,state3*x);

  //Reset signal recieved
  sigrec = 0;
}


