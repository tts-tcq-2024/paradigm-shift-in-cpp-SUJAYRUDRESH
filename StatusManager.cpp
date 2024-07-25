#include "StatusManager.h"
#include <stdexcept>
#include <iostream>

void StatusManager::addStatusAndMessage(Parameter parameter, const std::string& name, float min, float max, const std::map<Language, std::string>& messages) {
    Status newStatus(parameter, name, min, max);
    statuses.push_back(newStatus);
    messageMap[newStatus] = messages;
}

std::vector<Status> StatusManager::getStatuses(Parameter parameter) const {
    std::vector<Status> parameterStatuses;
    for (const auto& status : statuses) {
        if (status.getParameter() == parameter) {
            parameterStatuses.push_back(status);
        }
    }
    return parameterStatuses;
}

std::string StatusManager::getMessage(const Status& status, Language language) const {
    try {
        return messageMap.at(status).at(language);
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: " << e.what() << " - Status or language not found" << std::endl;
        return "Message not found";
    }
}

void StatusManager::setOverallStatusMessage(Language language, const std::string& message) {
    overallStatusMessages[language] = message;
}
