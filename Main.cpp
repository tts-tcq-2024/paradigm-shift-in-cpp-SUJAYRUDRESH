#include <iostream>
#include "LanguageManager.h"
#include "StatusManager.h"
#include "BatteryChecker.h"

int main() {
    LanguageManager languageManager;
    StatusManager statusManager;

    // Initialize status manager with statuses and messages
    statusManager.addStatusAndMessage(Parameter::SOC, "LOW_SOC_BREACH", 0, 20, {
        {Language::ENGLISH, "State of Charge too low!"},
        {Language::GERMAN, "Ladezustand zu niedrig!"}
    });
    statusManager.addStatusAndMessage(Parameter::SOC, "LOW_SOC_WARNING", 21, 24, {
        {Language::ENGLISH, "State of Charge approaching low limit!"},
        {Language::GERMAN, "Ladezustand nähert sich dem niedrigen Limit!"}
    });
    statusManager.addStatusAndMessage(Parameter::SOC, "NORMAL", 25, 75, {
        {Language::ENGLISH, "Normal"},
        {Language::GERMAN, "Normal"}
    });
    statusManager.addStatusAndMessage(Parameter::SOC, "HIGH_SOC_WARNING", 76, 80, {
        {Language::ENGLISH, "State of Charge approaching high limit!"},
        {Language::GERMAN, "Ladezustand nähert sich dem hohen Limit!"}
    });
    statusManager.addStatusAndMessage(Parameter::SOC, "HIGH_SOC_BREACH", 81, 100, {
        {Language::ENGLISH, "State of Charge too high!"},
        {Language::GERMAN, "Ladezustand zu hoch!"}
    });

    statusManager.addStatusAndMessage(Parameter::TEMPERATURE, "LOW_TEMP_BREACH", -10, 0, {
        {Language::ENGLISH, "Temperature too low!"},
        {Language::GERMAN, "Temperatur zu niedrig!"}
    });
    statusManager.addStatusAndMessage(Parameter::TEMPERATURE, "LOW_TEMP_WARNING", 1, 10, {
        {Language::ENGLISH, "Temperature approaching low limit!"},
        {Language::GERMAN, "Temperatur nähert sich dem niedrigen Limit!"}
    });
    statusManager.addStatusAndMessage(Parameter::TEMPERATURE, "NORMAL", 11, 40, {
        {Language::ENGLISH, "Normal"},
        {Language::GERMAN, "Normal"}
    });
    statusManager.addStatusAndMessage(Parameter::TEMPERATURE, "HIGH_TEMP_WARNING", 41, 45, {
        {Language::ENGLISH, "Temperature approaching high limit!"},
        {Language::GERMAN, "Temperatur nähert sich dem hohen Limit!"}
    });
    statusManager.addStatusAndMessage(Parameter::TEMPERATURE, "HIGH_TEMP_BREACH", 46, 50, {
        {Language::ENGLISH, "Temperature too high!"},
        {Language::GERMAN, "Temperatur zu hoch!"}
    });

    statusManager.addStatusAndMessage(Parameter::CHARGE_RATE, "NORMAL", 0, 0.7, {
        {Language::ENGLISH, "Charge Rate normal."},
        {Language::GERMAN, "Laderate normal."}
    });
    statusManager.addStatusAndMessage(Parameter::CHARGE_RATE, "HIGH_CHARGE_RATE_WARNING", 0.71, 0.8, {
        {Language::ENGLISH, "Charge Rate approaching high limit!"},
        {Language::GERMAN, "Laderate nähert sich dem hohen Limit!"}
    });
    statusManager.addStatusAndMessage(Parameter::CHARGE_RATE, "HIGH_CHARGE_RATE_BREACH", 0.81, 1.0, {
        {Language::ENGLISH, "Charge Rate too high!"},
        {Language::GERMAN, "Laderate zu hoch!"}
    });

    // Set overall status messages
    statusManager.setOverallStatusMessage(Language::ENGLISH, "Overall battery status: ");
    statusManager.setOverallStatusMessage(Language::GERMAN, "Gesamtbatteriestatus: ");

    BatteryChecker batteryChecker(languageManager, statusManager);

    languageManager.setLanguage(Language::ENGLISH);
    batteryChecker.checkBatteryStatus(25, 70, 0.75);

    languageManager.setLanguage(Language::GERMAN);
    batteryChecker.checkBatteryStatus(50, 85, 0.9);

    return 0;
}
