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
//DFRobot_CCS811 sensor(&Wire, /*IIC_ADDRESS=*/0x5A);
DFRobot_CCS811 sensor;

void setup(void)
{
    Serial.begin(115200);
    /*Wait for the chip to be initailized completely, and then exit*/
    while(sensor.begin() != 0){
        Serial.println("failed to init chip, please check if the chip connection is fine ");
        delay(1000);
    }
    Serial.print("current configured parameter code is ");
    Serial.println(sensor.getMeasurementMode(),BIN);
    /**
     * @brief Measurement parameter configuration 
     * @param thresh:0 for Interrupt mode operates normally; 1 for interrupt mode only asserts the nINT signal (driven low) if the new
     * @param interrupt:0 for Interrupt generation is disabled; 1 for the nINT signal is asserted (driven low) when a new sample is ready in
     * @param mode:in typedef enum{
     *                eMode0, //Idle (Measurements are disabled in this mode)
     *                eMode1, //Constant power mode, IAQ measurement every second
     *                eMode2, //Pulse heating mode IAQ measurement every 10 seconds
     *                eMode3, //Low power pulse heating mode IAQ measurement every 60 seconds
     *                eMode4  //Constant power mode, sensor measurement every 250ms
     *               }eDRIVE_MODE_t;
     */
    sensor.setMeasurementMode(0, 0, sensor.eMode4);
    //Serial.println(getMeasurementMode(),HEX);
    /**
     * @brief Set environment parameter
     * @param temperature Set temperature, unit:℃, range: -40~85℃
     * @param humidity    Set humidity, unit:RH, range: 0~100RH
     */
    sensor.setInTempHum(/*temperature=*/25,/*humidity=*/50);
}
void loop() {
    if(sensor.checkDataReady() == true){
        Serial.print("CO2: ");
        Serial.print(sensor.getCO2PPM());
        Serial.print("ppm, TVOC: ");
        Serial.print(sensor.getTVOCPPB());
        Serial.println("ppb ");
    }
    else{
        Serial.println("Data is not ready!");
    }
    //set the delay time according to working mode, should not be less than minimum delay time of the working mode
    sensor.writeBaseLine(0x847B);
    delay(250);
}
