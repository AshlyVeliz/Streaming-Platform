//
// Created by Darlene on 24/02/2025.
//

#ifndef STREAMING_PLATFORM_SIMILITUDTAG_H
#define STREAMING_PLATFORM_SIMILITUDTAG_H

#include "AlgoritmoSimlitud.h"
#include <unordered_set>

class SimilitudPorTags : public AlgoritmoSimilitud<Pelicula> {
public:
    std::vector<Pelicula> encontrarSimilares(const Pelicula& pelicula, const std::vector<Pelicula>& peliculas) override {
        std::vector<Pelicula> similares;
        std::unordered_set<std::string> tagsPelicula(pelicula.tags.begin(), pelicula.tags.end());

        for (const auto& otra : peliculas) {
            if (pelicula.titulo == otra.titulo) continue; // Evitar recomendar la misma película

            int coincidencias = 0;
            for (const auto& tag : otra.tags) {
                if (tagsPelicula.count(tag)) {
                    coincidencias++;
                }
            }

            if (coincidencias >= 2) { // Ajusta este número según necesidad
                similares.push_back(otra);
            }
        }

        return similares;
    }
};

#endif //STREAMING_PLATFORM_SIMILITUDTAG_H
