#include <assert.h>
#include <iostream>

using namespace std;


class BatteryManagementSystem {
private:
    static constexpr float kMinTemperature = 0.0f;
    static constexpr float kMaxTemperature = 45.0f;
    static constexpr float kMinSoc = 20.0f;
    static constexpr float kMaxSoc = 80.0f;
    static constexpr float kMaxChargeRate = 0.8f;

public:
    bool isTemperatureInRange(float temperature) const;
    bool isSocInRange(float soc) const;
    bool isChargeRateInRange(float chargeRate) const;
    bool batteryIsOk(float temperature, float soc, float chargeRate) const;

private:
    void logMessage(const std::string& message, float value, bool isHigh) const;
};

void BatteryManagementSystem::logMessage(const std::string& message, float value, bool isHigh) const {
    cout << message << ": " << value << " (" << (isHigh ? "high" : "low") << ")" << endl;
}

bool BatteryManagementSystem::isTemperatureInRange(float temperature) const {
    if (temperature < kMinTemperature || temperature > kMaxTemperature) {
        logMessage("Temperature out of range", temperature, temperature > kMaxTemperature);
        return false;
    }
    return true;
}

bool BatteryManagementSystem::isSocInRange(float soc) const {
    if (soc < kMinSoc || soc > kMaxSoc) {
        logMessage("State of Charge out of range", soc, soc > kMaxSoc);
        return false;
    }
    return true;
}

bool BatteryManagementSystem::isChargeRateInRange(float chargeRate) const {
    if (chargeRate > kMaxChargeRate) {
        logMessage("Charge Rate out of range", chargeRate, true);
        return false;
    }
    return true;
}

bool BatteryManagementSystem::batteryIsOk(float temperature, float soc, float chargeRate) const {
    return isTemperatureInRange(temperature) && isSocInRange(soc) && isChargeRateInRange(chargeRate);
}

void testIsTemperatureInRange() {
    BatteryManagementSystem bms;
    assert(bms.isTemperatureInRange(0) == true);
    assert(bms.isTemperatureInRange(45) == true);
    assert(bms.isTemperatureInRange(25) == true);
    assert(bms.isTemperatureInRange(-0.1) == false);
    assert(bms.isTemperatureInRange(45.1) == false);
    assert(bms.isTemperatureInRange(-5) == false);
    assert(bms.isTemperatureInRange(50) == false);
}

void testIsSocInRange() {
    BatteryManagementSystem bms;
    assert(bms.isSocInRange(20) == true);
    assert(bms.isSocInRange(80) == true);
    assert(bms.isSocInRange(50) == true);
    assert(bms.isSocInRange(19.9) == false);
    assert(bms.isSocInRange(80.1) == false);
    assert(bms.isSocInRange(10) == false);
    assert(bms.isSocInRange(90) == false);
}

void testIsChargeRateInRange() {
    BatteryManagementSystem bms;
    assert(bms.isChargeRateInRange(0.7) == true);
    assert(bms.isChargeRateInRange(0) == true);
    assert(bms.isChargeRateInRange(0.7) == true);
    assert(bms.isChargeRateInRange(0.81) == false);
    assert(bms.isChargeRateInRange(0.9) == false);
}

void testBatteryIsOk() {
    BatteryManagementSystem bms;
    assert(bms.batteryIsOk(25, 70, 0.7) == true);
    assert(bms.batteryIsOk(25, 70, 0.7) == true);
    assert(bms.batteryIsOk(0, 20, 0) == true);
    assert(bms.batteryIsOk(-1, 70, 0.7) == false);
    assert(bms.batteryIsOk(25, 19, 0.7) == false);
    assert(bms.batteryIsOk(25, 70, 0.9) == false);
    assert(bms.batteryIsOk(50, 85, 0) == false);
}

int main() {
    testIsTemperatureInRange();
    testIsSocInRange();
    testIsChargeRateInRange();
    testBatteryIsOk();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}

