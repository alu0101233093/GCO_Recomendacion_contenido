#include <vector>
#include <iostream>
#include <stdio.h>
#include <math.h>

#include "documento.h"

class Valoraciones {
    private:
        std::vector<Documento> valoraciones_;
        std::vector<std::string> palabras_;
        int n_docs_; // Número de documentos
        int n_palabras_;
        void set_palabra(std::string);
        
    public:
        Valoraciones();
        ~Valoraciones();
        void set_documento(std::string);
        int TF(std::string,int);
        float IDF(std::string);
        float TFIDF(std::string,int);
        int get_n();
        void print(std::string);
        float coseno(int,int);
};