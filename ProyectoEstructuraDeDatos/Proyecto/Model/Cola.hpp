#ifndef COLA_HPP
#define COLA_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

struct NodoCola {
    int dato;
    sf::Color color;
    sf::Vector2f posicion;
    NodoCola* siguiente;

    NodoCola(int d, sf::Color c, sf::Vector2f pos)
        : dato(d), color(c), posicion(pos), siguiente(nullptr) {}
};

class ModeloCola {
private:
    NodoCola* frente;
    NodoCola* final;
    int tamanio;
    int capacidadMaxima;

public:
    ModeloCola(int capacidad = 8);
    ~ModeloCola();

    bool enqueue(int valor, sf::Color color, sf::Vector2f posicion);
    NodoCola* dequeue();
    NodoCola* front() const;
    bool empty() const;
    bool full() const;
    int size() const;
    NodoCola* obtenerFrente() const;
    void mostrarRecursivo(NodoCola* nodo, int nivel = 0) const;
};

#endif

