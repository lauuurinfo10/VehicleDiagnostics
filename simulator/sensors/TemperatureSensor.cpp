#include "TemperatureSensor.h"
#include<random>

namespace VehicleDiagnostics{
    TemperatureSensor::TemperatureSensor():Sensor("TEMPERATURE",70,105),targetTemperature(90),gen(std::random_device{}()),dist(targetTemperature,2.0){}
    
   double TemperatureSensor::generateData(){
     currentValue = dist(gen);
     std::uniform_real_distribution<double>chanceDist(0.0,100.0);
     double chance = chanceDist(gen);
     if(chance<=5.0){
          if(chance<=2.5){
               currentValue = 125.0;      //Motor supraincalzit
          }
          else{
               currentValue = -40.0;      // Scurtcircuit senzor
          }
     }
     return currentValue;
   }
}
