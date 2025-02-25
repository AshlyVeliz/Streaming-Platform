//
// Created by Darlene on 24/02/2025.
//

#ifndef STREAMING_PLATFORM_VER_MASTARDE_H
#define STREAMING_PLATFORM_VER_MASTARDE_H
#include "ListaPila.h"
#include "DataProcessor.h"

class Ver_masTarde {
private:
    ListaPila<Pelicula> lista;

public:
    void agregar(const Pelicula& pelicula) { lista.agregar(pelicula, "Ver más tarde"); }
    void mostrar() const { lista.mostrar("Ver más tarde"); }
    void eliminar() { lista.eliminar("Ver más tarde"); }
};

#endif //STREAMING_PLATFORM_VER_MASTARDE_H