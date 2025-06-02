#ifndef PILA_HPP
#define PILA_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

// TDA para Nodo de Pila
struct NodoPila {
    int dato;
    sf::Color color;
    sf::Vector2f posicion;
    sf::Vector2f posicionDestino;
    bool enMovimiento;
    NodoPila* siguiente;

    NodoPila(int d, sf::Color c, sf::Vector2f pos)
        : dato(d), color(c), posicion(pos), posicionDestino(pos),
          enMovimiento(false), siguiente(nullptr) {}
};

// Clase Modelo para Pila (implementacion propia sin std::stack)
class ModeloPila {
private:
    NodoPila* tope;
    int tamanio;
    int capacidadMaxima;

public:
    ModeloPila(int capacidad = 8);
    ~ModeloPila();

    // Operaciones basicas
    bool push(int valor, sf::Color color, sf::Vector2f posicion);
    NodoPila* pop();
    NodoPila* top() const;
    bool empty() const;
    bool full() const;
    int size() const;

    // Para visualizacion
    NodoPila* obtenerTope() const;

    // Sobrecarga de operadores
    ModeloPila& operator+=(int valor);
    ModeloPila& operator--(); // Para pop

    // Funcion recursiva para mostrar elementos
    void mostrarRecursivo(NodoPila* nodo, int nivel = 0) const;
};

#endif
