
#include "includes.h"

WiFiUDP Udp;
WiFiClient espClient;
PubSubClient client(espClient);

const char* router_ssid = LOCAL_ROUTER_SSID;
const char* password = LOCAL_ROUTER_PASSWORD;
const char* mqtt_server = MQTT_SERVER;

// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE + 1]; //buffer to hold incoming packet,
char  ReplyBuffer[] = "100\r\n";       // a string to send back
 
void reconnect(void) {
  while (!client.connected()) {

#if DEBUG
    Serial.print("Attempting MQTT connection...");
#endif

    if (client.connect("ESP8266 Client")) {

#if DEBUG
      Serial.println("connected");
#endif

    } 
    else {

#if DEBUG
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
#endif

      delay(5000);
    }
  }
}
void wait_for_packet(void)
{
  int packetSize = Udp.parsePacket();

  if (packetSize) {

#if DEBUG
    Serial.printf("Received packet of size %d from %s:%d\n    (to %s:%d, free heap = %d B)\n",
                  packetSize,
                  Udp.remoteIP().toString().c_str(), Udp.remotePort(),
                  Udp.destinationIP().toString().c_str(), Udp.localPort(),
                  ESP.getFreeHeap());
#endif

    int n = Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    packetBuffer[n] = '\0';

#if DEBUG
    Serial.println("Contents:");
    Serial.println(packetBuffer);
#endif

    client.publish(MQTT_PUB_TOPIC_ADC,packetBuffer);
  }
}
void setup()
{
  Serial.begin(9600);
  client.setServer(mqtt_server, 1883);
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(LOCAL_ROUTER_SSID, LOCAL_ROUTER_PASSWORD);
  WiFi.softAP(AP_SSID, AP_PASS);
  
#if DEBUG
  Serial.print("AP IP address: ");
  Serial.print(WiFi.softAPIP());
  Serial.println();
#endif

  Udp.begin(BROADCAST_PORT);
  pinMode(LED_BUILTIN, OUTPUT);
  
}
 
void loop()
{
 if (!client.connected()) {
  reconnect();
 }
 wait_for_packet();
 client.loop();
}
