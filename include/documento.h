#include <vector>
#include <iostream>
#include <stdio.h>
#include <math.h>

class Documento {
    private:
        std::vector<std::pair<std::string,int>> keywords_;
        
    public:
        Documento();
        ~Documento();
        void set_word(std::string);

        // getters
        std::string get_word(int); // getter de palabra
        int get_frec(int); // getter frecuencia
};