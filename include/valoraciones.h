#include <vector>
#include <iostream>
#include <stdio.h>
#include <math.h>

typedef std::vector<std::vector<int>> Matriz;

class Valoraciones {
    private:
        Matriz CI_; // calificaciones - ítems
        Matriz CIF_; // calificaciones - ítems final
        Matriz SP_; // similitud - personas
        std::vector<float> Mval_; // Media valoraciones
        int n_; // número de items
        int p_; // número de personas
        int dist_; // distancia escogida
    public:
        Valoraciones(int, int);
        ~Valoraciones();
        void set_persona_item_valor(int, int, int);
        std::pair<float,int> Pearson(int,int);   // dist_ = 0
        std::pair<float,int> Coseno(int,int);    // dist_ = 1
        std::pair<float,int> Euclidea(int,int);  // dist_ = 2
        void Pred_simple(int);
        void Pred_media(int);
        void imprimir_matriz();
        void imprimir_matrizf();
};