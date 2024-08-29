#!/bin/bash
set -x
set -e

../build/shortest_path \
    --algorithm astar \
    --graph_file ../graph/graph_bel.txt \
    --coords_file ../graph/coords_bel.txt \
    --from 1 \
    --to 0 \
    --debug \
    --output_file output.txt
