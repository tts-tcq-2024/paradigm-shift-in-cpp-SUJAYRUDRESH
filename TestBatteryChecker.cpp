#include "TestBatteryChecker.h"
#include "LanguageManager.h"  
#include "StatusManager.h" 
#include "BatteryChecker.h"  

void testStatusManager() {
    StatusManager statusManager;

    // Initialize status manager with statuses and messages
    statusManager.addStatusAndMessage(Parameter::SOC, "LOW_SOC_BREACH", 0, 20, {
        {Language::ENGLISH, "State of Charge too low!"},
        {Language::GERMAN, "Ladezustand zu niedrig!"}
    });
    statusManager.addStatusAndMessage(Parameter::SOC, "NORMAL", 25, 75, {
        {Language::ENGLISH, "Normal"},
        {Language::GERMAN, "Normal"}
    });

    // Test getStatuses
    auto socStatuses = statusManager.getStatuses(Parameter::SOC);
    assert(socStatuses.size() == 2); // We added 2 statuses

    // Test getMessage
    Status lowSocBreach(Parameter::SOC, "LOW_SOC_BREACH", 0, 20);
    assert(statusManager.getMessage(lowSocBreach, Language::ENGLISH) == "State of Charge too low!");
    assert(statusManager.getMessage(lowSocBreach, Language::GERMAN) == "Ladezustand zu niedrig!");

    // Test overall status messages
    statusManager.setOverallStatusMessage(Language::ENGLISH, "Overall battery status: ");
    assert(statusManager.getMessage(lowSocBreach, Language::ENGLISH) == "State of Charge too low!");

    std::cout << "StatusManager tests passed!" << std::endl;
}

void testBatteryChecker() {
    LanguageManager languageManager;
    StatusManager statusManager;

    // Initialize status manager with statuses and messages
    statusManager.addStatusAndMessage(Parameter::SOC, "LOW_SOC_BREACH", 0, 20, {
        {Language::ENGLISH, "State of Charge too low!"},
        {Language::GERMAN, "Ladezustand zu niedrig!"}
    });
    statusManager.addStatusAndMessage(Parameter::SOC, "NORMAL", 25, 75, {
        {Language::ENGLISH, "Normal"},
        {Language::GERMAN, "Normal"}
    });
    statusManager.addStatusAndMessage(Parameter::TEMPERATURE, "NORMAL", 11, 40, {
        {Language::ENGLISH, "Normal"},
        {Language::GERMAN, "Normal"}
    });

    BatteryChecker batteryChecker(languageManager, statusManager);

    languageManager.setLanguage(Language::ENGLISH);
    // Test case where SOC is in LOW_SOC_BREACH and temperature is NORMAL
    batteryChecker.checkBatteryStatus(30, 10, 0.5);  // Expect LOW_SOC_BREACH message

    languageManager.setLanguage(Language::GERMAN);
    // Test case where SOC is NORMAL and temperature is NORMAL
    batteryChecker.checkBatteryStatus(35, 25, 0.5);  // Expect NORMAL message

}
