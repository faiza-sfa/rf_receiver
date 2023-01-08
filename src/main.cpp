#include <Arduino.h>
#include <RCSwitch.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <string> 

const char*  wifiSSID="Faiza";
const char*  wifiPassword="faizafaiza";
const char* mqttBroker = "broker.hivemq.com";
const char* topic_to_publish = "Smart_Home/test";

WiFiClient WIFI_CLIENT;
PubSubClient MQTT_CLIENT;
RCSwitch mySwitch = RCSwitch();

void reconnect() ;

void setup() {


  Serial.begin(9600);
  WiFi.begin(wifiSSID, wifiPassword);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  mySwitch.enableReceive(0);  // Connect To GPIO0 (D3) On The ESP
}

void loop() {
  int value = mySwitch.getReceivedValue();
  // String str= std::to_string(value); 
  if (mySwitch.available()) {
      Serial.print(" The Device Code Is: ");
      Serial.println(mySwitch.getReceivedValue());
      String message = "Device id: ";
      message = message + value;

  // Publish a message to a topic
      MQTT_CLIENT.publish(topic_to_publish, message.c_str());
  
      }
  // Check if we're connected to the MQTT broker
  if (!MQTT_CLIENT.connected()) {
    // If we're not, attempt to reconnect
    reconnect();
  }

  mySwitch.resetAvailable();

  }

void reconnect() {
  // Set our MQTT broker address and port
  MQTT_CLIENT.setServer(mqttBroker, 1883);
  MQTT_CLIENT.setClient(WIFI_CLIENT);

  // Loop until we're reconnected
  while (!MQTT_CLIENT.connected()) {
    // Attempt to connect
    Serial.println("Hi from Fai");
    MQTT_CLIENT.connect("995080bdsdsdsdawe");
    // Wait some time to space out connection requests
    delay(3000);
  }

  Serial.println("MQTT connected");
}