///
 /// @file Battery_Library.cpp
 /// @author Alix ANNERAUD (alix.anneraud@outlook.fr)
 /// @brief Battery management library source file.
 /// @version 0.1.0
 /// @date 21/05/2020
 /// 
 /// @copyright Copyright (c) 2021
 /// 


#include "Battery_Library.hpp"

Battery_Class::Battery_Class(uint8_t Sensing_Pin, uint16_t Minimum_Voltage, uint16_t Maximum_Voltage, float Resistor_1, float Resistor_2)
    : Sensing_Pin(Sensing_Pin),
      Minimum_Voltage(Minimum_Voltage),
      Maximum_Voltage(Maximum_Voltage)
{
    // Calculate conversion factor (maximum output voltage of the voltage divider)
    Set_Resistors(Resistor_1, Resistor_2);

    pinMode(Sensing_Pin, INPUT);
}

Battery_Class::~Battery_Class()
{
}

uint16_t Battery_Class::Get_Voltage()
{
    if (Sensing_Pin == 0xFF)
    {
        return 0;
    }
    return (((analogRead(Sensing_Pin) * 3300) / 4096) * Conversion_Factor);
}

uint8_t Battery_Class::Get_Charge_Level()
{
    if (Maximum_Voltage - Minimum_Voltage == 0 || Sensing_Pin == 0xFF)
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
