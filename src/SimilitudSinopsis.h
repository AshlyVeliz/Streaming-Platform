//
// Created by Darlene on 24/02/2025.
//

#ifndef STREAMING_PLATFORM_SIMILITUDSINOPSIS_H
#define STREAMING_PLATFORM_SIMILITUDSINOPSIS_H

#include "AlgoritmoSimlitud.h"
#include <algorithm>
#include <unordered_set>

class SimilitudPorSinopsis : public AlgoritmoSimilitud<Pelicula> {
public:
    std::vector<Pelicula> encontrarSimilares(const Pelicula& pelicula, const std::vector<Pelicula>& peliculas) override {
        std::vector<Pelicula> similares;

        for (const auto& otra : peliculas) {
            if (pelicula.titulo == otra.titulo) continue;

            int coincidencias = contarPalabrasComunes(pelicula.sinopsis, otra.sinopsis);
            if (coincidencias >= 3) { // Ajusta este número según necesidad
                similares.push_back(otra);
            }
        }

        return similares;
    }

private:
    int contarPalabrasComunes(const std::string& s1, const std::string& s2) {
        std::unordered_set<std::string> palabras1 = dividirEnPalabras(s1);
        std::unordered_set<std::string> palabras2 = dividirEnPalabras(s2);

        int contador = 0;
        for (const auto& palabra : palabras1) {
            if (palabras2.count(palabra)) {
                contador++;
            }
        }
        return contador;
    }

    std::unordered_set<std::string> dividirEnPalabras(const std::string& texto) {
        std::unordered_set<std::string> palabras;
        std::string palabra;
        for (char c : texto) {
            if (isspace(c)) {
                if (!palabra.empty()) {
                    palabras.insert(palabra);
                    palabra.clear();
                }
            } else {
                palabra += tolower(c);
            }
        }
        if (!palabra.empty()) palabras.insert(palabra);
        return palabras;
    }
};

#endif //STREAMING_PLATFORM_SIMILITUDSINOPSIS_H
