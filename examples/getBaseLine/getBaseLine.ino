/*!
 * @file getBaseLine.ino
 * @brief Put the module in clear air and work a few minutes, wait for baseline doing not change 
 * @n Experiment phenomenon: get
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
    /*Wait for the chip to be initialized completely, and then exit*/
    while(CCS811.begin() != 0){
        Serial.println("failed to init chip, please check if the chip connection is fine");
        delay(1000);
    }
}
void loop() {
    if(CCS811.checkDataReady() == true){
        /*!
         * @brief Set baseline
         * @return baseline in clear air
         */
        Serial.println(CCS811.readBaseLine(), HEX);
        
    } else {
        Serial.println("Data is not ready!");
    }
    //delay cannot be less than measurement cycle
    delay(1000);
}
