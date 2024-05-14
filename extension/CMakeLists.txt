cmake_minimum_required(VERSION 3.10)
project(extension)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

find_package(PostgreSQL REQUIRED)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PostgreSQL_INCLUDE_DIRS}
        ${PostgreSQL_SERVER_INCLUDE_DIRS})

add_postgresql_extension(graph_db
        VERSION 1.0
        SOURCES graph_db.c
        SCRIPTS graph_db--1.0.sql)