//
// Created by krzysiu on 22.07.2020.
//

#ifndef TRAMHOLDUP_VEHICLEDATACONTAINER_H
#define TRAMHOLDUP_VEHICLEDATACONTAINER_H

#include "VehicleData.h"

using namespace std;

namespace DataManagerStructure {
    class VehicleDataContainer {
    private:
        chrono::system_clock::time_point date;
    public:
        vector<VehicleData> vehicleList;

        VehicleDataContainer(chrono::system_clock::time_point date) : date(date) {}
        VehicleDataContainer(time_t date) : date(chrono::system_clock::from_time_t(date)) {}
        VehicleDataContainer(time_t date, vector<VehicleData> &vehicleList) :
        date(chrono::system_clock::from_time_t(date)), vehicleList(move(vehicleList)) {}

        time_t getTime_tDate() {
            return chrono::system_clock::to_time_t(date);
        }

        chrono::system_clock::time_point getChronoDate() {
            return date;
        }
    };
}

#endif //TRAMHOLDUP_VEHICLEDATACONTAINER_H
