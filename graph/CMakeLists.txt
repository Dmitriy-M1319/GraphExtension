cmake_minimum_required(VERSION 3.14)
project(graph)

set(HEADERS include/NodeEdgeVault.h
        include/Graph.h
        include/GraphTypes.h
        include/PropVault.h
        include/StringsVault.h)

include_directories(include)

add_library(${PROJECT_NAME}
        src/StringsVault.cpp
        src/NodeEdgeVault.cpp
        src/Graph.cpp
        src/PropVault.cpp ${HEADERS})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_include_directories(${PROJECT_NAME} PUBLIC includes)