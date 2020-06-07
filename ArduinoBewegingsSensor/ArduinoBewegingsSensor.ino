#include <WiFiNINA.h>
#include <SPI.h>
#include <PubSubClient.h>

int statusWifi = WL_IDLE_STATUS;           

//Objects 
IPAddress server(000,000,0,00);       //FILL IN OWN IP ADDRESS FOR MQTT BROKER!
WiFiClient wifiClient;


//Methods setup
void wifiSetup() {
  Serial.println("Attempting to connect to the network...");
  Serial.print("Network name: ");
  Serial.println("YOUR WIFI NAME HERE");

  statusWifi = WiFi.begin("YOUR NETWORK NAME HERE", "YOUR NETWORK PASSWORD HERE");
  if (statusWifi != WL_CONNECTED) { 
    Serial.println("Couldn't get a wifi connection");
    while(true);
  } 
  else {
    Serial.println("Connected to wifi");
  }
}

const int defaultportMosquitto = 1883; 
const char* arduino_ID = "YOUR ARDUINO NAME HERE";
const char* pubTopic = "YOUR TOPICS HERE";

//Objects 
PubSubClient mqttClient(wifiClient); 

//Methods setup
void commSetup() {
  mqttClient.setServer(server, defaultportMosquitto);
}  

void connToMqttBroker() {
    while (!mqttClient.connected()) {
    Serial.println("Connecting to MQTT server...");
    if (mqttClient.connect(arduino_ID)) {
      Serial.println("Connected to MQTT server");
    } else {
      Serial.print("failed with state: ");
      Serial.print(mqttClient.state());
      delay(2000); }
    }
}


void pubMessage() {
    const char* payload = "FIRE";
    mqttClient.publish(pubTopic, String(String (payload)).c_str());
    Serial.println("Message published");
}


const int PIN_TO_SENSOR = 3;   // the pin that OUTPUT pin of sensor is connected to
int pinStateCurrent   = LOW; // current state of pin

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);            // initialize serial
  pinMode(PIN_TO_SENSOR, INPUT);
  wifiSetup();
  commSetup();
  connToMqttBroker();
}

void loop() {
    pinStateCurrent = digitalRead(PIN_TO_SENSOR);   // read new state
    if (pinStateCurrent == HIGH) {   // pin state change: LOW -> HIGH
      Serial.println("Motion detected!");
      connToMqttBroker();
      pubMessage();
      delay(20000);
    } else {
      Serial.println("Not detection");
      delay(5000);
    }
    
}
