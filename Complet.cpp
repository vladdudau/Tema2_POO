#include <bits/stdc++.h>
#include "Graf.h"
#include "Arbore.h"
#include "Complet.h"
#include "Exceptii.h"
using namespace std;
Graf_Complet::Graf_Complet()
{
    nr_orase=0;
    coordonate_orase={};
    oras_distanta={};
    nr_strazi=0;
}
Graf_Complet::Graf_Complet(int cop_nr_orase=0,int cop_nr_strazi=0,vector<pair<double, double>> cop_coordonate_orase={},
                 vector<vector<pair<int, double>>> cop_oras_distanta={}):
        Graf(cop_nr_orase,cop_coordonate_orase,cop_oras_distanta),nr_strazi(cop_nr_strazi){}
Graf_Complet::~Graf_Complet()
{
    nr_strazi=0;
}
Graf_Complet::Graf_Complet(const Graf_Complet &g)
    {
        this->nr_orase=g.nr_orase;
        this->nr_strazi=g.nr_strazi;
        this->coordonate_orase=g.coordonate_orase;
        this->oras_distanta=g.oras_distanta;
    }
Graf_Complet &Graf_Complet::operator=(const Graf_Complet &g)
    {
        if(this!=&g)
        {
            this->nr_orase=g.nr_orase;
            this->nr_strazi=g.nr_strazi;
            this->coordonate_orase=g.coordonate_orase;
            this->oras_distanta=g.oras_distanta;
        }
        return *this;
    }
double Graf_Complet::dist(int orasA,int orasB)
    {
        cout<<"S-a apelat distanta din clasa Graf_Complet"<<"\n";
        if(oras_distanta.size()==0)
            throw Exception("Orasul A si orasul B trebuie sa aiba index intre 1 si nr de orase existente");
        int lungime=oras_distanta.size()-1;
        if(orasA>lungime || orasA<1 || orasB>lungime || orasB<1)
            throw Exception("Orasul A si orasul B trebuie sa aiba index intre 1 si nr de orase existente");
        for(unsigned j=0;j<oras_distanta[orasA].size();++j)
            if(oras_distanta[orasA][j].first==orasB)
                return oras_distanta[orasA][j].second;
        throw Exception("Nu a fost gasita o strada");
    }
int Graf_Complet::getNrStrazi()
    {
        return nr_strazi;
    }
istream& operator>>(istream &in, Graf_Complet &g)       ///Op de citire pt Graf_Complet
{
    if(g.oras_distanta.size()!=0)
        g.oras_distanta={};
    if(g.coordonate_orase.size()!=0)
        g.coordonate_orase={};
    cout<<"Ati ales regiunea de baza GRAF COMPLET\n";
    cout<<"Dati numarul de orase: ";
    in>>g.nr_orase;
    if(g.nr_orase<=0)
        throw Exception("Ati introdus un numar de orase mai mic decat 1");
    g.oras_distanta.resize(g.nr_orase+1);
    cout<<"Dati coordonatele fiecarul oras\n";
    double xOras,yOras;
    for(int i=1;i<=g.nr_orase;++i)
    {
        cout<<"Orasul "<<i<<" are coordonatele: ";
        in>>xOras>>yOras;
        for(unsigned j=0;j<g.coordonate_orase.size();++j)
            if(g.coordonate_orase[j].first==xOras && g.coordonate_orase[j].second==yOras)
                throw Exception("Doua orase nu pot avea aceleasi coordonate");
        g.coordonate_orase.push_back(make_pair(xOras,yOras));
    }
    cout<<"Nu mai trebuie sa dati numarul de strazi, deoarece fiind GRAF COMPLET este ";
    cout<<"(nr_orase*(nr_orase-1))/2 adica: ";
    g.nr_strazi=(g.nr_orase*(g.nr_orase-1))/2;
    cout<<g.nr_strazi<<"\n";
    cout<<"Dati orasele intre care exista o strada:\n";
    int orasA,orasB;
    double dist=0,cdist;
    for(int i=1;i<=g.nr_strazi;++i)
    {
        in>>orasA>>orasB;
        if(orasA==orasB)
            throw Exception("Nu poate exista o strada intre un oras si el insusi");
        if(orasA>g.nr_orase||orasA<=0||orasB>g.nr_orase||orasB<=0)
            throw Exception("Ati introdus orasul in limitele gresite");
        dist=(g.coordonate_orase[orasB-1].first-g.coordonate_orase[orasA-1].first);
        dist=dist*dist;
        cdist=(g.coordonate_orase[orasB-1].second-g.coordonate_orase[orasA-1].second);
        cdist=cdist*cdist;
        dist=sqrt(dist+cdist);
        g.oras_distanta[orasA].emplace_back(orasB,dist);
        g.oras_distanta[orasB].emplace_back(orasA,dist);
    }
    cout<<"\n";
    return in;
}
ostream& operator<<(ostream &out, Graf_Complet &g)
{
    out<<"Regiunea aleasa este de tip GRAF COMPLET\n";
    out<<"Numarul de orase este: "<<g.nr_orase<<"\n";
    out<<"Numarul de strazi este: "<<g.nr_strazi<<"\n";
    if(g.nr_strazi==0)
        throw Exception("Nu exista strazi");
    for(int i=1;i<=g.nr_orase;++i)
    {
        out<<"Orasul "<<i<<" are drum direct cu urmatoarele orase: ";
        for(unsigned j=0;j<g.oras_distanta[i].size();++j)
            out<<"Orasul "<<g.oras_distanta[i][j].first<<" aflat la distanta "<<g.oras_distanta[i][j].second<<"km | ";
        out<<"\n";
    }
    return out;
}
