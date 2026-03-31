#pragma once
#include "Sensor.h"
#include<random>

namespace VehicleDiagnostics{

    class RPMSensor:public Sensor{
        private:
            double targetRPM;
            std::mt19937 gen;                            
            std::normal_distribution<double> dist;

        public:
            RPMSensor();
            double generateData() override;
    };
}