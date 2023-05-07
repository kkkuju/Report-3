//HC SR04 sensor on LCD (no button) displays cm

// Include NewPing Library for the ultrasonic sensor
#include "NewPing.h"

#define TRIGGER_PIN  2 //trigger pin
#define ECHO_PIN     6// echo pin
#define MAX_DISTANCE 400// Maximum Distance is 400 cm
float duration;
int iterations = 5;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);// funtion needed for the Newping library

float distance;//storing variable for distance


#include <LiquidCrystal.h>// this is the libray for the LCD display

LiquidCrystal lcd(7, 8, 9, 10, 11, 12); // setup for the LCD pins
 


void setup() {
  Serial.begin (9600);// activates serial monitor
  lcd.begin(16,2); // set up the available space on the LCD display. 16 colums and 2 rows.

}

void loop() {
  duration = sonar.ping_median(iterations);// function needed for the library 
   
  distance = (duration / 2) * 0.0343;// equation to calculate the distance
  
  // Send results to Serial Monitor
  Serial.print("Distance = ");
  if (distance >= 400 || distance <= 2) {// error condition outside of these range
    Serial.println("Out of range");// print the text 
  }
  else {// if the range is acceptable
    Serial.print(distance);//print the value of the distance
    Serial.println(" cm");// print the text 
    delay(100);// time given to the sensor to receive the echo 
  }
  
  lcd.setCursor(0, 0); //setup the position for the text x=0 y=0
    lcd.print("Distance=");// print the text 

  if (distance >= 400 || distance <= 2) {// error condition outside of these range
    lcd.setCursor(0, 1);//setup the position for the text x=0 y=1 
    lcd.println("Out of range");// print the text 
    lcd.println("              ");// print the space to avoid visual bugs 

  }
    else {
    lcd.setCursor(0, 1); //setup the position for the text x=0 y=1 
    lcd.print(distance);// print the text 
    lcd.print("cm");// print the text 
    lcd.println("                 ");// print the space to avoid visual bugs 
    delay(100);// time given to read the value
    }
         
  }





