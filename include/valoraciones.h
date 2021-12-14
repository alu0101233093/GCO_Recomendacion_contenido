#include <vector>
#include <iostream>
#include <stdio.h>
#include <math.h>

#include "documento.h"

class Valoraciones {
    private:
        std::vector<Documento> valoraciones_;
        int n_docs_; // Número de documentos
        
    public:
        Valoraciones();
        ~Valoraciones();
        void set_documento(std::string);
        int TF(std::string,int);
        float IDF(std::string);
        void TFIDF(int,int);
        int get_n();
        void print();
};