#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <PubSubClient.h>
#include <Wire.h>

//#include <ESP8266mDNS.h> add mDNS? Problem with running it on Windows and Linux

/*
 * Access point defines
 */
#define AP_SSID     "5G server"
#define AP_PASS     "teorijazavere"
//#define AP_mDNS     "base"

/*
 * Topic defines
 */
#define MQTT_PUB_TOPIC_ADC    "adcval"
#define MQTT_SUB_TOPIC_LED    "ledStatus"
 
/*
 * Local router defines
 */
#define LOCAL_ROUTER_SSID     "Kolko ih je bilo?"
#define LOCAL_ROUTER_PASSWORD "lomljenjekreveta123"
#define MQTT_SERVER           "broker.mqttdashboard.com"
 
const char* router_ssid = LOCAL_ROUTER_SSID;
const char* password = LOCAL_ROUTER_PASSWORD;
const char* mqtt_server = MQTT_SERVER;

unsigned int localPort = 8888;      // local port to listen on
unsigned int broadcast_port = 2000;
// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE + 1]; //buffer to hold incoming packet,
char  ReplyBuffer[] = "100\r\n";       // a string to send back

WiFiClient espClient;
WiFiUDP Udp;
PubSubClient client(espClient);

const byte ledPin = LED_BUILTIN;
 
void receive_message(char* topic, byte* payload, unsigned int length) {
 Serial.print("Message arrived [");
 Serial.print(topic);
 Serial.print("] ");
 for (int i=0;i<length;i++) {
  char receivedChar = (char)payload[i];
  Serial.print(receivedChar);
  if (receivedChar == '0')
  // ESP8266 Huzzah outputs are "reversed"
  digitalWrite(ledPin, HIGH);
  if (receivedChar == '1')
   digitalWrite(ledPin, LOW);
  }
  Serial.println();
}
 
 
void reconnect() {
 // Loop until we're reconnected
 while (!client.connected()) {
 Serial.print("Attempting MQTT connection...");
 // Attempt to connect
 if (client.connect("ESP8266 Client")) {
  Serial.println("connected");
 //client.publish(MQTT_PUB_TOPIC_ADC);
  // ... and subscribe to topic
  client.subscribe(MQTT_SUB_TOPIC_LED);
 } else {
  Serial.print("failed, rc=");
  Serial.print(client.state());
  Serial.println(" try again in 5 seconds");
  // Wait 5 seconds before retrying
  delay(5000);
  }
 }
}
 
void setup()
{
 Serial.begin(9600);
 client.setServer(mqtt_server, 1883);
 client.setCallback(receive_message);
 WiFi.mode(WIFI_AP_STA);
 WiFi.begin(LOCAL_ROUTER_SSID, LOCAL_ROUTER_PASSWORD);
 WiFi.softAP(AP_SSID, AP_PASS);
 Serial.print("AP IP address: ");
 Serial.print(WiFi.softAPIP());
 Serial.println();
 Udp.begin(broadcast_port);
 pinMode(ledPin, OUTPUT);
}
 
void loop()
{
 if (!client.connected()) {
  reconnect();
 }
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    Serial.printf("Received packet of size %d from %s:%d\n    (to %s:%d, free heap = %d B)\n",
                  packetSize,
                  Udp.remoteIP().toString().c_str(), Udp.remotePort(),
                  Udp.destinationIP().toString().c_str(), Udp.localPort(),
                  ESP.getFreeHeap());

    // read the packet into packetBufffer
    int n = Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    packetBuffer[n] = '\0';
    Serial.println("Contents:");
    Serial.println(packetBuffer);

    // send a reply, to the IP address and port that sent us the packet we received
    //Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    //Udp.write(ReplyBuffer);
    //Udp.endPacket();
    client.publish(MQTT_PUB_TOPIC_ADC,packetBuffer);
  }
 client.loop();
}
