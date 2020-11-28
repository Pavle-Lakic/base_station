/** @file base_functions.cpp
 *  @brief
 *  
 *  This file contains relevant defines, structures and
 *  functions that base_station.ino will call.
 *  
 *  @author Pavle Lakic
 *  @bug No known bugs
 */
#include "includes.h"

#define IP(a,b,c,d) (uint32_t)(a | (b << 8) | (c << 16) | (d << 24))

typedef enum
{
  NODE0,
  NODE1,
  NODE2,
  NODE3,
  NODE4,
  NODE5,
  NODE6
} nodes;

WiFiUDP Udp;
WiFiClient espClient;
PubSubClient client(espClient);
uint32_t apIP = IP(192,168,4,1);
IPAddress subnet(255,255,255,0);

const char* router_ssid = LOCAL_ROUTER_SSID;
const char* password = LOCAL_ROUTER_PASSWORD;
const char* mqtt_server = MQTT_SERVER;

char packetBuffer[UDP_TX_PACKET_MAX_SIZE + 1];

unsigned char nodes_number(char *txt)
{
    unsigned char ret = 0;
    unsigned short i = 0;
    
    while (txt[i] != '\0') {
        if (txt[i] == 'N') {
            ret += 1;
        }
        i += 1;
    }
    
    return ret;
}

void publish_node(char *txt, unsigned short l)
{
    char node_id[20];
    char adc_value[20];
    //unsigned short node;
    unsigned short k;
    unsigned short number;
    

    
  for (int i = 0; i < l; i++) {

    k = 0;
    while (!isdigit(txt[0])) {
        txt += 1;
    }

     number = txt[0] - '0';
     txt += 2;
     
     while (isdigit(txt[0])) {
        adc_value[k] = txt[0];
        k += 1;
        txt += 1;
     }
     adc_value [k] = '\0';
     Serial.println(adc_value);

     switch (number) {
      
      case NODE0:

        client.publish(NODE_0, adc_value);
      
      break;

      case NODE1:

        client.publish(NODE_1, adc_value);
      
      break;

      case NODE2:

        client.publish(NODE_2, adc_value);
      
      break;

      case NODE3:

        client.publish(NODE_3, adc_value);
      
      break;
      
      case NODE4:

        client.publish(NODE_4, adc_value);
      
      break;
      
      case NODE5:

        client.publish(NODE_5, adc_value);
      
      break;

      case NODE6:

        client.publish(NODE_6, adc_value);
      
      break;
      
     }
     
  }
}

void setup_base(void)
{

#if DEBUG
  Serial.begin(9600);
#endif

  client.setServer(mqtt_server, 1883);
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(LOCAL_ROUTER_SSID, LOCAL_ROUTER_PASSWORD);
  WiFi.softAPConfig(IPAddress(apIP), IPAddress(apIP), subnet);

  WiFi.softAP(AP_SSID, AP_PASS, WIFI_CHANNEL, false, MAX_CONNECTED);
  
#if DEBUG
  Serial.print("AP IP address: ");
  Serial.print(WiFi.softAPIP());
  Serial.println();
#endif

  Udp.begin(BROADCAST_PORT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void reconnect(void) 
{
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
      digitalWrite(LED_BUILTIN, HIGH);

      delay(5000);
    }
  }
}

void loop_function(void)
{
  if (!client.connected()) {
    reconnect();
  }
  wait_for_packet();
  client.loop();
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

    unsigned char number_of_nodes = nodes_number(packetBuffer);

    publish_node(packetBuffer, number_of_nodes);

  }
}
