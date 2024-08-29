#pragma once

#include <limits>
#include <queue>
#include <string>
#include <vector>
#include "base_path_finder.h"
#include "graph.h"
#include "heuristic.h"

class AStarPathFinder final : public PathFinder {
public:
    virtual std::string Name() override { return "AStar"; }
    
    virtual AlgoOutput findShortestPath(const Graph& graph, int from, int to, bool debug) override {
        if (to < 0 || to >= graph.Size() || from < 0 || from >= graph.Size()) {
            return AlgoOutput{};
        }

        const int num_vertices = graph.Size();
        std::priority_queue < std::pair <WeightType, int> , std::vector<std::pair<WeightType, int>> , std::greater<> > vertices_queue;
        std::vector<WeightType> min_distance(num_vertices, std::numeric_limits<WeightType>::infinity());
        std::vector<int> previous(num_vertices, -1);
        std::vector<bool> used(num_vertices, false);

        min_distance[from] = 0;
        vertices_queue.push({0, from});

        while (!vertices_queue.empty()) {
            int current_vertex = vertices_queue.top().second;
            WeightType current_distance = min_distance[current_vertex];

            vertices_queue.pop();

            if (used[current_vertex]) {
                continue;
            }
            used[current_vertex] = true;
            if (current_vertex == to) {
                break;
            }
            
            for (const auto &edge : graph.adjacency_list[current_vertex]) {
                int neighbor = edge.node;
                WeightType weight = edge.weight;
                WeightType distance_through_vertex = current_distance + weight;
                
                if (distance_through_vertex < min_distance[neighbor]) {
                    min_distance[neighbor] = distance_through_vertex;
                    previous[neighbor] = current_vertex;
                    WeightType gfunction = distance_through_vertex  + heuristic(neighbor, to, graph);
                    vertices_queue.push({gfunction, neighbor});
                }
            }
        }

        WeightType minimal_length = min_distance[to];
        PathFinder::AlgoOutput output{.minimal_length=minimal_length};

        if(debug) {
            output.path = reconstructPath(from, to, previous);
            
            for(int i = 0; i < num_vertices; ++i) {
                if(used[i]) {
                    output.used.push_back(i);
                }
            }

        }

        return output;
    }
};
