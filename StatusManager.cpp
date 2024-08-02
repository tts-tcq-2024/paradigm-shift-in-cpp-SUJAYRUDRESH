#include "StatusManager.h"

void StatusManager::addParameter(Parameter parameter, const std::string& name, float min, float max, const std::map<Language, std::string>& messages) {
    BatteryParameterInfo parameterInfo(parameter, name, min, max);
    parameters.push_back(parameterInfo);
    messageMap[parameterInfo] = messages;
}

std::vector<BatteryParameterInfo> StatusManager::getStatuses(Parameter parameter) const {
    std::vector<BatteryParameterInfo> statuses;
    for (const auto& param : parameters) {
        if (param.getParameter() == parameter) {
            statuses.push_back(param);
        }
    }
    return statuses;
}

std::string StatusManager::getMessage(const BatteryParameterInfo& status, Language language) const {
    auto it = messageMap.find(status);
    if (it != messageMap.end()) {
        auto langIt = it->second.find(language);
        if (langIt != it->second.end()) {
            return langIt->second;
        }
    }
    return "No message found!";
}

void StatusManager::setOverallStatusMessage(Language language, const std::string& message) {
    overallStatusMessages[language] = message;
}
