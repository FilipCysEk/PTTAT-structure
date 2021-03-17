//
// Created by krzysiu on 02.09.2020.
//

#ifndef TRAMHOLDUP_TRIP_H
#define TRAMHOLDUP_TRIP_H

using namespace std;

namespace DataManagerStructure {
    class Line;
    class Stop;
    class Position;

    class Trip {
    public:
        string tripId;
        string direction;
        Line *line;
        vector<Stop *> stopList;
        vector<Position> shape;

        Trip(const string &tripId, const string &direction, DataManagerStructure::Line *line) : tripId(tripId), direction(direction),
                                                                          line(line) {}

        Trip(const string &tripId, const string &direction, Line *line, const vector<Stop *> &stopList) : tripId(
                tripId), direction(direction), line(line), stopList(stopList) {}

        Trip(const string &tripId, const string &direction, Line *line, const vector<Position> &shape) : tripId(tripId),
                direction(direction), line(line),  shape(shape) {}

        Trip(const string &tripId, const string &direction, Line *line, const vector<Stop *> &stopList,
             const vector<Position> &shape) : tripId(tripId), direction(direction), line(line), stopList(stopList),
                                              shape(shape) {}
    };
}

#endif //TRAMHOLDUP_TRIP_H
