//
// Created by krzysiu on 21.06.2020.
//

#ifndef TRAMHOLDUPAJIO_POSITION_H
#define TRAMHOLDUPAJIO_POSITION_H

namespace DataManagerStructure {
    class Position {
    public:
        double latitude; //szerokośc geograficzna - y
        double longitude; //długość geograficzna - x

        Position(double latitude, double longitude) : latitude(latitude), longitude(longitude) {}
    };
}

#endif //TRAMHOLDUPAJIO_POSITION_H
