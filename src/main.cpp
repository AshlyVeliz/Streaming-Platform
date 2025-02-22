#include <iostream>
#include "DataProcessor.h"


int main() {
    string rutaCSV = "/Users/ashlyveliz/Documents/PROYECTOS/Streaming-Platform/data/movies.csv";  //cambiar a su ruta
    vector<Pelicula> peliculas = DataProcessor::cargarPeliculasDesdeCSV(rutaCSV);

    if (peliculas.empty()) {
        cout << "No se cargaron películas. Revisa el archivo CSV." << endl;
        return 1;
    }

    // Mostrar las primeras 5 películas cargadas
    cout << "📽️ Películas cargadas desde CSV: " << endl;
    for (size_t i = 0; i < min(peliculas.size(), size_t(5)); ++i) {
        cout << "\n🎬 Título: " << peliculas[i].titulo << endl;
        cout << "📖 Sinopsis: " << peliculas[i].sinopsis << endl;
        cout << "🏷️ Tags: ";
        for (const auto& tag : peliculas[i].tags) {
            cout << "#" << tag << " ";
        }
        cout << endl;
    }

}
