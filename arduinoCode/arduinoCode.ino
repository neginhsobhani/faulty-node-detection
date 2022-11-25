// Arduino Code
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

#define sensorPin0 A0
#define sensorPin1 A1
#define sensorPin2 A2

const unsigned long postingInterval = 15L * 1000L;
long lastUpdateTime = 0;
int intervalCounter = 0;

//Initialise Arduino to NodeMCU (5=Rx & 6=Tx)
SoftwareSerial nodemcu(5, 6);
//SoftwareSerial espSerial(5, 6);

// Temperature read from sensor each second
float temp_sensor0;
float temp_sensor1;
float temp_sensor2;

// Sum of temperatures read from sensor in a posting interval
float sumSensor0;
float sumSensor1;
float sumSensor2;

//-------------------------------------------------- SETUP ------------------------------------------------------------

void setup() {
  Serial.begin(9600);

  nodemcu.begin(9600);
  //  delay(1000);

  Serial.println("Program started");
}

//-------------------------------------------------- LOOP ------------------------------------------------------------

void loop()
{
  //Obtain Tempreture from 3 sensors
  lm35_func();
  intervalCounter ++; 
  // printing some stuff for debugging - remove later
  Serial.println(intervalCounter);
  long now = millis() - lastUpdateTime;
  Serial.println(millis());
  Serial.println(lastUpdateTime);
  Serial.println(postingInterval);
  Serial.println(now);
  
  if (millis() - lastUpdateTime >=  postingInterval) {
    lastUpdateTime = millis();
    Serial.print("reached post interval!");
    Serial.println(millis());
    StaticJsonBuffer<1000> jsonBuffer;
    JsonObject& data = jsonBuffer.createObject();

    //Assign collected data to JSON Object
    data["sensor0"] = sumSensor0 / 15;
    data["sensor1"] = sumSensor1 / 15;
    data["sensor2"] = sumSensor2 / 15;

    //  data.printTo(Serial);
    data.printTo(nodemcu);
    jsonBuffer.clear();

    sumSensor0 = 0;
    sumSensor1 = 0;
    sumSensor2 = 0;

//    delay(1000);
  }
  if (intervalCounter < 15){
    delay(1000);
    }
  else {
    // intervalCounter is 15
    Serial.println("the last interval counter");
    Serial.println(intervalCounter);
    Serial.println("--------------------------");
    intervalCounter = 0;
    }
}
//----------------------------------------- FUNCTION - LM35 sensor reading -----------------------------------------
void lm35_func() {
  int reading0 = analogRead(sensorPin0);
  float voltage0 = reading0 * (5.0 / 1024.0);
  temp_sensor0 = voltage0 * 100;
  sumSensor0 += temp_sensor0;

  int reading1 = analogRead(sensorPin1);
  float voltage1 = reading1 * (5.0 / 1024.0);
  temp_sensor1 = voltage1 * 100;
  sumSensor1 += temp_sensor1;

  int reading2 = analogRead(sensorPin2);
  float voltage2 = reading2 * (5.0 / 1024.0);
  temp_sensor2 = voltage2 * 100;
  sumSensor2 += temp_sensor2;

  // Print the tempreture in Celsius
  Serial.print("Temperature sensor 0: ");
  Serial.print(temp_sensor0);
  Serial.print("Temperature Sum 0: ");
  Serial.print(sumSensor0);
  Serial.print("\xC2\xB0"); // shows degree symbol
  Serial.println("C");

  Serial.print("Temperature sensor 1: ");
  Serial.print(temp_sensor1);
  Serial.print("Temperature Sum 1: ");
  Serial.print(sumSensor1);
  Serial.print("\xC2\xB0"); // shows degree symbol
  Serial.println("C");

  Serial.print("Temperature sensor 2: ");
  Serial.print(temp_sensor2);
  Serial.print("Temperature Sum 2: ");
  Serial.print(sumSensor2);
  Serial.print("\xC2\xB0"); // shows degree symbol
  Serial.println("C");
}
