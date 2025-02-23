//
// Created by Ashly Veliz on 22/02/25.
//

#include "RelevanceCalculator.h"
#include <cmath>

// Calcular relevancia de una película según la consulta
int RelevanceCalculator::calcularRelevancia(const Pelicula& pelicula, const string& consulta) {
    int puntuacion = 0;

    //Buscar consulta en título (5 puntos exacta, 3 parcial)
    if (pelicula.titulo == consulta) {
        puntuacion += 5;
    } else if (pelicula.titulo.find(consulta) != string::npos) {
        puntuacion += 3;
    }

    //Buscar consulta en sinopsis (3 puntos por aparición)
    size_t pos = pelicula.sinopsis.find(consulta);
    while (pos != string::npos) {
        puntuacion += 3;
        pos = pelicula.sinopsis.find(consulta, pos + 1);
    }

    //Buscar consulta en tags (4 puntos si coincide con un tag)
    for (const string& tag : pelicula.tags) {
        if (tag == consulta) {
            puntuacion += 4;
            break;
        }
    }

    //Ajustar por cantidad de likes usando logaritmo
    if (pelicula.likes > 0) {
        puntuacion += round(pelicula.likes / log(1 + pelicula.likes));
    }

    return puntuacion;
}
