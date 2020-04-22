#include "Graf.h"
#include <bits/stdc++.h>
#include "Exceptii.h"
using namespace std;
Graf::Graf()
{
    nr_orase=0;
    coordonate_orase={};
    oras_distanta={};
}
Graf::Graf(int cop_nr_orase=0,vector<pair<double, double>> cop_coordonate_orase={},
                vector<vector<pair<int, double>>> cop_oras_distanta={}):
    nr_orase(cop_nr_orase),coordonate_orase(cop_coordonate_orase),oras_distanta(cop_oras_distanta){}
Graf::~Graf()
{
    nr_orase=0;
    coordonate_orase.clear();
    oras_distanta.clear();
}
Graf::Graf(const Graf &graf)
    {
        this->nr_orase=graf.nr_orase;
        this->coordonate_orase=graf.coordonate_orase;
        this->oras_distanta=graf.oras_distanta;
    }
Graf &Graf::operator = (const Graf &graf)
    {
        if(this!=&graf)
        {
            this->nr_orase=graf.nr_orase;
            this->coordonate_orase=graf.coordonate_orase;
            this->oras_distanta=graf.oras_distanta;
        }
        return *this;
    }
int Graf::getNrOrase()
{
    return nr_orase;
}
void Graf::setNrOrase(int x)
{
    if(x<=0)
        throw Exception("Orasul trebuie sa fie mai mare decat 0");
    nr_orase=x;
}
double Graf::dist(int orasA,int orasB)
    {
        cout<<"S-a apelat distanta GRAF"<<"\n";
        if(oras_distanta.size()==0)
            throw Exception("Nu au fost citite inca orase");
        priority_queue <pair<double,int> > Coada_Prioritati;
        int lungime=oras_distanta.size()-1;
        if(orasA>lungime || orasA<1 || orasB>lungime || orasB<1)
            throw Exception("Orasul A si orasul B trebuie sa aiba index intre 1 si nr de orase existente");
        double solutie[lungime+1];
        for(int i=1;i<=lungime;i++)
        {
            if(i!=orasA)
                solutie[i]=oo;
            else
                solutie[i]=0;
        }
        Coada_Prioritati.push({0,orasA});
        while(Coada_Prioritati.empty()==false)
        {
            int oras=Coada_Prioritati.top().second;
            Coada_Prioritati.pop();
            for(unsigned i=0; i<oras_distanta[oras].size();i++)
            {
                int j=oras_distanta[oras][i].first;
                double distanta = oras_distanta[oras][i].second;
                if(solutie[j]>distanta+solutie[oras])
                {
                     solutie[j]=distanta+solutie[oras];
                     Coada_Prioritati.push({-solutie[j],j});
                }
            }
        }
        if(solutie[orasB]!=oo)
            return solutie[orasB];
        throw Exception("Nu exista un drum posibil intre orasele cerute");
    }
istream& operator>>(istream &in, Graf &graf)     ///operator de citire pt Graf
{
    if(graf.oras_distanta.size()!=0)
        graf.oras_distanta={};
    if(graf.coordonate_orase.size()!=0)
        graf.coordonate_orase={};
    cout<<"Ati ales regiunea de baza GRAF\n";
    cout<<"Dati numarul de orase: ";
    in>>graf.nr_orase;
    if(graf.nr_orase<=0)
        throw Exception("Ati introdus un numar de orase mai mic decat 1");
    graf.oras_distanta.resize(graf.nr_orase+1);
    cout<<"Dati coordonatele fiecarul oras\n";
    double xOras,yOras;
    for(int i=1;i<=graf.nr_orase;++i)
    {
        cout<<"Orasul "<<i<<" are coordonatele: ";
        in>>xOras>>yOras;
        for(unsigned j=0;j<graf.coordonate_orase.size();++j)
            if(graf.coordonate_orase[j].first==xOras && graf.coordonate_orase[j].second==yOras)
                throw Exception("Doua orase nu pot avea aceleasi coordonate");
        graf.coordonate_orase.push_back(make_pair(xOras,yOras));
    }
    cout<<"Dati numarul de strazi: ";
    int nr_strazi=0;
    in>>nr_strazi;
    if(nr_strazi==0)
        throw Exception("Nu sunt strazi");
    cout<<"Dati orasele intre care exista o strada:\n";
    int orasA,orasB;
    double dist=0,cdist;
    for(int i=1;i<=nr_strazi;++i)
    {
        in>>orasA>>orasB;
        if(orasA==orasB)
            throw Exception("Nu poate exista o strada intre un oras si el insusi");
        if(orasA>graf.nr_orase||orasA<=0||orasB>graf.nr_orase||orasB<=0)
            throw Exception("Ati introdus orasul in limitele gresite");
        dist=(graf.coordonate_orase[orasB-1].first-graf.coordonate_orase[orasA-1].first);
        dist=dist*dist;
        cdist=(graf.coordonate_orase[orasB-1].second-graf.coordonate_orase[orasA-1].second);
        cdist=cdist*cdist;
        dist=sqrt(dist+cdist);
        graf.oras_distanta[orasA].emplace_back(orasB,dist);
        graf.oras_distanta[orasB].emplace_back(orasA,dist);
    }
    cout<<"\n";
    return in;
}
ostream& operator<< (ostream &out, Graf &g)    ///operator de afisare pt Graf
{
    out<<"Regiunea aleasa este de tip GRAF\n";
    out<<"Numarul de orase este: "<<g.nr_orase<<"\n";
    if(g.oras_distanta.size()==0)
        throw Exception("Nu exista strazi");
    for(int i=1;i<=g.nr_orase;++i)
    {
        if(g.oras_distanta[i].size()==0)
            out<<"Orasul "<<i<<" nu are drum direct cu niciun oras";
        else
        {
            out<<"Orasul "<<i<<" are drum direct cu urmatoarele orase: ";
            for(unsigned j=0;j<g.oras_distanta[i].size();++j)
                out<<"Orasul "<<g.oras_distanta[i][j].first<<" aflat la distanta "<<g.oras_distanta[i][j].second<<"km | ";
        }
        out<<"\n";
    }
    return out;
}
int Graf::getLungime()
{
    return oras_distanta.size();
}
