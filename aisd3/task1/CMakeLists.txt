cmake_minimum_required(VERSION 3.17)
project(task1)

set(CMAKE_CXX_STANDARD 14)


add_executable(task1
        main.cpp IGraph.h /
        ListGraph.cpp ListGraph.h /
        MatrixGraph.cpp MatrixGraph.h /
        SetGraph.cpp SetGraph.h /
        ArcGraph.cpp ArcGraph.h)