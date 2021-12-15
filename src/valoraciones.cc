/*
Autor: Leonardo Alfonso Cruz Rodríguez
Práctica: Sistemas de recomendaciones
Asignatura: Gestión del conocimiento en las Organizaciones
Universidad: ULL
*/

#include <iomanip>
#include "../include/valoraciones.h"

Valoraciones::Valoraciones() :valoraciones_(0), palabras_(0){
    n_docs_ = 0;
    n_palabras_ = 0;
}

Valoraciones::~Valoraciones() {}

void 
Valoraciones::set_documento(std::string documento){
    std::string palabra;
    Documento aux;
    for(int i = 0; i < int(documento.size()); i++){
        if(documento[i] == ' ' || documento[i] == '.' || documento[i] == ','){
            if(palabra != ""){
                aux.set_word(palabra);
                set_palabra(palabra);
                palabra = "";
            }
        }else if(i == int(documento.size()-1)){
            palabra.push_back(documento[i]);
            aux.set_word(palabra);
            set_palabra(palabra);
            palabra = "";
        }else
            palabra.push_back(documento[i]);
    }
    valoraciones_.push_back(aux);
    n_docs_++;
}

void 
Valoraciones::set_palabra(std::string palabra){
    bool found = false;
    for(int i = 0; i < n_palabras_; i++)
        if(palabras_[i] == palabra)
            found = true;
    
    if(!found){
        palabras_.push_back(palabra);
        n_palabras_++;
    }
}

int 
Valoraciones::TF(std::string x, int y){
    return valoraciones_[y].get_frec(x);
}

float 
Valoraciones::IDF(std::string x){ // REVISAR
    float dfx = 0; // número de documentos en N en los que la palabra x aparece
    for(int i = 0; i < int(valoraciones_.size()); i++){
        if(valoraciones_[i].get_frec(x) >= 1)
            dfx++;
    }
    return log10(n_docs_/dfx);
}

float  
Valoraciones::TFIDF(std::string x,int y){
    return TF(x,y)*IDF(x);
}

int Valoraciones::get_n(){return n_docs_;}

void
Valoraciones::print(){

    for(int i = 0; i < n_docs_; i++){
        std::cout << "Documento " << i << ":" << std::endl;
        std::cout << "Índice\tTérmino\t\tTF\tIDF\tTF-IDF" << std::endl;
        for(int j = 0; j < n_palabras_; j++){
            std::string palabra = palabras_[j];
            std::cout << j << "\t";
            std::cout << palabra;
            // inicio alineación de la tabla
            if(palabras_[j].size() >= 8)
                std::cout << "\t";
            else
                std::cout << "\t\t";
            // fin alineación de la tabla
            std::cout << TF(palabra,i) << "\t";
            std::cout << std::fixed << std::setprecision(5) << IDF(palabra) << "\t";
            std::cout << std::fixed << std::setprecision(5) << TFIDF(palabra,i) << "\t";
            std::cout << std::endl;
        }
        std::cout << std::endl << std::endl;
    }
}