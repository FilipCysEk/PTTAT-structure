//
// Created by krzysiu on 09.07.2020.
//

#ifndef TRAMHOLDUPAJIO_DATACONTAINER_H
#define TRAMHOLDUPAJIO_DATACONTAINER_H

#include <list>
#include <vector>
#include <algorithm>
#include "VehicleData.h"
#include "VehicleDataContainer.h"
#include "PointsFunctions.h"

using namespace std;

namespace DataManagerStructure {
    class DataContainer {
    private:

        list<DataManagerStructure::Stop> stopList;
        list<DataManagerStructure::Line> lineList;
        vector<DataManagerStructure::VehicleDataContainer> vehiclePosition;
        unsigned amountOldVehiclePositions = 5;

    public:
        void setAmountOldVehiclePositions(unsigned int amountOldVehiclePositions);

        virtual ~DataContainer();

        void clearData();

        Line *addLine(const Line &line);

        void addStop(Stop stop);

        void addVehicleList(vector<VehicleData> vehicleList, time_t date);

        list <DataManagerStructure::Stop> * getStopList();

        list <DataManagerStructure::Line> * getLineList();

        vector<DataManagerStructure::VehicleDataContainer> * getVehiclePosition();
    };
};


#endif //TRAMHOLDUPAJIO_DATACONTAINER_H
