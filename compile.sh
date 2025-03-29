#!/bin/bash
# Clean
rm -f *.o dydx_cli

# Compile
g++ -std=c++17 -I. -c dydx_api.cpp
g++ -std=c++17 -I. -c dydx_cli.cpp
g++ -std=c++17 -I. -c main.cpp

# Link
g++ -std=c++17 dydx_api.o dydx_cli.o main.o -lcurl -o dydx_cli

# Set permissions
chmod +x dydx_cli