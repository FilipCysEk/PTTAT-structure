//
// Created by krzysiu on 21.06.2020.
//

#ifndef TRAMHOLDUPAJIO_ELIMINATEDPOSITIONSHAPE_H
#define TRAMHOLDUPAJIO_ELIMINATEDPOSITIONSHAPE_H

#include <vector>
#include <cmath>
#include "Logger.h"

#include "Position.h"

using namespace std;

namespace DataManagerStructure {
    class EliminatedPositionShape {
    public:
        EliminatedPositionShape();

        vector<Position> positionList;

        bool isIn(Position position);

    private:
        // Must be less then 0.0000001
        const double epsilon = 0.000000001;
        std::shared_ptr<spdlog::logger> loggerMain;

        bool intersect(Position &point, Position edgeA, Position edgeB);

        double calculateSlope(Position base, Position point);
    };
}


#endif //TRAMHOLDUPAJIO_ELIMINATEDPOSITIONSHAPE_H
