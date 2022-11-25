#include <SoftwareSerial.h>
#include <ArduinoJson.h>

// D6 = Rx & D5 = Tx
SoftwareSerial nodemcu(D6, D5);

void setup() {
  // Initialize Serial port
  Serial.begin(9600);
  nodemcu.begin(9600);
  while (!Serial) continue;
}
void loop() { // run over and over
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& data = jsonBuffer.parseObject(nodemcu);

  if (data == JsonObject::invalid()) {
    //    Serial.println("Invalid Json Object");
    jsonBuffer.clear();
    return;
  }

  Serial.println("JSON Object Recieved");
  Serial.println(millis());
  Serial.print("Recieved Sensor0:  ");
  float temp_sensor0 = data["sensor0"];
  Serial.println(temp_sensor0);

  Serial.print("Recieved Sensor1:  ");
  float temp_sensor1 = data["sensor1"];
  Serial.println(temp_sensor1);

  Serial.print("Recieved Sensor2:  ");
  float temp_sensor2 = data["sensor2"];
  Serial.println(temp_sensor2);
  Serial.println("-----------------------------------------");

}
