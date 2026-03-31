#pragma once
#include<string>

namespace VehicleDiagnostics{
    class Sensor{
        protected:
            std::string name;
            double currentValue;
            double minValue;
            double maxValue;

        public:
            Sensor(std::string name, double minValue, double maxValue);

            virtual double generateData() = 0;
            virtual bool isAnomaly() const;

            std::string getName() const;
            double getCurrentValue() const;

            virtual ~Sensor() = default;
    };
}