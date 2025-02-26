//
// Created by Darlene on 25/02/2025.
//

#ifndef STREAMING_PLATFORM_SUBJECT_H
#define STREAMING_PLATFORM_SUBJECT_H
#include <vector>
#include "Observer.h"

class subject {
private:
    std::vector<Observer*> observadores;

public:
    void agregarObservador(Observer* obs) {
        observadores.push_back(obs);
    }

    void eliminarObservador(Observer* obs) {
        observadores.erase(remove(observadores.begin(), observadores.end(), obs), observadores.end());
    }

    void notificarObservadores(const Pelicula& pelicula) {
        for (Observer* obs : observadores) {
            obs->actualizar(pelicula);
        }
    }
};

#endif //STREAMING_PLATFORM_SUBJECT_H
