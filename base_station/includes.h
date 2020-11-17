/** @file includes.h
 *  @brief Functions which base 
 *  station of LEACH protocol will use.
 *
 *  This file contains other necessary includes,
 *  structures, and defines needed for complete
 *  node functionality.
 *
 *  @author Pavle Lakic
 *  @bug No known bugs.
 */
 
#ifndef INCLUDES_H_
#define INCLUDES_H_

#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <PubSubClient.h>
#include <Wire.h>

/** Set this flag to 1 if you want to see debug messages.*/
#define DEBUG                       1

/** Local router connected to Internet SSID.*/
#define LOCAL_ROUTER_SSID           "It burns when IP"

/***/
#define LOCAL_ROUTER_PASSWORD       "nakacisenamoj"

/** Hive MQ server where topics will be published.*/
#define MQTT_SERVER                 "broker.mqttdashboard.com"

/** Access point SSID of base station.*/
#define AP_SSID                     "5G server"

/** Access point password of base station.*/
#define AP_PASS                     "teorijazavere"

/**WiFi channel.*/
#define WIFI_CHANNEL              1

/** Maximum possible number of connected devices to base station.*/
#define MAX_CONNECTED             7

/** Port which base station will listen for CH`s or nodes.*/
#define BROADCAST_PORT              2000

/** Node 0 AP name.*/
#define NODE_0                    "Node 0"

/** Node 1 AP name.*/
#define NODE_1                    "Node 1"

/** Node 2 AP name.*/
#define NODE_2                    "Node 2"

/** Node 3 AP name.*/
#define NODE_3                    "Node 3"

/** Node 4 AP name.*/
#define NODE_4                    "Node 4"

/** Node 5 AP name.*/
#define NODE_5                    "Node 5"

/** Node 6 AP name.*/
#define NODE_6                    "Node 6"

/** MAC address of node which name will be Node 0.*/
#define MAC_NODE_0                "A4:CF:12:C3:04:FD"

/** MAC address of node which name will be Node 1*/
#define MAC_NODE_1                "FC:F5:C4:AC:36:86"

/** MAC address of node which name will be Node 2.*/
#define MAC_NODE_2                "C8:2B:96:29:F1:03"

/** MAC address of node which name will be Node 3.*/
#define MAC_NODE_3                "A4:CF:12:C3:0A:9B"

/** MAC address of node which name will be Node 4.*/
#define MAC_NODE_4                "C8:2B:96:29:FB:9E"

/** MAC address of node which name will be Node 5.*/
#define MAC_NODE_5                "A4:CF:12:C3:0F:77"

/** MAC address of node which name will be Node 6.*/
#define MAC_NODE_6                "A4:CF:12:C3:08:1C"

/**
 * @brief This function will find number of nodes in string.
 * @param Recieved string from node.
 * @return Number of nodes in string.
 */
unsigned char nodes_number(char *txt);

/**
 * @brief Parsing of string containing number of nodes, and
 * their ADC values.
 * @param String with nodes and their adc values.
 * @param Number of nodes.
 * @return none.
 */
void publish_node(char *txt, unsigned short l);

/**
 * @brief Waits for nodes to send packet to broadcast port.
 * @param none.
 * @return none.
 */
void wait_for_packet(void);

/**
 * @brief Function which will be in infinite loop.
 * @param none.
 * @returns none.
 */
void loop_function(void);

/**
 * @brief If base is not connected, will retry connection to
 * MQTT server each 5 seconds.
 * @param none.
 * @returns none.
 */
void reconnect(void);

/**
 * @brief Configuration of ESP8266 as Access point,
 * listening to UDP broadcast port etc.
 * @param none.
 * @returns none.
 */
void setup_base(void);

#endif // INCLUDES_H_
