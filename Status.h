#ifndef STATUS_H
#define STATUS_H

#include <string>
#include "Parameter.h"

class Status {
public:
    Status(Parameter parameter, const std::string& name, float min, float max)
        : parameter(parameter), name(name), min(min), max(max) {}

    Parameter getParameter() const { return parameter; }
    std::string getName() const { return name; }
    float getMin() const { return min; }
    float getMax() const { return max; }

    bool operator<(const Status& other) const {
        return std::tie(parameter, name, min, max) < std::tie(other.parameter, other.name, other.min, other.max);
    }

    bool operator==(const Status& other) const {
        return std::tie(parameter, name, min, max) == std::tie(other.parameter, other.name, other.min, other.max);
    }

private:
    Parameter parameter;
    std::string name;
    float min;
    float max;
};

#endif // STATUS_H
