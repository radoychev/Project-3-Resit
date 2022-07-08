#include "Adafruit_VL53L0X.h"
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <HCSR04.h>
#include <ESP32Servo.h>



#define TRIG_PIN 25
#define ECHO_PIN 26


Adafruit_VL53L0X lox = Adafruit_VL53L0X();
UltraSonicDistanceSensor distanceSensor(TRIG_PIN, ECHO_PIN);

//defining the Arduino pins
//Front
const byte frontLeft = 16; // the PWM pin the LED is attached to
const byte frontRight = 18; // the PWM pin the LED is attached to



//Back
const byte backLeft = 17; // the PWM pin the LED is attached to
const byte backRight = 5; // the PWM pin the LED is attached to



long duration;
float distanceCm;

bool checked = false;

void setup() {
  Serial.begin(115200);

  ledcAttachPin(led_gpio, 0); // assign a led pins to a channel
  ledcAttachPin(led_gpio1, 1); // assign a led pins to a channel
  ledcAttachPin(back1, 2); // assign a led pins to a channel
  ledcAttachPin(back2, 3); // assign a led pins to a channel

  // Initialize channels
  
  ledcSetup(0, 4000, 8); // 12 kHz PWM, 8-bit resolution
  ledcSetup(1, 4000, 8); // 12 kHz PWM, 8-bit resolution
  ledcSetup(2, 4000, 8); // 12 kHz PWM, 8-bit resolution
  ledcSetup(3, 4000, 8); // 12 kHz PWM, 8-bit resolution


   
}

void loop() {


    VL53L0X_RangingMeasurementData_t measure;
    lox.rangingTest(&measure, false);
    Serial.println(measure.RangeMilliMeter);
    if (measure.RangeMilliMeter > 200) {
        lox.rangingTest(&measure, false);
        robot_straight(180);
    } else {
        stop_robot();
        if (get_lefto_sensor_dist() < 100) {
        while (measure.RangeMilliMeter < 150) { // rotate
            robot_right(190);
            lox.rangingTest(&measure, false);

            delay(50);
        }
        } else {
        while (measure.RangeMilliMeter < 150  ) { // rotate
            robot_left(190);
            lox.rangingTest(&measure, false);

            delay(50);
        }
        }
    }


  }


int robot_straight(int speed) {
  ledcWrite(0, speed);
  ledcWrite(1, speed);
  ledcWrite(2, 0);
  ledcWrite(3, 0);
}
int robot_left(int speed) {
  ledcWrite(0, speed);
  ledcWrite(1, 0);
  ledcWrite(2, 0);
  ledcWrite(3, speed);
}

int robot_right(int speed) {
  ledcWrite(0, 0);
  ledcWrite(1, speed);
  ledcWrite(2, speed);
  ledcWrite(3, 0);
}

int stop_robot() {
  ledcWrite(0, 0);
  ledcWrite(1, 0);
  ledcWrite(2, 0);
  ledcWrite(3, 0);
}
 
int get_lefto_sensor_dist() {
  return distanceSensor.measureDistanceCm();
}



int displayDistance() {
  VL53L0X_RangingMeasurementData_t measure;


  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

}
