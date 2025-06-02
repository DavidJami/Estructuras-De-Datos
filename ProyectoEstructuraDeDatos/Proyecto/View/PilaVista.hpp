#ifndef PILAVISTA_HPP
#define PILAVISTA_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <locale.h>
#include <cmath>
#include "../Model/Pila.hpp"
#include "VistaBase.hpp"

enum EstadoMenu {
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

class PilaVista : public VistaBase {
private:
    EstadoMenu estadoActual;
    const float CIRCLE_RADIUS = 40.0f;
    const float CIRCLE_SPACING = 10.0f;
    const int BASE_X = 600;
    const int BASE_Y = 700;
    const float VELOCIDAD_ANIMACION = 2.0f;

    // Sistema de animaciones
    float tiempoAnimacion;
    TipoAnimacion tipoAnimacionActual;
    bool animacionEnCurso;
    ElementoAnimado elementoEnAnimacion;
    bool mostrandoTop;
    float tiempoMostrarTop;

public:
    PilaVista(sf::RenderWindow* window);
    // Metodos de renderizado
    void mostrarGestionPila(const ModeloPila& pila);
    void dibujarPila(const ModeloPila& pila);
    void dibujarCirculo(const NodoPila* nodo, int posicion, int totalElementos);
    void dibujarElementoAnimado();
    void dibujarTuboContenedor();
    void dibujarPanelInfo(const ModeloPila& pila);
    void dibujarPanelControles();

    // Sistema de animaciones
    void iniciarAnimacionPush(int valor, sf::Color color, const ModeloPila& pila);
    void iniciarAnimacionPop(int valor, sf::Color color, const ModeloPila& pila);
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
};

#endif
