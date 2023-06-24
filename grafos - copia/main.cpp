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

    string graf = "prueba.txt";
    Grafo g(graf);
    g.inicializarSuma();
    g.mostrarGrafo();
    cout<<"=============== SEPARADOR ===================="<<endl;
    g.crearListaV();
    g.crearMatrizAdj();

    cout << "Entregas por realizar: "<<endl;
    int entregas;
    cin >> entregas;
    g.combinaciones(entregas);


    //Utilizar colores para imprimir


    return 0;
}
