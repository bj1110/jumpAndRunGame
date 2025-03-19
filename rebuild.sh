#!/bin/bash
rm -rf build
mkdir build && cd build
cmake ..
make -j$(nproc)  # Nutzt alle CPU-Kerne für schnelleren Build
