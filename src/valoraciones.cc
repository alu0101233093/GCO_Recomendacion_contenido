/*
Autor: Leonardo Alfonso Cruz Rodríguez
Práctica: Sistemas de recomendaciones
Asignatura: Gestión del conocimiento en las Organizaciones
Universidad: ULL
*/

#include "../include/valoraciones.h"

Valoraciones::Valoraciones(int p, int n) {
    p_ = p;
    n_ = n;
    dist_ = 0;

    // redimensionando matrices
    Mval_.resize(p_);
    CI_.resize(p_);
    for (int i = 0; i < p_; i++)
        CI_[i].resize(n_);
    CIF_.resize(p_);
    for (int i = 0; i < p_; i++)
        CIF_[i].resize(n_);
    SP_.resize(p_);
    for (int i = 0; i < p_; i++)
        SP_[i].resize(p_);

    // valores por defecto
    for(int i = 0; i < p_; i++){
        for (int j = 0; j < n_; j++){
            CI_[i][j] = -1;
        }
    }
    for(int i = 0; i < p_; i++){
        for (int j = 0; j < n_; j++){
            CIF_[i][j] = 0;
        }
    }
    for(int i = 0; i < p_; i++){
        for (int j = 0; j < n_; j++){
            SP_[i][j] = 0;
        }
    }
}

Valoraciones::~Valoraciones() {
    CI_.clear();
    CIF_.clear();
}

void 
Valoraciones::set_persona_item_valor(int person, int item, int val) {
    CI_[person][item] = val;
    CIF_[person][item] = val;

    float suma = 0,count = 0;
    for(int i = 0; i < n_; i++){
        if(CI_[person][i] != -1){
            suma += CI_[person][i];
            count++;
        }
    }
    if(count != 0)
    Mval_[person] = suma/count;
}

std::pair<float,int>
Valoraciones::Pearson(int u, int v) {
    float num = 0, den1 = 0, den2 = 0;
    std::pair<float,int> val_num; // valor y número de items considerados
    int num_items = n_;

    // numerador
    for(int i = 0; i < n_; i++){
        if (CI_[u][i] != -1 && CI_[v][i] != -1)
            num += (CI_[u][i] - Mval_[u])*(CI_[v][i] - Mval_[v]);
        else
            num_items--;
    }

    // denominador izquierda
    for(int i = 0; i < n_; i++){
        if(CI_[u][i] != -1)
            den1 += pow((CI_[u][i] - Mval_[u]), 2);
    }
    den1 = sqrt(den1);

    // denominador derecha
    for(int i = 0; i < n_; i++){
        if(CI_[v][i] != -1)
            den2 += pow((CI_[v][i] - Mval_[v]), 2);
    }
    den2 = sqrt(den2);

    val_num.first = (num/(den1*den2));
    val_num.second = num_items;
    return val_num;
}

std::pair<float,int>
Valoraciones::Coseno(int u, int v) {
    float num = 0, den1 = 0, den2 = 0;
    std::pair<float,int> val_num; // valor y número de items considerados
    int num_items = n_;

    // numerador
    for(int i = 0; i < n_; i++){
        if (CI_[u][i] != -1 && CI_[v][i] != -1)
            num += (CI_[u][i]*CI_[v][i]);
        else
            num_items--;
    }

    // denominador izquierda
    for(int i = 0; i < n_; i++){
        if(CI_[u][i] != -1)
            den1 += pow(CI_[u][i], 2);
    }
    den1 = sqrt(den1);

    // denominador derecha
    for(int i = 0; i < n_; i++){
        if(CI_[v][i] != -1)
            den2 += pow(CI_[v][i], 2);
    }
    den2 = sqrt(den2);

    val_num.first = (num/(den1*den2));
    val_num.second = num_items;
    return val_num;
}

std::pair<float,int>
Valoraciones::Euclidea(int u, int v) {
    float num = 0;
    std::pair<float,int> val_num; // valor y número de items considerados
    int num_items = n_;

    for(int i = 0; i < n_; i++){
        if (CI_[u][i] != -1 && CI_[v][i] != -1)
            num += pow((CI_[u][i]-CI_[v][i]),2);
        else
            num_items--;
    }

    val_num.first = sqrt(num);
    val_num.second = num_items;
    return val_num;
}

void
Valoraciones::Pred_simple(int distancia) {
    float num = 0, den = 0;

    for(int p = 0; p < p_; p++){
        for (int i = 0; i < n_; i++){
            if(CI_[p][i] == -1){
                // formula
                for(int q = 0; q < p_; q++){
                    if(p != q && CI_[q][i] != -1){
                        switch (distancia) {
                        case 1:
                            num += Pearson(p,q).first*CI_[q][i];
                            den += abs(Pearson(p,q).first);
                            break;
                        
                        case 2:
                            num += Coseno(p,q).first*CI_[q][i];
                            den += abs(Coseno(p,q).first);
                            break;
                        
                        case 3:
                            num += Euclidea(p,q).first*CI_[q][i];
                            den += abs(Euclidea(p,q).first);
                            break;
                        }
                    }
                }
                // fin de la formula
                CIF_[p][i] = num/den;
            }
        }
    }
    imprimir_matrizf();
}

void
Valoraciones::Pred_media(int distancia) {
    float num = 0,den = 0;

    for(int p = 0; p < p_; p++){
        for (int i = 0; i < n_; i++){
            if(CI_[p][i] == -1){
                // formula
                for(int q = 0; q < p_; q++){
                    if(p != q && CI_[q][i] != -1){
                        num += Pearson(p,q).first*CI_[q][i];
                        den += abs(Pearson(p,q).first);
                    }
                }
                // fin de la formula
                CIF_[p][i] = num/den;
            }
        }
    }
    
    
}

void
Valoraciones::imprimir_matriz() {
    std::cout << "\n\n";
    for(int i = 0; i < p_; i++){
        for (int j = 0; j < n_; j++){
            if(CI_[i][j] != -1)
                std::cout << CI_[i][j] << " ";
            else
                std::cout << "- ";
        }
        std::cout << "\n";
    }
    std::cout << "\n\n";
}

void
Valoraciones::imprimir_matrizf() {
    std::cout << "\n\n";
    for(int i = 0; i < p_; i++){
        for (int j = 0; j < n_; j++){
            if(CIF_[i][j] != -1)
                std::cout << CIF_[i][j] << " ";
            else
                std::cout << "- ";
        }
        std::cout << "\n";
    }
    std::cout << "\n\n";
}