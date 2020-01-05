/**
 * @brief: Prueba control serial BB8 con rutina autónoma.
 * @author: Lucas Cortés Gutiérrez.
 * @date: 10/7/2019
 */

#include <SoftwareSerial.h>
#include <Sabertooth.h>

#define NONE 0

#define POWER_MAX 64

#define POWER 30

#define PIN_SERIAL_ST 6

SoftwareSerial SWSerial(NOT_A_PIN, PIN_SERIAL_ST);
Sabertooth ST(128, SWSerial); // Address 128, and use SWSerial as the serial port.

int aux=0;

void setup(){
    pinMode(LED_BUILTIN, OUTPUT);
    SWSerial.begin(9600);
    ST.autobaud();
    Serial.begin(115200);
    Serial.println("BB8 - SERIAL"); 
}

void loop(){
        ST.motor(1, POWER);
        digitalWrite(LED_BUILTIN,HIGH);
        delay(1000);
        digitalWrite(LED_BUILTIN,LOW);
        ST.motor(1, 0);
        ST.motor(2, POWER);
        delay(1000);
        digitalWrite(LED_BUILTIN,HIGH);
        ST.motor(2, 0);
        delay(1000);
        digitalWrite(LED_BUILTIN,LOW);
        ST.motor(1, -POWER);
        delay(1000);
        digitalWrite(LED_BUILTIN,HIGH);
        ST.motor(1, 0);
        ST.motor(2, -POWER);
        delay(1000);
        ST.motor(2, 0);
        digitalWrite(LED_BUILTIN,LOW);
        delay(100);
        digitalWrite(LED_BUILTIN,HIGH);
        delay(100);
        digitalWrite(LED_BUILTIN,LOW);
        delay(100);
        digitalWrite(LED_BUILTIN,HIGH);
        delay(100);
        digitalWrite(LED_BUILTIN,LOW);
        delay(100);
        digitalWrite(LED_BUILTIN,HIGH);
        delay(100);
        digitalWrite(LED_BUILTIN,LOW);
        delay(100);
        digitalWrite(LED_BUILTIN,HIGH);
        delay(100);
        digitalWrite(LED_BUILTIN,LOW);
        delay(100);
        digitalWrite(LED_BUILTIN,HIGH);
        delay(100);
        digitalWrite(LED_BUILTIN,LOW);
        delay(100);
        digitalWrite(LED_BUILTIN,HIGH);
        delay(100);
        digitalWrite(LED_BUILTIN,LOW);
        delay(100);
        digitalWrite(LED_BUILTIN,HIGH);
        delay(100);
        digitalWrite(LED_BUILTIN,LOW);
        delay(100);
        digitalWrite(LED_BUILTIN,HIGH);
        delay(100);
        digitalWrite(LED_BUILTIN,LOW);
        delay(100);
        digitalWrite(LED_BUILTIN,HIGH);
        delay(100);
        digitalWrite(LED_BUILTIN,LOW);
        delay(100);
        digitalWrite(LED_BUILTIN,HIGH);
        delay(100);
        digitalWrite(LED_BUILTIN,LOW);
        delay(100);
        digitalWrite(LED_BUILTIN,HIGH);
        delay(100);
        digitalWrite(LED_BUILTIN,LOW);
        delay(100);
        digitalWrite(LED_BUILTIN,HIGH);
        delay(100);
        digitalWrite(LED_BUILTIN,LOW);
        delay(100);
        digitalWrite(LED_BUILTIN,HIGH);
        delay(100);
        digitalWrite(LED_BUILTIN,LOW);
        delay(100);
        digitalWrite(LED_BUILTIN,HIGH);
        delay(100);
        
}
