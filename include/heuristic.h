#pragma once

#include <cmath>
#include "graph.h"

inline double haversine(double lat1, double lon1, double lat2, double lon2) {
    // distance between latitudes and longitudes
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;
    // convert to radians
    lat1 = lat1 * M_PI / 180.0;
    lat2 = lat2 * M_PI / 180.0;
    // apply formula
    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

inline double heuristic(const int &from, const int &to, const Graph &grap) {
    double lat1 = grap.coordinates[from].lat;
    double lon1 = grap.coordinates[from].lon;
    double lat2 = grap.coordinates[to].lat;
    double lon2 = grap.coordinates[to].lon;
    return haversine(lat1, lon1, lat2, lon2) * 1000;
}
