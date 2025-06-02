#include "PilaVista.hpp"

PilaVista::PilaVista(sf::RenderWindow* window) : VistaBase(window), estadoActual(GESTION_PILA),
                                        tiempoAnimacion(0.0f), tipoAnimacionActual(SIN_ANIMACION),
                                        animacionEnCurso(false), elementoEnAnimacion(),
                                        mostrandoTop(false), tiempoMostrarTop(0.0f) {
    elementoEnAnimacion.activo = false;
}

void PilaVista::mostrarGestionPila(const ModeloPila& pila) {
    limpiarPantalla();

    // Fondo
    sf::RectangleShape fondo(sf::Vector2f(1000, 700));
    fondo.setFillColor(sf::Color(25, 30, 45));
    fondo.setPosition(sf::Vector2f(0, 0));
    ventana->draw(fondo);

    // Titulo compacto
    sf::Text titulo(fuente, "PILA (LIFO) - SIMULACION REALISTA", 22);
    titulo.setFillColor(sf::Color::White);
    titulo.setPosition(sf::Vector2f(280, 15));
    titulo.setStyle(sf::Text::Bold);

    dibujarTuboContenedor();
    dibujarPanelInfo(pila);
    dibujarPanelControles();
    dibujarPila(pila);

    // Dibujar elemento en animacion si existe
    if (animacionEnCurso && elementoEnAnimacion.activo) {
        dibujarElementoAnimado();
    }

    mostrarPantalla();
}

void PilaVista::dibujarTuboContenedor() {
    // Dibujar el "tubo" contenedor con base ABAJO
    sf::RectangleShape paredIzquierda(sf::Vector2f(8, 400));
    paredIzquierda.setFillColor(sf::Color(100, 100, 100));
    paredIzquierda.setPosition(sf::Vector2f(BASE_X - CIRCLE_RADIUS - 15, BASE_Y - 400));

    sf::RectangleShape paredDerecha(sf::Vector2f(8, 400));
    paredDerecha.setFillColor(sf::Color(100, 100, 100));
    paredDerecha.setPosition(sf::Vector2f(BASE_X + CIRCLE_RADIUS + 7, BASE_Y - 400));

    // BASE DEL TUBO (ABAJO)
    sf::RectangleShape base(sf::Vector2f(CIRCLE_RADIUS * 2.5f, 12));
    base.setFillColor(sf::Color::White);
    base.setOutlineThickness(2);
    base.setOutlineColor(sf::Color(200, 200, 200));
    base.setPosition(sf::Vector2f(BASE_X - CIRCLE_RADIUS * 1.25f, BASE_Y));

    // Entrada del tubo (arriba)
    sf::RectangleShape entrada(sf::Vector2f(CIRCLE_RADIUS * 2.2f, 8));
    entrada.setFillColor(sf::Color(150, 150, 150));
    entrada.setPosition(sf::Vector2f(BASE_X - CIRCLE_RADIUS * 1.1f, BASE_Y - 405));

    ventana->draw(paredIzquierda);
    ventana->draw(paredDerecha);
    ventana->draw(base);
    ventana->draw(entrada);

    // Etiquetas
    sf::Text baseText(fuente, "BASE DEL TUBO", 12);
    baseText.setFillColor(sf::Color::White);
    baseText.setPosition(sf::Vector2f(BASE_X - 50, BASE_Y + 20));
    baseText.setStyle(sf::Text::Bold);
    ventana->draw(baseText);

    sf::Text entradaText(fuente, "ENTRADA", 10);
    entradaText.setFillColor(sf::Color::Yellow);
    entradaText.setPosition(sf::Vector2f(BASE_X - 30, BASE_Y - 425));
    ventana->draw(entradaText);
}

void PilaVista::dibujarPila(const ModeloPila& pila) {
    if (!animacionEnCurso) {
        NodoPila* actual = pila.obtenerTope();
        int posicion = 0;
        int totalElementos = pila.size();

        while (actual != nullptr) {
            dibujarCirculo(actual, posicion, totalElementos);
            actual = actual->siguiente;
            posicion++;
        }
    } else {
        if (tipoAnimacionActual == ANIMACION_PUSH) {
            NodoPila* actual = pila.obtenerTope();
            if (actual && actual->siguiente) {
                actual = actual->siguiente;
                int posicion = 1;
                int totalElementos = pila.size();
                while (actual != nullptr) {
                    dibujarCirculo(actual, posicion, totalElementos);
                    actual = actual->siguiente;
                    posicion++;
                }
            }
        } else if (tipoAnimacionActual == ANIMACION_POP) {
            NodoPila* actual = pila.obtenerTope();
            int posicion = 0;
            int totalElementos = pila.size();
            while (actual != nullptr) {
                dibujarCirculo(actual, posicion, totalElementos);
                actual = actual->siguiente;
                posicion++;
            }
        }
    }

    // Mensaje si esta vacia
    if (pila.empty() && !animacionEnCurso) {
        sf::Text vacia(fuente, "TUBO VACIO", 20);
        vacia.setFillColor(sf::Color::Red);
        vacia.setPosition(sf::Vector2f(BASE_X - 60, BASE_Y + 80));  // MOVIDO HACIA ABAJO
        vacia.setStyle(sf::Text::Bold);
        ventana->draw(vacia);

        sf::Text instruccion(fuente, "El primer elemento ira a la BASE", 12);
        instruccion.setFillColor(sf::Color::White);
        instruccion.setPosition(sf::Vector2f(BASE_X - 120, BASE_Y + 110));  // MOVIDO HACIA ABAJO
        ventana->draw(instruccion);

        sf::Text instruccion2(fuente, "Los siguientes se apilaran ENCIMA", 12);
        instruccion2.setFillColor(sf::Color::White);
        instruccion2.setPosition(sf::Vector2f(BASE_X - 130, BASE_Y + 130));  // MOVIDO HACIA ABAJO
        ventana->draw(instruccion2);
    }
}

void PilaVista::dibujarCirculo(const NodoPila* nodo, int posicion, int totalElementos) {
    // Crear circulo
    sf::CircleShape circle(CIRCLE_RADIUS);
    circle.setFillColor(nodo->color);
    circle.setOutlineThickness(3);

    // Efecto especial para el TOP
    if (posicion == 0) {
        if (mostrandoTop) {
            circle.setOutlineColor(sf::Color::Magenta);
            circle.setOutlineThickness(6);
            float pulso = std::sin(tiempoMostrarTop * 8.0f) * 0.15f + 1.0f;
            circle.setScale(sf::Vector2f(pulso, pulso));
        } else {
            circle.setOutlineColor(sf::Color::Yellow);
            float pulso = std::sin(tiempoAnimacion * 4.0f) * 0.05f + 1.0f;
            circle.setScale(sf::Vector2f(pulso, pulso));
        }
    } else {
        circle.setOutlineColor(sf::Color::White);
    }

    // CORRECTO: Apilar desde la BASE hacia ARRIBA
    float circleX = BASE_X - CIRCLE_RADIUS;
    int nivelDesdeBase = totalElementos - 1 - posicion;
    float circleY = BASE_Y - CIRCLE_RADIUS * 2 - (nivelDesdeBase * (CIRCLE_RADIUS * 2 + CIRCLE_SPACING));

    circle.setPosition(sf::Vector2f(circleX, circleY));

    // Texto del valor
    sf::Text valorTexto(fuente, std::to_string(nodo->dato), 16);
    valorTexto.setFillColor(sf::Color::Black);
    valorTexto.setStyle(sf::Text::Bold);

    // Centrar texto
    sf::FloatRect textBounds = valorTexto.getLocalBounds();
    float textX = BASE_X - textBounds.size.x / 2;
    float textY = circleY + CIRCLE_RADIUS - textBounds.size.y / 2;
    valorTexto.setPosition(sf::Vector2f(textX, textY));

    // Indicador TOP (elemento en posicion 0)
    if (posicion == 0) {
        sf::Text topIndicator(fuente, "<-- TOP", 14);
        if (mostrandoTop) {
            topIndicator.setFillColor(sf::Color::Magenta);
            topIndicator.setString("<-- TOP (CONSULTANDO)");
        } else {
            topIndicator.setFillColor(sf::Color::Red);
        }
        topIndicator.setStyle(sf::Text::Bold);
        topIndicator.setPosition(sf::Vector2f(
            BASE_X + CIRCLE_RADIUS + 15,
            circleY + CIRCLE_RADIUS - 8
        ));
        ventana->draw(topIndicator);

        if (mostrandoTop) {
            sf::Text consultaMsg(fuente, "Valor: " + std::to_string(nodo->dato) + " (sin quitar)", 12);
            consultaMsg.setFillColor(sf::Color::Magenta);
            consultaMsg.setPosition(sf::Vector2f(
                BASE_X + CIRCLE_RADIUS + 15,
                circleY + CIRCLE_RADIUS + 15
            ));
            ventana->draw(consultaMsg);
        }
    }

    // Indicador BASE (elemento en el fondo)
    if (posicion == totalElementos - 1) {
        sf::Text baseIndicator(fuente, "<-- BASE", 12);
        baseIndicator.setFillColor(sf::Color::Green);
        baseIndicator.setPosition(sf::Vector2f(
            BASE_X + CIRCLE_RADIUS + 15,
            circleY + CIRCLE_RADIUS + 20
        ));
        ventana->draw(baseIndicator);
    }

    // Etiqueta de nivel desde la base
    sf::Text nivelLabel(fuente, "N" + std::to_string(nivelDesdeBase + 1), 10);
    nivelLabel.setFillColor(sf::Color::Cyan);
    nivelLabel.setPosition(sf::Vector2f(circleX - 30, circleY + CIRCLE_RADIUS - 5));
    ventana->draw(nivelLabel);

    ventana->draw(circle);
    ventana->draw(valorTexto);
}

void PilaVista::dibujarElementoAnimado() {
    if (!elementoEnAnimacion.activo) return;

    // Crear circulo animado
    sf::CircleShape circle(CIRCLE_RADIUS);
    circle.setFillColor(elementoEnAnimacion.color);
    circle.setOutlineThickness(4);
    circle.setOutlineColor(sf::Color::Yellow);

    // Efecto de brillo durante animacion
    float brillo = std::sin(tiempoAnimacion * 10.0f) * 0.1f + 1.0f;
    circle.setScale(sf::Vector2f(brillo, brillo));

    circle.setPosition(elementoEnAnimacion.posicionActual);

    // Texto del valor
    sf::Text valorTexto(fuente, std::to_string(elementoEnAnimacion.valor), 16);
    valorTexto.setFillColor(sf::Color::Black);
    valorTexto.setStyle(sf::Text::Bold);

    sf::FloatRect textBounds = valorTexto.getLocalBounds();
    valorTexto.setPosition(sf::Vector2f(
        elementoEnAnimacion.posicionActual.x + CIRCLE_RADIUS - textBounds.size.x / 2,
        elementoEnAnimacion.posicionActual.y + CIRCLE_RADIUS - textBounds.size.y / 2
    ));

    ventana->draw(circle);
    ventana->draw(valorTexto);

    // Efecto de particulas durante el movimiento
    if (tipoAnimacionActual == ANIMACION_PUSH) {
        sf::Text efecto(fuente, "v", 20);
        efecto.setFillColor(sf::Color::Yellow);
        efecto.setPosition(sf::Vector2f(
            elementoEnAnimacion.posicionActual.x - 30,
            elementoEnAnimacion.posicionActual.y + CIRCLE_RADIUS
        ));
        ventana->draw(efecto);
    } else if (tipoAnimacionActual == ANIMACION_POP) {
        sf::Text efecto(fuente, "^", 20);  // Flecha hacia arriba
        efecto.setFillColor(sf::Color::Red);
        efecto.setPosition(sf::Vector2f(
            elementoEnAnimacion.posicionActual.x + CIRCLE_RADIUS * 2 + 10,
            elementoEnAnimacion.posicionActual.y + CIRCLE_RADIUS
        ));
        ventana->draw(efecto);
    }
}

void PilaVista::iniciarAnimacionPush(int valor, sf::Color color, const ModeloPila& pila) {
    tipoAnimacionActual = ANIMACION_PUSH;
    animacionEnCurso = true;
    tiempoAnimacion = 0.0f;

    elementoEnAnimacion.valor = valor;
    elementoEnAnimacion.color = color;
    elementoEnAnimacion.activo = true;
    elementoEnAnimacion.progreso = 0.0f;

    // Posicion inicial: arriba del tubo (entrada)
    elementoEnAnimacion.posicionActual = sf::Vector2f(BASE_X - CIRCLE_RADIUS, BASE_Y - 450);

    // Posicion destino: TOP de la pila (arriba de todos los elementos)
    int totalElementos = pila.size();
    int nivelDesdeBase = totalElementos - 1;
    float destinoY = BASE_Y - CIRCLE_RADIUS * 2 - (nivelDesdeBase * (CIRCLE_RADIUS * 2 + CIRCLE_SPACING));
    elementoEnAnimacion.posicionDestino = sf::Vector2f(BASE_X - CIRCLE_RADIUS, destinoY);
}

void PilaVista::iniciarAnimacionPop(int valor, sf::Color color, const ModeloPila& pila) {
    tipoAnimacionActual = ANIMACION_POP;
    animacionEnCurso = true;
    tiempoAnimacion = 0.0f;

    elementoEnAnimacion.valor = valor;
    elementoEnAnimacion.color = color;
    elementoEnAnimacion.activo = true;
    elementoEnAnimacion.progreso = 0.0f;

    // Posicion inicial: donde está el TOP actualmente
    int totalElementos = pila.size();
    int nivelDesdeBase = totalElementos;
    float inicioY = BASE_Y - CIRCLE_RADIUS * 2 - (nivelDesdeBase * (CIRCLE_RADIUS * 2 + CIRCLE_SPACING));
    elementoEnAnimacion.posicionActual = sf::Vector2f(BASE_X - CIRCLE_RADIUS, inicioY);

    // Posicion destino: fuera del tubo (arriba)
    elementoEnAnimacion.posicionDestino = sf::Vector2f(BASE_X - CIRCLE_RADIUS, BASE_Y - 450);
}

void PilaVista::actualizarAnimaciones(float deltaTime) {
    tiempoAnimacion += deltaTime;

    if (mostrandoTop) {
        tiempoMostrarTop += deltaTime;
        if (tiempoMostrarTop >= 2.0f) {
            desactivarVisualizacionTop();
        }
    }

    if (animacionEnCurso && elementoEnAnimacion.activo) {
        float velocidadActual = VELOCIDAD_ANIMACION;
        elementoEnAnimacion.progreso += deltaTime * velocidadActual;

        if (elementoEnAnimacion.progreso >= 1.0f) {
            elementoEnAnimacion.progreso = 1.0f;
            terminarAnimacion();
        }

        float t = easeInOutQuad(elementoEnAnimacion.progreso);
        elementoEnAnimacion.posicionActual = interpolarPosicion(
            elementoEnAnimacion.posicionActual,
            elementoEnAnimacion.posicionDestino,
            t * deltaTime * 3.0f
        );
    }
}

sf::Vector2f PilaVista::interpolarPosicion(sf::Vector2f inicio, sf::Vector2f fin, float t) {
    return sf::Vector2f(
        inicio.x + (fin.x - inicio.x) * t,
        inicio.y + (fin.y - inicio.y) * t
    );
}

float PilaVista::easeInOutQuad(float t) {
    return t < 0.5f ? 2.0f * t * t : -1.0f + (4.0f - 2.0f * t) * t;
}

bool PilaVista::hayAnimacionEnCurso() const {
    return animacionEnCurso;
}

void PilaVista::terminarAnimacion() {
    animacionEnCurso = false;
    elementoEnAnimacion.activo = false;
    tipoAnimacionActual = SIN_ANIMACION;
}

void PilaVista::dibujarPanelInfo(const ModeloPila& pila) {

    sf::RectangleShape panelInfo(sf::Vector2f(200, 160));
    panelInfo.setFillColor(sf::Color(35, 40, 55));
    panelInfo.setOutlineThickness(2);
    panelInfo.setOutlineColor(sf::Color(70, 130, 180));
    panelInfo.setPosition(sf::Vector2f(15, 50));

    sf::Text tituloInfo(fuente, "INFORMACION DE LA PILA", 12);
    tituloInfo.setFillColor(sf::Color::White);
    tituloInfo.setPosition(sf::Vector2f(25, 60));
    tituloInfo.setStyle(sf::Text::Bold);

    sf::Text elementos(fuente, "Elementos: " + std::to_string(pila.size()) + "/8", 11);
    elementos.setFillColor(sf::Color(100, 200, 255));
    elementos.setPosition(sf::Vector2f(25, 85));

    sf::Text topInfo(fuente, "", 11);
    topInfo.setFillColor(sf::Color(100, 255, 100));
    topInfo.setPosition(sf::Vector2f(25, 105));

    if (!pila.empty()) {
        topInfo.setString("TOP: " + std::to_string(pila.top()->dato));
    } else {
        topInfo.setString("TOP: Vacia");
    }

    sf::Text estado(fuente, "", 11);
    estado.setPosition(sf::Vector2f(25, 125));

    if (pila.empty()) {
        estado.setString("Estado: VACIA");
        estado.setFillColor(sf::Color::Red);
    } else if (pila.full()) {
        estado.setString("Estado: LLENA");
        estado.setFillColor(sf::Color::Red);
    } else {
        estado.setString("Estado: NORMAL");
        estado.setFillColor(sf::Color::Green);
    }

    sf::Text empty(fuente, "", 11);
    empty.setPosition(sf::Vector2f(25, 145));
    if (pila.empty()) {
        empty.setString("Empty(): true");
        empty.setFillColor(sf::Color::Yellow);
    } else {
        empty.setString("Empty(): false");
        empty.setFillColor(sf::Color::Cyan);
    }

    // Barra de capacidad
    sf::RectangleShape barraFondo(sf::Vector2f(150, 10));
    barraFondo.setFillColor(sf::Color(40, 40, 40));
    barraFondo.setOutlineThickness(1);
    barraFondo.setOutlineColor(sf::Color::White);
    barraFondo.setPosition(sf::Vector2f(25, 165));

    sf::RectangleShape barraLleno(sf::Vector2f((150.0f * pila.size()) / 8.0f, 10));
    sf::Color colorBarra = pila.size() < 6 ? sf::Color::Green :
                          pila.size() < 8 ? sf::Color::Yellow : sf::Color::Red;
    barraLleno.setFillColor(colorBarra);
    barraLleno.setPosition(sf::Vector2f(25, 165));

    ventana->draw(panelInfo);
    ventana->draw(tituloInfo);
    ventana->draw(elementos);
    ventana->draw(topInfo);
    ventana->draw(estado);
    ventana->draw(empty);
    ventana->draw(barraFondo);
    ventana->draw(barraLleno);
}

void PilaVista::dibujarPanelControles() {
    sf::RectangleShape panelControles(sf::Vector2f(200, 180));
    panelControles.setFillColor(sf::Color(35, 40, 55));
    panelControles.setOutlineThickness(2);
    panelControles.setOutlineColor(sf::Color(255, 150, 100));
    panelControles.setPosition(sf::Vector2f(15, 230));

    sf::Text tituloControles(fuente, "CONTROLES", 12);
    tituloControles.setFillColor(sf::Color::White);
    tituloControles.setPosition(sf::Vector2f(25, 240));
    tituloControles.setStyle(sf::Text::Bold);

    sf::Text pushControl(fuente, "ENTER: Push (Insertar pelota)", 10);
    pushControl.setFillColor(sf::Color(100, 255, 100));
    pushControl.setPosition(sf::Vector2f(25, 265));

    sf::Text popControl(fuente, "SPACE: Pop (Sacar pelota)", 10);
    popControl.setFillColor(sf::Color(255, 100, 100));
    popControl.setPosition(sf::Vector2f(25, 285));

    sf::Text topControl(fuente, "T: Top (Ver pelota superior)", 10);
    topControl.setFillColor(sf::Color(100, 100, 255));
    topControl.setPosition(sf::Vector2f(25, 305));

    sf::Text emptyControl(fuente, "E: Empty (Verificar vacio)", 10);
    emptyControl.setFillColor(sf::Color(255, 255, 100));
    emptyControl.setPosition(sf::Vector2f(25, 325));

    sf::Text mostrarControl(fuente, "M: Mostrar recursivo", 10);
    mostrarControl.setFillColor(sf::Color(255, 150, 255));
    mostrarControl.setPosition(sf::Vector2f(25, 345));

    sf::RectangleShape separador(sf::Vector2f(150, 1));
    separador.setFillColor(sf::Color(100, 100, 100));
    separador.setPosition(sf::Vector2f(25, 365));

    sf::Text volverControl(fuente, "ESC: Volver al menu", 10);
    volverControl.setFillColor(sf::Color(200, 200, 200));
    volverControl.setPosition(sf::Vector2f(25, 375));


    ventana->draw(panelControles);
    ventana->draw(tituloControles);
    ventana->draw(pushControl);
    ventana->draw(popControl);
    ventana->draw(topControl);
    ventana->draw(emptyControl);
    ventana->draw(mostrarControl);
    ventana->draw(separador);
    ventana->draw(volverControl);
}

void PilaVista::activarVisualizacionTop() {
    mostrandoTop = true;
    tiempoMostrarTop = 0.0f;
}

void PilaVista::desactivarVisualizacionTop() {
    mostrandoTop = false;
}

void PilaVista::cambiarEstado(EstadoMenu nuevoEstado) {
    estadoActual = nuevoEstado;
}

EstadoMenu PilaVista::obtenerEstado() const {
    return estadoActual;
}

