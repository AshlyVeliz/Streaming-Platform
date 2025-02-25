//
// Created by Darlene on 24/02/2025.
//

#ifndef STREAMING_PLATFORM_ALGORITMOSIMILITUD_H
#define STREAMING_PLATFORM_ALGORITMOSIMILITUD_H

#include "DataProcessor.h"
#include <vector>

template<typename T>
class AlgoritmoSimilitud {
public:
    virtual ~AlgoritmoSimilitud() = default;
    virtual std::vector<T> encontrarSimilares(const T& pelicula, const std::vector<T>& peliculas) = 0;
};

#endif //STREAMING_PLATFORM_ALGORITMOSIMILITUD_H
