#include "SpeedSensor.h"
#include<random>

namespace VehicleDiagnostics{
    SpeedSensor::SpeedSensor():Sensor("SPEED",0,200),targetSpeed(60),gen(std::random_device{}()),dist(targetSpeed,5.0){}

    double SpeedSensor::generateData(){
        currentValue = dist(gen);
        std::uniform_real_distribution < double> chanceDist(0.0, 100.0);
        double chance = chanceDist(gen);
        if(chance<=5.0){
            if(chance<=2.5){
                currentValue = 250.0;       //Eroare magistrala
            }
            else{
                currentValue = 0.0;     //Pierde brusca de semnal
            }
        }

        return currentValue;
    }
}
