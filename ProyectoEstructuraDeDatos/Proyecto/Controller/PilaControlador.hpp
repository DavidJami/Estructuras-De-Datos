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
    int semilla;
    bool salir;

public:
    PilaControlador(sf::RenderWindow* window);
    ~PilaControlador();

    void ejecutar();
    void manejarEventosPila(const sf::Event& evento);

    void agregarElementoConAnimacion();
    void eliminarElementoConAnimacion();
    void agregarElemento();
    void eliminarElemento();
    void mostrarTope();
    void verificarVacia();
    void mostrarPilaCompleta();

    int generarNumeroAleatorio();
    sf::Color generarColorAleatorio();
};

#endif
