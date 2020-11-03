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
#define AP_SSID                     "5G server."

/** Access point password of base station.*/
#define AP_PASS                     "teorijazavere"

/** Name of publish topic.*/
#define MQTT_PUB_TOPIC_ADC          "adcval"

/** Name of subscribed topic.*/
#define MQTT_SUB_TOPIC_LED          "ledStatus"

/** Port which base station will listen for CH`s or nodes.*/
#define BROADCAST_PORT              2000

#endif // INCLUDES_H_
