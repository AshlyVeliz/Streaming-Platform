#ifndef STREAMING_PLATFORM_MEGUSTA_H
#define STREAMING_PLATFORM_MEGUSTA_H

#include "ListaPila.h"
#include "DataProcessor.h"
#include "SimilitudFactory.h"
#include "subject.h"

using namespace std;

class Megusta : public subject {
private:
    ListaPila<Pelicula> lista;
    unique_ptr<AlgoritmoSimilitud<Pelicula>> algoritmo;

public:
    explicit Megusta(TipoSimilitud tipoSimilitud) {
        algoritmo = SimilitudFactory::crearSimilitud(tipoSimilitud);
    }

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
                size_t maxRecomendaciones = min(recomendaciones.size(), size_t(5));
                for (size_t i = 0; i < maxRecomendaciones; ++i) {
                    cout << "🎬 " << recomendaciones[i].titulo << "\n";
                }
            }
        } else {
            cout << "No hay un algoritmo de similitud definido. \n";
        }
    }
};

#endif //STREAMING_PLATFORM_MEGUSTA_H
