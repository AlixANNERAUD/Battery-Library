///
 /// @file Battery_Library.hpp
 /// @author Alix ANNERAUD (alix.anneraud@outlook.fr)
 /// @brief Battery management library header file.
 /// @version 0.1
 /// @date 02-04-2021
 /// 
 /// @copyright Copyright (c) 2021
 /// 

#ifndef BATTERY_H_INCLUDED
#define BATTERY_H_INCLUDED

#include "Arduino.h"

class Battery_Class
{
public:
    Battery_Class(uint8_t Sensing_Pin, uint16_t Minimum_Voltage, uint16_t Maximum_Voltage, float Resistor_1, float Resistor_2);
    Battery_Class(uint8_t Sensing_Pin, uint16_t Minimum_Voltage, uint16_t Maximum_Voltage, float Conversion_Factor);
    Battery_Class();
    ~Battery_Class();

    inline void Set_Voltages(uint16_t Minimum_Voltage, uint16_t Maximum_Voltage)
    {
        this->Minimum_Voltage = Minimum_Voltage;
        this->Maximum_Voltage = Maximum_Voltage;
    }

    inline void Set_Resistors(float Resistor_1, float Resistor_2)
    {
        Conversion_Factor = Resistor_1 + Resistor_2;
        Conversion_Factor /= Resistor_2;
    }

    inline void Set_Conversion_Factor(float Conversion_Factor)
    {
        this->Conversion_Factor = Conversion_Factor;
    }

    inline void Set_Sessing_Pin(uint8_t Sensing_Pin)
    {
        this->Sensing_Pin = Sensing_Pin;
    }

    inline uint8_t Get_Sensing_Pin()
    {
        return Sensing_Pin;
    }

    inline float Get_Conversion_Factor()
    {
        return Conversion_Factor;
    }

    inline uint16_t Get_Minimum_Voltage()
    {
        return Minimum_Voltage;
    }

    inline uint16_t Get_Maximum_Voltage()
    {
        return Maximum_Voltage;
    }

    uint8_t Get_Charge_Level();
    uint16_t Get_Voltage();

protected:
    uint8_t Sensing_Pin;
    float Conversion_Factor;
    uint16_t Minimum_Voltage;
    uint16_t Maximum_Voltage;
};

#endif