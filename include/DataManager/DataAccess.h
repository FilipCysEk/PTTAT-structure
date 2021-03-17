//
// Created by krzysiu on 05.08.2020.
//

#ifndef TRAMHOLDUP_DATAACCESS_H
#define TRAMHOLDUP_DATAACCESS_H

#pragma once

#include "Logger.h"

#include "DataContainer.h"

using namespace DataManagerStructure;


class DataAccess {
private:
    DataContainer *dataContainer;
    shared_ptr<spdlog::logger> loggerMain;

public:
    DataAccess(DataContainer *dataContainer);

    /**
     * Return stop with passed id. If not found return nullptr.
     * @param id
     * @return
     */
    Stop *getStopById(const string &id);

    /**
     * Return all lines
     * @return
     */
    list<DataManagerStructure::Line> * getLines();

//    /**
//     * Return line with fit to passed lne and direction if not find return nullptr.
//     * @param number
//     * @param direction
//     * @return
//     */
//    Trip * getTrip(const string &number, string direction);

    /**
     * Search trip and return first record (if id is redundant in datasource)
     * @param tripId
     * @return null if not found
     */
    Trip *getTrip(const string &tripId);

    /**
     * Search trip and return first record
     * @param lineNumber
     * @param lineDirection
     * @return null if not found
     */
    Trip *getTrip(const string &lineNumber, string lineDirection);

    /**
     * Get list of actual vehicles positions
     * @return Pointer to vehicle list.
     */
    vector<VehicleData> *getActualVehiclesPositions();

    /**
     * Get list of previous vehicles positions
     * @param num 0 - prvious, 1 - previous, previous, 2 - previous, previous, previous. Default 0.
     * @return Pointer to vehicle list.
     */
    vector<VehicleData> *getPreviousVehiclesPositions(unsigned short num = 0);

    /**
     * Get list of previous vehicles positions
     * @param vehicleId
     * @param num 0 - prvious, 1 - previous, previous, 2 - previous, previous, previous. Default 0.
     * @return Pointer to vehicle list.
     */
    VehicleData * getPreviousVehiclePosition(string vehicleId, unsigned short num = 0);

    /**
     * Search nearest stop
     * @param position of vehicle
     * @return stop
     */
    DataManagerStructure::Stop *getNearestStop(Position position);
};


#endif //TRAMHOLDUP_DATAACCESS_H
