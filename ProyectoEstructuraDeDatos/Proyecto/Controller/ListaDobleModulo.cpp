#include "../Model/ListaDoble.hpp"
#include "../View/ListaDobleVisual.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

void ejecutarListaDoble(sf::RenderWindow& window) {
    sf::Font fuente;
    if (!fuente.openFromFile("C:/Windows/Fonts/consola.ttf")) {
        std::cerr << "No se pudo cargar la fuente.\n";
        return;
    }

    ListaDoble<std::string> lista;
    std::string entradaUsuario = "";
    bool esperandoTexto = false;
    int modo = 0;

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (esperandoTexto) {
                if (auto te = event->getIf<sf::Event::TextEntered>()) {
                    char c = static_cast<char>(te->unicode);
                    if (c == '\b' && !entradaUsuario.empty()) {
                        entradaUsuario.pop_back();
                    } else if (c == '\r') {
                        if (!entradaUsuario.empty()) {
                            std::string dato = entradaUsuario;
                            if (modo == 1) {
                                lista.insertar(dato);
                                int pos = 0;
                                auto nodo = lista.getCabeza();
                                while (nodo && nodo->dato < dato) {
                                    pos++;
                                    nodo = nodo->siguiente;
                                }
                                animarInsercion(window, fuente, dato, pos);
                            } else if (modo == 2) {
                                if (lista.eliminar(dato)) {
                                    eliminarVisual(window, fuente, dato);
                                }
                            }
                        }
                        entradaUsuario = "";
                        esperandoTexto = false;
                        modo = 0;
                    } else if (isprint(c)) {
                        entradaUsuario += c;
                    }
                }
            }

            if (!esperandoTexto) {
                if (auto keyEvent = event->getIf<sf::Event::KeyPressed>()) {
                    auto key = keyEvent->code;

                    if (key == sf::Keyboard::Key::I) {
                        esperandoTexto = true;
                        modo = 1;
                        entradaUsuario = "";
                    } else if (key == sf::Keyboard::Key::E) {
                        esperandoTexto = true;
                        modo = 2;
                        entradaUsuario = "";
                    } else if (key == sf::Keyboard::Key::Escape) {
                        return; // salir y volver al menú
                    }
                }
            }
        }

        window.clear(sf::Color::Black);

        sf::Text instrucciones(fuente, "[I] Insertar   [E] Eliminar   [ESC] Volver", 20);
        instrucciones.setFillColor(sf::Color::White);
        instrucciones.setPosition(sf::Vector2f(50, 20));
        window.draw(instrucciones);

        if (esperandoTexto) {
            std::string etiqueta = (modo == 1) ? "Insertar: " : "Eliminar: ";
            sf::Text entrada(fuente, etiqueta + entradaUsuario, 20);
            entrada.setFillColor(sf::Color::Yellow);
            entrada.setPosition(sf::Vector2f(50, 60));
            window.draw(entrada);
        }

        dibujarLista(window, fuente);
        window.display();
    }
}
