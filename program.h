#ifndef PROGRAM_H_INCLUDED
#define PROGRAM_H_INCLUDED
#include "curs.h"
#include "competenta.h"

enum nivel {netrecut,mic,mediu,mare};


class Program:public Curs_subprogram
{
    friend class Cursant;
protected:

    vector<Curs_subprogram*> cursuri_necesare;
    Program(string x):Curs_subprogram(x),schimbabil(true) {};
    bool schimbabil;



    void resetare_note()
    {
        for(unsigned int i=0; i<cursuri_necesare.size(); i++)cursuri_necesare[i]->resetare_note();

    }

    bool este_schimbabil()
    {
        return schimbabil;

    }

    void poate_fi_schimbat()
    {
        if(nota_minima()>=3)
        {
            schimbabil=true;

        }
        else schimbabil=false;

    }


    Competenta* generare_competenta()
    {
        poate_fi_schimbat();
        if(nota_minima()<5)return NULL;
        else
        {
            int med=medie();
            if(med<5)return NULL;
            else if(med<=6)return new Competenta(nume,"Nivel mic");
            else if(med<=8)return new Competenta(nume,"Nivel mediu");
            else if(med<=10)return new Competenta(nume,"Nivel Mare");

        }

        return NULL;
    }



    int nota_minima()
    {
        int minim=11;
        for(unsigned int i=0; i<cursuri_necesare.size(); i++)if(cursuri_necesare[i]->nota_minima()<minim)minim=cursuri_necesare[i]->nota_minima();

        return minim;
    }

    int medie()
    {
        float suma=0;

        for(unsigned int i=0; i<cursuri_necesare.size(); i++)suma+=cursuri_necesare[i]->medie();

        int med=suma/cursuri_necesare.size();
        if(med-(int)med>=0.5)med++;
        return (int)med;

    }

    posibilitate_meniu schimbare_nota()
    {
        cout<<"Alegeti cursul sau subprogramul la care vreti sa schimbati nota:\n";
        int aux;
        posibilitate_meniu x;
        do
        {
            x=oki;
            for(unsigned int i=0; i<cursuri_necesare.size(); i++)cout<<i<<'.'<<cursuri_necesare[i]->ret_nume();
            cout<<cursuri_necesare.size()+1<<".Inapoi\n";
            aux=citire_numar();
            aux--;
            if(aux>(int)cursuri_necesare.size()||aux<0)
            {
                cout<<"Nu avem acest curs, alege unul nou\n";

            }
            else
            {

                if(aux==(int)cursuri_necesare.size())return inapoi;
                x=cursuri_necesare[aux]->schimbare_nota();


            }



        }
        while(x!=oki);

        return x;

    }

    void citire_note()
    {
        cout<<"Se citesc notele din programul "<<nume<<" :\n";
        for(unsigned int i=0; i<cursuri_necesare.size(); i++)cursuri_necesare[i]->citire_note();
        cout<<"S-a terminat citirea notelor pentru programul "<<nume<<'\n';

    }


    void afiseaza()
    {

        cout<<"In programul: "<<nume<<":\n";
        for(unsigned int i=0; i<cursuri_necesare.size(); i++)cursuri_necesare[i]->afiseaza();
    }
    bool operator==(Program& x)
    {
        if(nume==x.nume)return true;
        return false;

    };

    bool e_promovat()
    {

        if(Curs_subprogram::promovat==true)return true;
        else
        {
            bool ok=true;
            for(unsigned int i=0; i<cursuri_necesare.size(); i++)if(cursuri_necesare[i]->e_promovat()==false)ok=false;
            if(ok)Curs_subprogram::promovat=true;
            return false;
        }


    }

};

//contine algebra, financiar
class Program_Finantist: public Program
{

    friend class Cursant;


    Program_Finantist(vector<Curs_subprogram*>&x):Program("Finantist")
    {
        bool ok=true;
        for(unsigned int i=0; i<x.size(); i++)
        {
            if(x[i]->ret_nume()=="Algebra")
            {
                ok=false;
                Program::cursuri_necesare.push_back(x[i]);
                break;
            }

        }

        if(ok)
        {
            Program::cursuri_necesare.push_back(new Curs_Algebra());
            x.push_back(cursuri_necesare[cursuri_necesare.size()-1]);
        }
        ok=true;
        for(unsigned int i=0; i<x.size(); i++)
        {
            if(x[i]->ret_nume()=="Financiar")
            {
                ok=false;
                Program::cursuri_necesare.push_back(x[i]);
                break;
            }

        }
        if(ok)
        {
            Program::cursuri_necesare.push_back(new Curs_Financiar());
            x.push_back(Program::cursuri_necesare[Program::cursuri_necesare.size()-1]);
        }
    }




};

//contine  resurse_umane,financiar si engleza
class Program_Manager: public Program
{

    friend class Program_man_pro;
    friend class Program_Man_turisti;
    friend class Cursant;


    Program_Manager(vector<Curs_subprogram*>&x):Program("Manager")
    {
        bool ok=true;
        for(unsigned int i=0; i<x.size(); i++)
        {
            if(x[i]->ret_nume()=="Resurse umane")
            {
                ok=false;
                Program::cursuri_necesare.push_back(x[i]);
                break;
            }

        }

        if(ok)
        {
            Program::cursuri_necesare.push_back(new Curs_HR());
            x.push_back(Program::cursuri_necesare[Program::cursuri_necesare.size()-1]);

        }
        ok=true;
        for(unsigned int i=0; i<x.size(); i++)
        {
            if(x[i]->ret_nume()=="Financiar")
            {
                ok=false;
                Program::cursuri_necesare.push_back(x[i]);
                break;
            }

        }
        if(ok)
        {
            Program::cursuri_necesare.push_back(new Curs_Financiar());
            x.push_back(Program::cursuri_necesare[Program::cursuri_necesare.size()-1]);

        }

        ok=true;
        for(unsigned int i=0; i<x.size(); i++)
        {
            if(x[i]->ret_nume()=="Engleza")
            {
                ok=false;
                Program::cursuri_necesare.push_back(x[i]);
                break;
            }

        }
        if(ok)
        {
            Program::cursuri_necesare.push_back(new Curs_Engleza());
            x.push_back(Program::cursuri_necesare[Program::cursuri_necesare.size()-1]);

        }
    }

};

//contine toate matematicile(algebra,analiza,geometrie),programare si engleza
class Program_Programator: public Program
{
    friend class Cursant;

    Program_Programator(vector<Curs_subprogram*>&x):Program("Programator")
    {
        bool ok=true;
        for(unsigned int i=0; i<x.size(); i++)
        {
            if(x[i]->ret_nume()=="Algebra")
            {
                ok=false;
                Program::cursuri_necesare.push_back(x[i]);
                break;
            }

        }

        if(ok)
        {
            Program::cursuri_necesare.push_back(new Curs_Algebra());
            x.push_back(Program::cursuri_necesare[Program::cursuri_necesare.size()-1]);

        }

        ok=true;
        for(unsigned int i=0; i<x.size(); i++)
        {
            if(x[i]->ret_nume()=="Analiza")
            {
                ok=false;
                Program::cursuri_necesare.push_back(x[i]);
                break;
            }

        }
        if(ok)
        {
            Program::cursuri_necesare.push_back(new Curs_Analiza());
            x.push_back(Program::cursuri_necesare[Program::cursuri_necesare.size()-1]);

        }

        ok=true;
        for(unsigned int i=0; i<x.size(); i++)
        {
            if(x[i]->ret_nume()=="Geometrie")
            {
                ok=false;
                Program::cursuri_necesare.push_back(x[i]);
                break;
            }

        }
        if(ok)
        {
            Program::cursuri_necesare.push_back(new Curs_Geometrie());
            x.push_back(Program::cursuri_necesare[Program::cursuri_necesare.size()-1]);

        }

        ok=true;


        for(unsigned int i=0; i<x.size(); i++)
        {


            if(x[i]->ret_nume()=="Programare")
            {
                ok=false;
                Program::cursuri_necesare.push_back(x[i]);
                break;
            }

        }
        if(ok)
        {
            Program::cursuri_necesare.push_back(new Curs_Programare());
            x.push_back(Program::cursuri_necesare[Program::cursuri_necesare.size()-1]);

        }

        ok=true;
        for(unsigned int i=0; i<x.size(); i++)
        {
            if(x[i]->ret_nume()=="Engleza")
            {
                ok=false;
                Program::cursuri_necesare.push_back(x[i]);
                break;
            }

        }
        if(ok)
        {
            Program::cursuri_necesare.push_back(new Curs_Engleza());
            x.push_back(Program::cursuri_necesare[Program::cursuri_necesare.size()-1]);

        }
    }
};


//contine Manager, programare si comunicare nlp
class Program_man_pro: public Program
{
    friend class Cursant;



    ~Program_man_pro()
    {
        delete cursuri_necesare[0];

    }

    int medie()
    {
        float suma=0;
        suma+=cursuri_necesare[0]->medie()*3;
        suma+=cursuri_necesare[1]->medie();
        suma+=cursuri_necesare[2]->medie();

//return suma/5;
        int med=suma/5;
        if(med-(int)med>=0.5)med++;
        return (int)med;
    }


    Program_man_pro(vector<Curs_subprogram*> &x):Program("Manager programator")
    {

        Program::cursuri_necesare.push_back(new Program_Manager(x));

        bool ok=true;
        for(unsigned int i=0; i<x.size(); i++)
        {
            if(x[i]->ret_nume()=="Programare")
            {
                ok=false;
                Program::cursuri_necesare.push_back(x[i]);
                break;
            }

        }
        if(ok)
        {
            Program::cursuri_necesare.push_back(new Curs_Programare());
            x.push_back(Program::cursuri_necesare[Program::cursuri_necesare.size()-1]);

        }

        ok=true;
        for(unsigned int i=0; i<x.size(); i++)
        {
            if(x[i]->ret_nume()=="Comunicare NLP")
            {
                ok=false;
                Program::cursuri_necesare.push_back(x[i]);
                break;
            }

        }
        if(ok)
        {
            Program::cursuri_necesare.push_back(new Curs_ComNLP());
            x.push_back(Program::cursuri_necesare[Program::cursuri_necesare.size()-1]);

        }

    }

};


//contine legislatie auto, sofat auto practic
class Program_Sofer: public Program
{
    friend class Cursant;

    Program_Sofer(vector<Curs_subprogram*>&x):Program("Sofer")
    {
        bool ok=true;
        for(unsigned int i=0; i<x.size(); i++)
        {
            if(x[i]->ret_nume()=="Legislatie Auto")
            {
                ok=false;
                Program::cursuri_necesare.push_back(x[i]);
                break;
            }

        }

        if(ok)
        {
            Program::cursuri_necesare.push_back(new Curs_LegAuto());
            x.push_back(Program::cursuri_necesare[Program::cursuri_necesare.size()-1]);

        }

        ok=true;
        for(unsigned int i=0; i<x.size(); i++)
        {
            if(x[i]->ret_nume()=="Sofat Practic")
            {
                ok=false;
                Program::cursuri_necesare.push_back(x[i]);
                break;
            }

        }
        if(ok)
        {
            Program::cursuri_necesare.push_back(new Curs_Sofat_Practic());
            x.push_back(Program::cursuri_necesare[Program::cursuri_necesare.size()-1]);

        }
    }

};


//contine turca, Manager si legislatie auto
class Program_Man_turisti: public Program
{
    friend class Cursant;

    ~Program_Man_turisti()
    {
        delete cursuri_necesare[0];

    }

    int medie()
    {
        float suma=0;
        suma+=cursuri_necesare[0]->medie();
        suma+=cursuri_necesare[1]->medie()*3;
        suma+=cursuri_necesare[2]->medie();

//return suma/5;
        int med=suma/5;
        if(med-(int)med>=0.5)med++;
        return (int)med;

    }

    Program_Man_turisti(vector<Curs_subprogram*>&x):Program("Manager turisti")
    {




        Program::cursuri_necesare.push_back(new Program_Manager(x));

        bool ok=true;
        for(unsigned int i=0; i<x.size(); i++)
        {
            if(x[i]->ret_nume()=="Turca")
            {
                ok=false;
                Program::cursuri_necesare.push_back(x[i]);
                break;
            }

        }
        if(ok)
        {
            Program::cursuri_necesare.push_back(new Curs_Turca());
            x.push_back(Program::cursuri_necesare[Program::cursuri_necesare.size()-1]);

        }

        ok=true;
        for(unsigned int i=0; i<x.size(); i++)
        {
            if(x[i]->ret_nume()=="Legislatie Auto")
            {
                ok=false;
                Program::cursuri_necesare.push_back(x[i]);
                break;
            }

        }

        if(ok)
        {
            Program::cursuri_necesare.push_back(new Curs_LegAuto());
            x.push_back(Program::cursuri_necesare[Program::cursuri_necesare.size()-1]);

        }


    }
};

#endif // PROGRAM_H_INCLUDED
