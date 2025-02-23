#ifndef DATA_PROCESSOR_H
#define DATA_PROCESSOR_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "../include/json.hpp"  // Asegúrate de que json.hpp está en la carpeta include/

using namespace std;
using json = nlohmann::json;

struct Pelicula {
    string titulo;
    string sinopsis;
    vector<string> tags;

    Pelicula(const string& _titulo, const string& _sinopsis, const vector<string>& _tags)
            : titulo(_titulo), sinopsis(_sinopsis), tags(_tags) {}
};

class DataProcessor {
public:
    // Cargar películas desde JSON a un vector
    static vector<Pelicula> cargarPeliculasDesdeJSON(const string& rutaJSON);

    // Cargar películas desde CSV (si no existe JSON) y convertir a JSON
    static vector<Pelicula> cargarPeliculasDesdeCSV(const string& rutaCSV, const string& rutaJSON);
};

#endif // DATA_PROCESSOR_H
