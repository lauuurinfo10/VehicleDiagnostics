#include "RPMSensor.h"
#include<random>

namespace VehicleDiagnostics{
    RPMSensor::RPMSensor() : Sensor("RPM", 600, 7000), targetRPM(800),gen(std::random_device{}()),dist(targetRPM,50.0){}

    double RPMSensor::generateData(){
        currentValue = dist(gen);
        std::uniform_real_distribution<double> chanceDist(0.0, 100.0);
        double chance = chanceDist(gen);
        if(chance<=5.0){
            if(chance<=2.5){
                currentValue = 7600.0;     //Supraturare
            }
            else{
                currentValue = 0.0;  // Pierdere semnal
            }
            
        }
        return currentValue;
    }
}