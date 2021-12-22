/*
Autor: Leonardo Alfonso Cruz Rodríguez
Práctica: Sistemas de recomendaciones
Asignatura: Gestión del conocimiento en las Organizaciones
Universidad: ULL
*/

#include <iomanip>
#include <fstream>
#include <cctype>
#include "../include/valoraciones.h"

Valoraciones::Valoraciones() :valoraciones_(0), diccionario_(0){
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
            palabra.push_back(tolower(documento[i]));
            aux.set_word(palabra);
            set_palabra(palabra);
            palabra = "";
        }else
            palabra.push_back(tolower(documento[i]));
    }
    valoraciones_.push_back(aux);
    n_docs_++;
}

void 
Valoraciones::set_palabra(std::string palabra){
    bool found = false;
    for(int i = 0; i < n_palabras_; i++)
        if(diccionario_[i] == palabra)
            found = true;
    
    if(!found){
        diccionario_.push_back(palabra);
        n_palabras_++;
    }
}

float 
Valoraciones::TF(std::string x, int y){
    return (float(valoraciones_[y].get_frec(x))/float(valoraciones_[y].get_terms()));
}

float 
Valoraciones::IDF(std::string x){
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

float 
Valoraciones::sim_coseno(int x,int y){
    float suma = 0;
    for(int i = 0; i < n_palabras_; i++){
        suma += TFIDF(diccionario_[i],x) * TFIDF(diccionario_[i],y);
    }
    return suma;
}

int Valoraciones::get_n(){return n_docs_;}

void
Valoraciones::print(std::string nombre){
    std::ofstream fsalida;
    std::string output = "output/";
    output = output + nombre;
    fsalida.open(output,std::ios::out);

    for(int i = 0; i < n_docs_; i++){
        fsalida << "Documento " << i << ":" << std::endl;
        fsalida << "Índice\tTérmino\t\t\tTF\tIDF\tTF-IDF" << std::endl;
        for(int j = 0; j < valoraciones_[i].get_diff_terms(); j++){
            std::string palabra = valoraciones_[i].get_word(j);
            int k = 0;
            while(k < n_palabras_ && palabra != diccionario_[k])
                k++;

            fsalida << k << "\t";
            fsalida << palabra;
            // inicio alineación de la tabla
            if(palabra.size() >= 8)
                fsalida << "\t\t";
            else
                fsalida << "\t\t\t";
            // fin alineación de la tabla
            fsalida << std::fixed << std::setprecision(5) << TF(palabra,i) << "\t";
            fsalida << std::fixed << std::setprecision(5) << IDF(palabra) << "\t";
            fsalida << std::fixed << std::setprecision(5) << TFIDF(palabra,i) << "\t";
            fsalida << std::endl;
        }
        fsalida << std::endl << std::endl;
    }

    fsalida << "---------------- Similaridad coseno ----------------" << std::endl;
    std::vector<std::pair<std::pair<int,int>,float>> c;
    std::pair<std::pair<int,int>,float> p;
    int count = 0;
    for(int i = 0; i < n_docs_; i++){
        for(int j = i; j < n_docs_; j++){
            if(i != j){
                p.first.first = i;
                p.first.second = j;
                p.second = sim_coseno(i,j);
                c.push_back(p);
                int k = count;
                while(k > 0 && c[k].second > c[k-1].second){
                    c[k].swap(c[k-1]);
                    k--;
                }
                count++;
            }
        }
    }
    for(int i = 0; i < int(c.size()); i++){
        fsalida << "cos(" << c[i].first.first << "," << c[i].first.second << ") = " << c[i].second << std::endl;
    }
    fsalida.close();
}