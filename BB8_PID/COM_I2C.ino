/**
 * @function I2C : Driver I2C
 * @param : address, reg, data
 * @return : Valores obtenidos del acelerómetro
 */

// void because this only tells the cip to send data to its output register
// writes data to the slave's buffer
void i2c_write(int address, byte reg, byte data) {

    // Send output register address
    Wire.beginTransmission(address);
    // Connect to device
    Wire.write(reg);
    // Send data
    Wire.write(data); //low byte
    Wire.endTransmission();
}


// void because using pointers
// microcontroller reads data from the sensor's input register
void i2c_read(int address, byte reg, int count, byte* data) {
    // Used to read the number of data received
    int i = 0;
    // Send input register address
    Wire.beginTransmission(address);
    // Connect to device
    Wire.write(reg);
    Wire.endTransmission();

    // Connect to device
    Wire.beginTransmission(address);
    // Request data from slave
    // Count stands for number of bytes to request
    Wire.requestFrom(address, count);
    while(Wire.available()){ // slave may send less than requested
        char c = Wire.read(); // receive a byte as character
        data[i] = c;
        i++;
    }
    Wire.endTransmission();
}




void init_adxl345() {
    byte data = 0;

    i2c_write(ADXL345_ADDRESS, 0x31, 0x0B);   // 13-bit mode  +_ 16g
    i2c_write(ADXL345_ADDRESS, 0x2D, 0x08);   // Power register


    i2c_write(ADXL345_ADDRESS, 0x1E, 0x00);   // x
    i2c_write(ADXL345_ADDRESS, 0x1F, 0x00);   // Y
    i2c_write(ADXL345_ADDRESS, 0x20, 0x05);   // Z

    // Check to see if it worked!
    i2c_read(ADXL345_ADDRESS, 0X00, 1, &data);
    if(data==0xE5) Serial.println("it work Success");
    else Serial.println("it work Fail");
}

void read_adxl345() {
    byte bytes[6];
    memset(bytes,0,6);

    // Read 6 bytes from the ADXL345
    i2c_read(ADXL345_ADDRESS, ADXL345_REGISTER_XLSB, 6, bytes);
    // Unpack data
    for (int i=0;i<3;++i) {
        accelerometer_data[i] = (int)bytes[2*i] + (((int)bytes[2*i + 1]) << 8);
    }

    #if DEBUG_ACE > NONE
        Serial.print(ang_x);
        Serial.print("\t");
        Serial.print(ang_y);
        Serial.print("\t");
        Serial.print(ang_z);
        Serial.print("\n");
    #endif
    #if DEBUG_ANG > NONE
        Serial.print("\n>>> LOG: angle y:\t");
        Serial.println(ang_y);
    #endif
}
