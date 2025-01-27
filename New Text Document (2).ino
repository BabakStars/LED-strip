#include"DHT.h"
#include<ESP8266WiFi.h>
#include<ThingerESP8266.h>
#define ssid "BABAK"
#define pass_ssid "YOUR PASSWORD"
#define USERNAME "YOUR USERNAME "
#define DEVICE_ID "DEVICE_ID IN WEBSITE"
#define DEVICE_CREDENTIAL "DEVICE CREDENTIAL IN WEBSITE"
#define DHT_PIN D3
#define DHT_TYPE DHT11
#define REDPIN D5
#define GREENPIN D1
#define BLUEPIN D2
ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);
DHT dht(DHT_PIN,DHT_TYPE);
int localHum  =0;
int localTemp =0;
int thingtemp =0;
int thinghum  =0;
int R=200;
int G=200;
int B=200;
void setup() {
  delay(2000);
  //Serial.begin(115200);
  WiFi.disconnect();
  thing.add_wifi(ssid,pass_ssid);
  pinMode(D5,OUTPUT);
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(2,OUTPUT);
  digitalWrite(2,HIGH);
  //leds on bord test
  thing["led02"]<<invertedDigitalPin(2);
  //sensors...
  thing["Temperature"]>>outputValue(localTemp);
  thing["Humidity"]>>outputValue(localHum);
  //Control Lights
  thing["R"]<<inputValue(R);
  thing["G"]<<inputValue(G);
  thing["B"]<<inputValue(B);
}

void loop() {
  getDHT();
  getLIT();
  thing.handle();
  
}
void getDHT(){
 
 thingtemp = localTemp;
 thinghum  = localHum;
 localTemp = dht.readTemperature();
 localHum =  dht.readHumidity();
  if(isnan(localHum) || isnan(localTemp)){
    localTemp=thingtemp;
    localHum=thinghum;
    return;
    
  }
  if(localTemp>99 || localHum>99){
    localTemp=thingtemp;
    localHum=thinghum;
    return;
    
  }
}

void getLIT(){
     analogWrite(REDPIN,R);
     analogWrite(GREENPIN,G); 
     analogWrite(BLUEPIN,B);
     delay(2);
    }
