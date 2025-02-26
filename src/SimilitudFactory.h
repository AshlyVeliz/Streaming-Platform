//
// Created by Ashly Veliz on 25/02/25.
//
// SimilitudFactory.h
#ifndef STREAMING_PLATFORM_SIMILITUDFACTORY_H
#define STREAMING_PLATFORM_SIMILITUDFACTORY_H

#include "AlgoritmoSimlitud.h"
#include "SimilitudSinopsis.h"
#include "SimilitudTag.h"
#include <memory>

using namespace std;

enum class TipoSimilitud {
    SINOPSIS,
    TAGS
};

class SimilitudFactory {
public:
    static unique_ptr<AlgoritmoSimilitud<Pelicula>> crearSimilitud(TipoSimilitud tipo) {
        switch (tipo) {
            case TipoSimilitud::SINOPSIS:
                return make_unique<SimilitudPorSinopsis>();
            case TipoSimilitud::TAGS:
                return make_unique<SimilitudPorTags>();
            default:
                throw invalid_argument("Tipo de similitud no válido");
        }
    }
};

#endif // STREAMING_PLATFORM_SIMILITUDFACTORY_H