/*!
 * @file setInterrupt.ino
 * @brief Set interrupt parameter, when CO2 concentration range changes, get an interrupt
 * @n Experiment phenomenon: read data every 1s, and print it out on serial port.
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [LuoYufeng](yufeng.luo@dfrobot.com)
 * @maintainer  [fary](feng.yang@dfrobot.com)
 * @version  V1.0
 * @date  2019-07-13
 * @url https://github.com/DFRobot/DFRobot_Sensor
 */
#include "DFRobot_CCS811.h"

volatile  int8_t GPIO1TRIG = 0;

/*
 * IIC address default 0x5A, the address becomes 0x5B if the ADDR_SEL is soldered.
 */
//DFRobot_CCS811 CCS811(&Wire, /*IIC_ADDRESS=*/0x5A);
DFRobot_CCS811 CCS811;

void setup(void)
{
    Serial.begin(115200);
    /*wait for the chip to be initialized completely, and then exit*/
    while(CCS811.begin() != 0){
        Serial.println("failed to init chip, please check if the chip connection is fine");
        delay(1000);
    }
    attachInterrupt(0, interrupt, RISING);
    /**
     * Measurement parameter configuration 
     * mode:in typedef enum{
     *       eClosed,      //Idle (Measurements are disabled in this mode)
     *       eCycle_1s,    //Constant power mode, IAQ measurement every second
     *       eCycle_10s,   //Pulse heating mode IAQ measurement every 10 seconds
     *       eCycle_60s,   //Low power pulse heating mode IAQ measurement every 60 seconds
     *       eCycle_250ms  //Constant power mode, sensor measurement every 250ms 1xx: Reserved modes (For future use)
     *   }eCycle_t;
     * thresh:0 for Interrupt mode operates normally; 1 for interrupt mode only asserts the nINT signal (driven low) if the new
     * interrupt:0 for Interrupt generation is disabled; 1 for the nINT signal is asserted (driven low) when a new sample is ready in
     */
    CCS811.setMeasurementMode(CCS811.eCycle_250ms, 1, 1);
    /**
     * Set interrupt thresholds 
     * lowToMed: interrupt triggered value in range low to middle 
     * medToHigh: interrupt triggered value in range middle to high 
     */
    CCS811.setThresholds(1500,2500);
}
void loop() {
    if(GPIO1TRIG == 1){
        Serial.println("CO2 range has changed");
        Serial.print("CO2: ");
        Serial.print(CCS811.getCO2PPM());
        Serial.print("ppm, TVOC: ");
        Serial.print(CCS811.getTVOCPPB());
        Serial.println("ppb");
        delay(1000);
    }
    GPIO1TRIG = 0;
    Serial.print("CO2: ");
    Serial.print(CCS811.getCO2PPM());
    Serial.print("ppm, TVOC: ");
    Serial.print(CCS811.getTVOCPPB());
    Serial.println("ppb");
    CCS811.writeBaseLine(0x447B);
    delay(1000);
}


void interrupt(){
  GPIO1TRIG = 1;
}

