#ifndef VERTICE_H
#define VERTICE_H
#include <string>

using namespace std;

class Vertice
{
    string nom;

    public:
        bool visitado;
        Vertice();
        Vertice(string n);
        string getNom();
        setNom(string n);
        setVis(bool n);
        bool getVis();

};

#endif // VERTICE_H
