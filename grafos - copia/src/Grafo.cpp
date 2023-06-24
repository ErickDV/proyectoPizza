#include "Grafo.h"
#include <fstream>
#include <string>
#include <iostream>
#include "Vertice.h"
#include <algorithm>

using namespace std;


Grafo::Grafo(string nomArchG)
{
    arch.open(nomArchG);

    string s;
    int n;
    getline(arch,s);
    n = stoi(s);
    numVertices = n;
    listaV = new Vertice[numVertices];
    matAdj = new int*[numVertices];

    verticeAnterior = new int[numVertices];

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
string Grafo::invertirYReemplazar(string cadena) {
    // Invertir la cadena
    reverse(cadena.begin(), cadena.end());

    // Reemplazar los símbolos "<" por ">"
    replace(cadena.begin(), cadena.end(), '<', '>');

    cadena = cadena.substr(4);

    return cadena;
}


string Grafo::obtenerRuta(string n){
    int resAnterior;
    resAnterior=buscarV(n);
    string ruta="";
    do{
        resAnterior=verticeAnterior[resAnterior];
        if(resAnterior!=-1)
            ruta += listaV[resAnterior].getNom() + " <- ";
    }while(resAnterior!=-1);
    return ruta;
}

void Grafo::combinaciones(int n){

    string pizzeria="A";

    int tiempoMenor = limite;
    string rutaMenor="";

    int primeraComb;
    string ruta[4];
    string comb[4];
    string dir[4];
    int posDir[4];
    int tiempo[4];

    int posDirTemp;
    string dirTemp;

    switch(n){
    case 1:
        //==================== LECTURA DE DATOS ===============================
        cout<<"Ingrese la dirección a la que quiere ir: "<<endl;
        cin >> dir[0];
        posDir[0] = buscarV(dir[0]);
        //=======================Dijkstra a 1 punto============================
        dijkstra("A",dir[0]);

        ruta[0]=dir[0]+" <- "+obtenerRuta(dir[0]);
        ruta[0]= invertirYReemplazar(ruta[0]);
        cout<<"La mejor ruta es: "<<ruta[0]<<endl;
        cout<<"El mejor tiempo es: "<<suma[posDir[0]]<<endl;
        break;

    case 2: //sumar 1 al tiempo
        //==================== LECTURA DE DATOS ===============================
        cout<<"Ingrese la primera dirección a la que quiere ir: "<<endl;
        cin >> dir[0];
        posDir[0] = buscarV(dir[0]);
        cout<<"Ingrese la segunda dirección a la que quiere ir: "<<endl;
        cin >> dir[1];
        posDir[1] = buscarV(dir[1]);

        //===================CICLO PIZZERIA A 1 PUNTO==========================
        for(int i=0;i<2;i++){
            dijkstra(pizzeria,dir[i]);
            ruta[0] = obtenerRuta(dir[i]);
            tiempo[0] = suma[posDir[i]];
            //===================CICLO PUNTO 1 A PUNTO 2===========================
            for (int j=0;j<2;j++){
                if(j!=i){
                    dijkstra(dir[i],dir[j]);
                    ruta[1]=dir[j]+" <- "+obtenerRuta(dir[j])+ruta[0];
                    tiempo[1] = tiempo[0] + suma[posDir[j]];
                    tiempo[1] += 1;
                    if(tiempo[1]<tiempoMenor){
                        tiempoMenor=tiempo[1];
                        rutaMenor = ruta[1];
                    }
                }
            }
        }
        rutaMenor = invertirYReemplazar(rutaMenor);
        cout<<"La mejor ruta es: "<<rutaMenor<<endl;
        cout<<"El mejor tiempo es: "<<tiempoMenor<<endl;
        break;

    case 3:
        //==================== LECTURA DE DATOS ===============================
        cout<<"Ingrese la primera dirección a la que quiere ir: "<<endl;
        cin >> dir[0];
        posDir[0] = buscarV(dir[0]);
        cout<<"Ingrese la segunda dirección a la que quiere ir: "<<endl;
        cin >> dir[1];
        posDir[1] = buscarV(dir[1]);
        cout<<"Ingrese la tercera dirección a la que quiere ir: "<<endl;
        cin >> dir[2];
        posDir[2] = buscarV(dir[2]);

        //===================CICLO PIZZERIA A 1 PUNTO==========================
        for(int i=0;i<3;i++){
            dijkstra(pizzeria,dir[i]);
            ruta[0] = obtenerRuta(dir[i]);
            tiempo[0] = suma[posDir[i]];
            //===================CICLO PUNTO 2 A PUNTO 3===========================
            for (int j=0;j<3;j++){
                if(j!=i){
                    dijkstra(dir[i],dir[j]);
                    ruta[1]=obtenerRuta(dir[j])+ruta[0];
                    tiempo[1] = tiempo[0] + suma[posDir[j]];
                    //===================CICLO PUNTO 2 A PUNTO 3===========================
                    for (int k=0; k<3; k++){
                        if(k!=j && k!=i){
                            dijkstra(dir[j],dir[k]);
                            ruta[2]=dir[k]+" <- "+obtenerRuta(dir[k])+ruta[1];
                            tiempo[2] = tiempo[1]+suma[posDir[k]];
                            tiempo[2] +=2;
                            if(tiempo[2]<tiempoMenor){
                                tiempoMenor=tiempo[2];
                                rutaMenor = ruta[2];
                            }
                        }
                    }
                }
            }
        }
        rutaMenor = invertirYReemplazar(rutaMenor);
        cout<<"La mejor ruta es: "<<rutaMenor<<endl;
        cout<<"El mejor tiempo es: "<<tiempoMenor<<endl;
        break;

    case 4: //sumar 3 al tiempo
        //==================== LECTURA DE DATOS ===============================
        cout<<"Ingrese la primera dirección a la que quiere ir: "<<endl;
        cin >> dir[0];
        posDir[0] = buscarV(dir[0]);
        cout<<"Ingrese la segunda dirección a la que quiere ir: "<<endl;
        cin >> dir[1];
        posDir[1] = buscarV(dir[1]);
        cout<<"Ingrese la tercera dirección a la que quiere ir: "<<endl;
        cin >> dir[2];
        posDir[2] = buscarV(dir[2]);
        cout<<"Ingrese la cuarta dirección a la que quiere ir: "<<endl;
        cin >> dir[3];
        posDir[3] = buscarV(dir[3]);


        //=============RUTA MENOR PIZZERIA A PRIMER NODO=======================
        for (int i =0;i<4;i++){
            dijkstra(pizzeria,dir[i]);
            if(suma[posDir[i]]<tiempoMenor){
                primeraComb = i;
                tiempoMenor = suma[posDir[i]];
            }
        }
        tiempoMenor = limite;
        dijkstra(pizzeria,dir[primeraComb]);
        ruta[3] =obtenerRuta(dir[primeraComb]);
        tiempo[3] = suma[posDir[primeraComb]];
        //Establecer ese nodo como la primera combinación.
        //Hacer que los 3 restantes utilicen los espacios de arreglo del 0 al 2 para reutilizar código
        // (intercambiar nodo elegido con la última posición)
        if(primeraComb!=3){
            posDirTemp = posDir[primeraComb];
            dirTemp = dir[primeraComb];

            posDir[primeraComb] = posDir[3];
            dir[primeraComb] = dir[3];

            posDir[3] = posDirTemp;
            dir[3] = dirTemp;
        }
        //===================CICLO PUNTO 1 A PUNTO 2===========================
        for(int i=0;i<3;i++){
            dijkstra(dir[3],dir[i]);
            ruta[0] = obtenerRuta(dir[i]) + ruta[3];
            tiempo[0] = tiempo[3] + suma[posDir[i]];
            //===================CICLO PUNTO 2 A PUNTO 3===========================
            for (int j=0;j<3;j++){
                if(j!=i){
                    dijkstra(dir[i],dir[j]);
                    ruta[1]=obtenerRuta(dir[j])+ruta[0];
                    tiempo[1] = tiempo[0] + suma[posDir[j]];
                    //===================CICLO PUNTO 3 A PUNTO 4===========================
                    for (int k=0; k<3; k++){
                        if(k!=j && k!=i){
                            dijkstra(dir[j],dir[k]);
                            ruta[2]=dir[k]+" <- "+obtenerRuta(dir[k])+ruta[1];
                            tiempo[2] = tiempo[1]+suma[posDir[k]];
                            tiempo[2] +=3;
                            if(tiempo[2]<tiempoMenor){
                                tiempoMenor=tiempo[2];
                                rutaMenor = ruta[2];
                            }
                        }
                    }
                }
            }
        }
        cout<<"===================================================="<<endl;
        rutaMenor = invertirYReemplazar(rutaMenor);
        cout<<"La mejor ruta es: "<<rutaMenor<<endl;
        cout<<"El mejor tiempo es: "<<tiempoMenor<<endl;
        cout<<"===================================================="<<endl<<endl;
    break;

    case 0:
        cout << "Hasta luego." << endl;
        break;

    default:
        cout<<"Por favor, solo ingrese números del 1 al 4."<<endl
        ;

    }

}

void Grafo::inicializarSuma()
{
    suma = new int[numVertices];
    for (int i = 0; i < numVertices; i++) {
        suma[i] = limite;
    }
}

void Grafo::dijkstra(string a, string b) {
    //Se obtienen los vertices de inicio y de fin
    int posicion = buscarV(a);
    int fin = buscarV(b);

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
                    this->suma[i] = sumaTemp; //Se establece la suma acumulada del nodo
                    verticeAnterior[i] = posicion; //Se establece su vertice anterior
                }

                //Se busca al menor de las sumas acumuladas
                if (suma[i] < menor) {
                    menor = suma[i];
                    posMenor = i;
                }
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
        }
    } while (!listaV[fin].getVis());

    if (listaV[posMenor].getVis()) {
        cout << endl;
    } else {
        cout << "El destino no fue visitado" << endl;
    }
}


