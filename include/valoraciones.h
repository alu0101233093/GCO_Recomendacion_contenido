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
        void TF(int,int);
        void IDF(int);
        void TFIDF(int,int);
};