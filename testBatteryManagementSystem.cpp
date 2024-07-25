#include <cassert>
#include <iostream>
#include "BatteryManagementSystem.h"

// Helper function to test language-specific messages
void testLanguageMessages() {
    // Set the language to English
    currentLanguage = Language::ENGLISH;
    assert(getMessage(Status::LOW_SOC_BREACH, Language::ENGLISH) == "State of Charge too low!");
    assert(getMessage(Status::HIGH_TEMP_WARNING, Language::ENGLISH) == "Temperature approaching high limit!");

    // Set the language to German
    currentLanguage = Language::GERMAN;
    assert(getMessage(Status::LOW_SOC_BREACH, Language::GERMAN) == "Ladezustand zu niedrig!");
    assert(getMessage(Status::HIGH_TEMP_WARNING, Language::GERMAN) == "Temperatur nähert sich dem hohen Limit!");
}

void testBatteryIsOk() {
    BatteryManagementSystem bms;
    
    // Testing with values within range
    assert(bms.batteryIsOk(25, 70, 0.7) == true);
    assert(bms.batteryIsOk(0, 20, 0) == true);
    assert(bms.batteryIsOk(45, 80, 0.8) == true);

    // Testing with values out of range
    assert(bms.batteryIsOk(-1, 20, 0) == false);
    assert(bms.batteryIsOk(25, 19, 0.7) == false);
    assert(bms.batteryIsOk(25, 70, 0.9) == false);
    assert(bms.batteryIsOk(50, 85, 0) == false);

    // Testing with boundary values
    assert(bms.batteryIsOk(0, 20, 0) == true);
    assert(bms.batteryIsOk(45, 80, 0.8) == true);
    assert(bms.batteryIsOk(45.1, 80, 0.8) == false);
    assert(bms.batteryIsOk(45, 80.1, 0.8) == false);
    assert(bms.batteryIsOk(45, 80, 0.81) == false);
}

void runTests() {
    testBatteryIsOk();
    testLanguageMessages();
    std::cout << "All tests passed!" << std::endl;
}
