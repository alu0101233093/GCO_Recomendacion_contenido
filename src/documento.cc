/*
Autor: Leonardo Alfonso Cruz Rodríguez
Práctica: Sistemas de recomendaciones
Asignatura: Gestión del conocimiento en las Organizaciones
Universidad: ULL
*/

#include "../include/documento.h"

Documento::Documento() :n_terms_(0) {}

Documento::~Documento() {}

void 
Documento::set_word(std::string cadena){
    n_terms_++;
    for(int i = 0; i < int(terminos_.size()); i++){
        if(cadena == terminos_[i].first){
            terminos_[i].second += 1;
            return;
        }
    }

    std::pair<std::string,int> cr(cadena,1);
    terminos_.push_back(cr);
}

int 
Documento::get_frec(std::string cadena){
    for(int i = 0; i < int(terminos_.size()); i++){
        if(cadena == terminos_[i].first)
            return terminos_[i].second;
    }
    return 0;
}

std::string 
Documento::get_word(int n){return terminos_[n].first;}

int 
Documento::get_terms(){return n_terms_;}