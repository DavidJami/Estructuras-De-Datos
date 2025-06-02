#ifndef COLACONTROLADOR_HPP
#define COLACONTROLADOR_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Model/Cola.hpp"
#include "../View/ColaVista.hpp"

class ColaControlador {
private:
    ModeloCola* cola;
    ColaVista* vista;
    sf::RenderWindow* ventana;
    sf::Clock reloj;
    int semilla;
    bool salir;

public:
    ColaControlador(sf::RenderWindow* window);
    ~ColaControlador();

    void ejecutar();
    void manejarEventosMenu(const sf::Event& evento);
    void manejarEventosCola(const sf::Event& evento);

    void agregarElementoConAnimacion();
    void eliminarElementoConAnimacion();
    void mostrarFrente();
    void verificarVacia();
    void mostrarColaCompleta();

    int generarNumeroAleatorio();
    sf::Color generarColorAleatorio();
};

#endif
