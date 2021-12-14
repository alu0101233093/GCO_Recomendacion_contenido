/*
Autor: Leonardo Alfonso Cruz Rodríguez
Práctica: Sistemas de recomendaciones
Asignatura: Gestión del conocimiento en las Organizaciones
Universidad: ULL
*/

#include "../include/documento.h"

Documento::Documento() :n_words(0) {}

Documento::~Documento() {}

void 
Documento::set_word(std::string cadena){
    for(int i = 0; i < int(keywords_.size()); i++){
        if(cadena == keywords_[i].first){
            keywords_[i].second += 1;
            return;
        }
    }

    std::pair<std::string,int> cr(cadena,1);
    keywords_.push_back(cr);
    n_words++;
}

int 
Documento::get_frec(std::string cadena){
    for(int i = 0; i < int(keywords_.size()); i++){
        if(cadena == keywords_[i].first)
            return keywords_[i].second;
    }
    return 0;
}

std::string 
Documento::get_word(int n){return keywords_[n].first;}

int 
Documento::get_n(){return n_words;}