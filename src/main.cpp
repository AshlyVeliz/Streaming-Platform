#include <iostream>
#include "DataProcessor.h"
#include "TagTree.h"
#include "SearchTree.h"
#include "Ver_masTarde.h"
#include "Megusta.h"
#include "SimilitudTag.h"
#include "recomendador.h"

using namespace std;

int main() {
    string rutaCSV = "/Users/ashlyveliz/Documents/PROYECTOS/Streaming-Platform/data/movies.csv";
    string rutaJSON = "/Users/ashlyveliz/Documents/PROYECTOS/Streaming-Platform/data/movies.json";

    // Cargar películas en un vector desde JSON o CSV
    vector<Pelicula> peliculas = DataProcessor::getInstance().cargarPeliculasDesdeCSV(rutaCSV, rutaJSON);

    if (peliculas.empty()) {
        cout << "🚨 No se cargaron películas. Revisa el archivo .CSV o .JSON 🚨" << endl;
        return 1;
    }

    TagTree tagTree;
    SearchTree searchTree;
    Ver_masTarde verMasTarde;

    // Estrategia de similitud basada en tags
    SimilitudPorTags estrategiaSimilitud;
    Megusta meGusta(TipoSimilitud::TAGS);


    //Crear recomendador y suscribirlo a "Me gusta"
    Recomendador recomendador(&estrategiaSimilitud, peliculas);
    meGusta.agregarObservador(&recomendador);

    // Insertar las películas en los árboles
    for (const auto& pelicula : peliculas) {
        for (const auto& tag : pelicula.tags) {
            tagTree.insertar(tag, pelicula);
        }
        searchTree.insertar(pelicula);
    }

    cout << "🎉 Bienvenido a CINEFLIX (movie discovery system) 🎬🍿" << endl;

    while (true) {
        string opcionBusqueda;
        cout << "\n Opciones de búsqueda: (Ingresa el número de la opción)\n"
             << "1️⃣ Buscar por palabra o frase\n"
             << "2️⃣ Buscar por tag\n"
             << "3️⃣ Salir\n"
             << "➡️ Selecciona una opción: ";
        cin >> opcionBusqueda;
        cin.ignore();

        if (opcionBusqueda == "3") break;

        string consulta;
        if (opcionBusqueda == "1") {
            cout << "\n🔎Ingrese una palabra o frase para buscar: ";
            getline(cin, consulta);
        } else if (opcionBusqueda == "2") {
            cout << "\n🔍#️⃣Ingrese un tag para buscar películas: ";
            cin >> consulta;
            cin.ignore();
        } else {
            cout << "Opción inválida😒 Intente nuevamente😛\n";
            continue;
        }

        int pagina = 0;
        int peliculasPorPagina = 5;
        vector<Pelicula> resultados;

        while (true) {
            if (opcionBusqueda == "1") {
                resultados = searchTree.buscar(consulta, pagina, peliculasPorPagina);
            } else if (opcionBusqueda == "2") {
                resultados = tagTree.buscarPeliculasPorTag(consulta);
            }

            if (resultados.empty()) {
                cout << "No se encontraron coincidencias😩 \n";
                break;
            }

            cout << "\n📜 Página " << (pagina + 1) << ":\n";
            for (size_t i = 0; i < min(resultados.size(), size_t(peliculasPorPagina)); ++i) {
                cout << i + 1 << ". 🎬 " << resultados[i].titulo << " | 📖 " << resultados[i].sinopsis << endl;
            }

            cout << "\nOpciones:\n"
                 << "'mas' -> Ver más resultados\n"
                 << "'agregar' -> Agregar a 'Ver más tarde'\n"
                 << "'like' -> Agregar a 'Me gusta'\n"
                 << "'ver' -> Ver listas guardadas\n"
                 << "'recomendar' -> Mostrar películas similares a 'Me gusta'\n"
                 << "'eliminar' -> Quitar la última añadida de una lista\n"
                 << "'salir' -> Terminar búsqueda\n"
                 << "➡️ Selecciona una opcion: ";

            string opcion;
            cin >> opcion;
            cin.ignore();

            if (opcion == "mas") {
                if ((pagina + 1) * peliculasPorPagina >= resultados.size()) {
                    cout << "No hay más resultados 👻 (busca otra peli 🤓)\n";
                } else {
                    pagina++;
                }
            } else if (opcion == "agregar") {
                cout << "Ingrese el número de la película para agregar a 'Ver más tarde': ";
                int num;
                cin >> num;

                if (cin.fail() || num < 1 || num > (int)resultados.size()) {
                    cout << "Número inválido 😒\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                } else {
                    verMasTarde.agregar(resultados[num - 1]);
                    cout << "✔︎ Agregada a 'Ver más tarde'.\n";
                }
            } else if (opcion == "like") {
                cout << "Ingrese el número de la película para agregar a 'Me gusta': ";
                int num;
                cin >> num;

                if (cin.fail() || num < 1 || num > (int)resultados.size()) {
                    cout << "Número inválido 😒\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                } else {
                    meGusta.agregar(resultados[num - 1]);
                    cout << "❤️ Agregada a 'Me gusta'.\n";
                }
            } else if (opcion == "ver") {
                cout << "\n📂Lista 'Ver más tarde':\n";
                verMasTarde.mostrar();
                cout << "\n❤️Lista 'Me gusta':\n";
                meGusta.mostrar();
            } else if (opcion == "recomendar") {
                meGusta.recomendarSimilares(peliculas);
            } else if (opcion == "eliminar") {
                cout << "¿De qué lista deseas eliminar? ('ver' para 'Ver más tarde' 👀, 'like' para 'Me gusta'❤️): ";
                string lista;
                cin >> lista;

                if (lista == "ver") {
                    verMasTarde.eliminar();
                    cout << "🗑️ Última película eliminada de 'Ver más tarde'.\n";
                } else if (lista == "like") {
                    meGusta.eliminar();
                    cout << "🗑️ Última película eliminada de 'Me gusta'.\n";
                } else {
                    cout << "Opción inválida😒\n";
                }
            } else if (opcion == "salir") {
                break;
            } else {
                cout << "Opción inválida😒\n";
            }
        }
    }

    return 0;
}