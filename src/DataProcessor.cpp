#include "DataProcessor.h"

using namespace std;

// Método estático para devolver la única instancia de DataProcessor
DataProcessor& DataProcessor::getInstance() {
    static DataProcessor instance; // Instancia única
    return instance;
}

// Cargar películas desde JSON
vector<Pelicula> DataProcessor::cargarPeliculasDesdeJSON(const string& rutaJSON) {
    vector<Pelicula> peliculas;
    ifstream jsonFile(rutaJSON);

    if (!jsonFile.is_open()) {
        cerr << "Error: No se pudo abrir el archivo JSON " << rutaJSON << endl;
        return peliculas;
    }

    json jsonPeliculas;
    jsonFile >> jsonPeliculas;
    jsonFile.close();

    for (const auto& item : jsonPeliculas) {
        peliculas.emplace_back(
                item["titulo"].get<string>(),
                item["sinopsis"].get<string>(),
                item["tags"].get<vector<string>>(),
                item.value("likes", 0),
                item.value("ver_luego", false)
        );
    }

    cout << "✔ Películas cargadas desde JSON: " << peliculas.size() << endl;
    return peliculas;
}

// Guardar películas en JSON
void DataProcessor::guardarJSON(const vector<Pelicula>& peliculas, const string& rutaJSON) {
    json jsonPeliculas;
    for (const auto& pelicula : peliculas) {
        jsonPeliculas.push_back({
                                        {"titulo", pelicula.titulo},
                                        {"sinopsis", pelicula.sinopsis},
                                        {"tags", pelicula.tags},
                                        {"likes", pelicula.likes},
                                        {"ver_luego", pelicula.ver_luego}
                                });
    }

    ofstream outFile(rutaJSON);
    if (outFile.is_open()) {
        outFile << jsonPeliculas.dump(4);
        outFile.close();
        cout << "✔ Archivo JSON creado con éxito: " << rutaJSON << endl;
    } else {
        cerr << "Error: No se pudo guardar el archivo JSON." << endl;
    }
}

// Cargar películas desde CSV con Singleton
vector<Pelicula> DataProcessor::cargarPeliculasDesdeCSV(const string& rutaCSV, const string& rutaJSON) {
    vector<Pelicula> peliculas;

    // Si JSON ya existe, cargar desde JSON en lugar de CSV
    ifstream jsonFile(rutaJSON);
    if (jsonFile.good()) {
        cout << "✔ Archivo JSON encontrado. Cargando datos desde JSON.\n";
        return cargarPeliculasDesdeJSON(rutaJSON);
    }

    ifstream archivoCSV(rutaCSV);
    if (!archivoCSV.is_open()) {
        cerr << "Error: No se pudo abrir el archivo CSV " << rutaCSV << endl;
        return peliculas;
    }

    string linea;
    getline(archivoCSV, linea);

    while (getline(archivoCSV, linea)) {
        stringstream ss(linea);
        string id, titulo, sinopsis, tagsStr;

        getline(ss, id, ',');
        getline(ss, titulo, ',');
        getline(ss, sinopsis, ',');
        getline(ss, tagsStr, ',');

        vector<string> tags;
        stringstream ssTags(tagsStr);
        string tag;
        while (getline(ssTags, tag, ' ')) {
            if (!tag.empty() && tag.front() == '"') tag.erase(0, 1);
            if (!tag.empty() && tag.back() == '"') tag.pop_back();
            tags.push_back(tag);
        }

        Pelicula pelicula(titulo, sinopsis, tags, 0, false);
        peliculas.push_back(pelicula);
    }

    archivoCSV.close();

    guardarJSON(peliculas, rutaJSON);

    return peliculas;
}