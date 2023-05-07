//temperature sensor DHT11 value with HC SR04 sensor values on LCD


#include <Adafruit_Sensor.h>// theses are the 3 libraries for the DHT sensors 
#include <DHT.h>
#include <DHT_U.h>

#include <NewPing.h>//this library is for the HC ultrasonic sensor

#define trigPin  2 //Utrasonic sensor pin;
#define echoPin  6  //Utrasonic sensor pin;
#include <LiquidCrystal.h>// this is the libray for the LCD display
#define Max_DISTANCE 400  //Utrasonic sensor measurement maximum distance in cm;
LiquidCrystal lcd(7, 8, 9, 10, 11, 12); // setup for the LCD pins

float duration;//storing variable for duration


float distance;//storing variable for distance
float inch =0; //storing bit for inch


byte degree[8] = {//degree symbol as custom character
  B00000,
  B01000,
  B10100,
  B01000,
  B00000,
  B00000,
  B00000,
  B00000
};

byte percent[8] = {//% symbol as custom character
  B00000,
  B00000,
  B11001,
  B11010,
  B00100,
  B01011,
  B10011,
  B00000
};

#define DHTPIN 13     // Digital pin connected to the DHT sensor 

#define DHTTYPE    DHT11     // DHT 11 model used

DHT_Unified dht(DHTPIN, DHTTYPE); // setup the DHT11 as sensor 

uint32_t delayMS; //variable setup

NewPing sonar(trigPin, echoPin, Max_DISTANCE);// functions for the library
float Hum;  //humidity;
float Temperature;
int iterations= 5; // Ultrasonic sensor reading;
float soundcm;  //cm/ms

float soundms;  //m/s



//**************************************************************SETUP****************************************************************
void setup() {


lcd.createChar(0, degree );// this line creates the custom shape that was added as byte 0 degree C
lcd.createChar(1, percent );//this line creates the custom shape that was added as byte 1 percent
 
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  Serial.begin(9600);// activates serial monitor 

lcd.begin(16,2); // set up the available space on the LCD display. 16 colums and 2 rows.

  // Initialize device.
  dht.begin();// activtes DHT 11
  Serial.println(F("DHTxx Unified Sensor Example"));// serial print all the texts for first start up (all given in the example)
  // Print temperature sensor details.
  sensor_t sensor;// get the value for the sensor
  dht.temperature().getSensor(&sensor);// get the value for the temperature
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);// serial print all the texts for first start up (all given in the example)
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 10000;
}
//********************************************************LOOP**************************************************************************
void loop() {
   delay(delayMS);
   sensors_event_t event;// define event variable
   //read the value from DHT 11;
   dht.temperature().getEvent(&event); //get data for the temp sensor
   dht.humidity().getEvent(&event);

  soundms = 331.4 +( 0.606 *Temperature) + (0.0124 *Hum);  //the speed sound in m/s;
    soundcm = soundms / 10000; //the speed of sound in cm/ms
  // using the distance to calculate the distance;
  duration = sonar.ping_median(iterations); // function needed for the library
  distance = (duration / 2) *soundcm; //math equation for distance
  // check the distance is within the valid range;
  if (distance >=400 && distance<=2 ){
  Serial.print("out of range");//print the text

  }
  else {
Serial.print(distance);//print the distance variable
Serial.println(" CM");// print the text 
delay(100);

  }
 //print it on the serial printer;
 Serial.print("sound:=");// print the text 
 Serial.print("soundms");// print the text 
 Serial.print(" m/s");// print the text 
 Serial.print("Humidity:=");// print the text 
 Serial.print("Hum");// print the text 
 Serial.print("%  Temperature:");// print the text 
 Serial.print("Temperature");// print the text 
 Serial.print("C ");// print the text 
 Serial.print("distance");// print the text 
  
// make sure the LCD is clear screen;
lcd.clear();
 
  lcd.setCursor(0, 0); //setup the position for the text x=0 y=0
  lcd.print("Sound:"); // print the text 
  lcd.print(soundms); //print the soundms variable 
  lcd.print("m/s");
  delay(10);// time given to read the value


  lcd.setCursor(0, 1);//setup the position for the text x=0 y=1 
  lcd.print("Distance:");// print the text 
  lcd.print(distance);//print the distance variable
  lcd.print("CM");// print the text 
  delay(10);// time given to read the value
  
}


  



