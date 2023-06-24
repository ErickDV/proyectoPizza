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
    int entregas;

    do{
        cout << "Entregas por realizar (ingrese 0 para salir): "<<endl;
        cin >> entregas;
        g.combinaciones(entregas);
    }while(entregas!=0);

    return 0;
}
