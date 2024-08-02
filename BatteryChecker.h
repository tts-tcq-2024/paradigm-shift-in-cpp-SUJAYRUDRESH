#ifndef BATTERYCHECKER_H
#define BATTERYCHECKER_H

#include "LanguageManager.h"
#include "StatusManager.h"
#include "BatteryParameterInfo.h"

class BatteryChecker {
public:
    BatteryChecker(LanguageManager& languageManager, StatusManager& statusManager)
        : languageManager(languageManager), statusManager(statusManager) {}

    void checkBatteryStatus(float temperature, float soc, float chargeRate);

private:
    LanguageManager& languageManager;
    StatusManager& statusManager;

    BatteryParameterInfo mapToStatus(float value, const std::vector<BatteryParameterInfo>& statuses) const;
    bool isValueInRange(float value, const BatteryParameterInfo& status) const;
    BatteryParameterInfo getOverallStatus(BatteryParameterInfo temperatureStatus, BatteryParameterInfo socStatus, BatteryParameterInfo chargeRateStatus) const;
    bool hasHighStatus(const BatteryParameterInfo& temperatureStatus, const BatteryParameterInfo& socStatus, const BatteryParameterInfo& chargeRateStatus) const;
    void outputMessage(const BatteryParameterInfo& status) const;
};

#endif // BATTERYCHECKER_H
