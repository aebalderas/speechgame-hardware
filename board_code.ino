/*
  Aaron B. - Aditi S.
  Physcomp Project - Hardware/Software Layer Code
  Spring 2015
*/


// these constants won't change:
const int ledCount = 10;    // the number of LEDs in the bar graph
const int buttonPin = 12; // button sending data through this pin
const int maxLEDs = 9;

// other globals
int incomingData = 0; // incoming data will be written to this
int thisLed = 11;
int buttonState = 0; // beginning state of putton, presumably unpressed
int prevButtonState = 0;
int ptsMin = 11; // see player point allocation for data transmitting
int ptsMax = 19;
int ptsWin = 110;
int ledPins[] = { 
  2, 3, 4, 5, 6, 7,8,9,10,11 };   // an array of pin numbers to which LEDs are attached


void setup() {
  Serial.begin(9600);
  // initializing push button at pin #...
  pinMode(buttonPin, INPUT);  
  // loop over the pin array and set them all to output:
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    pinMode(ledPins[thisLed], OUTPUT); 
  }
}

void loop() {
  // Maximum points that a player can get in a round
  int maxPoints = 10;
  //Serial.print("thisLed = ");
  //Serial.println(thisLed);
  int pressedCur = 0;
  int pressedNext = 0; 
  buttonState = digitalRead(buttonPin);
  
    // CHECK TO SEE IF BUTTON HAS BEEN PRESSED SINCE LAST LOOP ITER
    if (buttonState != prevButtonState) {
        //Serial.print("Current state of Pushbutton: ");
        //if(buttonState==LOW){Serial.println("OFF!");}
        //else{Serial.println("ON!");}
        
        // Send webapp signal that btn pressed
        Serial.println(100); // 100 is P1, 200 is P2
        
        // listen for signal from webapp
        // if player was correct...
        if (Serial.available() > 0) {
            // Serial.print("RECEIVED DATA!!!");
            thisLed = Serial.read();
            Serial.print("DATA RECEIVED VIA SERIAL: ");
            Serial.println(thisLed); // convert serial data to decimal form
            // CHECK TO SEE IF THIS IS PLAYER ONE DATA
            // i.e. BETWEEN 11-19
            if (ptsMin <= thisLed <= ptsMax) {
                Serial.println("I received a number between 11 and 19");
                int toLight = (thisLed - ptsMin) + 1;
                for (int i=0; i < toLight; i++){
                    //if ((thisLed - ptsMin) < maxPoints) {
                    //Serial.println("Inside the if statement...");
                    digitalWrite(ledPins[i], HIGH);
                    delay(50);
                    //}else {
                    //Serial.println("Inside the else statement...");
                    //digitalWrite(ledPins[thisLed-ptsMin], LOW); 
                    //}
                }
                //Serial.println("...Upping thisLed...");
                //thisLed++;
                //Serial.print("thisLed = ");
                //Serial.println(thisLed);
                
            }
            // PLAYER JUST WON THE ROUND aka 110
            if (thisLed == ptsWin) {
                //Serial.println("This is the second if statement!!!");
                int flashNum = 0;
                int upOrDown = 0; // if 0 --> decrease LEDs; if 1 --> increase LEDs
                int maxFlashNum = 6;
                int thisLed = 10;
                
                while (flashNum < maxFlashNum) { // goes up and down 3x
                    //Serial.println("We're inside the while loop");
                    if (upOrDown == 0) {
                        //Serial.print("upOrDown == 0");
                        for(thisLed; thisLed > 0; thisLed--) {
                            digitalWrite(ledPins[thisLed], LOW);
                            delay(50);
                        }
                        upOrDown = 1;
                    }else { // upOrDown = 0; LEDs goin up (on a Tuesday)
                        //Serial.print("upOrDown == 1");
                        for (thisLed; thisLed < 10; thisLed++) {
                            digitalWrite(ledPins[thisLed], HIGH);
                            delay(50);
                        }
                        upOrDown = 0;
                    }
                    flashNum++;
                }
            }
        }
    }
}
