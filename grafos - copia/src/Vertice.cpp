#include "Vertice.h"

Vertice::Vertice()
{
    nom ="";
    visitado=false;
}

Vertice::Vertice(string n){
    nom = n;
}


string Vertice::getNom(){
    return nom;
}


Vertice::setNom(string n){
    nom = n;
}
Vertice::setVis(bool n){
    visitado = n;
}
bool Vertice::getVis(){
    return visitado;
}
