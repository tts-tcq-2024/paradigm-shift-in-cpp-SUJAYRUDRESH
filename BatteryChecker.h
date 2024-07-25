#ifndef BATTERYCHECKER_H
#define BATTERYCHECKER_H

#include "LanguageManager.h"
#include "StatusManager.h"

class BatteryChecker {
public:
    BatteryChecker(LanguageManager& langMgr, StatusManager& statusMgr)
        : languageManager(langMgr), statusManager(statusMgr) {}

    void checkBatteryStatus(float temperature, float soc, float chargeRate);

private:
    LanguageManager& languageManager;
    StatusManager& statusManager;

    Status mapToStatus(float value, const std::vector<Status>& statuses) const;
    Status getOverallStatus(Status temperatureStatus, Status socStatus, Status chargeRateStatus) const;
    bool isValueInRange(float value, const Status& status) const;
    void outputMessage(const Status& status) const;
};

#endif // BATTERYCHECKER_H
