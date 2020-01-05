/**
 * @brief: Prueba control serial BB8 a través de USB.
 * @author: Lucas Cortés Gutiérrez.
 * @date: 10/7/2019
 */

#include <SoftwareSerial.h>
#include <Sabertooth.h>

#define NONE 0

#define POWER_MAX 64

#define PIN_SERIAL_ST 3

SoftwareSerial SWSerial(NOT_A_PIN, PIN_SERIAL_ST);
Sabertooth ST(128, SWSerial); // Address 128, and use SWSerial as the serial port.

int aux=0;

void setup(){
    SWSerial.begin(9600);
    ST.autobaud();
    Serial.begin(115200);
    Serial.println("BB8 - USB_ALT"); 
}

void loop(){
    char command = (Serial.available() > NONE) ? Serial.read() : NONE;
    switch (command) {
        case 'F':
            Serial.println("Moviendo adelante"); 
            ST.motor(1, 20);
            ST.motor(2, 20);
            delay(1000);
            break;

        case 'f':
            Serial.println("Moviendo adelante");  
            ST.motor(1, 20);
            ST.motor(2, 20);
            delay(1000);
            break;

        case 'B':
            Serial.println("Moviendo atrás"); 
            ST.motor(1, -20);
            ST.motor(2, -20);
            delay(1000);
            break;

        case 'b':
            Serial.println("Moviendo atrás"); 
            ST.motor(1, -20);
            ST.motor(2, -20);
            delay(1000);
            break;

        case 'R':
            Serial.println("Moviendo derecha"); 
            ST.motor(1, -20);
            ST.motor(2, 20);
            delay(1000);
            break;

        case 'r':
            Serial.println("Moviendo derecha"); 
            ST.motor(1, -20);
            ST.motor(2, 20);
            delay(1000);
            break;

        case 'L':
            Serial.println("Moviendo izquierda"); 
            ST.motor(1, 20);
            ST.motor(2, -20);
            delay(1000);
            break;

        case 'l':
            Serial.println("Moviendo izquierda"); 
            ST.motor(1, 20);
            ST.motor(2, -20);
            delay(1000);
            break;

        case 'S':
            Serial.println("Deteniendo"); 
            ST.motor(1, 0);
            ST.motor(2, 0);
            break;

        case 's':
            Serial.println("Deteniendo"); 
            ST.motor(1, 0);
            ST.motor(2, 0);
            break;

        default:
            ST.motor(1, 0);
            ST.motor(2, 0);
            break;
    }
}
