// final version
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <ThingSpeak.h>
#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// Network parameters
const char* ssid     = "your ssid";
const char* password = "your pass";

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

const unsigned long postingInterval2 = 30L * 1000L;
long lastUpdateTime2 = 0;
int intervalCounter2 = 0;

//---------Channel Details---------//
unsigned long tempChannel = 2029861;            
char * tempReadAPIKey = "MF7JJ1U7450IWFOH"; 
unsigned int tempField1 = 1;

//---------Channel Details---------//
unsigned long resChannel = 2029822;            
const char * resReadAPIKey = "SZN0LN73V8L0ZXJ8"; // Read API Key
unsigned int resField1 = 1;

//---------Time Channel Details---------//
unsigned long timeChannel = 2035024;            
const char * timeReadAPIKey = "A1SZ87KB5LB9AMZS"; // Read API Key
unsigned int timeField1 = 1;
unsigned int timeField2 = 2;
unsigned int timeField3 = 3;
//-------------------------------//

// D6 = Rx & D5 = Tx
SoftwareSerial nodemcu(D6, D5);
// initialize LCD with I2C driver
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

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
int statusCode1 = 0;
int statusCode2 = 0;
int statusCode3 = 0;
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

//-------------------------------------------------- SETUP ------------------------------------------------------------

void setup() {
  Serial.begin(9600);
  nodemcu.begin(9600);
  ThingSpeak.begin(client);
  while (!Serial) continue;
  
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Display Test:OK");
  delay(3000);
  lcd.clear();
  Serial.println("Program Started");
  
  timeClient.begin();
  timeClient.setTimeOffset(16200); // GMT+4:30 (4.5*3600)
  //Establish WiFi Connection
  wifi_connect();
}

//-------------------------------------------------- LOOP ------------------------------------------------------------

void loop() {
   timeClient.update();
   String formattedTime = timeClient.getFormattedTime();
  //Check if connected to WiFi, else connect
  if (WiFi.status() != WL_CONNECTED) {
    wifi_connect();
  }
  else {
    Serial.println("Currently Connected to WiFi");
  }
  if (millis() - lastUpdateTime2 >=  postingInterval2) {
    lastUpdateTime2 = millis();
    long temp = ThingSpeak.readLongField(tempChannel, tempField1, tempReadAPIKey);
    statusCode1 = ThingSpeak.getLastReadStatus();
    long faulty = ThingSpeak.readLongField(resChannel, resField1, resReadAPIKey);
    statusCode2 = ThingSpeak.getLastReadStatus();
    long report_hour = ThingSpeak.readLongField(timeChannel, timeField1, timeReadAPIKey);
    long report_minute = ThingSpeak.readLongField(timeChannel, timeField2, timeReadAPIKey);
    long report_second = ThingSpeak.readLongField(timeChannel, timeField3, timeReadAPIKey);
    statusCode3 = ThingSpeak.getLastReadStatus();

   
    if (statusCode1 == 200 & statusCode2 == 200 & statusCode3 == 200)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(report_hour);
      lcd.setCursor(2, 0);
      lcd.print(":");
      lcd.setCursor(3, 0);
      lcd.print(report_minute);
      lcd.setCursor(5, 0);
      lcd.print(":");
      lcd.setCursor(6, 0);
      lcd.print(report_second);
      lcd.setCursor(0, 1);
      lcd.print("Temp:");
      lcd.print("24.5");
//      lcd.print("*C");
      lcd.setCursor(9, 1);
      lcd.print("Fault:");
      lcd.print("-");
//       if (faulty == 4){
//        lcd.print("-"); 
//        }
//       else{
//         lcd.print("1");
//         }     
    }
    else
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Unable to read");
      lcd.setCursor(0, 1);
      lcd.print("or No internet!");
    }
//    delay(100);
  }
  
  // receiving data sent from arduino
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
