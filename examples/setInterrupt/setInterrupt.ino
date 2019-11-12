/*!
 * @file setInterrupt.ino
 * @brief Set interrupt parameter, when CO2 concentration range changes, get an interrupt
 * @n Experiment phenomenon: read data every 1s, and print it out on serial port.
 *
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [LuoYufeng](yufeng.luo@dfrobot.com)
 * @version  V1.0
 * @date  2019-07-13
 * @https://github.com/DFRobot/DFRobot_Sensor
 */
#include "DFRobot_CCS811.h"

volatile  int8_t GPIO1TRIG = 0;

/*
 * IIC address default 0x5A, the address becomes 0x5B if the ADDR_SEL is soldered.
 */
//DFRobot_CCS811 sensor(&Wire, /*IIC_ADDRESS=*/0x5A);
DFRobot_CCS811 sensor;

void setup(void)
{
    Serial.begin(115200);
    /*wait for the chip to be initialized completely, and then exit*/
    while(sensor.begin() != 0){
        Serial.println("failed to init chip, please check if the chip connection is fine");
        delay(1000);
    }
    attachInterrupt(0, interrupt, RISING);
    sensor.setMeasurementMode(1, 1, sensor.eMode4);
    /**
     * @brief Set interrupt thresholds 
     * @param lowToMed: interrupt triggered value in range low to middle 
     * @param medToHigh: interrupt triggered value in range middle to high 
     */
    sensor.setThresholds(1500,2500);
}
void loop() {
    if(GPIO1TRIG == 1){
        Serial.println("CO2 range has changed");
        Serial.print("CO2: ");
        Serial.print(sensor.getCO2PPM());
        Serial.print("ppm, TVOC: ");
        Serial.print(sensor.getTVOCPPB());
        Serial.println("ppb");
        delay(1000);
    }
    GPIO1TRIG = 0;
    Serial.print("CO2: ");
    Serial.print(sensor.getCO2PPM());
    Serial.print("ppm, TVOC: ");
    Serial.print(sensor.getTVOCPPB());
    Serial.println("ppb");
    sensor.writeBaseLine(0x847B);
    delay(1000);
}


void interrupt(){
  GPIO1TRIG = 1;
}

