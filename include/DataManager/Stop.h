//
// Created by krzysiu on 21.06.2020.
//

#ifndef TRAMHOLDUPAJIO_STOP_H
#define TRAMHOLDUPAJIO_STOP_H

#include <string>
#include "Position.h"

using namespace std;

namespace DataManagerStructure {
    class Stop {
    public:
        string id;
        string name;
        Position position;
        string parentId;

        Stop(const string &id, const string &name, const Position &position, const string &parentId)
                : id(id), name(name), position(position), parentId(parentId) {}

        Stop(const string &id, const string &name, const Position &position) : id(id), name(name), position(position) {}
    };
}

#endif //TRAMHOLDUPAJIO_STOP_H
