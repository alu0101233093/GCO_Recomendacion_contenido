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

int main (int argc, char *argv[]) {

    // Lectura y carga de datos
    if (argc == 5){
        // Comprobar argumentos
        std::string arguments[5];
        for(int i = 0; i < 5; i++)
            arguments[i] = argv[i];
        if((arguments[1] == "-i" || arguments[1] == "-I") & (arguments[3] == "-o" || arguments[3] == "-O")){
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
                V.print(arguments[4]);      
            }
        }
    } else
        Ayuda();
    return 0;
}