/*
 * Arduino Menorah
 * Simulates a Hanukkah Menorah using LED's and a Button
 * Click the button to light the candles!2018
 * based on code by Liz Miller
 * added code by Debbie Sleeper
 * 
 */

//define global variables
const int button = 12;     
const int start = 2;
const int shamash = 10;
int count = 0;
bool off = true;

int state = HIGH;   
int buttonState;            
int lastButtonState = LOW;   
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

//setup all pins as OUTPUTS and give initial state (off)
void allPlay(int delayTime){
    for(int pin=start; pin<10; pin++){
      pinMode(pin, OUTPUT);
      digitalWrite(pin, HIGH);
      delay(delayTime);
      Serial.println(pin);
      digitalWrite(pin, LOW);
    }
}

 void allBack(int delayTime){
  for(int pin=10; pin>start; pin--){
      pinMode(pin, OUTPUT);
      digitalWrite(pin, HIGH);
      delay(delayTime);
      Serial.println(pin);
      digitalWrite(pin, LOW);
    }
  }

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Initializing...");
  pinMode(shamash,OUTPUT);
  pinMode(button, INPUT);

 
  // run test
  allPlay(50);
  Serial.println("Ready!");
}

//shut off all lights
void allOff(){
    for(int pin=start; pin <= 10; pin++){
      digitalWrite(pin, LOW);
    }
}

void allOn(){
    for(int pin=start; pin <= 10; pin++){
      digitalWrite(pin, HIGH);
    }
}

void flicker(){
  allOn();
  delay(50);
  allOff();
  delay(50);
 }


//method to control the menorah
void lightMenorah(){
  int reading = digitalRead(button);
  
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {

    if (reading != buttonState) {
      buttonState = reading;
     // Serial.println(buttonState);
    
      if (buttonState == 1) {
        if(count == 0){
          //the shamash is lit first
          digitalWrite(shamash, HIGH);
          Serial.println("push");
          //give yourself time to light both candles
          delay(100);
        }
          //turn on correct LED      
          digitalWrite(start+count,HIGH);
          Serial.println(count);
          count=count+1;
       }
     
    }
  }
   if (count == 9){
    for (int i = 0; i < 6; i++){
      for (int i = 0; i < 3; i++){
        allPlay(100);
        allBack(100);
      }
        for (int i = 0; i < 15; i++){
        flicker();
      }
    }
    allOn();
    count = count+1;
    } 

  //reset the counter and shut off the lights
  if (count > 10){
    count = 0;
    allOff();
  }
  
  lastButtonState = reading;
}
void loop() {
  // put your main code here, to run repeatedly:
  lightMenorah();
}
