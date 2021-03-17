//
// Created by krzysiu on 21.06.2020.
//

#ifndef TRAMHOLDUPAJIO_LINE_H
#define TRAMHOLDUPAJIO_LINE_H

#include <string>
#include <list>
#include "Stop.h"
#include "Trip.h"

using namespace std;

namespace DataManagerStructure {
    class Line {
    public:
        string lineId;
        string lineNumber;
        list<Trip> tripList;

        Line(const string &lineId, const string &lineNumber) : lineId(lineId), lineNumber(lineNumber) {}
    };
}

#endif //TRAMHOLDUPAJIO_LINE_H
