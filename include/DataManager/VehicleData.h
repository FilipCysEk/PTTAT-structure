//
// Created by krzysiu on 21.06.2020.
//

#ifndef TRAMHOLDUPAJIO_VEHICLEDATA_H
#define TRAMHOLDUPAJIO_VEHICLEDATA_H

#include <string>
#include <chrono>
#include "Position.h"
#include "Line.h"

using namespace std;

namespace DataManagerStructure {
    class VehicleData {
    public:
        chrono::system_clock::time_point date;
        string id;
        Position position;
        Trip *trip;
        bool isInEliminatedPosition;
        int delay;

        VehicleData(const chrono::system_clock::time_point &date, const string &id, const Position &position,
                    Trip *trip) : date(date), id(id), position(position), trip(trip) {}
    };
}

#endif //TRAMHOLDUPAJIO_VEHICLEDATA_H
