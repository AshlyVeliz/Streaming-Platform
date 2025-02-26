#ifndef STREAMING_PLATFORM_RECOMENDADOR_H
#define STREAMING_PLATFORM_RECOMENDADOR_H

#include "Observer.h"
#include "AlgoritmoSimlitud.h"
#include "RelevanceCalculator.h"
#include <algorithm>

class Recomendador : public Observer {
private:
    AlgoritmoSimilitud<Pelicula>* algoritmo;
    vector<Pelicula> peliculas;

public:
    Recomendador(AlgoritmoSimilitud<Pelicula>* estrategia, const vector<Pelicula>& todasLasPeliculas)
            : algoritmo(estrategia), peliculas(todasLasPeliculas) {}

    void actualizar(const Pelicula& pelicula) override {
        cout << "\n Nueva recomendación basada en '" << pelicula.titulo << "'\n";
        vector<Pelicula> recomendaciones = algoritmo->encontrarSimilares(pelicula, peliculas);

        if (recomendaciones.empty()) {
            cout << "No se encontraron recomendaciones \n";
            return;
        }

        // Calcular relevancia para cada película
        vector<pair<int, Pelicula>> relevancias;
        for (const auto& peli : recomendaciones) {
            int relevancia = RelevanceCalculator::calcularRelevancia(peli, pelicula.titulo);
            relevancias.emplace_back(relevancia, peli);
        }

        // Ordenar por relevancia descendente y tomar solo las 5 mejores
        sort(relevancias.begin(), relevancias.end(), [](const auto& a, const auto& b) {
            return a.first > b.first;
        });

        size_t newSize = std::min(relevancias.size(), static_cast<size_t>(5));
        if (relevancias.size() > newSize) {
            relevancias.erase(relevancias.begin() + newSize, relevancias.end());
        }

        // Mostrar solo las 5 más relevantes
        cout << "Top 5 recomendaciones:\n";
        for (const auto& rec : relevancias) {
            cout << "🎬 " << rec.second.titulo << " (Relevancia: " << rec.first << ")\n";
        }
    }

};
#endif //STREAMING_PLATFORM_RECOMENDADOR_H
