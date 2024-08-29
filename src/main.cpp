#include <argparse/argparse.hpp>
#include <cctype>
#include <fstream>
#include <ios>
#include <iostream>
#include <memory>
#include <ostream>

#include "a_star.h"
#include "base_path_finder.h"
#include "dijkstra.h"
#include "graph.h"

std::unique_ptr<PathFinder> GetAlgoImplementation(std::string&& algo) {
    std::transform(algo.begin(), algo.end(), algo.begin(), [](unsigned char c) { return std::tolower(c); });

    if (algo == "d" || algo == "dijkstra") {
        return std::unique_ptr<DijkstraPathFinder>(new DijkstraPathFinder());
    } else if (algo == "a" || algo == "astar") {
        return std::unique_ptr<AStarPathFinder>(new AStarPathFinder());
    } else {
        std::cerr << "Invalid algo. Use \"dijkstra\" or \"astar\"";
        std::exit(1);
    }
}

int main(int argc, char* argv[]) {
    argparse::ArgumentParser arguments("shortest_path");

    arguments.add_argument("--algorithm")
        .default_value(std::string{"dijkstra"})
        .help("Algorithm to use. Possible variants: dijkstra, astar");

    arguments.add_argument("--debug").help("If set, print debug information [path, used vertexes]").flag();

    arguments.add_argument("--graph_file").required().help("Input graph file");

    arguments.add_argument("--coords_file").required().help("Input coordinates file");

    arguments.add_argument("--from")
        .required()
        .help("Algorithm's start point [integer from 0 to graph size]")
        .scan<'i', int>();

    arguments.add_argument("--to")
        .required()
        .help("Point to find distance to [integer from 0 to graph size]")
        .scan<'i', int>();

    arguments.add_argument("--output_file")
        .help("If set, write output information to a file. Otherwise, to the console.");

    try {
        arguments.parse_args(argc, argv);
    } catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << arguments;
        std::exit(1);
    }

    double debug_flag = false;
    if (arguments["--debug"] == true) {
        debug_flag = true;
        std::cout << "Path saving enabled" << std::endl;
    }

    Graph g(arguments.get("--coords_file"), arguments.get("--graph_file"));

    auto algo_name = arguments.get<std::string>("--algorithm");
    auto algo_impl = GetAlgoImplementation(std::move(algo_name));

    int from = arguments.get<int>("--from");
    int to = arguments.get<int>("--to");
    auto output = algo_impl->findShortestPathWithTiming(g, from, to, debug_flag);

    std::ofstream output_file;
    std::ostream* output_stream;
    if (arguments.is_used("output_file")) {
        output_file.open(arguments.get("--output_file"), std::ios_base::out);
        if (!output_file.is_open()) {
            throw std::runtime_error("Can not open output file");
        }
        output_stream = &output_file;
    } else {
        output_stream = &std::cout;
    }

    *output_stream << "Time: " << output.time_ms << '\n';
    *output_stream << "Length: " << output.minimal_length << '\n';

    if (arguments["--debug"] == true) {
        *output_stream << "Path: ";

        for (int node : output.path) {
            *output_stream << node << ' ';
        }
        *output_stream << "\nUsed: ";
        for (int node : output.used) {
            *output_stream << node << ' ';
        }
    }

    return 0;
}
