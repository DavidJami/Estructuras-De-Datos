#ifndef VISTABASE_HPP
#define VISTABASE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class VistaBase {
protected:
    sf::RenderWindow* ventana;
    sf::Font fuente;

public:
    VistaBase(sf::RenderWindow* window) : ventana(window) {}
    virtual ~VistaBase() = default;

    bool cargarFuente() {
        if (!fuente.openFromFile("C:/Windows/Fonts/arial.ttf")) {
            if (!fuente.openFromFile("C:/Windows/Fonts/calibri.ttf")) {
                if (!fuente.openFromFile("C:/Windows/Fonts/times.ttf")) {
                    std::cout << "Error: No se pudo cargar ninguna fuente" << std::endl;
                    return false;
                }
            }
        }
        return true;
    }

    void limpiarPantalla() { ventana->clear(sf::Color::Black); }
    void mostrarPantalla() { ventana->display(); }

    // Método común para centrar texto (SFML 3.0)
    void centrarTexto(sf::Text& texto, float x, float y, float width, float height) {
        sf::FloatRect textBounds = texto.getLocalBounds();
        float textX = x + width / 2 - textBounds.size.x / 2 - textBounds.position.x;
        float textY = y + height / 2 - textBounds.size.y / 2 - textBounds.position.y;
        texto.setPosition(sf::Vector2f(textX, textY));
    }

    // Fondo común
    void dibujarFondoComun() {
        sf::RectangleShape fondo(sf::Vector2f(1200, 800));  // Ventana más grande
        fondo.setFillColor(sf::Color(25, 30, 45));
        fondo.setPosition(sf::Vector2f(0, 0));
        ventana->draw(fondo);
    }
};

#endif

