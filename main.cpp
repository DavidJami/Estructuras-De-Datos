#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include "Visualizadors.hpp"

int main() {
    // Crear ventana con SFML 3.0.0
    sf::RenderWindow window({800, 600}, "Pila Dinámica Visual", sf::Style::Default);
    window.setFramerateLimit(60);

    // Cargar fuente
    sf::Font fuente;
    if (!fuente.loadFromFile("arial.ttf")) {
        std::cerr << "Error al cargar la fuente." << std::endl;
        return 1;
    }

    // Inicializar visualizador y contador
    VisualizadorPila visualizador;
    int contador = 1;

    // Bucle principal
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Cerrar ventana
            if (event.type == sf::Event::Closed)
                window.close();

            // Detectar teclas presionadas
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::M) {
                    visualizador.agregarNodo("N" + std::to_string(contador++));
                }
                if (event.key.code == sf::Keyboard::P) {
                    visualizador.iniciarAnimacionPop();
                }
                if (event.key.code == sf::Keyboard::T) {
                    visualizador.resaltarTop();
                }
            }
        }

        // Dibujar
        window.clear(sf::Color::White);
        visualizador.actualizarAnimaciones();
        visualizador.dibujar(window, fuente);
        window.display();
    }

    return 0;
}

