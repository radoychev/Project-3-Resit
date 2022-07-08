
//defining the Arduino pins
//Front
const byte frontLeft = 16; // the PWM pin the LED is attached to
const byte frontRight = 18; // the PWM pin the LED is attached to



//Back
const byte backLeft = 17; // the PWM pin the LED is attached to
const byte backRight = 5; // the PWM pin the LED is attached to

//Sensor
int leftSensor = 39;
int rightSensor = 34;
 
 



void setup() {
   //-----------Line Tracking Sensor----------
  pinMode (leftSensor, INPUT); // sensor pin INPUT
  pinMode (rightSensor, INPUT); // sensor pin INPUT


Serial.begin(115200);

  ledcAttachPin(frontLeft, 0); // assign a led pins to a channel
  ledcAttachPin(frontRight, 1); // assign a led pins to a channel
  ledcAttachPin(backLeft, 2); // assign a led pins to a channel
  ledcAttachPin(backRight, 3); // assign a led pins to a channel

  // Initialize channels
  // channels 0-15, resolution 1-16 bits, freq limits depend on resolution
  // ledcSetup(uint8_t channel, uint32_t freq, uint8_t resolution_bits);
  ledcSetup(0, 4000, 8); // 12 kHz PWM, 8-bit resolution
  ledcSetup(1, 4000, 8); // 12 kHz PWM, 8-bit resolution
  ledcSetup(2, 4000, 8); // 12 kHz PWM, 8-bit resolution
  ledcSetup(3, 4000, 8); // 12 kHz PWM, 8-bit resolution

 
}

void loop() {
  //LineTracking()
   int sensorL = analogRead(leftSensor);
   int sensorR = analogRead(rightSensor);
   int turn_speed = 150;
    
   //Serial.print(F("Right sensor = "));
   //Serial.println((sensorR));
   //Serial.print(F("Left sensor = "));
   //Serial.println((sensorL));
   if(sensorL > 100 && sensorR >100){
    
    Serial.println("STOP");
    goForward(0); 
    }
    if(sensorL < 100 && sensorR < 100){
      Serial.println("GOING FORWARD");
      goForward(190);
    }
    if(sensorL > 100 && sensorR < 100){
      Serial.println("Turning Left");
      while (sensorR < 200 && sensorL > 200) {
        //turnLeft(turn_speed);
        sensorL = analogRead (leftSensor);
        sensorR = analogRead (rightSensor);
    }
    }
    if(sensorL < 100 && sensorR > 100){
      //Serial.println("turning Right");
      while (sensorR > 150 && sensorL < 200) {
        //turnRight(turn_speed);
        Serial.println("TURNING RIGHT");
        sensorL = analogRead (leftSensor);
        sensorR = analogRead (rightSensor);
      
     
      }
    }
    
    
    
     
    
}





// FUNCTIONS
int goForward(int speed) {
  ledcWrite(0, speed);
  ledcWrite(1, speed);
  ledcWrite(2, 0);
  ledcWrite(3, 0);
}

int goBack(int speed) {
  ledcWrite(0, 0);
  ledcWrite(1, 0);
  ledcWrite(2, speed);
  ledcWrite(3, speed);
}
int turnLeft(int speed) {
  ledcWrite(0, speed);
  ledcWrite(1, 0);
  ledcWrite(2, 0);
  ledcWrite(3, speed);
}
int turnRight(int speed) {
  ledcWrite(0, 0);
  ledcWrite(1, speed);
  ledcWrite(2, speed);
  ledcWrite(3, 0);
}
