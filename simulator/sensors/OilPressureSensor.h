#pragma once
#include "Sensor.h"
#include<random>

namespace VehicleDiagnostics{
    class OilPressureSensor:public Sensor{
        private:
            double targetPressure;
            std::mt19937 gen;
            std::normal_distribution<double> dist;

        public:
            OilPressureSensor();
            double generateData() override;
    };
}