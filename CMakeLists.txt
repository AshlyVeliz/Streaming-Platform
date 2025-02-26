cmake_minimum_required(VERSION 3.16)
project(Streaming_Platform)

set(CMAKE_CXX_STANDARD 17)
include_directories(src)
add_executable(Streaming_Platform
        src/main.cpp
        src/DataProcessor.cpp
        src/TagTree.cpp
        src/RelevanceCalculator.cpp
        src/SearchTree.cpp
        src/SearchTree.h
        src/Ver_masTarde.h
        src/ListaPila.h
        src/Megusta.h
        src/AlgoritmoSimlitud.h
        src/SimilitudTag.h
        src/SimilitudSinopsis.h
        src/observer.h
        src/subject.h
        src/recomendador.h
)


