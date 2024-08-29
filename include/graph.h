#pragma once

#include <cstdio>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

struct Graph {
    struct Edge {
        double weight;
        int node;
        double lat;
        double lon;
    };

    struct Cords {
        double lat;
        double lon;
    };

    using Neighbours = std::vector<Edge>;

    std::vector<Neighbours> adjacency_list;
    std::vector<Cords> coordinates;

    Graph(const std::string& filecords, const std::string& filegraph) {
        ReadCords(filecords);
        ReadFromFile(filegraph);
    }

    Graph() = default;

    Graph(const Graph& other) : adjacency_list(other.adjacency_list), coordinates(other.coordinates) {}

    Graph operator=(Graph&& other) {
        adjacency_list = std::move(other.adjacency_list);
        coordinates = std::move(other.coordinates);
        return *this;
    }

    Graph operator=(const Graph& other) {
        adjacency_list = other.adjacency_list;
        coordinates = other.coordinates;
        return *this;
    }

    Graph(Graph&& other) {
        adjacency_list = std::move(other.adjacency_list);
        coordinates = std::move(other.coordinates);
    }

    void AddEdge(int node1, int node2, double weight, double lat1, double lon1, double lat2, double lon2) {
        adjacency_list[node1].emplace_back(Edge{weight, node2, lat2, lon2});
        adjacency_list[node2].emplace_back(Edge{weight, node1, lat1, lon1});
    }

    void ReadCords(const std::string& filecords) {
        std::ifstream cords_file(filecords);
        if (!cords_file.is_open()) {
            throw std::runtime_error("Can not open the cords file");
        }
        int node;
        double lat, lon;
        while (cords_file >> node >> lat >> lon) {
            coordinates.emplace_back(Cords{lat, lon});
        }
    }

    void ReadFromFile(const std::string& filegraph) {
        std::ifstream graph_file(filegraph);
        if (!graph_file.is_open()) {
            throw std::runtime_error("Can not open the graph file");
        }

        size_t n;
        graph_file >> n;
        adjacency_list.resize(n);

        int node1, node2;
        double weight;
        while (graph_file >> node1 >> node2 >> weight) {
            double lat1 = coordinates[node1].lat;
            double lon1 = coordinates[node1].lon;
            double lat2 = coordinates[node2].lat;
            double lon2 = coordinates[node2].lon;

            AddEdge(node1, node2, weight, lat1, lon1, lat2, lon2);
        }
    }

    const size_t Size() const { return adjacency_list.size(); }
};
