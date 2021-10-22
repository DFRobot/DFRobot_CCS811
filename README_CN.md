# DFRobot_CCS811
- [English Version](./README.md)

CCS811空气质量传感器能够测量eCO2(equivalent CO2)和TVOC(Total Volatile Organic Compounds)浓度。可用于空气测量应用，例如：空气质量检测、空气净化器、新风系统等。
CCS811使用AMS独有的微热板技术，相比传统的气体传感器，功耗更低、预热时间更短、体积更小。内部集成ADC和MCU，可以对数据进行采集、计算，并且通过I2C返回数据。
CCS811支持多种模式：每1秒、10秒、1分钟、250毫秒测量一次以及休眠模式，这些模式在传感器测量期间进行了低功耗优化，因此CCS811适用于便携式应用。CCS811支持浓度报警，
当浓度超过用户设置的阈值时，INT引脚就会触发。
⚠注意：该芯片对I2C进行了时钟延展，有些控制器不支持时钟延展，例如树莓派。

**二氧化碳浓度参考**

二氧化碳浓度(ppm)|人体反映
------------------  | -----
<500	    |正常        |
500-1000	|感到空气污浊 |
1000-2500	|感到困倦     |
2500-5000	|对健康不利   |
大于5000	|有中毒危险    |

**TVOC浓度参考**

TVOC浓度(ppb)       | 人体反应   |
------------------  |  -----
<50	                |     正常                        |
50-750              |     可能会急躁不安和不舒服        |
750-6000            |     可能会急躁不安、不舒服和头疼  |
大于6000               |     头痛和其他神经问题           |

<br>
<img src="./resources/images/SEN0318-image.jpg">
<br>

* Arduino UNO
<br>
<img src="./resources/images/SEN0318-CONNECT.jpg">
<br>

## 产品链接(https://www.dfrobot.com.cn/goods-2677.html)

    SKU：SEN0315

## 目录

* [概述](#概述)
* [库安装](#库安装)
* [方法](#方法)
* [兼容性](#兼容性)
* [历史](#历史)
* [创作者](#创作者)
 
## 概述

1. 读取二氧化碳浓度(单位:ppm) <br>
2. 读取TVOC浓度(单位:ppb)<br>
3. 改变数据读取的采样间隔以改变功耗 <br>
4. 设置环境参数来校准读数 <br>
5. 支持中断测量 <br>

## 库安装

这里提供两种使用本库的方法：
1. 打开Arduino IDE,在状态栏中的Tools--->Manager Libraries 搜索"DFRobot_VEML6075"并安装本库.
2. 首先下载库文件,将其粘贴到\Arduino\libraries目录中,然后打开examples文件夹并在该文件夹中运行演示.


## 方法

```C++
    /**
     * @fn begin
     * @brief 初始化函数
     * @return 初始化结果
     * @retval ERR_OK          初始化成功
     * @retval ERR_DATA_BUS    总线数据错误
     * @retval ERR_IC_VERSION  传感器id错误
     */ 
    int begin();

    /**
     * @fn checkDataReady
     * @brief 判断传感器数据是否准备就绪
     * @return  检查结果
     * @retval  true   数据准备就绪
     * @retval  false  数据还未准备好
     */
    bool checkDataReady();

    /**
     * @fn softReset
     * @brief 复位传感器，清除所有配置数据。
     */
    void softReset();

    /**
     * @fn setInTempHum
     * @brief 设置环境参数
     * @param temperature 设定温度值，单位:摄氏度，范围(-40~85℃)
     * @param humidity    设置湿度值，单位:RH，范围(0~100)
     */
    void setInTempHum(float temperature, float humidity);

    /**
     * @fn setMeasurementMode
     * @brief 测量参数配置
     * @param mode
     * @n            eClosed       空闲(在此模式下测量被禁用)
     * @n            eCycle_1s     恒功率模式，每秒测量室内空气质量
     * @n            eCycle_10s    每10秒测量一次脉冲加热模式的室内空气质量
     * @n            eCycle_60s    每60秒测量一次低功率脉冲加热模式的室内空气质量
     * @n            eCycle_250ms  恒功率模式，传感器每250ms测量一次1xx:预留模式(供以后使用)
     * @param thresh  阈值中断模式
     * @n            0             正常中断模式
     * @n            1             达到或者超过阈值产生中断信号
     * @param interrupt
     * @n            0             禁止中断模式
     * @n            1             当一个新的样本准备就绪时，int信号被触发(驱动低)
     */
    void setMeasurementMode(eCycle_t mode, uint8_t thresh = 0, uint8_t interrupt = 0);

    /**
     * @fn setThresholds
     * @brief 设置中断阈值
     * @param lowToMed: 中断触发值范围从低到中
     * @param medToHigh: 中断触发值范围中至高
     */
    void setThresholds(uint16_t lowToMed, uint16_t medToHigh);

    /**
     * @fn getMeasurementMode
     * @brief 获取当前配置参数
     * @return configuration code, needs to be converted into binary code to analyze
     * @n       第二位： 0 正常中断模式；1:当数据不在阈值内，中断模式触发nINT信号
     * @n       第三位:  0 禁止中断； 1: 当一个新的样本准备就绪时，int信号被触发(驱动低)
     * @n       第四到六位: 详情见 eCycle_t
     */
    uint8_t getMeasurementMode();

    /**
     * @fn getCO2PPM
     * @brief 获取当前的二氧化碳浓度
     * @return 当前二氧化碳浓度，单位:ppm
     */
    uint16_t getCO2PPM();

    /**
     * @fn getTVOCPPB
     * @brief 得到当前TVOC浓度
     * @return 当前TVOC浓度，单位:ppb
     */
    uint16_t getTVOCPPB();

    /**
     * @fn readBaseLine
     * @brief 获取当前基线数
     * @return 当前基线数，16进制数
     */
    uint16_t readBaseLine();

    /**
     * @fn writeBaseLine
     * @brief 将基线数写入寄存器
     * @param baseLine 基线数
     */
    void writeBaseLine(uint16_t baseLine);
```

## 兼容性

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino uno        |      √       |              |             | 
Mega2560        |      √       |              |             | 
Leonardo        |      √       |              |             | 
ESP32        |      √       |              |             | 
micro:bit        |      √       |              |             | 


## 历史

- 2021/10/22 - 1.0.1 版本
- 2019/07/19 - 1.0.0 版本

## 创作者

Written by yangfeng(feng.yang@dfrobot.com), 2021. (Welcome to our [website](https://www.dfrobot.com/))
