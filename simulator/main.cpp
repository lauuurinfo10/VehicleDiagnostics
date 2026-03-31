#include <iostream>
#include <vector>
#include <memory>
#include <thread>
#include <chrono>
#include <fstream>
#include <nlohmann/json.hpp>
#include "sensors/Sensor.h"
#include "sensors/RPMSensor.h"
#include "sensors/TemperatureSensor.h"
#include "sensors/SpeedSensor.h"
#include "sensors/OilPressureSensor.h"

using namespace VehicleDiagnostics;
using json = nlohmann::json;

int main()
{
    std::vector<std::unique_ptr<Sensor>> sensors;

    sensors.push_back(std::make_unique<RPMSensor>());
    sensors.push_back(std::make_unique<TemperatureSensor>());
    sensors.push_back(std::make_unique<SpeedSensor>());
    sensors.push_back(std::make_unique<OilPressureSensor>());

    std::cout << "Vehicle Diagnostics System started..." << std::endl;
    std::cout << "-----------------------------------" << std::endl;

    for (int i = 0; i < 200; i++)
    {
        json reading;
        reading["reading_number"] = i + 1;
        reading["readings"] = json::array();

        std::cout << "Reading #" << i + 1 << std::endl;

        for (auto &sensor : sensors)
        {
            double value = sensor->generateData();
            bool anomaly = sensor->isAnomaly();

            json sensorData;
            sensorData["sensor"] = sensor->getName();
            sensorData["value"] = value;
            sensorData["anomaly"] = anomaly;

            reading["readings"].push_back(sensorData);

            std::cout << "  " << sensor->getName() << ": " << value;
            if (anomaly)
                std::cout << " [ANOMALY!]";
            std::cout << std::endl;
        }

        // Salvam in fisier JSON
        // "../" ii spune sa iasa din "simulator" si sa intre in "data"
        std::ofstream file("../data/readings.json", std::ios::app);

        if (!file.is_open())
        {
            std::cerr << "  [EROARE] Nu am putut deschide fisierul. Verifica daca exista folderul '../data'!\n";
        }
        else
        {
            file << reading.dump() << "\n";
            file.close();
        }

        std::cout << "-----------------------------------" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}