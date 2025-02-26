//
// Created by Darlene on 25/02/2025.
//

#ifndef STREAMING_PLATFORM_RECOMENDADOR_H
#define STREAMING_PLATFORM_RECOMENDADOR_H
#include "Observer.h"
#include "AlgoritmoSimlitud.h"

class recomendador : public Observer {
private:
    AlgoritmoSimilitud<Pelicula>* algoritmo;
    vector<Pelicula> peliculas;

public:
    recomendador(AlgoritmoSimilitud<Pelicula>* estrategia, const vector<Pelicula>& todasLasPeliculas)
            : algoritmo(estrategia), peliculas(todasLasPeliculas) {}

    void actualizar(const Pelicula& pelicula) override {
        cout << "\n Nueva recomendación basada en '" << pelicula.titulo << "'\n";
        vector<Pelicula> recomendaciones = algoritmo->encontrarSimilares(pelicula, peliculas);

        if (recomendaciones.empty()) {
            cout << "No se encontraron recomendaciones \n";
        } else {
            for (const auto& peli : recomendaciones) {
                cout << "peli " << peli.titulo << endl;
            }
        }
    }
};
#endif //STREAMING_PLATFORM_RECOMENDADOR_H
