//temperature sensor DHT11 with LCD display (with button) displays C, F and Humidity

#include <Adafruit_Sensor.h>// theses are the 3 libraries for the DHT sensors 
#include <DHT.h>
#include <DHT_U.h>

#include <LiquidCrystal.h>// this is the libray for the LCD display

LiquidCrystal lcd(7, 8, 9, 10, 11, 12); // setup for the LCD pins


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


// Uncomment the type of sensor in use:

#define DHTTYPE    DHT11     // DHT 11 model used



DHT_Unified dht(DHTPIN, DHTTYPE); // setup the DHT11 as sensor 

uint32_t delayMS; //variable setup
double fer = 0; //variable stetp

bool oldSwitchState = LOW;//variable setup for the button funtion
bool newSwitchState = LOW;//variable setup for the button funtion
byte state = 0;//variable setup for the button funtion
int but = 3;//pin connected to the button




//***********************************************SETUP****************************************************************
void setup() {

pinMode(but, INPUT_PULLUP);// define button pin as pullup

lcd.createChar(0, degree );// this line creates the custom shape that was added as byte 0 degree C
lcd.createChar(1, percent );//this line creates the custom shape that was added as byte 1 percent

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
  // Delay between measurements.
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;// define event variable
  dht.temperature().getEvent(&event); //get data for the temp sensor
  if (isnan(event.temperature)) { //condition if there's a problem 
    Serial.println(F("Error reading temperature!"));// print the error message
  }
  else {// condition if no error
    Serial.print(F("Temperature: "));// print the text 
    Serial.print(event.temperature);// print the actual value of the temperature read from the sensor
    Serial.print(F("°C"));// print the text 
    Serial.print("\t");//print the text 


  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {//condition if there's a problem
    Serial.println(F("Error reading humidity!"));// print the error message
  }
  else {
    Serial.print(F("Humidity: "));// condition if no error
    Serial.print(event.relative_humidity);// print the actual value of the humidity read from the sensor
    Serial.println(F("%"));// print the text 
  }

  //conversion into F from C
double fer = ((event.temperature * (9.0/5.0)) + 32.0);// euqation for the conversion
 Serial.print(F("Temperature(F): "));// print the text 
 Serial.print(fer);// print the value of the fahrenheit
 Serial.print("F");// print the text 
 Serial.print("\t");// print the tab space 
  

 //***************TOGGLE BUTTON on LCD
Serial.print(state);// print the current value of the button

  bool newSwitchState = digitalRead(but);// read the input of the button
  if ( newSwitchState != oldSwitchState )// if input reading is not the same as the last state,

    
  {
    // has the button switch been closed?
    if ( newSwitchState == HIGH )
    {
      // increase the value of state
      state++;
      if (state >= 4) {//more than 4 = 1
        state = 1;
      }

      
      // Because the value of state does not change while we are testing it we don't need to use else if
      if (state == 1) {// Turn on the page 1 temp (C)

        dht.temperature().getEvent(&event);; //get data for the temp sensor
         lcd.setCursor(0, 0); //setup the position for the text x=0 y=0
         lcd.print(F("T(C"));// print the text 
         lcd.write(byte(0));// print the text 
         lcd.print("):");// print the text 
         lcd.print(event.temperature);//print the actual value of the temperature from the sensor
         lcd.print(F("C"));// print the text 
         lcd.write(byte(0));// print the custom character setup previously 
         lcd.print("     ");// print the space to avoid visual bugs 
      }
    if (state == 2) {// Turn on the page 2 temp (F)

      dht.temperature().getEvent(&event);; //get data for the temp sensor
      lcd.setCursor(0, 0);//setup the position for the text x=0 y=0
      lcd.print("Temp(F): ");// print the text 
      lcd.print(event.temperature * (9.0/5.0) + 32.0);//equation to convert to fahrenheit
      lcd.print("F");// print the text 
      lcd.print("      ");// print the space to avoid visual bugs 
      }
    if (state == 3) {// Turn on the page 2 humidity

      dht.humidity().getEvent(&event); //get data for the humidity sensor
      lcd.setCursor(0, 0);//setup the position for the text x=0 y=0
      lcd.print("Humid:");// print the text 
      lcd.print(event.relative_humidity);//print the actual value of the humidity from the sensor
      lcd.write(byte(1));// print the custom character setup previously 
      lcd.print("     ");// print the space to avoid visual bugs 
      }
    }
    oldSwitchState = newSwitchState;//reset the state so the loop can restart
  }
  
}


