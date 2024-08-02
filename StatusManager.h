#ifndef STATUSMANAGER_H
#define STATUSMANAGER_H

#include <vector>
#include <map>
#include <string>
#include "BatteryParameterInfo.h"
#include "Parameter.h"
#include "Language.h"

class StatusManager {
public:
    void addParameter(Parameter parameter, const std::string& name, float min, float max, const std::map<Language, std::string>& messages);
    std::vector<BatteryParameterInfo> getStatuses(Parameter parameter) const;
    std::string getMessage(const BatteryParameterInfo& status, Language language) const;
    void setOverallStatusMessage(Language language, const std::string& message);

private:
    std::vector<BatteryParameterInfo> parameters;
    std::map<BatteryParameterInfo, std::map<Language, std::string>> messageMap;
    std::map<Language, std::string> overallStatusMessages;
};

#endif // STATUSMANAGER_H
