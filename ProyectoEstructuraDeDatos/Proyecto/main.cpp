#include <SFML/Graphics.hpp>
#include <iostream>
#include <locale.h>
#include "Controller/PilaControlador.hpp"

int main() {
    using namespace std;
    setlocale(LC_ALL, " ");

    sf::RenderWindow ventana(sf::VideoMode(sf::Vector2u(1000, 700)),
                            "Gestor de Pilas - Arquitectura MVC");

    cout << "Iniciando Gestor de Pilas con soporte para español" << endl;

    PilaControlador controlador(&ventana);
    controlador.ejecutar();

    cout << "Programa terminado. ¡Gracias por usar el gestor!" << endl;
    return 0;
}
