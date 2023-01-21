// final version
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <ThingSpeak.h>
#include <ESP8266WiFi.h>

// Network parameters
const char* ssid     = "HS";
const char* password = "nhs780726";

// D6 = Rx & D5 = Tx
SoftwareSerial nodemcu(D6, D5);

// ThingSpeak information
char thingSpeakAddress[] = "api.thingspeak.com";
unsigned long channelID = 1943777;
//char* readAPIKey = "XXXXXXXXXXXXXXXX";
char* writeAPIKey = "0D6EJXQGWY8KNG3T";
//const unsigned long postingInterval = 15L * 1000L;
unsigned int dataFieldOne = 1;                            // Field to write temperature data
unsigned int dataFieldTwo = 2;                       // Field to write temperature data
unsigned int dataFieldThree = 3;                     // Field to write temperature data

unsigned long lastConnectionTime = 0;
long lastUpdateTime = 0;

WiFiClient client;

//-------------------------------------------------- SETUP ------------------------------------------------------------

void setup() {
  Serial.begin(9600);
  nodemcu.begin(9600);
  ThingSpeak.begin(client);
  while (!Serial) continue;
  delay(2000);

  Serial.println("Program Started");

  //Establish WiFi Connection
  wifi_connect();
}

//-------------------------------------------------- LOOP ------------------------------------------------------------

void loop() {
  //Check if connected to WiFi, else connect
  if (WiFi.status() != WL_CONNECTED) {
    wifi_connect();
  }
  else {
    Serial.println("Currently Connected to WiFi");
  }
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

  int x = write2TSData( channelID , dataFieldOne , temp_sensor0 , dataFieldTwo , temp_sensor1 , dataFieldThree , temp_sensor2);
  Serial.println(x);
}

//----------------------------------------- FUNCTION - WiFi Connect -----------------------------------------

void wifi_connect() {
  Serial.println("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  //ThingSpeak.begin(client);
  Serial.println("WiFi Connected");
}

//----------------------------------------- FUNCTION - Write Data to ThingSpeak -----------------------------------------
// Use this function if you want to write multiple fields simultaneously.

int write2TSData( long TSChannel, unsigned int TSField1, float field1Data, unsigned int TSField2, long field2Data, unsigned int TSField3, long field3Data ) {

  ThingSpeak.setField( TSField1, field1Data );
  ThingSpeak.setField( TSField2, field2Data );
  ThingSpeak.setField( TSField3, field3Data );

  int writeSuccess = ThingSpeak.writeFields( TSChannel, writeAPIKey );
  return writeSuccess;
}
