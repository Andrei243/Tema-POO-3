#ifndef EVALUARE_H_INCLUDED
#define EVALUARE_H_INCLUDED
#include <bits/stdc++.h>
using namespace std;
unsigned int citire_numar();
class Curs;
class Evaluare
{
protected:

    const string tip;
    int nota;
    string ret_nume()
    {
        return tip;
    }

    Evaluare(string x):tip(x),nota(0) {};

    friend class Curs;
    friend class Curs_un;
    friend class Curs_nul;
    friend class Curs_doi;
    friend class Curs_Algebra;
    friend class Curs_Analiza;
    friend class Curs_ComNLP;
    friend class Curs_Engleza;
    friend class Curs_Financiar;
    friend class Curs_Geometrie;
    friend class Curs_HR;
    friend class Curs_LegAuto;
    friend class Curs_Programare;
    friend class Curs_Sofat_Practic;
    friend class Curs_Turca;

    void setnota(int x)
    {
        nota=x;
    }

    void schimbare_nota()
    {
        int aux;
        do
        {
            cout<<"Introduceti nota noua la "<<tip<<": ";

            aux=citire_numar();
            if(aux>10||aux<=0)cout<<"Nota introdusa gresit\n";

            setnota(aux);
        }
        while(aux>10||aux<=0);



    }

    void citire_nota()
    {
        int aux;
        do
        {
            cout<<"Introduceti nota la "<<tip<<": ";

            aux=citire_numar();
            if(aux>10||aux<=0)cout<<"Nota introdusa gresit\n";

            setnota(aux);
        }
        while(aux>10||aux<=0);

    }



    int ret_nota()
    {
        return nota;
    }
};




#endif // EVALUARE_H_INCLUDED
