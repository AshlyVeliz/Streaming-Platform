#ifndef DATA_PROCESSOR_H
#define DATA_PROCESSOR_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <thread>
#include <mutex>
#include "../include/json.hpp"

using namespace std;
using json = nlohmann::json;

struct Pelicula {
    string titulo;
    string sinopsis;
    vector<string> tags;
    int likes;
    bool ver_luego;

    Pelicula(const string& _titulo, const string& _sinopsis, const vector<string>& _tags, int _likes = 0, bool _ver_luego = false)
            : titulo(_titulo), sinopsis(_sinopsis), tags(_tags), likes(_likes), ver_luego(_ver_luego) {}
};

class DataProcessor {
public:
    static vector<Pelicula> cargarPeliculasDesdeCSV(const string& rutaCSV, const string& rutaJSON);
    static vector<Pelicula> cargarPeliculasDesdeJSON(const string& rutaJSON);
    static void guardarJSON(const vector<Pelicula>& peliculas, const string& rutaJSON);

private:
    static void procesarLinea(const string& linea, vector<Pelicula>& peliculas, mutex& m);
};

#endif // DATA_PROCESSOR_H

