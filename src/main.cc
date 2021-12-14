/*
Autor: Leonardo Alfonso Cruz Rodríguez
Práctica: Sistemas de recomendaciones
Asignatura: Gestión del conocimiento en las Organizaciones
Universidad: ULL
*/

#include <fstream>
#include "../include/valoraciones.h"

void Ayuda(){
    std::cout << "La sintaxis de los argumentos no es correcta\n";
    std::cout << "Ejemplo:\n";
    std::cout << "estval -i input.txt -o output.txt\n\n";
}

void menu(Valoraciones *v){/*
    int opcion = 1;
    int opcion2 = 1;

    do {
        std::cout << "Seleccione una métrica:\n";
        std::cout << "1. Correlación de Pearson\n";
        std::cout << "2. Distancia Coseno\n";
        std::cout << "3. Distancia Euclídea\n";
        std::cin >> opcion;

        std::cout << "Seleccione el tipo de predicción:\n";
        std::cout << "1. Simple\n";
        std::cout << "2. Diferencia con la media\n";
        std::cin >> opcion2;

        switch (opcion2) {
            case 1:
                v->Pred_simple(opcion);
                v->imprimir_matrizf();
                break;
            case 2:
                v->Pred_media(opcion);
                break;
            default:
                std::cout << "Por favor introduzca un numero de los indicados en el menu \n";
                break;
        }
    } while (opcion > 3 || opcion < 1);*/
}

int main (int argc, char *argv[]) {

    // Lectura y carga de datos
    if (argc == 5){
        std::ifstream fentrada;
        fentrada.open(argv[2], std::ios::in);
        if (!fentrada.is_open())
            std::cout << "No se pudo abrir el fichero\n";
        else{
            std::cout << "Fichero abierto correctamente\n\n";
            std::string documento;
            Valoraciones V;
            while (!fentrada.eof()) {
                std::getline(fentrada, documento);
                V.set_documento(documento);
            }
            V.print();      
            menu(&V);
        }
    } else
        Ayuda();
}