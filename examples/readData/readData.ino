/*!
 * @file readData.ino
 * @brief Read the concentration of carbon dioxide and TVOC
 * @n Experiment phenomenon: read data every 0.5s, and print it out on serial port. 
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [LuoYufeng](yufeng.luo@dfrobot.com)
 * @maintainer  [fary](feng.yang@dfrobot.com)
 * @version  V0.1
 * @date  2019-07-19
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
    /*Wait for the chip to be initialized completely, and then exit*/
    while(CCS811.begin() != 0){
        Serial.println("failed to init chip, please check if the chip connection is fine");
        delay(1000);
    }
}
void loop() {
    if(CCS811.checkDataReady() == true){
        Serial.print("CO2: ");
        Serial.print(CCS811.getCO2PPM());
        Serial.print("ppm, TVOC: ");
        Serial.print(CCS811.getTVOCPPB());
        Serial.println("ppb");
        
    } else {
        Serial.println("Data is not ready!");
    }
    /*!
     * @brief Set baseline
     * @param get from getBaseline.ino
     */
    CCS811.writeBaseLine(0x447B);
    //delay cannot be less than measurement cycle
    delay(1000);
}
