#pragma once

#include <chrono>
#include <vector>
#include "graph.h"

using WeightType = double;
using Path = std::vector<int>;

class PathFinder {
   public:
    struct AlgoOutput {
        double minimal_length;  // always
        Path path;              // if debug
        Path used;              // if debug
        double time_ms;
    };

    virtual ~PathFinder() = default;

    virtual AlgoOutput findShortestPathWithTiming(const Graph& graph, int from, int to, bool debug) {
        auto start = std::chrono::high_resolution_clock::now();

        auto output = findShortestPath(graph, from, to, debug);

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;
        output.time_ms = elapsed.count();

        return output;
    }

    virtual AlgoOutput findShortestPath(const Graph& graph, int from, int to, bool debug) = 0;

    virtual std::string Name() = 0;

   protected:
    Path reconstructPath(int from, int to, const std::vector<int>& previous) {
        Path path;
        for (int at = to; at != -1; at = previous[at]) {
            path.push_back(at);
        }

        std::reverse(path.begin(), path.end());

        if (!path.empty() && path.front() == from) {
            return path;
        }
        return Path();
    }
};
