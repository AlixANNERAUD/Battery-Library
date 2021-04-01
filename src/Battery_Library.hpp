/**
 * @file Battery.cpp
 * @brief Xila's battery management driver header file.
 * @author Alix ANNERAUD
 * @copyright MIT License
 * @version 0.1.0
 * @date 21/05/2020
 * @details Xila battery driver declaration, used by the core and softwares to know the INR 18650 25R level of charge.
 * @section License
 * 
 * Copyright (c) 2020 Alix ANNERAUD
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * 
*/

#ifndef BATTERY_H_INCLUDED
#define BATTERY_H_INCLUDED

#include "Arduino.h"

/* Conversion factor =  With a voltage divider with 1:1 relation (here 47 kOhm / 47 kOhm)*/

class Battery_Class
{
public:
    Battery_Class(uint8_t Sensing_Pin = 0xFF, uint16_t Minimum_Voltage = 0, uint16_t Maximum_Voltage = 0, float Resistor_1 = 10, float Resistor_2 = 10);
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

    uint8_t Get_Charge_Level();
    uint16_t Get_Voltage();

protected:
    uint8_t Sensing_Pin;
    float Conversion_Factor;
    uint16_t Minimum_Voltage;
    uint16_t Maximum_Voltage;
};

#endif