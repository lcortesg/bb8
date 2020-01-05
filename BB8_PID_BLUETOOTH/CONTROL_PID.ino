/**
 * @function penduloPID : Función de equilibrio PID
 * @param : ang_y
 * @return : Equilibra el contrapeso con un control PID
 */

bool penduloPID(){
    measure = ang_y;
    error = ref - measure;
    error_int += (actuation >= POWER_MAX)?(0):(error);
    error_dev = error - error_prev;
    error_prev = error;
    actuation = (error*KP + error_int*KI + error_dev*KD);
    actuation = (actuation >= POWER_MAX)?(POWER_MAX):(actuation <= -POWER_MAX)?(-POWER_MAX):(actuation);
    ST.motor(1, actuation);

    #if DEBUG_PID > NONE
        Serial.print("\n>>> LOG: measure:\t");
        Serial.println(measure);
        Serial.print("\n>>> LOG: error:\t");
        Serial.println(error);
        Serial.print("\n>>> LOG: error int:\t");
        Serial.println(error_int);
        Serial.print("\n>>> LOG: error_dev:\t");
        Serial.println(error_dev);
        Serial.print("\n>>> LOG: error_prev:\t");
        Serial.println(error_prev);
        Serial.print("\n>>> LOG: actuation:\t");
        Serial.println(actuation);
    #endif

    #if DEBUG_ACT > NONE
        Serial.print("\n>>> LOG: actuation:\t");
        Serial.println(actuation);
    #endif

    return ( (ang_y >= -0.1) && (ang_y <= 0.1) && (actuation < 10) );

}


void run(){
    unsigned long next = millis() + 10000;
    actuation = 0;
    if(actuation < POWER_MAX){
        while(millis() < next){
            actuation = (actuation >= POWER_MAX)?(POWER_MAX):(actuation+10);
            ST.motor(1, actuation);
            delay(20);
        }
    }
    else{
        ST.motor(1, POWER_MAX);
    }
    return;
}


void pendulo(){
    measure = ang_y;
    error = ref - measure;
    error_int += (actuation >= POWER_MAX)?(0):(error);
    error_dev = error - error_prev;
    error_prev = error;
    actuation = (error*KP + error_int*KI + error_dev*KD);
    actuation = (actuation >= POWER_MAX)?(POWER_MAX):(actuation <= -POWER_MAX)?(-POWER_MAX):(actuation);
    ST.motor(1, actuation);
    //delay(20);

    #if DEBUG_PID > NONE
        Serial.print("\n>>> LOG: measure:\t");
        Serial.println(measure);
        Serial.print("\n>>> LOG: error:\t");
        Serial.println(error);
        Serial.print("\n>>> LOG: error int:\t");
        Serial.println(error_int);
        Serial.print("\n>>> LOG: error_dev:\t");
        Serial.println(error_dev);
        Serial.print("\n>>> LOG: error_prev:\t");
        Serial.println(error_prev);
        Serial.print("\n>>> LOG: actuation:\t");
        Serial.println(actuation);
    #endif
        
    #if DEBUG_ACT > NONE
        Serial.print("\n>>> LOG: actuation:\t");
        Serial.println(actuation);
    #endif
}
