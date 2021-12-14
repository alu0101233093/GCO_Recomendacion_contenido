/*
Autor: Leonardo Alfonso Cruz Rodríguez
Práctica: Sistemas de recomendaciones
Asignatura: Gestión del conocimiento en las Organizaciones
Universidad: ULL
*/

#include "../include/valoraciones.h"

Valoraciones::Valoraciones() {
    valoraciones_.resize(1);
    n_docs_ = 0;
}

Valoraciones::~Valoraciones() {}

void 
Valoraciones::set_documento(std::string documento){
    std::string palabra;
    Documento aux;
    for(int i = 0; i < int(documento.size()); i++){
        palabra.push_back(documento[i]);
        if(documento[i] == ' ' || i == int(documento.size()-1)){
            aux.set_word(palabra);
            palabra = "";
        }
    }
    valoraciones_.push_back(aux);
    n_docs_++;
}