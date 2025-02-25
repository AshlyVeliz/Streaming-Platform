//
// Created by Darlene on 24/02/2025.
//

#ifndef STREAMING_PLATFORM_MEGUSTA_H
#define STREAMING_PLATFORM_MEGUSTA_H

#include "ListaPila.h"
#include "DataProcessor.h"
#include "AlgoritmoSimlitud.h"  // ✅ Corrección de nombre
using namespace std;

class Megusta {  // ✅ Cambiar a Megusta en todas partes para que coincida con main.cpp
private:
    ListaPila<Pelicula> lista;
    AlgoritmoSimilitud<Pelicula>* algoritmo = nullptr;  // Estrategia de similitud

public:
    Megusta(AlgoritmoSimilitud<Pelicula>* estrategia) : algoritmo(estrategia) {}

    void agregar(const Pelicula& pelicula) { lista.agregar(pelicula, "Me gusta"); }
    void mostrar() const { lista.mostrar("Me gusta"); }
    void eliminar() { lista.eliminar("Me gusta"); }

    void recomendarSimilares(const vector<Pelicula>& todasLasPeliculas) {
        if (lista.estaVacia()) {
            cout << "❌ No tienes películas en 'Me gusta' para generar recomendaciones.\n";
            return;
        }

        cout << "\n🎥 Películas recomendadas basadas en tus 'Me gusta':\n";
        Pelicula ultimaPelicula = lista.obtenerUltima();
        vector<Pelicula> recomendaciones = algoritmo->encontrarSimilares(ultimaPelicula, todasLasPeliculas);

        if (recomendaciones.empty()) {
            cout << "❌ No se encontraron películas similares.\n";
        } else {
            for (const auto& pelicula : recomendaciones) {
                cout << "🎬 " << pelicula.titulo << "\n";
            }
        }
    }
};

#endif //STREAMING_PLATFORM_MEGUSTA_H
