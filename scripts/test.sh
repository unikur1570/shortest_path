#!/bin/bash

for i in {1..25}; do
    ./build/shortest_path --algorithm d --graph_file ./graph/graphbel.txt --coords_file ./graph/coordsbel.txt --from 1647088 --to 1766212 >> ./output_data/time/dijkstra_2_time.txt
done
