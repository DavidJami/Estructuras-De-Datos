#ifndef VISUALIZADORS_HPP
#define VISUALIZADORS_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

struct NodoVisual {
    std::string texto;
    float yObjetivo;
    float x, y;
    bool entrando = false;
    bool saliendo = false;
    bool resaltado = false;
    sf::CircleShape circulo;
};

class VisualizadorPila {
private:
    std::vector<NodoVisual> elementos;
    const float radio = 30.0f;
    const float espacio = 10.0f;
    const float origenX = 300.0f;
    const float baseY = 500.0f;
    const float velocidad = 5.0f;

public:
    void agregarNodo(const std::string& texto) {
        float yFinal = baseY - elementos.size() * (2 * radio + espacio);
        float yInicial = 600;

        sf::CircleShape circulo(radio);
        circulo.setFillColor(sf::Color::Cyan);
        circulo.setPosition(sf::Vector2f(origenX, yInicial));

        NodoVisual nodo;
        nodo.texto = texto;
        nodo.yObjetivo = yFinal;
        nodo.x = origenX;
        nodo.y = yInicial;
        nodo.entrando = true;
        nodo.saliendo = false;
        nodo.resaltado = false;
        nodo.circulo = circulo;

        elementos.push_back(nodo);
    }

    void iniciarAnimacionPop() {
        if (!elementos.empty()) {
            elementos.back().saliendo = true;
        }
    }

    void actualizarAnimaciones() {
        if (!elementos.empty()) {
            NodoVisual& nodo = elementos.back();

            if (nodo.entrando) {
                nodo.y -= velocidad;
                if (nodo.y <= nodo.yObjetivo) {
                    nodo.y = nodo.yObjetivo;
                    nodo.entrando = false;
                }
                nodo.circulo.setPosition(sf::Vector2f(nodo.x, nodo.y));
            }
            else if (nodo.saliendo) {
                nodo.x += velocidad;
                nodo.circulo.setPosition(sf::Vector2f(nodo.x, nodo.y));
                if (nodo.x > 800) {
                    elementos.pop_back();
                }
            }
        }

        for (auto& nodo : elementos) {
            if (nodo.resaltado && !nodo.entrando && !nodo.saliendo) {
                nodo.circulo.setOutlineThickness(4);
                nodo.circulo.setOutlineColor(sf::Color::Red);
                nodo.resaltado = false;
            } else {
                nodo.circulo.setOutlineThickness(0);
            }
        }
    }

    void dibujar(sf::RenderWindow& window, sf::Font& fuente) {
        for (const auto& nodo : elementos) {
            window.draw(nodo.circulo);

            sf::Text texto(nodo.texto, fuente, 20);
            texto.setFillColor(sf::Color::Black);
            texto.setPosition(sf::Vector2f(nodo.circulo.getPosition().x + 5, nodo.circulo.getPosition().y + 8));

            window.draw(texto);
        }
    }

    void resaltarTop() {
        if (!elementos.empty()) {
            elementos.back().resaltado = true;
        }
    }
};

#endif
