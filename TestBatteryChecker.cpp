#include <cassert>
#include <iostream>
#include "LanguageManager.h"
#include "StatusManager.h"
#include "BatteryChecker.h"

void testStatusManager() {
    StatusManager statusManager;
    statusManager.addParameter(Parameter::SOC, "LOW_SOC_BREACH", 0, 20, {
        {Language::ENGLISH, "State of Charge too low!"},
        {Language::GERMAN, "Ladezustand zu niedrig!"}
    });
    statusManager.addParameter(Parameter::SOC, "NORMAL", 25, 75, {
        {Language::ENGLISH, "Normal"},
        {Language::GERMAN, "Normal"}
    });

    auto socStatuses = statusManager.getStatuses(Parameter::SOC);
    assert(socStatuses.size() == 2); // We added 2 statuses

    Status lowSocBreach(Parameter::SOC, "LOW_SOC_BREACH", 0, 20);
    assert(statusManager.getMessage(lowSocBreach, Language::ENGLISH) == "State of Charge too low!");
    assert(statusManager.getMessage(lowSocBreach, Language::GERMAN) == "Ladezustand zu niedrig!");

    statusManager.setOverallStatusMessage(Language::ENGLISH, "Overall battery status: ");
    assert(statusManager.getMessage(lowSocBreach, Language::ENGLISH) == "State of Charge too low!");

    std::cout << "StatusManager tests passed!" << std::endl;
}

void testBatteryChecker() {
    LanguageManager languageManager;
    StatusManager statusManager;

    statusManager.addParameter(Parameter::SOC, "LOW_SOC_BREACH", 0, 20, {
        {Language::ENGLISH, "State of Charge too low!"},
        {Language::GERMAN, "Ladezustand zu niedrig!"}
    });
    statusManager.addParameter(Parameter::SOC, "NORMAL", 25, 75, {
        {Language::ENGLISH, "Normal"},
        {Language::GERMAN, "Normal"}
    });
    statusManager.addParameter(Parameter::TEMPERATURE, "NORMAL", 11, 40, {
        {Language::ENGLISH, "Normal"},
        {Language::GERMAN, "Normal"}
    });

    BatteryChecker batteryChecker(languageManager, statusManager);

    languageManager.setLanguage(Language::ENGLISH);
    batteryChecker.checkBatteryStatus(30, 10, 0.5);  // Expect LOW_SOC_BREACH message

    languageManager.setLanguage(Language::GERMAN);
    batteryChecker.checkBatteryStatus(35, 25, 0.5);  // Expect NORMAL message
}
