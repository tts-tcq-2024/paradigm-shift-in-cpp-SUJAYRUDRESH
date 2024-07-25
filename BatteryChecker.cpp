#include <iostream>
#include "BatteryChecker.h"

Status BatteryChecker::mapToStatus(float value, const std::vector<Status>& statuses) const {
    for (const auto& status : statuses) {
        if (isValueInRange(value, status)) {
            return status;
        }
    }
    return Status(Parameter::SOC, "NORMAL", 0, 0);  // Default to NORMAL if no range matched
}

bool BatteryChecker::isValueInRange(float value, const Status& status) const {
    return value >= status.getMin() && value <= status.getMax();
}

Status BatteryChecker::getOverallStatus(Status temperatureStatus, Status socStatus, Status chargeRateStatus) const {
    // Logic to determine overall status; for simplicity, we assume any breach results in a critical status.
    bool hasHighStatus = temperatureStatus.getName() == "HIGH_TEMP_BREACH" ;
    hasHighStatus = socStatus.getName() == "HIGH_SOC_BREACH" ;
    hasHighStatus = chargeRateStatus.getName() == "HIGH_CHARGE_RATE_BREACH" ;

    return hasHighStatus ? Status(Parameter::SOC, "HIGH", 0, 0) : Status(Parameter::SOC, "NORMAL", 0, 0);
/**
    if (temperatureStatus.getName() == "HIGH_TEMP_BREACH" ||
        socStatus.getName() == "HIGH_SOC_BREACH" ||
        chargeRateStatus.getName() == "HIGH_CHARGE_RATE_BREACH") {
        return Status(Parameter::SOC, "HIGH_TEMP_BREACH", 0, 0);  // Example: Replace with appropriate status if needed
    }
    return Status(Parameter::SOC, "NORMAL", 0, 0);
**/
}

void BatteryChecker::outputMessage(const Status& status) const {
    std::string message = statusManager.getMessage(status, languageManager.getLanguage());
    std::cout << message << std::endl;
}

void BatteryChecker::checkBatteryStatus(float temperature, float soc, float chargeRate) {
    auto temperatureStatuses = statusManager.getStatuses(Parameter::TEMPERATURE);
    auto socStatuses = statusManager.getStatuses(Parameter::SOC);
    auto chargeRateStatuses = statusManager.getStatuses(Parameter::CHARGE_RATE);

    Status tempStatus = mapToStatus(temperature, temperatureStatuses);
    Status socStatus = mapToStatus(soc, socStatuses);
    Status chargeRateStatus = mapToStatus(chargeRate, chargeRateStatuses);

    outputMessage(tempStatus);
    outputMessage(socStatus);
    outputMessage(chargeRateStatus);

    Status overallStatus = getOverallStatus(tempStatus, socStatus, chargeRateStatus);
    std::cout << statusManager.getMessage(overallStatus, languageManager.getLanguage()) << std::endl;
}
