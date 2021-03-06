#include <vector>
#include <iostream>
#include <stdio.h>
#include <math.h>

class Documento {
    private:
        std::vector<std::pair<std::string,int>> terminos_;
        int n_diff_terms_;
        int n_terms_;
        
    public:
        Documento();
        ~Documento();
        void set_word(std::string);

        // getters
        int get_diff_terms(); // getter del número de términos distintos
        int get_terms(); // getter del número de términos
        std::string get_word(int); // getter de palabra
        int get_frec(std::string); // getter frecuencia
};