//
// Created by krzysiu on 21.06.2020.
//

#include "../includePublic/DataManager/DataManager.h"

DataManager::DataManager(ConfigFile *config, unsigned short amountKeepOldVehiclePositions)
        : amountKeepOldVehiclePositions(amountKeepOldVehiclePositions), conf(config) {
    loggerMain = Logger::getLogger("loggerMain");
    loggerMain->trace("Created data manager.");
    eliminatedPositionDistanceOnBight = config->getValue<unsigned>("eliminatedPositionDistanceFromBight");
    maxTimeGapBetweenVehiclePositions = config->getValue<unsigned>("maxTimeGapBetweenVehiclePositions");
    amountKeepOldVehiclePositions = config->getValue<unsigned short>("amountKeepVehiclePositions");
    dataContainer.setAmountOldVehiclePositions(amountKeepOldVehiclePositions);
    dataAccess = DataAccess(&dataContainer);
}

void DataManager::initializeInterface(ConfigFile *config, shared_ptr<spdlog::logger> &logger,
                                      unsigned short amountKeepOldVehiclePositions) {
    this->conf = config;
    this->amountKeepOldVehiclePositions = amountKeepOldVehiclePositions;
//    loggerMain =  Logger::getLogger("loggerMain");

    loggerMain = spdlog::get("loggerMain");
    if (not loggerMain) {
        spdlog::register_logger(logger);
        loggerMain = logger;
    }
    loggerMain->trace("Created data manager.");
    eliminatedPositionDistanceOnBight = config->getValue<unsigned>("eliminatedPositionDistanceFromBight");
    maxTimeGapBetweenVehiclePositions = config->getValue<unsigned>("maxTimeGapBetweenVehiclePositions");
    amountKeepOldVehiclePositions = config->getValue<unsigned short>("amountKeepVehiclePositions");
    dataContainer.setAmountOldVehiclePositions(amountKeepOldVehiclePositions);
    dataAccess = DataAccess(&dataContainer);
}

bool DataManager::isInEliminatedPosition(Position position) {
    for (auto &shape: eliminatedPositionList) {
        if (shape.isIn(position))
            return true;
    }
    return false;
}

DataManager::~DataManager() {
    clearData();
    loggerMain->trace("Deleted data manager.");
}

void DataManager::clearData() {
    loggerMain->trace("Clearing data in data manager.");
    dataContainer.clearData();
}

void DataManager::readEliminatedPositions() {
    loggerMain->trace("Start reading eliminated positions.");
    string path = FileLib::getFullPath(conf->getStringValue("eliminatedPositionsFilePath"));
    if (!FileLib::fileExist(path)) {
        loggerMain->error("Not found file with eliminated positions. Eliminated positions will be skipped. "
                          " (File path: {0})", path);
        return;
    }

    ifstream json;
    json.open(path);
    if (json.is_open()) {
        IStreamWrapper isw(json);
        Document doc;
        if (doc.ParseStream(isw).HasParseError()) {
            loggerMain->error("Error when parsing json file with eliminated positions."
                              " Eliminated positions will be skipped. (File path: {0})", path);
            return;
        }

        if (validateEliminatedPositions(doc)) {
            double lat, lon;
            string shapeName;

            for (auto &itr : doc["shapes"].GetObject()) {
                shapeName = itr.name.GetString();
                EliminatedPositionShape eps;

                for (auto &itrPosition: itr.value.GetArray()) {
                    auto position = itrPosition.GetArray();
                    lat = position[0].GetDouble();
                    lon = position[1].GetDouble();

                    eps.positionList.emplace_back(Position(lat, lon));
                }
                eliminatedPositionList.push_back(eps);
            }
        }
        loggerMain->trace("Eliminated positions read successfully.");
    } else {
        loggerMain->error("Can't open json file with eliminated positions. Eliminated positions will be skipped. "
                          " (File path: {0})", path);
    }
}

bool DataManager::validateEliminatedPositions(const Document &doc) {
    Document schemaDocument;
    schemaDocument.Parse(eliminatedPositionsJsonSchema);
    SchemaDocument schema(schemaDocument);

    SchemaValidator validator(schema);
    if (!doc.Accept(validator)) {
        StringBuffer sb;
        validator.GetInvalidDocumentPointer().StringifyUriFragment(sb);
        loggerMain->error("Error on checking eliminated position file. Line \"{0}\" is incorrect!",
                          sb.GetString());
        return false;
    }

    return true;
}

double DataManager::approximateDistanceInMeters(Position a, Position b) {
    double const oneMeter = 0.0000119;
    double dist = pow(fabs(a.latitude - b.latitude), 2) + pow(fabs(a.longitude - b.longitude), 2);
    dist = sqrt(dist);
    return dist / oneMeter;
}

bool DataManager::timeBetweenVehiclePositionsIsAcceptable() {
    auto vehiclePosition = dataContainer.getVehiclePosition();
    unsigned listSize = vehiclePosition->size();
    if (listSize < 3) return true;

    for (int i = 1; i < listSize; ++i) {
        if (vehiclePosition->at(i).getTime_tDate() - vehiclePosition->at(i - 1).getTime_tDate() >
            maxTimeGapBetweenVehiclePositions)
            return false;
    }
    return true;
}

time_t DataManager::getTimeLastVehiclePositions() {
    auto vehiclePosition = dataContainer.getVehiclePosition();
    if (!vehiclePosition->empty())
        return vehiclePosition->at(0).getTime_tDate();
    else
        return 0;
}

DataAccess *DataManager::getDataAccess() {
    return &dataAccess;
}

DataManager::DataManager() {}
