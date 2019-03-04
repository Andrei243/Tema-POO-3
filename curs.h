#ifndef CURS_H_INCLUDED
#define CURS_H_INCLUDED

#include "evaluare.h"


unsigned int citire_numar()
{
    char x[255];
    bool ok;
    do
    {
        ok=true;
        cin>>x;
        if(strspn(x,"0123456789")!=strlen(x))
        {
            cout<<"Ai introdus gresit,introdu din nou numarul\n";
            ok=false;

        }
        else if(x[0]=='0')
        {
            cout<<"Ai introdus numarul gresit, introdu din nou\n";
            ok=false;

        }

    }
    while(ok==false);

    unsigned int aux=stoi(x);
    return aux;

};

enum posibilitate_meniu {gresit,oki,inapoi,terminat};

class Curs_subprogram
{
    friend class Cursant;
    friend class Program;
    friend class Program_Finantist;
    friend class Program_Manager;
    friend class Program_man_pro;
    friend class Program_Man_turisti;
    friend class Program_Programator;
    friend class Program_Sofer;


protected:
    bool promovat;
    const string nume;

    virtual ~Curs_subprogram() {};
    virtual void afiseaza()=0;
    virtual int nota_minima()=0;

    string ret_nume()
    {
        return nume;
    }

    Curs_subprogram(string x):nume(x) {};
    virtual int medie()=0;

    virtual bool e_promovat()=0;
    virtual void citire_note()=0;
    virtual posibilitate_meniu schimbare_nota()=0;
    virtual void resetare_note()=0;
};


class Curs: public Curs_subprogram
{
    friend class Program;
    friend class Program_Finantist;
    friend class Program_Manager;
    friend class Program_man_pro;
    friend class Program_Man_turisti;
    friend class Program_Programator;
    friend class Program_Sofer;

protected:


    vector<Evaluare*> lucrari;



    friend class Program;

    Curs(string x):Curs_subprogram(x) {};



    void resetare_note()
    {
        for(unsigned int i=0; i<lucrari.size(); i++)lucrari[i]->setnota(0);


    }

    int nota_minima()
    {
        int minim=11;
        for(unsigned int i=0; i<lucrari.size(); i++)if(lucrari[i]->ret_nota()<minim)minim=lucrari[i]->ret_nota();
        return minim;
    }

    posibilitate_meniu schimbare_nota()
    {
        int aux;
        posibilitate_meniu x;
        do
        {
            x=oki;
            cout<<"Alege testul la care vrei sa schimbi nota:\n";
            for(unsigned int i=0; i<lucrari.size(); i++)cout<<i+1<<'.'<<lucrari[i]->ret_nume()<<'\n';
            cout<<lucrari.size()+1<<".Intoarcere alegere materie\n";
            aux=citire_numar();
            aux--;
            if(aux>(int)lucrari.size()||aux<0)
            {
                cout<<"Nu avem acest test, alege unul nou\n";
                x=gresit;
            }
            else
            {
                if(aux==(int)lucrari.size())return inapoi;

                lucrari[aux]->schimbare_nota();
            }

        }
        while(x==gresit);

        return oki;
    }


    void citire_note()
    {
        cout<<"Acum se citesc notele la materia "<<Curs_subprogram::nume<<'\n';
        for(unsigned int i=0; i<lucrari.size(); i++)lucrari[i]->citire_nota();
        cout<<"S-a terminat citirea notelor la materia "<<Curs_subprogram::nume<<'\n';
    }

    ~Curs()
    {
        for(unsigned int i=0; i<lucrari.size(); i++)
        {
            delete lucrari[i];

        }

    }

    void afiseaza()
    {

        cout<<Curs_subprogram::nume<<"\n";
    }

    bool e_promovat()
    {
        return Curs_subprogram::promovat;


    }

    bool operator==(Curs& x)
    {
        if(nume==x.nume)return true;
        return false;

    };

    bool operator<(Curs& x)
    {
        if(nume<x.nume)return true;
        return false;

    }

};

class Curs_un:public Curs
{
    friend class Program;
    friend class Program_Finantist;
    friend class Program_Manager;
    friend class Program_man_pro;
    friend class Program_Man_turisti;
    friend class Program_Programator;
    friend class Program_Sofer;

protected:
    Curs_un(string x):Curs(x) {};


    int medie()
    {
        vector<int> note;
        for(unsigned int i=0; i<Curs::lucrari.size(); i++)note.push_back(Curs::lucrari[i]->ret_nota());

        sort(note.begin(),note.end());
        note.erase(note.begin());

        int suma=0;
        for(unsigned int i=0; i<note.size(); i++)suma+=note[i];
//return suma/note.size();

        float med=suma/note.size();
        if(med-(int)med>=0.5)med++;
        return (int)med;

    }

};

class Curs_doi:public Curs
{
    friend class Program;
    friend class Program_Finantist;
    friend class Program_Manager;
    friend class Program_man_pro;
    friend class Program_Man_turisti;
    friend class Program_Programator;
    friend class Program_Sofer;

protected:
    Curs_doi(string x):Curs(x) {};


    int medie()
    {
        vector<int> note;
        for(unsigned int i=0; i<Curs::lucrari.size(); i++)note.push_back(Curs::lucrari[i]->ret_nota());

        sort(note.begin(),note.end());
        note.erase(note.begin());
        note.erase(note.end()-1);
        int suma=0;
        for(unsigned int i=0; i<note.size(); i++)suma+=note[i];
//return suma/note.size();
        float med=suma/note.size();
        if(med-(int)med>=0.5)med++;
        return (int)med;

    }


};

class Curs_nul:public Curs
{
    friend class Program;
    friend class Program_Finantist;
    friend class Program_Manager;
    friend class Program_man_pro;
    friend class Program_Man_turisti;
    friend class Program_Programator;
    friend class Program_Sofer;

protected:
    Curs_nul(string x):Curs(x) {};

    int medie()
    {
        vector<int> note;
        for(unsigned int i=0; i<Curs::lucrari.size(); i++)note.push_back(Curs::lucrari[i]->ret_nota());

        sort(note.begin(),note.end());

        int suma=0;
        for(unsigned int i=0; i<note.size(); i++)suma+=note[i];
//return suma/note.size();
        int med=suma/note.size();
        if(med-(int)med>=0.5)med++;
        return (int)med;
    }



};

class Curs_Algebra:public Curs_nul
{
    friend class Program;
    friend class Program_Finantist;
    friend class Program_Manager;
    friend class Program_man_pro;
    friend class Program_Man_turisti;
    friend class Program_Programator;
    friend class Program_Sofer;



    int medie()
    {
        float medie;
        medie=(Curs::lucrari[0]->ret_nota()+Curs::lucrari[1]->ret_nota()+Curs::lucrari[2]->ret_nota())/15;
        medie+=Curs::lucrari[3]->ret_nota()*(4/5);

        int nota=(int)medie;
        if(medie-nota>0.5)nota++;
        return nota;

    }


    Curs_Algebra():Curs_nul("Algebra Matematica")
    {
        Curs::lucrari.push_back(new Evaluare("Lucrare scrisa 1"));
        Curs::lucrari.push_back(new Evaluare("Lucrare scrisa 2"));
        Curs::lucrari.push_back(new Evaluare("Lucrare scrisa 3"));
        Curs::lucrari.push_back(new Evaluare("Examen final"));


    };

};


class Curs_Analiza:public Curs_un
{
    friend class Program;
    friend class Program_Finantist;
    friend class Program_Manager;
    friend class Program_man_pro;
    friend class Program_Man_turisti;
    friend class Program_Programator;
    friend class Program_Sofer;


    Curs_Analiza():Curs_un("Analiza Matematica")
    {
        Curs::lucrari.push_back(new Evaluare("Lucrare scrisa 1"));
        Curs::lucrari.push_back(new Evaluare("Lucrare scrisa 2"));
        Curs::lucrari.push_back(new Evaluare("Lucrare scrisa 3"));
        Curs::lucrari.push_back(new Evaluare("Lucrare scrisa 4"));
        Curs::lucrari.push_back(new Evaluare("Lucrare scrisa 5"));


    };

};


class Curs_Geometrie:public Curs_doi
{
    friend class Program;
    friend class Program_Finantist;
    friend class Program_Manager;
    friend class Program_man_pro;
    friend class Program_Man_turisti;
    friend class Program_Programator;
    friend class Program_Sofer;



    Curs_Geometrie():Curs_doi("Geometrie")
    {
        Curs::lucrari.push_back(new Evaluare("Lucrare scrisa 1"));
        Curs::lucrari.push_back(new Evaluare("Lucrare scrisa 2"));
        Curs::lucrari.push_back(new Evaluare("Lucrare scrisa 3"));
        Curs::lucrari.push_back(new Evaluare("Examen oral"));


    };
};


class Curs_Financiar:public Curs_nul
{
    friend class Program;
    friend class Program_Finantist;
    friend class Program_Manager;
    friend class Program_man_pro;
    friend class Program_Man_turisti;
    friend class Program_Programator;
    friend class Program_Sofer;



    Curs_Financiar():Curs_nul("Financiar")
    {
        Curs::lucrari.push_back(new Evaluare("Lucrare scrisa 1"));
        Curs::lucrari.push_back(new Evaluare("Lucrare scrisa 2"));
        Curs::lucrari.push_back(new Evaluare("Lucrare scrisa 3"));
        Curs::lucrari.push_back(new Evaluare("Lucrare scrisa 4"));
        Curs::lucrari.push_back(new Evaluare("Practica"));

    };
};


class Curs_HR:public Curs_un
{
    friend class Program;
    friend class Program_Finantist;
    friend class Program_Manager;
    friend class Program_man_pro;
    friend class Program_Man_turisti;
    friend class Program_Programator;
    friend class Program_Sofer;


    Curs_HR():Curs_un("Resurse umane")
    {
        Curs::lucrari.push_back(new Evaluare("Lucrare scrisa 1"));
        Curs::lucrari.push_back(new Evaluare("Lucrare scrisa 2"));
        Curs::lucrari.push_back(new Evaluare("Lucrare scrisa 3"));
        Curs::lucrari.push_back(new Evaluare("Lucrare scrisa 4"));
        Curs::lucrari.push_back(new Evaluare("Practica"));

    };
};

class Curs_Engleza:public Curs_doi
{
    friend class Program;
    friend class Program_Finantist;
    friend class Program_Manager;
    friend class Program_man_pro;
    friend class Program_Man_turisti;
    friend class Program_Programator;
    friend class Program_Sofer;


    Curs_Engleza():Curs_doi("Engleza")
    {
        Curs::lucrari.push_back(new Evaluare("Lucrare scrisa 1"));
        Curs::lucrari.push_back(new Evaluare("Lucrare orala 1"));
        Curs::lucrari.push_back(new Evaluare("Lucrare scrisa 2"));
        Curs::lucrari.push_back(new Evaluare("Lucrare orala 2"));
        Curs::lucrari.push_back(new Evaluare("Examen scris si oral"));

    };


};


class Curs_Programare:public Curs_nul
{
    friend class Program;
    friend class Program_Finantist;
    friend class Program_Manager;
    friend class Program_man_pro;
    friend class Program_Man_turisti;
    friend class Program_Programator;
    friend class Program_Sofer;


    Curs_Programare():Curs_nul("Programare")
    {
        Curs::lucrari.push_back(new Evaluare("Lucrare scrisa 1"));
        Curs::lucrari.push_back(new Evaluare("Lucrare laborator 1"));
        Curs::lucrari.push_back(new Evaluare("Lucrare laborator 2"));
        Curs::lucrari.push_back(new Evaluare("Lucrare scrisa 2"));
        Curs::lucrari.push_back(new Evaluare("Examen laborator"));


    };

};


class Curs_ComNLP:public Curs_un
{
    friend class Program;
    friend class Program_Finantist;
    friend class Program_Manager;
    friend class Program_man_pro;
    friend class Program_Man_turisti;
    friend class Program_Programator;
    friend class Program_Sofer;


    Curs_ComNLP():Curs_un("Comunicare NLP")
    {
        Curs::lucrari.push_back(new Evaluare("Lucrare orala 1"));
        Curs::lucrari.push_back(new Evaluare("Lucrare orala 2"));
        Curs::lucrari.push_back(new Evaluare("Lucrare orala 3"));
        Curs::lucrari.push_back(new Evaluare("Lucrare orala 4"));
        Curs::lucrari.push_back(new Evaluare("Lucrare orala 5"));

    };

    int medie()
    {
        int suma=0;
        for(unsigned int i=0; i<Curs::lucrari.size()-1; i++)suma+=Curs::lucrari[i]->ret_nota();

        if(suma/Curs::lucrari.size()<5)return 1;
        float med=lucrari[lucrari.size()-1]->ret_nota();
        if(med-(int)med>=0.5)med++;
        return (int)med;

    }


};


class Curs_LegAuto:public Curs_doi
{
    friend class Program;
    friend class Program_Finantist;
    friend class Program_Manager;
    friend class Program_man_pro;
    friend class Program_Man_turisti;
    friend class Program_Programator;
    friend class Program_Sofer;


    Curs_LegAuto():Curs_doi("Legislatie Auto")
    {
        Curs::lucrari.push_back(new Evaluare("Lucrare scrisa 1"));
        Curs::lucrari.push_back(new Evaluare("Lucrare practica 1"));
        Curs::lucrari.push_back(new Evaluare("Lucrare scrisa 2"));
        Curs::lucrari.push_back(new Evaluare("Lucrare practica 2"));
        Curs::lucrari.push_back(new Evaluare("Examen practic"));

    };

};


class Curs_Sofat_Practic:public Curs_nul
{
    friend class Program;
    friend class Program_Finantist;
    friend class Program_Manager;
    friend class Program_man_pro;
    friend class Program_Man_turisti;
    friend class Program_Programator;
    friend class Program_Sofer;



    Curs_Sofat_Practic():Curs_nul("Sofat Practic")
    {
        Curs::lucrari.push_back(new Evaluare("Lucrare practica 1"));
        Curs::lucrari.push_back(new Evaluare("Lucrare practica 2"));
        Curs::lucrari.push_back(new Evaluare("Lucrare practica 3"));
        Curs::lucrari.push_back(new Evaluare("Lucrare practica 4"));
        Curs::lucrari.push_back(new Evaluare("Lucrare practica 5"));

    };

};


class Curs_Turca:public Curs_un
{
    friend class Program;
    friend class Program_Finantist;
    friend class Program_Manager;
    friend class Program_man_pro;
    friend class Program_Man_turisti;
    friend class Program_Programator;
    friend class Program_Sofer;



    Curs_Turca():Curs_un("Turca")
    {
        Curs::lucrari.push_back(new Evaluare("Lucrare scrisa 1"));
        Curs::lucrari.push_back(new Evaluare("Lucrare orala 1"));
        Curs::lucrari.push_back(new Evaluare("Lucrare scrisa 2"));
        Curs::lucrari.push_back(new Evaluare("Lucrare orala 2"));
        Curs::lucrari.push_back(new Evaluare("Examen scris si oral"));

    };

};



#endif // CURS_H_INCLUDED
