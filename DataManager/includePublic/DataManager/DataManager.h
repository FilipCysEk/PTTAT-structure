//
// Created by krzysiu on 21.06.2020.
//

#ifndef TRAMHOLDUPAJIO_DATAMANAGER_H
#define TRAMHOLDUPAJIO_DATAMANAGER_H

#ifndef RAPIDJSON_HAS_STDSTRING
#define RAPIDJSON_HAS_STDSTRING 1
#endif

#include <vector>
#include "Logger.h"
#include "rapidjson_pch.h"
#include "VehicleData.h"
#include "EliminatedPositionShape.h"
#include "DataContainer.h"
#include "DataAccess.h"
#include "configLib/ConfigFile.h"
#include "fileLib/FileLib.h"
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

using namespace std;
using namespace DataManagerStructure;
using namespace rapidjson;

class DataManager {
private:
    vector<EliminatedPositionShape> eliminatedPositionList;

    // Amount of keeped old positions
    unsigned short amountKeepOldVehiclePositions;
    unsigned maxTimeGapBetweenVehiclePositions;

    const string eliminatedPositionsJsonSchema = R"json(
    {
        "$schema": "http://json-schema.org/draft-07/schema#",
        "type": "object",
        "properties": {
            "shapes": {
                "type": "object",
                "patternProperties": {
                    "^.*$": {
                        "type":"array",
                        "items": {
                            "type": "array",
                            "description": "Latitude and longitude",
                            "items": {
                                "type": "number"
                            },
                            "minItems": 2,
                            "maxItems": 2
                        }
                    }
                }

            }
        },
        "required": [ "shapes" ]
    }
    )json";

    bool validateEliminatedPositions(const Document &doc);

protected:
    unsigned eliminatedPositionDistanceOnBight;
    shared_ptr<spdlog::logger> loggerMain;
    ConfigFile *conf;
    DataManagerStructure::DataContainer dataContainer;
    DataAccess dataAccess = DataAccess(nullptr);

    /**
    * Delete all data.
    */
    void clearData();

public:
    /**
     * Create data manager
     * @param amountKeepOldVehiclePositions Amount of history vehicle positions. If set 1 there was keep actual position and previous position. Default 2.
     */
    DataManager(ConfigFile *config, unsigned short amountKeepOldVehiclePositions = 2);

    DataManager();

    void initializeInterface(ConfigFile *config, shared_ptr<spdlog::logger> &logger,
                             unsigned short amountKeepOldVehiclePositions = 2);

    virtual void initialize(ConfigFile *config, shared_ptr<spdlog::logger> &logger,
                            unsigned short amountKeepOldVehiclePositions = 2) = 0;

    /**
     * Destructor
     */
    virtual ~DataManager();

    /**
     * Update all data (lines, stops, ...)
     * Can throw GenericException. Handled:
     * - CRITICAL_ERROR_END_PROGRAM - endiong app
     */
    virtual void updateDb() = 0;

    /**
     * Update vehicle positions
     * @throw GenericException
     * @throws CRITICAL_ERROR_END_PROGRAM - endiong app
     * @throws ERROR_SKIP - skip this step to not create delay's in scheduler (eg. if can't download actual vehicle position)
     */
    virtual void updateVehiclePositions() = 0;

    /**
     * Check passed position is in eliminated
     * @param position
     * @return true - is in eliminated, false - is out of eliminated position
     */
    bool isInEliminatedPosition(Position position);

    /**
     * Read from file eliminated positions and load
     * @param path path to json file with eliminated positions
     */
    void readEliminatedPositions();

    /**
     * Checking timegap between downloaded vehicle positions and check is it not too big.
     * @return true - timegaps is OK, false - timegap is too big
     */
    bool timeBetweenVehiclePositionsIsAcceptable();

    /**
     * Return time last vehicle positions
     * @return time
     */
    time_t getTimeLastVehiclePositions();

    /**
     * Calculate aproximate distance in meters behind points
     * @param a point a
     * @param b point b
     * @return ~distance in meters
     */
    static double approximateDistanceInMeters(Position a, Position b);

    /**
     * Get data access classes address. This class is used to access to data (lines, stops, etc)
     * @return address of dataAccess class
     */
    DataAccess *getDataAccess();



//    unsigned short getAmountKeepOldVehiclePositions() const;

};


#endif //TRAMHOLDUPAJIO_DATAMANAGER_H
