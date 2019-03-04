#include <iostream>
#include "Clasa.h"




int main()
{


    int nr_maxim_studenti;
    posibilitate_meniu x=oki;
    cout<<"Numarul maxim de studenti este:\n";
    do
    {
        nr_maxim_studenti=citire_numar();
        if(nr_maxim_studenti<=0)cout<<"Ai introdus un numar invalid de elevi, introdu din nou numarul maxim de elevi:\n";
    }
    while(nr_maxim_studenti<=0);
    Clasa clasa((unsigned int)nr_maxim_studenti);
    int aux;
    do
    {
        x=oki;
        cout<<"Alege actiunea:\n";
        cout<<"1.Adauga student inainte de incepere program\n";
        cout<<"2.Afiseaza toti elevii\n";
        cout<<"3.Terminare\n\n";
        aux=citire_numar();

        if(aux==1)x=clasa.adaugare_student();
        if(aux==2)clasa.afiseaza_cursanti();
        if(aux==3)
        {

            if(clasa.nr_cursanti()>0)x=terminat;
            else
            {
                x=gresit;
                cout<<"Nu poti sa incepi un program fara elevi\n\n";


            }
        }


    }
    while(x!=terminat);
    cout<<"S-a terminat citirea studentilor, acum alege programul care vrei sa fie urmat:\n";

    do
    {
        x=oki;
        cout<<"Acestea sunt programele disponibile:\n";
        cout<<"1.Finatist\n";
        cout<<"2.Manager\n";
        cout<<"3.Programator\n";
        cout<<"4.Manager Programatori\n";
        cout<<"5.Sofer\n";
        cout<<"6.Manager turisti\n\n";
        aux=citire_numar();
        aux--;
        if(aux<0||aux>5)
        {
            cout<<"Ai ales un numar gresit, te rugam reintrodu numarul cursului\n";
            x=gresit;

        }
        else
        {
            cout<<aux<<"\n";
            clasa.aplica((prog)aux);
        }


    }
    while(x==gresit);

    cout<<"Ai terminat alegerea programului, urmeaza citirea initiala a tuturor notelor\n\n\n";

    clasa.citire_note();
    int ales;
    do
    {
        x=oki;
        cout<<"Vrei sa mai schimbi o nota?\n";
        cout<<"1.DA\n2.NU\n\n";
        ales=citire_numar();
        if(ales!=1&&ales!=2)
        {
            cout<<"Ai gresit alegerea\n";
            x=gresit;
        }

        if(ales==2)x=terminat;
        if(ales==1)x=clasa.schimbare_nota();

    }
    while(x!=terminat);
    clasa.generare_com();
    clasa.afisare_finsicom();
    if(clasa.exista_cu())
    {

        do
        {
            x=oki;
            if(clasa.exista_cu())
            {


                cout<<"Alege actiunea\n";
                cout<<"1.Reseteaza notele unui elev\n";
                cout<<"2.Afiseaza toti elevii care au competenta peste un anumit nivel\n";
                cout<<"3.Terminare program si afisare lista finala elevi\n\n";
                int aux=citire_numar();

                if(aux==1)
                {
                    x=clasa.reset_curs();
                }
                else if(aux==2)
                {
                    x=clasa.afis_com();

                }
                else if(aux==3)
                {
                    x=terminat;

                }
                else
                {
                    cout<<"Nu ai ales bine\n";
                    x=gresit;

                }

            }
            else
            {
                cout<<"Alege actiunea\n";
                cout<<"1.Afiseaza toti elevii care au competenta peste un anumit nivel\n";
                cout<<"2.Terminare program si afisare lista finala elevi\n\n";
                int aux=citire_numar();

                if(aux==1)
                {
                    x=clasa.afis_com();
                }
                else if(aux==2)
                {
                    x=terminat;

                }
                else
                {
                    cout<<"Nu ai ales bine\n\n";
                    x=gresit;
                }


            }

        }
        while(x!=terminat);

        clasa.afisare_finsicom();

    }
    return 0;

}




