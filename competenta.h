#ifndef COMPETENTA_H_INCLUDED
#define COMPETENTA_H_INCLUDED




class Competenta
{
    friend class Cursant;
    const string  nume;
    const string nivel;

    friend class Program;

    Competenta(string x,string y):nume(x),nivel(y) {};

    string ret_nume()
    {
        return nume;
    };
    string ret_niv()
    {
        return nivel;
    };

};


#endif // COMPETENTA_H_INCLUDED
