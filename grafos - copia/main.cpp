#include <iostream>
#include <fstream>
#include <string>
#include "Grafo.h"

using namespace std;

int main()
{
    /*
    ifstream grafo("grafo1.txt");
    string s;
    getline(grafo,s);
    int n = stoi(s);
    cout << s << "n = "<<n<< endl;

    int mat[n][n];
    */

    string graf = "pizza.txt";
    Grafo g(graf);
    g.mostrarGrafo();
    cout<<"=============== SEPARADOR ===================="<<endl;
    g.crearListaV();
    g.mostrarListasVertices();
    g.crearMatrizAdj();
    g.mostrarGrafo();
    g.dijkstra("a","b");

    return 0;
}
