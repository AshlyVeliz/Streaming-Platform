//
// Created by Ashly Veliz on 22/02/25.
//
#ifndef RELEVANCE_CALCULATOR_H
#define RELEVANCE_CALCULATOR_H

#include <string>
#include <cmath>
#include "DataProcessor.h"

class RelevanceCalculator {
public:
    static int calcularRelevancia(const Pelicula& pelicula, const string& consulta);
};

#endif // RELEVANCE_CALCULATOR_H
