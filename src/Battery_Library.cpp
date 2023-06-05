/// @file Battery_Library.cpp
/// @author Alix ANNERAUD (alix.anneraud@outlook.fr)
/// @brief Battery management library source file.
/// @version 0.1.0
/// @date 21/05/2020
///
/// @copyright Copyright (c) 2021

#include "Battery_Library.hpp"

Battery_Class::Battery_Class(uint8_t Sensing_Pin, uint16_t Minimum_Voltage, uint16_t Maximum_Voltage, float Resistor_1, float Resistor_2)
    : Sensing_Pin(Sensing_Pin),
      Minimum_Voltage(Minimum_Voltage),
      Maximum_Voltage(Maximum_Voltage),
      Reading_Index(0)
{
    for (uint8_t i = 0; i < Battery_Number_Of_Readings; i++)
        Readings[i] = 0;

    // Calculate conversion factor (maximum output voltage of the voltage divider)
    Set_Resistors(Resistor_1, Resistor_2);

    pinMode(Sensing_Pin, INPUT);
}

Battery_Class::Battery_Class(uint8_t Sensing_Pin, uint16_t Minimum_Voltage, uint16_t Maximum_Voltage, float Conversion_Factor)
    : Sensing_Pin(Sensing_Pin),
      Conversion_Factor(Conversion_Factor),
      Minimum_Voltage(Minimum_Voltage),
      Maximum_Voltage(Maximum_Voltage),
        Reading_Index(0)
{
    for (uint8_t i = 0; i < Battery_Number_Of_Readings; i++)
        Readings[i] = 0;

    pinMode(Sensing_Pin, INPUT);
}

Battery_Class::Battery_Class()
    : Sensing_Pin(0xFF),
      Conversion_Factor(0),
      Minimum_Voltage(0),
      Maximum_Voltage(0)
{
}

Battery_Class::~Battery_Class()
{
}

uint16_t Battery_Class::Get_Voltage()
{
    if (Sensing_Pin == 0xFF)
        return 0;

    // - Fill the readings array with the current reading
    while (Readings[Reading_Index] == 0)
    {
        Readings[Reading_Index] = analogRead(Sensing_Pin);
        Reading_Index = (Reading_Index + 1) % Battery_Number_Of_Readings;
        delayMicroseconds(1000);
    }

    Readings[Reading_Index] = analogRead(Sensing_Pin);
    Reading_Index = (Reading_Index + 1) % Battery_Number_Of_Readings;

    uint32_t Average = 0;

    for (uint8_t i = 0; i < Battery_Number_Of_Readings; i++)
        Average += Readings[i];

    return (((Average / Battery_Number_Of_Readings) * 3200) / 4096) * Conversion_Factor;
}

uint8_t Battery_Class::Get_Charge_Level()
{
    if (Maximum_Voltage - Minimum_Voltage == 0 || Sensing_Pin == 0xFF)
        return 0;

    uint16_t Current_Level = Get_Voltage();

    if (Current_Level < Minimum_Voltage)
        return 0;
    else if (Current_Level > Maximum_Voltage)
        return 100;

    return (Current_Level - Minimum_Voltage) / ((Maximum_Voltage - Minimum_Voltage) / 100);
}
