/**
 * @file Battery.cpp
 * @brief Xila's battery management driver source file.
 * @author Alix ANNERAUD
 * @copyright MIT License
 * @version 0.1.0
 * @date 21/05/2020
 * @details Xila battery driver definition, used by the core and softwares to know the INR 18650 25R level of charge.
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

#include "Battery_Library.hpp"

Battery_Class::Battery_Class(uint8_t Battery_Sensing_Pin, uint16_t Minimum_Voltage, uint16_t Maximum_Voltage, float Resistor_1, float Resistor_2)
    : Sensing_Pin(Battery_Sensing_Pin),
    Minimum_Voltage(Minimum_Voltage),
    Maximum_Voltage(Maximum_Voltage)
{
    pinMode(34, INPUT);

    // Calculate conversion factor (maximum output voltage of the voltage divider)
    Conversion_Factor = Resistor_1 + Resistor_2;
    Conversion_Factor /= Resistor_2;
}

Battery_Class::~Battery_Class()
{
}

uint16_t Battery_Class::Get_Voltage()
{
    return (((analogRead(Sensing_Pin) * 3300) / 4096) * Conversion_Factor);
}

uint8_t Battery_Class::Get_Charge_Level()
{
    if (Maximum_Voltage - Minimum_Voltage == 0)
    {
        return 0;
    }
    
    uint32_t Current_Level = analogRead(Sensing_Pin);

    uint8_t i = 1;
    for (; i < 10; i++)
    {
        Current_Level += analogRead(Sensing_Pin);
    }
    Current_Level /= i;
    Current_Level = (Current_Level * 3300) / 4096;
    Current_Level *= Conversion_Factor;
    Current_Level -= Minimum_Voltage;
    Current_Level = Current_Level * 100;
    Current_Level /= Maximum_Voltage - Minimum_Voltage;
    return Current_Level;
}
