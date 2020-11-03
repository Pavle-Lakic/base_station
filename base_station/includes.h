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

/** Name of publish topic.*/
#define MQTT_PUB_TOPIC_ADC          "adcval"

/** Name of subscribed topic.*/
#define MQTT_SUB_TOPIC_LED          "ledStatus"

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
#define MAC_NODE_1                "10:52:1C:F9:81:0A"

/** MAC address of node which name will be Node 2.*/
#define MAC_NODE_2                "48:3F:DA:77:0D:82"

/** MAC address of node which name will be Node 3.*/
#define MAC_NODE_3                "A4:CF:12:C3:0A:9B"

/** MAC address of node which name will be Node 4.*/
#define MAC_NODE_4                "48:3F:DA:76:C2:68"

/** MAC address of node which name will be Node 5.*/
#define MAC_NODE_5                "48:3F:DA:76:B3:33"

/** MAC address of node which name will be Node 6.*/
#define MAC_NODE_6                "macnode6"

#endif // INCLUDES_H_
