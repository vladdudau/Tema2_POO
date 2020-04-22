#ifndef GRAF_H_INCLUDED
#define GRAF_H_INCLUDED
#include <bits/stdc++.h>
#include "Exceptii.h"
class Graf
{
protected:
    int nr_orase;
    vector<pair<double, double>> coordonate_orase;
    vector<vector<pair<int, double>>> oras_distanta;
public:
    Graf();
    Graf(int cop_nr_orase,vector<pair<double, double>> cop_coordonate_orase,vector<vector<pair<int, double>>> cop_oras_distanta);
    ~Graf();
    Graf(const Graf &graf);
    Graf& operator = (const Graf &graf);
    virtual double dist(int orasA,int orasB);
    friend istream& operator>>(istream &in, Graf &g);
    friend ostream& operator<<(ostream &out, Graf &g);
    int getNrOrase();
    void setNrOrase(int x);
    int getLungime();
};
#endif // GRAF_H_INCLUDED
