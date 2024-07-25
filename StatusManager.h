#ifndef STATUSMANAGER_H
#define STATUSMANAGER_H

#include <vector>
#include <map>
#include <string>
#include "Status.h"
#include "Parameter.h"
#include "Language.h"

class StatusManager {
public:
    void addStatusAndMessage(Parameter parameter, const std::string& name, float min, float max, const std::map<Language, std::string>& messages);
    std::vector<Status> getStatuses(Parameter parameter) const;
    std::string getMessage(const Status& status, Language language) const;
    void setOverallStatusMessage(Language language, const std::string& message);

private:
    std::vector<Status> statuses;
    std::map<Status, std::map<Language, std::string>> messageMap;
    std::map<Language, std::string> overallStatusMessages;
};

#endif // STATUSMANAGER_H
