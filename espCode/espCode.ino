#include <ThingSpeak.h>
#include <ESP8266WiFi.h>

// Network parameters
const char* ssid     = "HS";
const char* password = "nhs780726";

// ThingSpeak information
char thingSpeakAddress[] = "api.thingspeak.com";
unsigned long channelID = 1943777;
//char* readAPIKey = "XXXXXXXXXXXXXXXX";
char* writeAPIKey = "0D6EJXQGWY8KNG3T";
const unsigned long postingInterval = 15L * 1000L;
unsigned int dataFieldOne = 1;                            // Field to write temperature data
unsigned int dataFieldTwo = 2;                       // Field to write temperature data
unsigned int dataFieldThree = 3;                     // Field to write temperature data

unsigned long lastConnectionTime = 0;
long lastUpdateTime = 0; 
WiFiClient client;

void setup() {

Serial.begin(115200);
Serial.println("Start");
connectWiFi();

}

void loop() {
  
 // Update only if the posting time is exceeded
    if (millis() - lastUpdateTime >=  postingInterval) {
        
        float fahrenheitTemperature, celsiusTemperature;
        
        lastUpdateTime = millis();
        
        celsiusTemperature = 237.15;
        fahrenheitTemperature = celsiusTemperature * 9 / 5 + 32;
        Serial.println("ADC =  " + String( celsiusTemperature )+ " Temp = "+String( fahrenheitTemperature ));
        write2TSData( channelID , dataFieldOne , fahrenheitTemperature , dataFieldTwo , celsiusTemperature , dataFieldThree , millis() );      // Write the temperature in F, C, and time since starting.
    }
}

void connectWiFi(){
    WiFi.begin( ssid, password );
    while (WiFi.status() != WL_CONNECTED) {
      
//        WiFi.begin( ssid, password );
        delay(2500);
        Serial.print(".");
    }
    
    Serial.println( "Connected" );
    ThingSpeak.begin( client );
}

// Use this function if you want to write multiple fields simultaneously.
int write2TSData( long TSChannel, unsigned int TSField1, float field1Data, unsigned int TSField2, long field2Data, unsigned int TSField3, long field3Data ){

  ThingSpeak.setField( TSField1, field1Data );
  ThingSpeak.setField( TSField2, field2Data );
  ThingSpeak.setField( TSField3, field3Data );
   
  int writeSuccess = ThingSpeak.writeFields( TSChannel, writeAPIKey );
  return writeSuccess;
}
