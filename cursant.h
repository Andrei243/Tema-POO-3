#ifndef CURSANT_H_INCLUDED
#define CURSANT_H_INCLUDED
#include "program.h"

enum prog {finantist,manager,programator,manager_programatori,sofer,manager_turist };

class Cursant
{
    friend class Clasa;

    const string nume;

    vector<Curs_subprogram*> cursuri_urmate;
    vector<Program*> programe_urmate;
    vector<Competenta*> competente_luate;
    bool poate_reface_programul;

    nivel ret_niv()
    {

        if(competente_luate.size()==0)return netrecut;
        else if(competente_luate[0]->ret_niv()=="Nivel mic")return mic;
        else if(competente_luate[0]->ret_niv()=="Nivel mediu")return mediu;
        else return mare;


    }

    bool este_peste(nivel x)
    {
        if(ret_niv()>=x)return true;
        return false;
    }

    void resetare_note()
    {
        for(unsigned int i=0; i<cursuri_urmate.size(); i++)cursuri_urmate[i]->resetare_note();
        citire_note();

        if(!competente_luate.empty())
        {
            delete competente_luate[0];
            competente_luate.pop_back();
        }
        generare_competenta();

    }

    bool afisare_nota_finalasicompetenta()
    {
        if(competente_luate.size()==0)
        {
            cout<<"Cursantul "<<nume<<" nu a reusit sa obtina competenta, avand nota finala "<<programe_urmate[0]->medie()<<"\n";
            if(!programe_urmate[0]->este_schimbabil())
            {
                poate_reface_programul=false;
                cout<<"Acesta nu mai poate reface cursul\n";
                return false;

            }
            else return true;
        }
        else
        {
            cout<<"Cursantul "<<nume << " a promovat programul "<<competente_luate[0]->ret_nume()<<" cu "<<competente_luate[0]->ret_niv()<<" si nota finala "<<programe_urmate[0]->medie()<<"\n";
            return true;

        }

    }

    void generare_competenta()
    {

        if(competente_luate.size()==0)
        {
            Competenta* aux=programe_urmate[0]->generare_competenta();
            if(aux!=NULL)competente_luate.push_back(aux);

        }

    }

    string ret_nume()
    {
        return nume;
    }

    Cursant(string x):nume(x),poate_reface_programul(true) {};
    int nr_prog()
    {
        return programe_urmate.size();
    }

    posibilitate_meniu schimbare_nota()
    {
        posibilitate_meniu x=oki;
        int aux;
        do
        {
            x=oki;
            cout<<"Alege cursul la care vrei sa schimbi nota studentului "<<nume<<'\n';
            for(unsigned int i=0; i<cursuri_urmate.size(); i++)cout<<i+1<<'.'<<cursuri_urmate[i]->ret_nume()<<'\n';
            cout<<cursuri_urmate.size()+1<<".Inapoi la alegere actiune\n";
            aux=citire_numar();
            aux--;
            if(aux>(int)cursuri_urmate.size()||aux<0)
            {
                cout<<"Ai ales gresit, alege din nou cursul\n";


            }
            else
            {

                if(aux==(int)cursuri_urmate.size())return inapoi;
                x=cursuri_urmate[aux]->schimbare_nota();

            }
        }
        while(x!=oki);

        return oki;
    }

    void citire_note()
    {
        cout<<"Se citesc acum notele cursantului "<<nume<<"\n\n";
        for(unsigned int i=0; i<cursuri_urmate.size(); i++)cursuri_urmate[i]->citire_note();
        cout<<"S-a terminat citirea notelor cursantului "<<nume<<"\n\n";
    }

    void afiseaza()
    {
        for(unsigned int i=0; i<cursuri_urmate.size(); i++)cursuri_urmate[i]->afiseaza();

    }


    void aplica(int x)
    {
        switch(x)
        {

        case finantist:
        {
            bool ok=true;
            for(unsigned int i=0; i<programe_urmate.size(); i++)if(programe_urmate[i]->ret_nume()=="Finantist")ok=false;
            if(ok)programe_urmate.push_back(new Program_Finantist(cursuri_urmate));
            break;
        }

        case manager:
        {
            bool ok=true;
            for(unsigned int i=0; i<programe_urmate.size(); i++)if(programe_urmate[i]->ret_nume()=="Manager")ok=false;
            if(ok)programe_urmate.push_back(new Program_Manager(cursuri_urmate));
            break;
        }

        case programator:
        {
            bool ok=true;
            for(unsigned int i=0; i<programe_urmate.size(); i++)if(programe_urmate[i]->ret_nume()=="Programator")ok=false;

            if(ok)programe_urmate.push_back(new Program_Programator(cursuri_urmate));
            break;
        }

        case manager_programatori:
        {
            bool ok=true;
            for(unsigned int i=0; i<programe_urmate.size(); i++)if(programe_urmate[i]->ret_nume()=="Manager programator")ok=false;
            if(ok)programe_urmate.push_back(new Program_man_pro(cursuri_urmate));
            break;
        }

        case sofer:
        {
            bool ok=true;
            for(unsigned int i=0; i<programe_urmate.size(); i++)if(programe_urmate[i]->ret_nume()=="Sofer")ok=false;
            if(ok)programe_urmate.push_back(new Program_Sofer(cursuri_urmate));
            break;
        }

        case manager_turist:
        {
            bool ok=true;
            for(unsigned int i=0; i<programe_urmate.size(); i++)if(programe_urmate[i]->ret_nume()=="Manager turisti")ok=false;
            if(ok)programe_urmate.push_back(new Program_Man_turisti(cursuri_urmate));
            break;
        }




        }


    }
    ~Cursant()
    {
        for(unsigned int i=0; i<cursuri_urmate.size(); i++)delete cursuri_urmate[i];

        for(unsigned int i=0; i<programe_urmate.size(); i++)delete programe_urmate[i];

        for(unsigned int i=0; i<competente_luate.size(); i++)delete competente_luate[i];


    }
};



#endif // CURSANT_H_INCLUDED
