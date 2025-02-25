#include <iostream>
#include "DataProcessor.h"
#include "TagTree.h"
#include "SearchTree.h"
#include "Ver_masTarde.h"
#include "Megusta.h"  // ✅ Asegurar que el include esté bien escrito
#include "SimilitudTag.h"

using namespace std;

int main() {
    string rutaCSV = "C:\\Streaming-Platform\\data\\movies.csv";
    string rutaJSON = "C:\\Streaming-Platform\\data\\movies.json";

    // Cargar películas en un vector desde JSON o CSV
    vector<Pelicula> peliculas = DataProcessor::cargarPeliculasDesdeCSV(rutaCSV, rutaJSON);

    if (peliculas.empty()) {
        cout << "❌ No se cargaron películas. Revisa el archivo CSV o JSON." << endl;
        return 1;
    }

    TagTree tagTree;
    SearchTree searchTree;
    Ver_masTarde verMasTarde;

    // 🔥 Estrategia de similitud basada en tags (puedes cambiar a SimilitudPorSinopsis)
    SimilitudPorTags estrategiaSimilitud;
    Megusta meGusta(&estrategiaSimilitud);  // ✅ Se asegura que el nombre es "Megusta"

    // Insertar las películas en los árboles
    for (const auto& pelicula : peliculas) {
        for (const auto& tag : pelicula.tags) {
            tagTree.insertar(tag, pelicula);
        }
        searchTree.insertar(pelicula);
    }

    // 🔹 Búsqueda por título con paginación y opciones
    while (true) {
        string consulta;
        cout << "\n🔎 Ingrese una palabra o frase para buscar (o 'salir'): ";
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

            cout << "\n📜 Página " << (pagina + 1) << ":\n";
            for (size_t i = 0; i < resultados.size(); ++i) {
                cout << i + 1 << ". 🎬 " << resultados[i].titulo << " | 📖 " << resultados[i].sinopsis << endl;
            }

            cout << "\n📌 Opciones:\n"
                 << "'mas' -> Ver más resultados\n"
                 << "'agregar' -> Agregar a 'Ver más tarde'\n"
                 << "'like' -> Agregar a 'Me gusta'\n"
                 << "'ver' -> Ver listas\n"
                 << "'recomendar' -> Mostrar películas similares a 'Me gusta'\n"
                 << "'eliminar' -> Quitar la última añadida\n"
                 << "'salir' -> Terminar\n"
                 << "➡️ Selecciona una opción: ";

            string opcion;
            cin >> opcion;
            cin.ignore();  // Limpiar buffer

            if (opcion == "mas") {
                pagina++;
            } else if (opcion == "agregar") {
                cout << "Ingrese el número de la película para agregar a 'Ver más tarde': ";
                int num; cin >> num;
                if (num >= 1 && num <= (int)resultados.size()) {
                    verMasTarde.agregar(resultados[num - 1]);
                } else {
                    cout << "❌ Número inválido.\n";
                }
            } else if (opcion == "like") {
                cout << "Ingrese el número de la película para agregar a 'Me gusta': ";
                int num; cin >> num;
                if (num >= 1 && num <= (int)resultados.size()) {
                    meGusta.agregar(resultados[num - 1]);
                } else {
                    cout << "❌ Número inválido.\n";
                }
            } else if (opcion == "ver") {
                cout << "\n📂 Lista 'Ver más tarde':\n";
                verMasTarde.mostrar();
                cout << "\n❤️ Lista 'Me gusta':\n";
                meGusta.mostrar();
            } else if (opcion == "recomendar") {
                meGusta.recomendarSimilares(peliculas);
            } else if (opcion == "eliminar") {
                cout << "¿De qué lista deseas eliminar? ('ver' para 'Ver más tarde', 'like' para 'Me gusta'): ";
                string lista;
                cin >> lista;
                if (lista == "ver") {
                    verMasTarde.eliminar();
                } else if (lista == "like") {
                    meGusta.eliminar();
                } else {
                    cout << "❌ Opción inválida.\n";
                }
            } else if (opcion == "salir") {
                break;
            } else {
                cout << "❌ Opción inválida.\n";
            }
        }
    }

    return 0;
}
