#include "Grafo.h"
#include <fstream>
#include <string>
#include <iostream>
#include "Vertice.h"

Grafo::Grafo(string nomArchG)
{
    arch.open(nomArchG);
    //Sustituir a partir de aqui


    //nomArchGraf = nomArchG;
    //ifstream grafo(nomArchG);
    string s;
    int n;
    getline(arch,s);
    n = stoi(s);
    numVertices = n;
    listaV = new Vertice[numVertices];
    matAdj = new int*[numVertices];
    for(int i=0; i<numVertices; i++){
        matAdj[i]=new int[numVertices];
        for(int j=0; j<numVertices;j++)
            matAdj[i][j]=10000;
    }
}

void Grafo::mostrarGrafo(){ //Muestra la matriz de adyacencia
    for(int i=0; i<numVertices; i++){
            for(int j=0; j<numVertices;j++)
                cout << matAdj[i][j] << "\t";
            cout << endl;
        }
}

void Grafo::crearListaV(){
    for(int i=0;i<numVertices;i++){
        string s;
        getline(arch,s);
        listaV[i]= Vertice(s);
    }
}

void Grafo::crearMatrizAdj(){
    string s;
    string origen,destino;
    int pos_i,pos_j,peso;

    while(getline(arch,s)){ //!arch.eof()
        int pos_s = s.find('*');
        origen = s.substr(0,pos_s);
        s.erase(0,pos_s+1);
        pos_s = s.find('*');
        destino = s.substr(0,pos_s);
        s.erase(0,pos_s+1);
        peso= stoi(s);

        pos_i = buscarV(origen);
        pos_j = buscarV(destino);

        matAdj[pos_i][pos_j] = peso;
        matAdj[pos_j][pos_i] = peso;

    }

    /**separar s en origen, destino y peso**/

}

int Grafo::buscarV(string s){
    int i=0;
    while ((i<numVertices) && (s!=listaV[i].getNom()))
        i++;
    return i;
}

void Grafo::mostrarListasVertices(){
    for (int i=0;i<numVertices;i++){
        cout << listaV[i].getNom() << endl;
    }
}
void Grafo::dijkstra(string a,string b){

    int posicion = buscarV(a);
    listaV[posicion].setVis(true);
    int menor=10000;
    int posMenor;

        for (int i=0;i<numVertices;i++){
        cout << matAdj[posicion][i] << endl;
        if (matAdj[posicion][i]<menor){
            menor=matAdj[posicion][i];
            posMenor = i;
        }
        }
    cout <<menor << endl;
    listaV[posMenor].setVis(true);
    if (listaV[posMenor].getVis()){
        cout<< "visitado" << endl;
    }
    else
         cout<< "no visitado" << endl;
}
