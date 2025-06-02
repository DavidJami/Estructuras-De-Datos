#include <SFML/Graphics.hpp>
#include <iostream>
#include "Controller/PilaControlador.hpp"
#include "Controller/ColaControlador.hpp"

void ejecutarListaDoble(sf::RenderWindow& ventana);

void mostrarMenuPrincipal(sf::RenderWindow* ventana, sf::Font& fuente) {
    ventana->clear(sf::Color(25, 30, 45));

    sf::Text titulo(fuente, "GESTOR DE ESTRUCTURAS DE DATOS", 26);
    titulo.setFillColor(sf::Color::White);
    titulo.setPosition(sf::Vector2f(250.f, 120.f));
    titulo.setStyle(sf::Text::Bold);
    ventana->draw(titulo);

    sf::Text opcion1(fuente, "1. Gestion de Pila", 20);
    opcion1.setFillColor(sf::Color(100, 255, 100));
    opcion1.setPosition(sf::Vector2f(360.f, 220.f));
    ventana->draw(opcion1);

    sf::Text opcion2(fuente, "2. Gestion de Cola", 20);
    opcion2.setFillColor(sf::Color(255, 255, 100));
    opcion2.setPosition(sf::Vector2f(360.f, 260.f));
    ventana->draw(opcion2);

    sf::Text opcion3(fuente, "3. Gestion de Lista", 20);
    opcion3.setFillColor(sf::Color(255, 150, 100));
    opcion3.setPosition(sf::Vector2f(360.f, 300.f));
    ventana->draw(opcion3);

    sf::Text opcion4(fuente, "4. Salir", 20);
    opcion4.setFillColor(sf::Color(255, 100, 100));
    opcion4.setPosition(sf::Vector2f(360.f, 340.f));
    ventana->draw(opcion4);

    sf::Text instrucciones(fuente, "Presiona el numero de la opcion", 16);
    instrucciones.setFillColor(sf::Color(150, 150, 150));
    instrucciones.setPosition(sf::Vector2f(360.f, 400.f));
    ventana->draw(instrucciones);

    ventana->display();
}

int main() {
    setlocale(LC_ALL, " ");
    sf::RenderWindow ventana(sf::VideoMode(sf::Vector2u(1200, 800)), "Gestor de Estructuras de Datos");
    sf::Font fuente;
    if (!fuente.openFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cerr << "No se pudo cargar la fuente Arial." << std::endl;
        return 1;
    }

    while (ventana.isOpen()) {
        mostrarMenuPrincipal(&ventana, fuente);
        bool opcionSeleccionada = false;

        while (!opcionSeleccionada && ventana.isOpen()) {
            auto eventOpt = ventana.pollEvent();
            if (!eventOpt.has_value()) {
                sf::sleep(sf::milliseconds(10));
                continue;
            }
            sf::Event event = eventOpt.value();

            if (event.is<sf::Event::Closed>()) {
                ventana.close();
            }
            else if (event.is<sf::Event::KeyPressed>()) {
                if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
                    switch (keyPressed->code) {
                        case sf::Keyboard::Key::Num1:
                            {
                                PilaControlador controladorPila(&ventana);
                                controladorPila.ejecutar();
                                opcionSeleccionada = true;
                            }
                            break;
                        case sf::Keyboard::Key::Num2:
                            {
                                ColaControlador controladorCola(&ventana);
                                controladorCola.ejecutar();
                                opcionSeleccionada = true;
                            }
                            break;
                        case sf::Keyboard::Key::Num3:
                            {
                                ejecutarListaDoble(ventana);
                                opcionSeleccionada = true;
                            }
                            break;
                        case sf::Keyboard::Key::Num4:
                        case sf::Keyboard::Key::Escape:
                            ventana.close();
                            opcionSeleccionada = true;
                            break;
                        default:
                            break;
                    }
                }
            }
        }
        while (ventana.pollEvent().has_value()) {}
    }
    return 0;
}
