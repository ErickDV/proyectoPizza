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
            matAdj[i][j]=limite;
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

void Grafo::dijkstra(string a, string b) {
    //Se obtienen los vertices de inicio y de fin
    int posicion = buscarV(a);
    int fin = buscarV(b);

    //Se crean los arreglos para almacenar la suma acumulada y el vertice anterior por nodo.
    int* suma = new int[numVertices];
    int* verticeAnterior = new int[numVertices];

    //Se estabece como visitado el inicio y como no visitado los demás
    for(int i=0;i<numVertices;i++){
        listaV[i].setVis(false);
        suma[i] = limite;

    }

    listaV[posicion].setVis(true);

    //Se establece que la suma acumulada del V inicial es 0 y que no tiene vertice anterior.
    suma[posicion] = 0;


    int menor = limite;
    int posMenor;

    verticeAnterior[posicion] = -1; // Usamos -1 para indicar que no hay un vértice anterior

    do {
        menor = limite;
        posMenor = -1;

        for (int i = 0; i < numVertices; i++) {
            if (!listaV[i].getVis() && matAdj[posicion][i] != limite) { //Si el nodo no ha sido visitado y tiene un peso diferente al limite (existe relacion)

                int sumaTemp = suma[posicion] + matAdj[posicion][i];

                if (sumaTemp < suma[i] || suma[i] == 0) { //Si la suma temporal es menor a la aumulada del nodo (o si el nodo no tiene suma acumulada)
                    suma[i] = sumaTemp; //Se establece la suma acumulada del nodo
                    verticeAnterior[i] = posicion; //Se establece su vertice anterior
                }

                //Se busca al menor de las sumas acumuladas
                if (suma[i] < menor) {
                    menor = suma[i];
                    posMenor = i;
                }

                cout << "===========================" << endl;
                cout << "Nodo actual: " << listaV[posicion].getNom()<< endl;
                cout << "Nodo a recorrer: " << listaV[i].getNom() << endl;
                cout << "Peso: " << suma[i] << endl;
                cout << "Vertice anterior: " << listaV[verticeAnterior[i]].getNom() << endl;
            }

        }

        for (int i = 0; i < numVertices; i++) {
            if (!listaV[i].getVis()){
                if(suma[i]<suma[posMenor]){
                    posMenor= i;
                }
            }
        }

        //Se establece el siguiente nodo a recorrer (y se marca como visitado)
        if (posMenor != -1) {
            listaV[posMenor].setVis(true);
            posicion = posMenor;
            cout << "Nueva posicion actual: " << listaV[posicion].getNom() << endl;
        }
    } while (!listaV[fin].getVis());

    cout << "Menor peso encontrado: " << menor << endl;

    if (listaV[posMenor].getVis()) {
        cout << "El destino fue visitado" << endl;
        cout << "Peso: " << suma[fin] << endl;

        // Imprimir el camino desde el nodo de inicio hasta el nodo de destino
        cout << "Camino: ";
        int nodoActual = fin;
        while (nodoActual != -1) {
            cout << listaV[nodoActual].getNom();
            nodoActual = verticeAnterior[nodoActual];
            if (nodoActual != -1) {
                cout << " -> ";
            }
        }
        cout << endl;
    } else {
        cout << "El destino no fue visitado" << endl;
    }

    delete[] suma;
    delete[] verticeAnterior;
}


