//
// Created by krzysiu on 05.08.2020.
//

#include "../includePublic/DataManager/DataAccess.h"


DataAccess::DataAccess(DataContainer *dataContainer) : dataContainer(dataContainer) {
    loggerMain =  Logger::getLogger("loggerMain");
}

DataManagerStructure::Stop * DataAccess::getStopById(const string& id) {
    auto stopList = dataContainer->getStopList();
    for(auto &stop: *stopList) {
        if(stop.id == id) {
            return &stop;
        }
    }
    return nullptr;
}

list<DataManagerStructure::Line> * DataAccess::getLines() {
    return dataContainer->getLineList();
}

//Trip * DataAccess::getTrip(const string &number, string direction) {
//    string temp;
//    for(auto &line : *dataContainer->getLineList()) {
//        for(auto &trip: line.tripList) {
//            transform(direction.begin(), direction.end(), direction.begin(), ::tolower);
//            direction.erase(remove_if(direction.begin(), direction.end(), ::isspace), direction.end());
//
//            temp = trip.direction;
//            temp.erase(remove_if(temp.begin(), temp.end(), ::isspace), temp.end());
//
//            transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
//            if (line.lineNumber == number && temp == direction) {
//                return &trip;
//            }
//        }
//    }
//
//    return nullptr;
//}

vector<VehicleData> *DataAccess::getActualVehiclesPositions() {
    auto vehiclePosition = dataContainer->getVehiclePosition();
    if (!vehiclePosition->empty()) {
        loggerMain->debug("Get actual vehicle position");
        return &vehiclePosition->front().vehicleList;
    } else {
        loggerMain->error("Try to get vehicle position list, where there no data. Returned nullptr.");
        return nullptr;
    }
}

VehicleData *DataAccess::getPreviousVehiclePosition(string vehicleId, unsigned short num) {
    vector<VehicleData> * list;
    list = getPreviousVehiclesPositions(num);
    if(list != nullptr) {
        for(auto &veh : *list) {
            if(vehicleId == veh.id)
                return &veh;
        }
    }
    return nullptr;
}

vector<VehicleData> *DataAccess::getPreviousVehiclesPositions(unsigned short num) {
    auto vehiclePosition = dataContainer->getVehiclePosition();
    if (vehiclePosition->size() > num + 1) {
//        loggerMain->trace("Get previous vehicle position");
        auto iterator = vehiclePosition->begin();
        advance(iterator, num + 1);
        return &iterator->vehicleList;
    } else {
        loggerMain->error("Try to get previous vehicle position list, but try to access over data."
                          " List previous size {}, try to access element on  index {}. Returned nullptr.",
                          vehiclePosition->size(), num + 1);
        return nullptr;
    }
    return nullptr;
}

Stop *DataAccess::getNearestStop(Position position) {
    double dst, temp;
    Stop *result;
    auto stopList = dataContainer->getStopList();
    if (stopList->empty()) {
        return nullptr;
    }
    dst = PFunctions::distanceBetweenPoints(position, stopList->front().position);
    result = &stopList->front();

    for (auto &stop: *stopList) {
        temp = PFunctions::distanceBetweenPoints(position, stop.position);
        if (temp < dst) {
            dst = temp;
            result = &stop;
        }
    }
    return result;
}

Trip *DataAccess::getTrip(const string &tripId) {
    auto lineList = dataContainer->getLineList();
    for(auto &line: *lineList) {
        for(auto &trip: line.tripList) {
            if(trip.tripId == tripId) {
                return &trip;
            }
        }
    }
    return nullptr;
}

Trip *DataAccess::getTrip(const string &lineNumber, string lineDirection) {
    string temp;
    auto lineList = dataContainer->getLineList();
    for(auto &line: *lineList) {
        if(line.lineNumber == lineNumber) {
            for(auto &trip: line.tripList) {
                transform(lineDirection.begin(), lineDirection.end(), lineDirection.begin(), ::tolower);
                lineDirection.erase(remove_if(lineDirection.begin(), lineDirection.end(), ::isspace),
                                    lineDirection.end());

                temp = trip.direction;
                temp.erase(remove_if(temp.begin(), temp.end(), ::isspace), temp.end());

                transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
                if (temp == lineDirection) {
                    return &trip;
                }
            }
        }
    }

    return nullptr;
}
