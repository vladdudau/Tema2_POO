#ifndef COMPLET_H_INCLUDED
#define COMPLET_H_INCLUDED
#include "Graf.h"
#include "Arbore.h"
#include <bits/stdc++.h>
#include "Exceptii.h"
using namespace std;
class Graf_Complet:public Graf
{
protected:
    int nr_strazi;
public:
    Graf_Complet();
    Graf_Complet(int cop_nr_orase,int cop_nr_strazi,vector<pair<double, double>> cop_coordonate_orase,
                 vector<vector<pair<int, double>>> cop_oras_distanta);
    ~Graf_Complet();
    Graf_Complet(const Graf_Complet &g);
    Graf_Complet& operator=(const Graf_Complet &g);
    virtual double dist(int orasA,int orasB);
    int getNrStrazi();
    friend istream& operator>>(istream &in,Graf_Complet &g);
    friend ostream& operator<<(ostream &out,Graf_Complet &g);
};


#endif // COMPLET_H_INCLUDED
