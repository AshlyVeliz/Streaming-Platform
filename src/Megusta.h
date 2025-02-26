#ifndef STREAMING_PLATFORM_MEGUSTA_H
#define STREAMING_PLATFORM_MEGUSTA_H

#include "ListaPila.h"
#include "DataProcessor.h"
#include "AlgoritmoSimlitud.h"
#include "Subject.h"

using namespace std;

class Megusta : public subject {
private:
    ListaPila<Pelicula> lista;
    AlgoritmoSimilitud<Pelicula>* algoritmo;

public:

    explicit Megusta(AlgoritmoSimilitud<Pelicula>* estrategia) : algoritmo(estrategia) {}


    void agregar(const Pelicula& pelicula) {
        lista.agregar(pelicula, "Me gusta");
        notificarObservadores(pelicula);
    }

    void mostrar() const { lista.mostrar("Me gusta"); }

    void eliminar() { lista.eliminar("Me gusta"); }

    void recomendarSimilares(const vector<Pelicula>& todasLasPeliculas) {
        if (lista.estaVacia()) {
            cout << "No tienes películas en 'Me gusta' para generar recomendaciones \n";
            return;
        }

        cout << "\n  Películas recomendadas basadas en tus 'Me gusta':\n";
        Pelicula ultimaPelicula = lista.obtenerUltima();


        if (algoritmo) {
            vector<Pelicula> recomendaciones = algoritmo->encontrarSimilares(ultimaPelicula, todasLasPeliculas);

            if (recomendaciones.empty()) {
                cout << "No se encontraron películas similares \n";
            } else {
                for (const auto& pelicula : recomendaciones) {
                    cout << "pelicula " << pelicula.titulo << "\n";
                }
            }
        } else {
            cout << "No hay un algoritmo de similitud definido. \n";
        }
    }
};

#endif //STREAMING_PLATFORM_MEGUSTA_H
