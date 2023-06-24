#ifndef GRAFO_H
#define GRAFO_H
#include "Vertice.h"
#include <fstream>

class Grafo
{
    int limite = 10000;
    Vertice *listaV;

    int **matAdj;
    int numVertices;
    //string nomArchGraf;
    ifstream arch;
    int buscarV(string s);

    public:

        string obtenerRuta(string n);
        int *suma;
        int *verticeAnterior;
        Grafo(string nomArchG);
        void mostrarGrafo();
        void crearListaV();
        void mostrarListasVertices();
        void crearMatrizAdj();
        void dijkstra(string a,string b);
        void combinaciones(int n);
        void inicializarSuma();
        string invertirYReemplazar(string cadena);
};

#endif // GRAFO_H
