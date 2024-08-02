#include <iostream>
#include "BatteryChecker.h"

BatteryParameterInfo BatteryChecker::mapToStatus(float value, const std::vector<BatteryParameterInfo>& statuses) const {
    for (const auto& status : statuses) {
        if (isValueInRange(value, status)) {
            return status;
        }
    }
    return BatteryParameterInfo(Parameter::SOC, "NORMAL", 0, 0);  // Default to NORMAL if no range matched
}

bool BatteryChecker::isValueInRange(float value, const BatteryParameterInfo& status) const {
    return value >= status.getMin() && value <= status.getMax();
}

BatteryParameterInfo BatteryChecker::getOverallStatus(BatteryParameterInfo temperatureStatus, BatteryParameterInfo socStatus, BatteryParameterInfo chargeRateStatus) const {
    bool highStatus = hasHighStatus(temperatureStatus, socStatus, chargeRateStatus);
    return highStatus ? BatteryParameterInfo(Parameter::SOC, "HIGH", 0, 0) : BatteryParameterInfo(Parameter::SOC, "NORMAL", 0, 0);
}

bool BatteryChecker::hasHighStatus(const BatteryParameterInfo& temperatureStatus, const BatteryParameterInfo& socStatus, const BatteryParameterInfo& chargeRateStatus) const {
    return temperatureStatus.getName() == "HIGH_TEMP_BREACH" ||
           socStatus.getName() == "HIGH_SOC_BREACH" ||
           chargeRateStatus.getName() == "HIGH_CHARGE_RATE_BREACH";
}

void BatteryChecker::outputMessage(const BatteryParameterInfo& status) const {
    std::string message = statusManager.getMessage(status, languageManager.getLanguage());
    std::cout << message << std::endl;
}

void BatteryChecker::checkBatteryStatus(float temperature, float soc, float chargeRate) {
    auto temperatureStatuses = statusManager.getStatuses(Parameter::TEMPERATURE);
    auto socStatuses = statusManager.getStatuses(Parameter::SOC);
    auto chargeRateStatuses = statusManager.getStatuses(Parameter::CHARGE_RATE);

    BatteryParameterInfo temperatureStatus = mapToStatus(temperature, temperatureStatuses);
    BatteryParameterInfo socStatus = mapToStatus(soc, socStatuses);
    BatteryParameterInfo chargeRateStatus = mapToStatus(chargeRate, chargeRateStatuses);

    BatteryParameterInfo overallStatus = getOverallStatus(temperatureStatus, socStatus, chargeRateStatus);
    outputMessage(overallStatus);
}
