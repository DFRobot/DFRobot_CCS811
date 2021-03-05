/*!
 * @file setConfig.ino
 * @brief Change data reading frequency, and read the concentration of carbon dioxide and TVOC. 
 * @n Experiment phenomenon: read data every 0.25 second, and print it on serial port. 
 *
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [LuoYufeng](yufeng.luo@dfrobot.com)
 * @version  V0.1
 * @date  2019-07-19
 * @get from https://www.dfrobot.com
 * @url https://github.com/DFRobot/DFRobot_CCS811
 */
#include "DFRobot_CCS811.h"

/*
 * IIC address default 0x5A, the address becomes 0x5B if the ADDR_SEL is soldered.
 */
//DFRobot_CCS811 CCS811(&Wire, /*IIC_ADDRESS=*/0x5A);
DFRobot_CCS811 CCS811;

void setup(void)
{
    Serial.begin(115200);
    /*Wait for the chip to be initailized completely, and then exit*/
    while(CCS811.begin() != 0){
        Serial.println("failed to init chip, please check if the chip connection is fine ");
        delay(1000);
    }
    Serial.print("current configured parameter code is ");
    Serial.println(CCS811.getMeasurementMode(),BIN);
    /**
     * @brief Measurement parameter configuration 
     * @param mode:in typedef enum{
     *              eClosed,      //Idle (Measurements are disabled in this mode)
     *              eCycle_1s,    //Constant power mode, IAQ measurement every second
     *              eCycle_10s,   //Pulse heating mode IAQ measurement every 10 seconds
     *              eCycle_60s,   //Low power pulse heating mode IAQ measurement every 60 seconds
     *              eCycle_250ms  //Constant power mode, sensor measurement every 250ms 1xx: Reserved modes (For future use)
     *          }eCycle_t;
     */
    CCS811.setMeasurementMode(CCS811.eCycle_250ms);
    //Serial.println(getMeasurementMode(),HEX);
    /**
     * @brief Set environment parameter
     * @param temperature Set temperature, unit:℃, range: -40~85℃
     * @param humidity    Set humidity, unit:RH, range: 0~100RH
     */
    CCS811.setInTempHum(/*temperature=*/25,/*humidity=*/50);
}
void loop() {
    if(CCS811.checkDataReady() == true){
        Serial.print("CO2: ");
        Serial.print(CCS811.getCO2PPM());
        Serial.print("ppm, TVOC: ");
        Serial.print(CCS811.getTVOCPPB());
        Serial.println("ppb ");
    }
    else{
        Serial.println("Data is not ready!");
    }
    //set the delay time according to working mode, should not be less than minimum delay time of the working mode
    CCS811.writeBaseLine(0x447B);
    delay(250);
}
