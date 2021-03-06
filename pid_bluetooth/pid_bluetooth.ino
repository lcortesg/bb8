/**
 * @brief: Prueba control serial BB8 con control PID en péndulo de contrapeso.
 * @author: Lucas Cortés Gutiérrez.
 * @date: 13/7/2019
 */

#include <Wire.h>
#include <math.h>
#include <SoftwareSerial.h>
#include <Sabertooth.h>

#define NONE 0

#define DEBUG_ACE 0
#define DEBUG_ANG 0
#define DEBUG_PID 0 
#define DEBUG_ACT 1

#define POWER_MAX 64 //64

#define VEL_MAX 30

#define PIN_SERIAL_ST 3

#define KC 200
#define PC 2 // No pude terminar las pruebas ya que el sostenedor del motor se destruyó.

#define KP 120  
#define KI 0 
#define KD 0  

#define REF 0

double actuation = 0;
double error_prev = 0;
double error = 0;
double error_int = 0;
double error_dev = 0;
double measure = 0;
double ref = REF;

char command;

SoftwareSerial SWSerial(NOT_A_PIN, PIN_SERIAL_ST);
Sabertooth ST(128, SWSerial); // Address 128, and use SWSerial as the serial port.

// Registers for ADXL345
#define ADXL345_ADDRESS (0xA6 >> 1)  // address for device is 8 bit but shift to the
                                     // right by 1 bit to make it 7 bit because the
                                     // wire library only takes in 7 bit addresses
#define ADXL345_REGISTER_XLSB (0x32)

int accelerometer_data[3];

float A_x, ang_x, A_y, ang_y, A_z, ang_z;

// initialise and start everything
void setup() {
    SWSerial.begin(9600);
    ST.autobaud();
    Serial.begin(115200);
    Serial.println("BB8 - PID"); 
    Wire.begin();
    for(int i=0; i<3; ++i) {
    accelerometer_data[i]  = 0;
    }
    init_adxl345();
}


void loop() {
    read_adxl345();
    A_x = float(accelerometer_data[0])*3.9/1000;//3.9mg/LSB scale factor in 13-bit mode
    A_y = float(accelerometer_data[1])*3.9/1000;
    A_z = float(accelerometer_data[2])*3.9/1000;
    //ang_x = atan(A_x / sqrt(square(A_y) + square(A_z)));
    ang_y = atan(A_y / sqrt(square(A_x) + square(A_z)));
    //ang_z = atan(A_z / sqrt(square(A_x) + square(A_y)));


    if(PenduloPID()){
        if(Serial.available()){   
            command = Serial.read();
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
    }

    else penduloPID();

}
