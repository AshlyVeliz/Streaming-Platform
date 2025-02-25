//
// Created by Darlene on 24/02/2025.
//

#ifndef STREAMING_PLATFORM_MEGUSTA_H
#define STREAMING_PLATFORM_MEGUSTA_H
#include "ListaPila.h"
#include "DataProcessor.h"

class MeGusta {
private:
    ListaPila<Pelicula> lista;

public:
    void agregar(const Pelicula& pelicula) { lista.agregar(pelicula, "Me gusta"); }
    void mostrar() const { lista.mostrar("Me gusta"); }
    void eliminar() { lista.eliminar("Me gusta"); }
};
#endif //STREAMING_PLATFORM_MEGUSTA_H
