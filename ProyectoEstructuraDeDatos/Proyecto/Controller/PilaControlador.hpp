#ifndef PILACONTROLADOR_HPP
#define PILACONTROLADOR_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Model/Pila.hpp"
#include "../View/PilaVista.hpp"

class PilaControlador {
private:
    ModeloPila* pila;
    PilaVista* vista;
    sf::RenderWindow* ventana;
    sf::Clock reloj;

    // Generador de numeros aleatorios simple
    int semilla;

public:
    PilaControlador(sf::RenderWindow* window);
    ~PilaControlador();

    void ejecutar();
    void manejarEventosMenu(const sf::Event& evento);
    void manejarEventosPila(const sf::Event& evento);

    // Operaciones de pila
    void agregarElemento();
    void eliminarElemento();
    void agregarElementoConAnimacion();  // <-- AGREGAR ESTA LÍNEA
    void eliminarElementoConAnimacion(); // <-- AGREGAR ESTA LÍNEA
    void mostrarTope();
    void verificarVacia();
    void mostrarPilaCompleta();

    // Utilidades
    int generarNumeroAleatorio();
    sf::Color generarColorAleatorio();
};

#endif
