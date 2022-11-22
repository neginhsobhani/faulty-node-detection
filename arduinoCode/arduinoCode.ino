// Arduino Code
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

#define sensorPin0 A0
#define sensorPin1 A1
#define sensorPin2 A2

const unsigned long postingInterval = 15L * 1000L;

//Initialise Arduino to NodeMCU (5=Rx & 6=Tx)
SoftwareSerial nodemcu(5, 6);
//SoftwareSerial espSerial(5, 6);

float temp_sensor0;
float temp_sensor1;
float temp_sensor2;

void setup(){
  Serial.begin(115200);
  
  nodemcu.begin(115200);
  delay(1000);
  
  Serial.println("Program started");
}
void loop()
{
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& data = jsonBuffer.createObject();
  
  //Obtain Tempreture from 3 sensors
  lm35_func();
  
  //Assign collected data to JSON Object
  data["sensor0"] = temp_sensor0;
  data["sensor1"] = temp_sensor1;
  data["sensor2"] = temp_sensor2;
//  data.printTo(Serial);
  data.printTo(nodemcu);
  jsonBuffer.clear();

  delay(postingInterval);
}

void lm35_func(){
  int reading0 = analogRead(sensorPin0);
  float voltage0 = reading0 * (5.0 / 1024.0);
  temp_sensor0 = voltage0 * 100;

  int reading1 = analogRead(sensorPin1);
  float voltage1 = reading1 * (5.0 / 1024.0);
  temp_sensor1 = voltage1 * 100;

  int reading2 = analogRead(sensorPin2);
  float voltage2 = reading2 * (5.0 / 1024.0);
  temp_sensor2 = voltage2 * 100;

  // Print the tempreture in Celsius
  Serial.print("Temperature sensor 0: ");
  Serial.print(temp_sensor0);
  Serial.print("\xC2\xB0"); // shows degree symbol
  Serial.println("C");

  Serial.print("Temperature sensor 1: ");
  Serial.print(temp_sensor1);
  Serial.print("\xC2\xB0"); // shows degree symbol
  Serial.println("C");

  Serial.print("Temperature sensor 2: ");
  Serial.print(temp_sensor2);
  Serial.print("\xC2\xB0"); // shows degree symbol
  Serial.println("C");
  }
