//
// Created by krzysiu on 09.07.2020.
//


#include "DataManager/DataContainer.h"

DataManagerStructure::DataContainer::~DataContainer() {
    clearData();
}

void DataManagerStructure::DataContainer::clearData() {
    for (auto &list: vehiclePosition) {
        list.vehicleList.clear();
    }

    vehiclePosition.clear();
    stopList.clear();
    lineList.clear();
}

DataManagerStructure::Line *DataManagerStructure::DataContainer::addLine(const DataManagerStructure::Line &line) {
//    return &lineList.emplace_back(line);
    return &lineList.emplace_back(line);
}

void DataManagerStructure::DataContainer::addStop(Stop stop) {
    stopList.emplace_back(stop);

}

void DataManagerStructure::DataContainer::addVehicleList(vector<VehicleData> vehicleList, time_t date) {
    if (vehiclePosition.size() > amountOldVehiclePositions) {
        vehiclePosition.erase(vehiclePosition.end());
    }

    vehiclePosition.insert(vehiclePosition.begin(), VehicleDataContainer(date, vehicleList));
}

void DataManagerStructure::DataContainer::setAmountOldVehiclePositions(unsigned int amountOldVehiclePositions) {
    DataContainer::amountOldVehiclePositions = amountOldVehiclePositions;
}

list<DataManagerStructure::Stop> * DataManagerStructure::DataContainer::getStopList() {
    return &stopList;
}

list<DataManagerStructure::Line> * DataManagerStructure::DataContainer::getLineList() {
    return &lineList;
}

vector<DataManagerStructure::VehicleDataContainer> * DataManagerStructure::DataContainer::getVehiclePosition() {
    return &vehiclePosition;
}
