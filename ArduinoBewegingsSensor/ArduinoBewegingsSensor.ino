#include <WiFiNINA.h>
#include <SPI.h>
#include <PubSubClient.h>

int statusWifi = WL_IDLE_STATUS;           // Tijdelijke status totdat WiFi.begin() wordt aangeroepen en blijft actief totdat de maximale aantal pogingen is gedaan of wanneer de connectie is gemaakt 

//Objects 
IPAddress server(192,168,2,31);       // Server, in dit geval mijn laptop
WiFiClient wifiClient;


//Methods setup
void wifiSetup() {
  Serial.println("Attempting to connect to the network...");
  Serial.print("Network name: ");
  Serial.println("MaisonPrettyBoy2.4");

  statusWifi = WiFi.begin("MaisonPrettyBoy2.4", "SjoTeiLis1");
  if (statusWifi != WL_CONNECTED) { 
    Serial.println("Couldn't get a wifi connection");
    while(true);
  } 
  else {
    Serial.println("Connected to wifi");
  }
}

const int defaultportMosquitto = 1883; 
const char* arduino_ID = "Arduino_Teije";
const char* pubTopic = "Motionsensor/Detection";

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
