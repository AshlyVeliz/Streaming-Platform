import { getLikedMovies } from "./movieService";
import { Stack } from "./stack";

// Instancia de la pila para "Ver más tarde"
const watchLaterStack = new Stack<string>();

// Función para mostrar películas que te gustaron
function loadLikedMovies() {
    const likedMoviesContainer = document.getElementById("liked-movies")!;
    likedMoviesContainer.innerHTML = ""; // Limpiar contenido anterior

    const movies = getLikedMovies().slice(0, 5); // Solo las primeras 5
    movies.forEach(movie => {
        const movieElement = document.createElement("div");
        movieElement.classList.add("movie-card");
        movieElement.innerHTML = `
            <div class="movie-title">${movie.title}</div>
            <div class="movie-tags">Tags: ${movie.tags.join(", ")}</div>
            <button class="movie-button" onclick="addToWatchLater('${movie.title}')">Ver más tarde</button>
        `;
        likedMoviesContainer.appendChild(movieElement);
    });
}

// Función para agregar a la pila de "Ver más tarde"
function addToWatchLater(movieTitle: string) {
    watchLaterStack.push(movieTitle);
    loadWatchLaterMovies();
}

// Función para mostrar la pila de "Ver más tarde"
function loadWatchLaterMovies() {
    const watchLaterContainer = document.getElementById("watch-later")!;
    watchLaterContainer.innerHTML = ""; // Limpiar contenido

    const movies = watchLaterStack.getAll();
    movies.forEach(movieTitle => {
        const movieElement = document.createElement("div");
        movieElement.classList.add("movie-card");
        movieElement.innerHTML = `
            <div class="movie-title">${movieTitle}</div>
            <button class="movie-button" onclick="removeFromWatchLater()">Eliminar</button>
        `;
        watchLaterContainer.appendChild(movieElement);
    });
}

// Función para eliminar la última película agregada (LIFO)
function removeFromWatchLater() {
    watchLaterStack.pop();
    loadWatchLaterMovies();
}

// Inicializar la carga de películas
loadLikedMovies();
loadWatchLaterMovies();

// Hacer accesible la función en el HTML
(window as any).addToWatchLater = addToWatchLater;
(window as any).removeFromWatchLater = removeFromWatchLater;
