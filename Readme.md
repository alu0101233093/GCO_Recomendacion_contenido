### <u>Autor:</u> Leonardo Alfonso Cruz Rodríguez
### <u>Correo:</u> alu0101233093@ull.edu.es
### <u>Asignatura:</u> Gestión del conocimiento en las organizaciones
### <u>Universidad:</u> Universidad de La Laguna
<br />

# Sistemas de Recomendación.<br /> Modelos basados en el contenido

El objetivo de esta práctica es implementar un sistema de recomendación siguiendo el modelo basados en el contenido. Para ello, he optado por implementarlo en el lenguaje orientado a objetos c++.

## <u>Modo de uso</u>
Para usar correctamente este programa ha de tener en cuenta los siguientes puntos:
- Debe usar la sintaxis correcta al ejecutar el programa: <br />
`./estval -i (nombre del archivo input) -o (nombre del archivo output)` <br />
- Debe situar el archivo input en la carpeta `input/`.
- El archivo output será generado en la carpeta `output/`.

## <u>Ejemplo de uso</u>
Situamos el archivo `example.txt` en el directorio `input/`. <br />
```
hola gol bye
hey. hola bye bye
adiós, bye
```
Ejecutamos el comando `./estval -i example.txt -o output.txt`. <br />
Obtendremos la siguiente salida por consola:
```
$ ./estval -i example2.txt -o output2.txt
Fichero abierto correctamente
```
Lo que quiere decir que se ha leido el archivo además del archivo `output/output.txt`:
```
Documento 0:
Índice	Término			TF	IDF	TF-IDF
0	hola			0.33333	0.17609	0.05870	
1	gol			0.33333	0.47712	0.15904	
2	bye			0.33333	0.00000	0.00000	
3	hey			0.00000	0.47712	0.00000	
4	adiós			0.00000	0.47712	0.00000	


Documento 1:
Índice	Término			TF	IDF	TF-IDF
0	hola			0.33333	0.17609	0.05870	
1	gol			0.00000	0.47712	0.00000	
2	bye			0.66667	0.00000	0.00000	
3	hey			0.33333	0.47712	0.15904	
4	adiós			0.00000	0.47712	0.00000	


Documento 2:
Índice	Término			TF	IDF	TF-IDF
0	hola			0.00000	0.17609	0.00000	
1	gol			0.00000	0.47712	0.00000	
2	bye			0.50000	0.00000	0.00000	
3	hey			0.00000	0.47712	0.00000	
4	adiós			0.50000	0.47712	0.23856	


---------------- Similaridad coseno ----------------
cos(0,0) = 1.00000
cos(0,1) = 0.00345
cos(0,2) = 0.00000
cos(1,1) = 1.00000
cos(1,2) = 0.00000
cos(2,2) = 1.00000
```

## <u>Implementación</u>
En esta práctica he decidido estructurar los datos que se han de manejar en 2 clases distintas.
El código se divide en 3 partes (main, clase valoraciones y clase documento).

## src/main.cc
Esta primera y principal parte del código se encarga de recibir correctamente los parámetros y
pasarle al objeto valoraciones cada documento que debe analizar. Además imprime los resultados.
```c++
int main (int argc, char *argv[]) {
    if (argc == 5){
        std::string arguments[5];
        for(int i = 0; i < 5; i++)
            arguments[i] = argv[i];
        if((arguments[1] == "-i" || arguments[1] == "-I") & (arguments[3] == "-o" || arguments[3] == "-O")){
            std::ifstream fentrada;
            std::string input = "input/";
            input = input + argv[2];
            fentrada.open(input, std::ios::in);
            if (!fentrada.is_open())
                std::cout << "No se pudo abrir el fichero\n";
            else{
                std::cout << "Fichero abierto correctamente\n";
                std::string documento;
                Valoraciones V;
                while (!fentrada.eof()) {
                    std::getline(fentrada, documento);
                    V.set_documento(documento);
                }
                V.print(arguments[4]);      
            }
        }
    } else
        Ayuda();
    return 0;
}
```

## Clase Valoraciones
Esta clase se encarga de almacenar distintos documentos (que son valoraciones).
```c++
class Valoraciones {
    private:
        std::vector<Documento> valoraciones_; // Almacena los documentos
        std::vector<std::string> diccionario_; // Almacena las palabras de todos los documentos (sin repeticiones)
        int n_docs_; // Número de documentos
        int n_palabras_; // Número de palabras en el diccionario
        void set_palabra(std::string); // Agrega una palabra al diccionario
        
    public:
        Valoraciones(); // Constructor
        ~Valoraciones(); // Destructor
        void set_documento(std::string); // Agrega un documento
        float TF(std::string,int);  // Calcula Term-Frecuency
        float IDF(std::string);     // Calcula Inverse-Document-Frecuency
        float TFIDF(std::string,int);     // Calcula TFIDF
        float sim_coseno(int,int);  // Calcula similaridad coseno
        int get_n();    // Devuelve el número de documentos almacenados (Para calcular TF)
        void print(std::string);    // Imprime todos los datos de cada documento
};
```
### Term-Frecuency (TF)
```c++
float 
Valoraciones::TF(std::string x, int y){
    return (float(valoraciones_[y].get_frec(x))/float(valoraciones_[y].get_n()));
}
```

### Inverse-Document-Frecuency (IDF)
```c++
float 
Valoraciones::IDF(std::string x){
    float dfx = 0;
    for(int i = 0; i < int(valoraciones_.size()); i++){
        if(valoraciones_[i].get_frec(x) >= 1)
            dfx++;
    }
    return log10(n_docs_/dfx);
}
```

### TF-IDF
```c++
float  
Valoraciones::TFIDF(std::string x,int y){
    return TF(x,y)*IDF(x);
}
```

### Similaridad coseno
```c++
float 
Valoraciones::sim_coseno(int x,int y){
    if (x == y)
        return 1;

    float suma = 0;
    for(int i = 0; i < n_palabras_; i++){
        suma += TFIDF(diccionario_[i],x) * TFIDF(diccionario_[i],y);
    }
    return suma;
}
```

## Clase Documento
Esta clase se encarga de almacenar distintos documentos (que son valoraciones).
```c++
class Documento {
    private:
        std::vector<std::pair<std::string,int>> keywords_; // Almacena las palabras del documento y la frecuencia absoluta del término
        int n_words; // Número de palabras distintas en el documento
        
    public:
        Documento(); // Constructor
        ~Documento(); // Destructor
        void set_word(std::string); // Añade una palabra al documento

        // Getters
        int get_n(); // Getter del número de palabras
        std::string get_word(int); // Getter de palabra
        int get_frec(std::string); // Getter frecuencia absoluta
};
```
