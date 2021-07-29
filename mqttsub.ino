#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
const char* SSID = "<YOUR WIFI SSID>";
const char* PSK =  "<YOUR WIFI PASSWORD>";
const char* MQTT_BROKER = "<YOUR MQTT BROKER ADDRESS>";
const int MQTT_PORT = <YOUR MQTT BROKER PORT>;
const char* MQTT_USER = "<YOUR MQTT USER>";
const char* MQTT_PSK = "<YOUR MQTT PASSWORD>";
const char* MQTT_CID = "<YOUR MQTT CLIENTID>";
const char* MQTT_SUB_TOPIC = "<Topic to Subscribe>";
const char* MQTT_INIT_TOPIC = "<Topic for Hello>";
 
WiFiClient espClient;
PubSubClient client(espClient);
 
void setup() {
 
  Serial.begin(9600);
 
  WiFi.begin(SSID, PSK);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println();
    Serial.println("Connecting to");
    Serial.println(SSID);
  }
  Serial.println("Connected to the WiFi network");
 
  client.setServer(MQTT_BROKER, MQTT_PORT);
  client.setCallback(callback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect(MQTT_CID, MQTT_USER, MQTT_PSK )) {
 
      Serial.println("Connected to MQTT.");  
 
    } else {
 
      Serial.print("Connection failed.");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
 
  client.publish(MQTT_INIT_TOPIC, "Hello from ESP8266");
  client.subscribe(MQTT_SUB_TOPIC);
 
}
 
void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
 
  Serial.println();
  Serial.println("-----------------------");
 
}
 
void loop() {
  client.loop();
}
