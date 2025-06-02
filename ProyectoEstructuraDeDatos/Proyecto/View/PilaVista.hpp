#ifndef PILAVISTA_HPP
#define PILAVISTA_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <locale.h>
#include <cmath>
#include "../Model/Pila.hpp"

enum EstadoMenu {
    MENU_PRINCIPAL,
    GESTION_PILA
};

enum TipoAnimacion {
    SIN_ANIMACION,
    ANIMACION_PUSH,
    ANIMACION_POP
};

struct ElementoAnimado {
    sf::Vector2f posicionActual;
    sf::Vector2f posicionDestino;
    sf::Color color;
    int valor;
    bool activo;
    float progreso;
};

class PilaVista {
private:
    sf::RenderWindow* ventana;
    sf::Font fuente;
    EstadoMenu estadoActual;

    // Parametros visuales (CORREGIDOS para que quepan 8 elementos)
    const float CIRCLE_RADIUS = 35.0f;  // REDUCIDO de 35 a 30
    const float CIRCLE_SPACING = 8.0f;  // REDUCIDO de 8 a 5
    const int BASE_X = 500;
    const int BASE_Y = 600;  // MOVIDO MÁS ABAJO de 550 a 600
    const float VELOCIDAD_ANIMACION = 2.0f;  // MÁS LENTO de 2.0f a 1.0f


    // Sistema de animaciones (ORDEN CORREGIDO)
    float tiempoAnimacion;
    TipoAnimacion tipoAnimacionActual;
    bool animacionEnCurso;
    ElementoAnimado elementoEnAnimacion;
    bool mostrandoTop;
    float tiempoMostrarTop;

public:
    PilaVista(sf::RenderWindow* window);
    bool cargarFuente();

    // Metodos de renderizado
    void mostrarMenuPrincipal();
    void mostrarGestionPila(const ModeloPila& pila);
    void dibujarPila(const ModeloPila& pila);
    void dibujarCirculo(const NodoPila* nodo, int posicion, int totalElementos);  // CORREGIDO: 3 parámetros
    void dibujarElementoAnimado();
    void dibujarTuboContenedor();
    void dibujarPanelInfo(const ModeloPila& pila);
    void dibujarPanelControles();

    // Sistema de animaciones
    void iniciarAnimacionPush(int valor, sf::Color color, const ModeloPila& pila);  // AGREGAR pila
    void iniciarAnimacionPop(int valor, sf::Color color, const ModeloPila& pila);   // AGREGAR pila
    void actualizarAnimaciones(float deltaTime);
    bool hayAnimacionEnCurso() const;
    void terminarAnimacion();

    // Funciones auxiliares de animacion
    sf::Vector2f interpolarPosicion(sf::Vector2f inicio, sf::Vector2f fin, float t);
    float easeInOutQuad(float t);

    // Gestion de estados
    void cambiarEstado(EstadoMenu nuevoEstado);
    EstadoMenu obtenerEstado() const;
    void activarVisualizacionTop();
    void desactivarVisualizacionTop();

    // Utilidades
    void limpiarPantalla();
    void mostrarPantalla();
};

#endif
