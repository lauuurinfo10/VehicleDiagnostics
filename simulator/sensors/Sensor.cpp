#include "Sensor.h"

namespace VehicleDiagnostics{
    Sensor::Sensor(std::string name,double minValue,double maxValue):name(name),minValue(minValue),maxValue(maxValue),currentValue(0){}

    bool Sensor::isAnomaly() const{
        return currentValue < minValue || currentValue > maxValue;
    }

    std::string Sensor::getName() const{
        return name;
    }

    double Sensor::getCurrentValue()const{
        return currentValue;
    }
}