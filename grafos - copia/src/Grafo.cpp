#include "Grafo.h"
#include <fstream>
#include <string>
#include <iostream>
#include "Vertice.h"

using namespace std;


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

    string dir[4];
    string dir1 = "";
    string dir2 = "";
    string dir3 = "";
    string dir4 = "";

    string pizzeria="A";

    int posDir[4];
    int posDir1;
    int posDir2;
    int posDir3;
    int posDir4;


    string comb[4];
    string comb1;
    string comb2;
    string comb3;
    string comb4;
    int primeraComb;

    int tiempo[4];
    int tiempo1=0;
    int tiempo2=0;
    int tiempo3=0;
    int tiempo4=0;

    int tiempoMenor = limite;
    string rutaMenor="";

    string ruta[4];

    string ruta1="";
    string ruta2="";
    string ruta3="";
    string ruta4="";


    int resAnterior;
    int res2;

    switch(n){
    case 1:
        cout<<"Ingrese la dirección a la que quiere ir: "<<endl;
        cin >> dir1;
        dijkstra("A",dir1);

        /*
        cout<<"=====PRUEBA HOLA======"<<endl;
        res = buscarV(dir1);
        cout<<suma[res]<<endl;
        cout<<verticeAnterior[res]<<endl;
        res2 = verticeAnterior[res];
        cout<<verticeAnterior[res2]<<endl;
        res2 = verticeAnterior[res2];
        cout<<verticeAnterior[res2]<<endl; */

        break;

    case 2: //sumar 1 al tiempo
        cout<<"Ingrese la primera dirección a la que quiere ir: "<<endl;
        cin >> dir1;
        posDir1 = buscarV(dir1);
        cout<<"Ingrese la segunda dirección a la que quiere ir: "<<endl;
        cin >> dir2;
        posDir2 = buscarV(dir2);

        dijkstra("A",dir1);
        resAnterior= posDir1;

        do{
            resAnterior=verticeAnterior[resAnterior];
        }while(resAnterior!=-1 && resAnterior!=posDir2);

        if(resAnterior==-1){
            //guardar primera ruta y peso

            resAnterior=posDir1;
            do{
                ruta1 += listaV[resAnterior].getNom() + " -> ";
                resAnterior=verticeAnterior[resAnterior];
            }while(resAnterior!=-1);

            tiempo1=suma[posDir1];

            dijkstra(dir1,dir2);

            resAnterior=posDir2;
            do{
                ruta2 += listaV[resAnterior].getNom() + " -> ";
                resAnterior=verticeAnterior[resAnterior];
            }while(resAnterior!=posDir1);

            ruta2+=ruta1;


            tiempo1+=suma[posDir2];
            tiempo1+=1;
            cout<<"Prueba de tiempo: "<< tiempo1<<endl;
            cout<<"Prueba de ruta: "<< ruta2<<endl;
            //dijstra con el otro vertice
        }else{
            //Imprimir ruta y peso.
            resAnterior=posDir1;
            do{
            cout << listaV[resAnterior].getNom() << " -> ";
            resAnterior=verticeAnterior[resAnterior];
        }while(resAnterior!=-1);
        cout << endl;
        cout << "Peso: "<<suma[posDir1]+1;
        }


        break;

    case 3:
        cout<<"Ingrese la primera dirección a la que quiere ir: "<<endl;
        cin >> dir[0];
        posDir[0] = buscarV(dir[0]);
        cout<<"Ingrese la segunda dirección a la que quiere ir: "<<endl;
        cin >> dir[1];
        posDir[1] = buscarV(dir[1]);
        cout<<"Ingrese la tercera dirección a la que quiere ir: "<<endl;
        cin >> dir[2];
        posDir[2] = buscarV(dir[2]);

        for(int i=0;i<3;i++){
            dijkstra(pizzeria,dir[i]);
            ruta[0] = obtenerRuta(dir[i]);
            tiempo[0] = suma[posDir[i]];
            //guardar ruta y tiempo
            for (int j=0;j<3;j++){
                if(j!=i){
                    dijkstra(dir[i],dir[j]);
                    ruta[1]=obtenerRuta(dir[j])+ruta[0];
                    tiempo[1] = tiempo[0] + suma[posDir[j]];
                    //guardar ruta y tiempo
                    // Concatenar ruta y aumentar tiempo
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
        cout<<"La mejor ruta es: "<<rutaMenor<<endl;
        cout<<"El mejor tiempo es: "<<tiempoMenor<<endl;
        break;

    case 4: //sumar 3 al tiempo
        cout<<"Ingrese la primera dirección a la que quiere ir: "<<endl;
        cin >> dir1;
        posDir1 = buscarV(dir1);
        cout<<"Ingrese la segunda dirección a la que quiere ir: "<<endl;
        cin >> dir2;
        posDir2 = buscarV(dir2);
        cout<<"Ingrese la tercera dirección a la que quiere ir: "<<endl;
        cin >> dir3;
        posDir3 = buscarV(dir3);
        cout<<"Ingrese la cuarta dirección a la que quiere ir: "<<endl;
        cin >> dir3;
        posDir4 = buscarV(dir4);

        //Se selecciona el primer camino más corto:
        for(int i = 1;i<=4;i++){
            if (i == 1) {
                comb4 = dir1;
            } else if (i == 2) {
                comb4 = dir2;
            } else if (i == 3) {
                comb4 = dir3;
            } else {
                comb4 = dir4;
            }
            dijkstra(pizzeria,comb4);

            if(tiempo1<tiempoMenor){
                tiempoMenor=tiempo3;
                rutaMenor = ruta3;
            }

        }



        for(int i=1;i<=3;i++){
            if (i == 1) {
                comb1 = dir1;
            } else if (i == 2) {
                comb1 = dir2;
            } else {
                comb1 = dir3;
            }
            dijkstra(pizzeria,comb1);
            ruta1 = obtenerRuta(comb1);
            tiempo1 = suma[buscarV(comb1)];
            //guardar ruta y tiempo
            for (int j=1;j<=3;j++){
                if(j!=i){
                    if (j == 1) {
                        comb2 = dir1;
                    } else if (j == 2) {
                        comb2 = dir2;
                    } else {
                        comb2 = dir3;
                    }
                    dijkstra(comb1,comb2);
                    ruta2=obtenerRuta(comb2)+ruta1;
                    tiempo2 = tiempo1 + suma[buscarV(comb2)];
                    //guardar ruta y tiempo
                    // Concatenar ruta y aumentar tiempo
                    for (int k=1; k<=3; k++){

                        if(k!=j && k!=i){
                            if (k == 1) {
                                comb3 = dir1;
                            } else if (k == 2) {
                                comb3 = dir2;
                            } else {
                                comb3 = dir3;
                            }
                            dijkstra(comb2,comb3);
                            ruta3=comb3+" <- "+obtenerRuta(comb3)+ruta2;
                            tiempo3 = tiempo2+suma[buscarV(comb3)];
                            tiempo3 +=2;
                            if(tiempo3<tiempoMenor){
                                tiempoMenor=tiempo3;
                                rutaMenor = ruta3;
                            }
                        }
                    }
                }
            }
        }
        cout<<"La mejor ruta es: "<<rutaMenor<<endl;
        cout<<"El mejor tiempo es: "<<tiempoMenor<<endl;
    break;

    default:
        cout<<"No"<<endl
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

void Grafo::imprimirSuma()
{
    for (int i = 0; i < numVertices; i++) {
        cout << "suma[" << i << "]: " << suma[i] << endl;
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

                /*
                cout << "===========================" << endl;
                cout << "Nodo actual: " << listaV[posicion].getNom()<< endl;
                cout << "Nodo a recorrer: " << listaV[i].getNom() << endl;
                cout << "Peso: " << suma[i] << endl;
                cout << "Vertice anterior: " << listaV[verticeAnterior[i]].getNom() << endl;
                */
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
            //cout << "Nueva posicion actual: " << listaV[posicion].getNom() << endl;
        }
    } while (!listaV[fin].getVis());

    //cout << "Menor peso encontrado: " << menor << endl;

    if (listaV[posMenor].getVis()) {
        //cout << "El destino fue visitado" << endl;
        //cout << "Peso: " << suma[fin] << endl;

        // Imprimir el camino desde el nodo de inicio hasta el nodo de destino
        /*
        cout << "Camino: ";
        int nodoActual = fin;
        while (nodoActual != -1) {
            cout << listaV[nodoActual].getNom();
            nodoActual = verticeAnterior[nodoActual];
            if (nodoActual != -1) {
                cout << " -> ";
            }
        }
        */
        cout << endl;
    } else {
        cout << "El destino no fue visitado" << endl;
    }

}


