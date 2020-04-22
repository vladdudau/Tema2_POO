#ifndef ARBORE_H_INCLUDED
#define ARBORE_H_INCLUDED
#include <bits/stdc++.h>
#include "Graf.h"
#include "Exceptii.h"
using namespace std;
class Arbore:public Graf
{
protected:
    int nr_strazi;
    int radacina;
public:
    Arbore();
    Arbore(int cop_nr_orase,int cop_nrstrazi,int cop_radacina,vector<pair<double, double>> cop_coordonate_orase,
        vector<vector<pair<int, double>>> cop_oras_distanta);
    ~Arbore();
    Arbore (const Arbore &arbore);
    Arbore& operator=(const Arbore &arbore);
    friend istream& operator>> (istream &in, Arbore &arbore);
    friend ostream& operator<< (ostream &out, Arbore &arbore);
    int getRadacina();
    int getNrStrazi();
    void setRadacina();
    virtual double dist(int orasA,int orasB);
};


#endif // ARBORE_H_INCLUDED
