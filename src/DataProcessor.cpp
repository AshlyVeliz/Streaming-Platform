#include "DataProcessor.h"

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

    cout << "Peliculas cargadas desde JSON: " << peliculas.size() << endl;
    return peliculas;
}

vector<Pelicula> DataProcessor::cargarPeliculasDesdeCSV(const string& rutaCSV, const string& rutaJSON) {
    vector<Pelicula> peliculas;

    ifstream jsonFile(rutaJSON);
    if (jsonFile.good()) {
        cout << "Archivo JSON encontrado. Cargando datos desde JSON.\n";
        return cargarPeliculasDesdeJSON(rutaJSON);
    }

    ifstream archivoCSV(rutaCSV);
    if (!archivoCSV.is_open()) {
        cerr << "Error: No se pudo abrir el archivo CSV " << rutaCSV << endl;
        return peliculas;
    }

    string linea;
    getline(archivoCSV, linea);

    json jsonPeliculas;

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

        peliculas.emplace_back(titulo, sinopsis, tags, 0, false);
        jsonPeliculas.push_back({
                                        {"id", id},
                                        {"titulo", titulo},
                                        {"sinopsis", sinopsis},
                                        {"tags", tags},
                                        {"likes", 0},
                                        {"ver_luego", false}
                                });
    }

    archivoCSV.close();

    ofstream outFile(rutaJSON);
    if (outFile.is_open()) {
        outFile << jsonPeliculas.dump(4);
        outFile.close();
        cout << "Archivo JSON creado con exito: " << rutaJSON << endl;
    } else {
        cerr << "Error: No se pudo guardar el archivo JSON." << endl;
    }

    return peliculas;
}
