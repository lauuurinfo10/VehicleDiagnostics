#pragma once
#include "Sensor.h"
#include<random>

namespace VehicleDiagnostics{
    class TemperatureSensor:public Sensor{
        private:
            double targetTemperature;
            std::mt19937 gen;                            
            std::normal_distribution<double> dist;

        public:
            TemperatureSensor();
            double generateData() override;
    };
}