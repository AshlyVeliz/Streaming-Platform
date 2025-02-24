#include <iostream>
#include "DataProcessor.h"
#include "TagTree.h"
#include "SearchTree.h"
#include "Ver_masTarde.h"

int main() {
    string rutaCSV = "/Users/ashlyveliz/Documents/PROYECTOS/Streaming-Platform/data/movies.csv";
    string rutaJSON = "/Users/ashlyveliz/Documents/PROYECTOS/Streaming-Platform/data/movies.json";

    // Cargar películas en un vector desde JSON o CSV
    vector<Pelicula> peliculas = DataProcessor::cargarPeliculasDesdeCSV(rutaCSV, rutaJSON);

    if (peliculas.empty()) {
        cout << "❌ No se cargaron películas. Revisa el archivo CSV o JSON." << endl;
        return 1;
    }

    TagTree tagTree;
    SearchTree searchTree;
    Ver_masTarde verMasTarde;

    // Insertar las películas en los árboles
    for (const auto& pelicula : peliculas) {
        for (const auto& tag : pelicula.tags) {
            tagTree.insertar(tag, pelicula);
        }
        searchTree.insertar(pelicula);
    }

    // 🔍 Búsqueda por título con paginación
    while (true) {
        string consulta;
        cout << "\n🔍 Ingrese una palabra o frase para buscar (o 'salir'): ";
        getline(cin, consulta);

        if (consulta == "salir") break;

        int pagina = 0;
        int peliculasPorPagina = 5;

        while (true) {
            vector<Pelicula> resultados = searchTree.buscar(consulta, pagina, peliculasPorPagina);

            if (resultados.empty()) {
                cout << "❌ No se encontraron coincidencias.\n";
                break;
            }

            cout << "\n🎥 Página " << (pagina + 1) << ":\n";
            for (size_t i = 0; i < resultados.size(); ++i) {
                cout << i + 1 << ". 🎬 " << resultados[i].titulo << " | 📖 " << resultados[i].sinopsis << endl;
            }

            cout << "\nOpciones:\n"
                 << "👉 'mas' para ver más\n"
                 << "👉 'agregar' para agregar una película a 'Ver más tarde'\n"
                 << "👉 'ver' para ver tu lista\n"
                 << "👉 'eliminar' para quitar la última añadida\n"
                 << "👉 'salir' para terminar\n"
                 << "Selecciona una opción: ";

            string opcion;
            cin >> opcion;
            cin.ignore();  // Limpiar buffer

            if (opcion == "mas") {
                pagina++;
            } else if (opcion == "agregar") {
                cout << "Ingrese el número de la película para agregar: ";
                int num; cin >> num;
                if (num >= 1 && num <= (int)resultados.size()) {
                    verMasTarde.agregar(resultados[num - 1]);
                } else {
                    cout << "⚠️ Número inválido.\n";
                }
            } else if (opcion == "ver") {
                verMasTarde.mostrar();
            } else if (opcion == "eliminar") {
                verMasTarde.eliminar();
            } else if (opcion == "salir") {
                break;
            } else {
                cout << "❌ Opción inválida.\n";
            }
        }
    }

    return 0;
}