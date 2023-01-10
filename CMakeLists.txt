cmake_minimum_required(VERSION 3.23)
project(Proj2_AED)

set(CMAKE_CXX_STANDARD 14)

add_executable(Proj2_AED src/main.cpp src/FileReader.cpp src/FileReader.h src/Airlines.cpp src/Airlines.h src/Airports.cpp src/Airports.h src/Coordinates.cpp src/Coordinates.h src/graph.cpp src/graph.h src/Flights.cpp src/Flights.h src/Path.cpp src/Path.h src/Menu.cpp src/Menu.h "src/AirTrafficControl.cpp" "src/AirTrafficControl.h" )
