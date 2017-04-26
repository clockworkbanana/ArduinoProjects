//Inputs/Outputs
const int RED = 11;
const int GREEN = 10;
const int BLUE = 9;
const int BTN = 8;

//Global Time
unsigned long currentMillis;
unsigned long previousMillis;
unsigned long calibratedHoldValue = 50000;//need to calibrate it once code changes

//MetronomeState
int clickNumber = 1;
int period = 500; //ms
const int flashTime = 20;

//Button status
unsigned long tapTime = 0;
unsigned long prevTapTime = 0;
boolean btnDown = false;
unsigned long holdTime = 0;

void setup() {
  // Init inputs and outputs
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(BTN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  digitalWrite(RED, HIGH);
  delay(750);
  digitalWrite(GREEN, HIGH);
  delay(750);
  digitalWrite(BLUE, HIGH);
  delay(1500);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
}

void loop() {
  currentMillis = millis();
  buttonActions();
  ledActions();
}

void buttonActions(){
    if(digitalRead(BTN)){ //button is pressed
      if(holdTime == 0){ //just now
          if((prevTapTime != 0) && (currentMillis - prevTapTime) < 3000 && (currentMillis - prevTapTime > 200)){
              period = currentMillis - prevTapTime;
              clickNumber = 4;//Re-start the metronome
              click();
          }
          prevTapTime = currentMillis;
      } else if(holdTime>calibratedHoldValue){//button been held for about half second
          if(!btnDown){
              holdAction();
              prevTapTime = 0; //setting this so next tap won't set the blink period
              btnDown = true;
         }
      }//else do nothing
      holdTime++;
    } else {//press is not detected - resetting holdtime
      if(holdTime!=0){
        releaseAction();
      };
      holdTime = 0;
      btnDown = false;
    }
}

void holdAction(){
    digitalWrite(BLUE, HIGH);
}

void releaseAction(){
    digitalWrite(BLUE, LOW);
}

void ledActions(){
  //Turn on
  if(currentMillis - previousMillis >= period){
    click();
  }
  //Turn off
  if(millis() - previousMillis >=20){
      digitalWrite(GREEN, LOW);
      digitalWrite(RED, LOW);
  }
}

void click(){
  previousMillis = millis();
  if(clickNumber == 1){
    digitalWrite(RED, HIGH);
  } else {
    digitalWrite(GREEN, HIGH);
  }
  clickNumber++;
  if(clickNumber == 5) {clickNumber = 1;}
}
