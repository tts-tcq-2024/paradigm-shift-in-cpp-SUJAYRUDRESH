#ifndef BATTERYPARAMETERINFO_H
#define BATTERYPARAMETERINFO_H

#include <string>
#include "Parameter.h"
#include "Language.h"

class BatteryParameterInfo {
public:
    BatteryParameterInfo(Parameter parameter, const std::string& name, float min, float max)
        : parameter(parameter), name(name), min(min), max(max) {}

    Parameter getParameter() const { return parameter; }
    std::string getName() const { return name; }
    float getMin() const { return min; }
    float getMax() const { return max; }

    bool operator<(const BatteryParameterInfo& other) const {
        return std::tie(parameter, name, min, max) < std::tie(other.parameter, other.name, other.min, other.max);
    }

    bool operator==(const BatteryParameterInfo& other) const {
        return std::tie(parameter, name, min, max) == std::tie(other.parameter, other.name, other.min, other.max);
    }

private:
    Parameter parameter;
    std::string name;
    float min;
    float max;
};

#endif // BATTERYPARAMETERINFO_H
