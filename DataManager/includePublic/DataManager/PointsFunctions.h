//
// Created by krzysiu on 29.07.2020.
//

#ifndef TRAMHOLDUP_POINTSFUNCTIONS_H
#define TRAMHOLDUP_POINTSFUNCTIONS_H

#include <cmath>
#include "Position.h"

using namespace DataManagerStructure;

namespace PFunctions{

    /**
     * Calculate aproximate distance in meters behind points
     * @param a point a
     * @param b point b
     * @return ~distance in meters
     */
    static double approximateDistanceInMeters(Position a, Position b){
        double const oneMeter = 0.0000119;
        double dist = pow(fabs(a.latitude - b.latitude), 2) + pow(fabs(a.longitude - b.longitude), 2);
        dist = sqrt(dist);
        return dist / oneMeter;
    }

    /**
     * Calculate distance in ' from meters
     * @param distance in meters
     * @return ~distance in '
     */
    static double approximateDistanceFromMeters(unsigned short distance) {
        double const oneMeter = 0.0000119;
        return distance * oneMeter;
    }
    //TODO move body to cpp
    static double distanceBetweenPoints(double latitude1, double latitude2, double longitude1, double longitude2){
        return sqrt(pow(longitude1 - longitude2, 2) +
                    pow(latitude1 - latitude2, 2));
    }
    static double distanceBetweenPoints(DataManagerStructure::Position pos1, DataManagerStructure::Position pos2){
        return distanceBetweenPoints(pos1.latitude, pos2.latitude, pos1.longitude, pos2.longitude);
    }

    static double distanceToPath(double latitudePath1, double latitudePath2, double longitudePath1, double longitudePath2,
                                 double latitudePoint, double longitudePoint) {
        //latitude - y; longitude - x
        if (longitudePath1 == longitudePath2) {
            return fabs(longitudePoint - longitudePath2);
        } else {
            //latitude - y; longitude - x
            double A, B, C;
            A = (latitudePath1 - latitudePath2) /
                (longitudePath1 - longitudePath2);
            B = -1;
            C = latitudePath1 - A * longitudePath1;
            return fabs(A * longitudePoint + B * latitudePoint + C) /
                   sqrt(A * A + B * B);
        }
    }

    static double distanceToPath(DataManagerStructure::Position pointPath1, DataManagerStructure::Position pointPath2, DataManagerStructure::Position point){
        return distanceToPath(pointPath1.latitude, pointPath2.latitude, pointPath1.longitude, pointPath2.longitude, point.latitude, point.longitude);
    }
}

#endif //TRAMHOLDUP_POINTSFUNCTIONS_H
