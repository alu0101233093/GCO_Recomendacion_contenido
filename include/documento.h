#include <vector>
#include <iostream>
#include <stdio.h>
#include <math.h>

class Documento {
    private:
        std::vector<std::pair<std::string,int>> keywords_;
        int n_words;
        
    public:
        Documento();
        ~Documento();
        void set_word(std::string);

        // getters
        int get_n(); // getter del número de palabras
        std::string get_word(int); // getter de palabra
        int get_frec(std::string); // getter frecuencia
};