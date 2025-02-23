//
// Created by Ashly Veliz on 22/02/25.
//
#ifndef STREAMING_PLATFORM_RELEVANCE_CALCULATOR_H
#define STREAMING_PLATFORM_RELEVANCE_CALCULATOR_H

#include <string>
#include <cmath>
#include "DataProcessor.h"

class RelevanceCalculator {
public:
    static int calcularRelevancia(const Pelicula& pelicula, const string& consulta);
};

#endif STREAMING_PLATFORM_RELEVANCE_CALCULATOR_H
