//
// Created by krzysiu on 21.06.2020.
//

#include "DataManager/EliminatedPositionShape.h"
#include <iostream>
bool DataManagerStructure::EliminatedPositionShape::isIn(DataManagerStructure::Position position) {
    bool inside = false;
    unsigned vsize = positionList.size();

    if (vsize > 2) {
        for (int i = 1; i < vsize; ++i) {
            if (intersect(position, positionList[i - 1], positionList[i])) {
                inside = !inside;
            }
        }

        if(intersect(position, positionList[vsize - 1], positionList[0])) {
            inside = !inside;
        }

        return inside;
    } else {
        loggerMain->error("One of eliminated position list have shape  created for les than 3 points");
        //TODO Maybe delete this?
    }
    return false;
}

bool DataManagerStructure::EliminatedPositionShape::intersect(DataManagerStructure::Position &point,
                                                              DataManagerStructure::Position edgeA,
                                                              DataManagerStructure::Position edgeB) {
    if (edgeA.latitude > edgeB.latitude) return intersect(point, edgeB, edgeA);

    if (edgeA.latitude == point.latitude || edgeB.latitude == point.latitude)
        point.latitude = point.latitude + epsilon;

    if (edgeA.latitude > point.latitude || point.latitude > edgeB.latitude)
        return false;

    if (point.longitude < min(edgeA.longitude, edgeB.longitude))
        return true;

    else if (point.longitude < max(edgeA.longitude, edgeB.longitude)) {
        double edgeSlope = calculateSlope(edgeA, edgeB);
        double pointSlope = calculateSlope(edgeA, point);

        return pointSlope >= edgeSlope;
    }
    else return false;
}

double DataManagerStructure::EliminatedPositionShape::calculateSlope(DataManagerStructure::Position base,
                                                                     DataManagerStructure::Position point) {
    double slope = base.longitude - point.longitude;
    if (slope < epsilon) {
        return INFINITY;
    }

    return (base.latitude - point.latitude) / slope;
}

DataManagerStructure::EliminatedPositionShape::EliminatedPositionShape() {
    // TODO think to move this to throw error
    loggerMain =  Logger::getLogger("loggerMain");
}
