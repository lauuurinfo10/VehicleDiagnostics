#include "OilPressureSensor.h"
#include<random>
namespace VehicleDiagnostics{
    OilPressureSensor::OilPressureSensor():Sensor("OILPRESSURE",20,80),targetPressure(40),gen(std::random_device{}()),dist(targetPressure,3.0){}

    double OilPressureSensor::generateData(){
        currentValue = dist(gen);
        std::uniform_real_distribution<double> chanceDist(0.0, 100.0);
        double chance = chanceDist(gen);
        if(chance<=5.0){
            if(chance<=2.5){
                currentValue = 95.0;    //Suprapresiune/blocaj

            }
            else{
                currentValue = 5.0;     //Scurgere de ulei/pompa defecta
            }
        }
        return currentValue;
    }

}
