#ifndef CLASA_H_INCLUDED
#define CLASA_H_INCLUDED
#include "cursant.h"


class Clasa
{

protected:
    vector<Cursant*> cursanti;
    vector<Cursant*> cursanti_care_pot_reface_cursurile;
    unsigned int nr_studenti;



    Cursant* alegecursant_ref()
    {
        if(cursanti_care_pot_reface_cursurile.size()==0)
        {
            cout<<"\nNimeni nu poate reface cursul\n\n";
            return NULL;
        }
        int aux;
        posibilitate_meniu x;
        do
        {
            x=oki;
            for(unsigned int i=0; i<cursanti_care_pot_reface_cursurile.size(); i++)cout<<i+1<<'.'<<cursanti_care_pot_reface_cursurile[i]->ret_nume()<<'\n';
            cout<<cursanti_care_pot_reface_cursurile.size()+1<<".Inapoi\n\n";
            aux=citire_numar();
            aux--;
            if(aux<0||aux>(int)cursanti_care_pot_reface_cursurile.size())
            {
                cout<<"\nAi ales gresit, alege din nou\n\n";
                x=gresit;
            }
            else if(aux==(int)cursanti_care_pot_reface_cursurile.size())
            {
                return NULL;

            }
            else
            {
                return cursanti_care_pot_reface_cursurile[aux];

            }

        }
        while(x==gresit);

        return NULL;

    }

    Cursant* alegecursant()
    {
        if(cursanti.size()==0)
        {
            cout<<"\nInca nu ai introdus cursanti\n\n";
            return NULL;

        }
        int aux;
        posibilitate_meniu x;
        do
        {
            x=oki;
            for(unsigned int i=0; i<cursanti.size(); i++)cout<<i+1<<'.'<<cursanti[i]->ret_nume()<<'\n';
            cout<<cursanti.size()+1<<".Inapoi\n\n";
            aux=citire_numar();
            aux--;
            if(aux<0||aux>(int)cursanti.size())
            {
                cout<<"\nAi ales gresit, alege din nou\n\n";
                x=gresit;
            }
            else if(aux==(int)cursanti.size())
            {
                return NULL;

            }
            else
            {
                return cursanti[aux];

            }

        }
        while(x==gresit);

        return NULL;
    }

public:

~Clasa(){
for(unsigned int i=0;i<cursanti.size();i++){
delete cursanti[i];

}

}

    unsigned int exista_cu()
    {
        return cursanti_care_pot_reface_cursurile.size();
    }

    unsigned int nr_cursanti()
    {
        return cursanti.size();
    }

    posibilitate_meniu reset_curs()
    {
        if(exista_cu()==0)
        {
            cout<<"\nNu exista cursanti care isi pot reface programul\n\n";
            return inapoi;

        }
        Cursant* aux=alegecursant_ref();
        if(aux==NULL)return inapoi;
        for(unsigned int i=0; i<cursanti_care_pot_reface_cursurile.size(); i++)
        {
            if(aux==cursanti_care_pot_reface_cursurile[i])
            {
                cursanti_care_pot_reface_cursurile.erase(cursanti_care_pot_reface_cursurile.begin()+i);
            }
        }

        aux->resetare_note();
        return oki;
    }


    posibilitate_meniu afis_com()
    {
        nivel y;
        posibilitate_meniu x;
        unsigned int aux;
        do
        {
            x=oki;
            cout<<"\nAlege nivelul la care vrei sa te raportezi:\n\n";
            cout<<"\n1.Nivel mic\n2.Nivel mediu\n3.Nivel mare\n4.Inapoi\n\n";
            aux=citire_numar();

            if(aux==1)
            {
                y=mic;

            }
            else if(aux==2)
            {
                y=mediu;
            }
            else if(aux==3)
            {
                y=mare;

            }
            else if(aux==4)
            {
                return inapoi;
            }
            else
            {
                cout<<"\nAi ales un numar gresit\n\n";
                x=gresit;

            }

        }
        while(x!=oki);

        for(unsigned int i=0; i<cursanti.size(); i++)
        {
            if(cursanti[i]->este_peste(y))cout<<cursanti[i]->ret_nume()<<'\n';

        }

        return oki;


    }




    void generare_com()
    {
        for(unsigned int i=0; i<cursanti.size(); i++)cursanti[i]->generare_competenta();

    }


    Clasa(unsigned int x):nr_studenti(x) {};
    void afisare_finsicom()
    {
        bool ok;
        for(unsigned int i=0; i<cursanti.size(); i++)
        {
            ok=cursanti[i]->afisare_nota_finalasicompetenta();
            if(ok)cursanti_care_pot_reface_cursurile.push_back(cursanti[i]);
        }

    }


    void afiseaza_cursanti()
    {
        if(cursanti.size()==0)cout<<"\nInca nu ai introdus cursanti\n\n";
        for(unsigned int i=0; i<cursanti.size(); i++)cout<<"Cursantul numarul "<<i+1<<" este " <<cursanti[i]->ret_nume()<<'\n';
        cout<<'\n';

    }
    void aplica(prog x)
    {

        for(unsigned int i=0; i<cursanti.size(); i++)cursanti[i]->aplica(x);



    }



    void citire_note()
    {

        for(unsigned int i=0; i<cursanti.size(); i++)cursanti[i]->citire_note();


    }

    posibilitate_meniu schimbare_nota()
    {
        Cursant* aux=alegecursant();
        if(aux==NULL)return inapoi;
        else
        {
            aux->schimbare_nota();
            return oki;
        }


    }


    posibilitate_meniu eliminare_student()
    {

        int aux;
        posibilitate_meniu x;
        do
        {
            cout<<"\nAlege studentul:\n\n";
            x=oki;
            for(unsigned int i=0; i<cursanti.size(); i++)cout<<i+1<<'.'<<cursanti[i]->ret_nume()<<"\n";
            cout<<cursanti.size()+1<<".Inapoi\n\n";
            aux=citire_numar();
            aux--;
            if(aux>(int)cursanti.size())
            {

                cout<<"\nAi ales gresit\n\n";
                x=gresit;
            }

            if(aux==(int)cursanti.size())return inapoi;
            else
            {
                delete cursanti[aux];
                cursanti.erase(cursanti.begin()+aux);

            }

        }
        while(x==gresit);


        return oki;
    }

    posibilitate_meniu adaugare_student()
    {

        posibilitate_meniu x=oki;
        if(cursanti.size()>=nr_studenti)
        {
            int aux;
            do
            {
                cout<<"\nS-a atins capacitatea maxima a clasei, alegeti o actiune din urmatoarele:\n1.Sterge un student din clasa\n2.Inapoi\n\n";
                aux=citire_numar();
                if(aux==1)
                {
                    x=eliminare_student();

                }
                if(aux==2)
                {
                    return inapoi;

                }
                if(aux!=1&&aux!=2)
                {
                    x=gresit;

                    cout<<"\nAi gresit actiunea\n\n";
                }

            }
            while(x!= oki);

        }

        cout<<"\nIntroduceti numele complet al noului elev:\n";
        char nume_de_familie[255];
        strcpy(nume_de_familie,"");
        cout<<"\nIntroduceti numele de familie fara spatii:\n\n";
        cin>>nume_de_familie;
        char prenume[255];
        strcpy(prenume,"");
        cout<<"\nIntroduceti prenumele fara spatii:\n\n";
        cin>>prenume;
        char nume_complet[512];
        strcpy(nume_complet,"");
        strcat(nume_complet,nume_de_familie);
        strcat(nume_complet,"  ");
        strcat(nume_complet,prenume);
        string nume(nume_complet);


        cursanti.push_back(new Cursant(nume_complet));




        return oki;
    }
};

#endif // CLASA_H_INCLUDED
