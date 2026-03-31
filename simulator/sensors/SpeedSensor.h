#pragma once
#include "Sensor.h"
#include<random>

namespace VehicleDiagnostics{
    class SpeedSensor:public Sensor{
        private:
            double targetSpeed;
            std::mt19937 gen;                            
            std::normal_distribution<double> dist;
        
        public:
            SpeedSensor();
            double generateData() override;
    };
}