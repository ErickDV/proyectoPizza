#ifndef GRAFO_H
#define GRAFO_H
#include "Vertice.h"
#include <fstream>

class Grafo
{
    Vertice *listaV;
    int **matAdj;
    int numVertices;
    //string nomArchGraf;
    ifstream arch;
    int buscarV(string s);

    public:
        Grafo(string nomArchG);
        void mostrarGrafo();
        void crearListaV();
        void mostrarListasVertices();
        void crearMatrizAdj();
        void dijkstra(string a,string b);
};

#endif // GRAFO_H
