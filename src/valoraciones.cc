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
        if(documento[i] == ' '){
            aux.set_word(palabra);
            palabra = "";
        }else if(i == int(documento.size()-1)){
            palabra.push_back(documento[i]);
            aux.set_word(palabra);
            palabra = "";
        }else
            palabra.push_back(documento[i]);
    }
    valoraciones_.push_back(aux);
    n_docs_++;
}

int 
Valoraciones::TF(std::string x, int y){
    return valoraciones_[y].get_frec(x);
}

float 
Valoraciones::IDF(std::string x){ // REVISAR
    int dfx = 0; // número de documentos en N en los que la palabra x aparece
    for(int i = 0; i < int(valoraciones_.size()); i++){
        if(valoraciones_[i].get_frec(x) >= 1)
            dfx++;
    }
    return log(n_docs_/dfx);
}

void 
Valoraciones::TFIDF(int x,int y){
    
}