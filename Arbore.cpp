#include "Arbore.h"
#include <bits/stdc++.h>
#include "Exceptii.h"
using namespace std;
Arbore::Arbore()
{
    nr_orase=0;
    radacina=0;
    nr_strazi=0;
    coordonate_orase={};
    oras_distanta={};
}
Arbore::Arbore(int cop_nr_orase=0,int cop_nrstrazi=0,int cop_radacina=0,vector<pair<double, double>> cop_coordonate_orase={},
            vector<vector<pair<int, double>>> cop_oras_distanta={}):
    Graf(cop_nr_orase,cop_coordonate_orase,cop_oras_distanta),nr_strazi(cop_nrstrazi),radacina(cop_radacina){}
Arbore::~Arbore()
{
    radacina=0;
    nr_strazi=0;
}
Arbore::Arbore (const Arbore &arbore)
    {
        this->nr_orase=arbore.nr_orase;
        this->nr_strazi=arbore.nr_strazi;
        this->radacina=arbore.radacina;
        this->coordonate_orase=arbore.coordonate_orase;
        this->oras_distanta=arbore.oras_distanta;
    }
Arbore &Arbore::operator=(const Arbore &arbore)
    {
        if(this!=&arbore)
        {
            this->nr_orase=arbore.nr_orase;
            this->nr_strazi=arbore.nr_strazi;
            this->radacina=arbore.radacina;
            this->coordonate_orase=arbore.coordonate_orase;
            this->oras_distanta=arbore.oras_distanta;
        }
        return *this;
    }
int Arbore::getRadacina()
    {
        return radacina;
    }
int Arbore::getNrStrazi()
{
    return nr_strazi;
}
 void Arbore::setRadacina()
    {
        cout<<"Un arbore poate avea orice nod ca radacina.\nCiteste nodul pe care il doresti ca radacina: ";
        cin>>radacina;
        if(radacina>nr_orase||radacina<1)
            throw Exception("Radacina nu poate avea indicele mai mare decat numarul de orase");
    }
double Arbore::dist(int orasA,int orasB)
    {
        cout<<"S-a apelat distanta din clasa Arbore"<<"\n";
        if(oras_distanta.size()==0)
            throw Exception("Nu au fost citite inca orase");
        int st=1,dr=1;
        int lungime=oras_distanta.size()-1;
        if(orasA>lungime || orasA<1 || orasB>lungime || orasB<1)
            throw Exception("Orasul A si orasul B trebuie sa aiba index intre 1 si nr de orase existente");
        int coada[lungime+1];
        coada[st]=orasA;
        int viz[lungime+1];
        double d[lungime+1];
        for(int i=1;i<=lungime;++i)
            {
                viz[i]=0;
                if(i==orasA)
                    d[i]=0;
                else
                    d[i]=oo;
            }
        viz[orasA]=1;
        while(st<=dr)
        {
            int nod=coada[st];
            for(unsigned i=0;i<oras_distanta[nod].size();++i)
                {
                    int j=oras_distanta[nod][i].first;
                    if(viz[j]==0)
                    {
                    if(d[j]>d[nod]+oras_distanta[nod][i].second)
                        d[j]=d[nod]+oras_distanta[nod][i].second;
                    dr++;
                    coada[dr]=j;
                    viz[j]=1;
                    }
                }
            st++;
        }
        return d[orasB];
    }
istream& operator>>(istream &in, Arbore &arbore)   ///operator de citire pt Arbore
{
    if(arbore.oras_distanta.size()!=0)
        arbore.oras_distanta={};
    if(arbore.coordonate_orase.size()!=0)
        arbore.coordonate_orase={};
    cout<<"Ati ales regiunea de baza ARBORE\n";
    cout<<"Dati numarul de orase: ";
    in>>arbore.nr_orase;
    if(arbore.nr_orase<=0)
        throw Exception("Ati introdus un numar de orase mai mic decat 1");
    arbore.oras_distanta.resize(arbore.nr_orase+1);
    cout<<"Dati coordonatele fiecarul oras\n";
    double xOras,yOras;
    for(int i=1;i<=arbore.nr_orase;++i)
    {
        cout<<"Orasul "<<i<<" are coordonatele: ";
        in>>xOras>>yOras;
        for(unsigned j=0;j<arbore.coordonate_orase.size();++j)
            if(arbore.coordonate_orase[j].first==xOras && arbore.coordonate_orase[j].second==yOras)
                throw Exception("Doua orase nu pot avea aceleasi coordonate");
        arbore.coordonate_orase.push_back(make_pair(xOras,yOras));
    }
    cout<<"Nu mai trebuie sa dati numarul de strazi, deoarece fiind arbore este numarul de orase-1,adica : ";
    cout<<arbore.nr_orase-1<<"\n";
    arbore.nr_strazi=arbore.nr_orase-1;
    cout<<"Dati orasele intre care exista o strada:\n";
    int orasA,orasB;
    double dist=0,cdist;
    for(int i=1;i<=arbore.nr_strazi;++i)
    {
        in>>orasA>>orasB;
        if(orasA==orasB)
            throw Exception("Nu poate exista o strada intre un oras si el insusi");
        if(orasA>arbore.nr_orase||orasA<=0||orasB>arbore.nr_orase||orasB<=0)
            throw Exception("Ati introdus orasul in limitele gresite");
        dist=(arbore.coordonate_orase[orasB-1].first-arbore.coordonate_orase[orasA-1].first);
        dist=dist*dist;
        cdist=(arbore.coordonate_orase[orasB-1].second-arbore.coordonate_orase[orasA-1].second);
        cdist=cdist*cdist;
        dist=sqrt(dist+cdist);
        arbore.oras_distanta[orasA].emplace_back(orasB,dist);
        arbore.oras_distanta[orasB].emplace_back(orasA,dist);
    }
    cout<<"\n";
    return in;
}
ostream& operator<< (ostream &out, Arbore &a)   ///operator de afisare pt Arbore
{
    out<<"Regiunea aleasa este de tip ARBORE\n";
    out<<"Numarul de orase este: "<<a.nr_orase<<"\n";
    out<<"Numarul de strazi este: "<<a.nr_strazi<<"\n";
    if(a.nr_strazi==0)
        throw Exception("Nu avem nicio strada");
    for(int i=1;i<=a.nr_orase;++i)
    {
        out<<"Orasul "<<i<<" are drum direct cu urmatoarele orase: ";
        for(unsigned j=0;j<a.oras_distanta[i].size();++j)
            out<<"Orasul "<<a.oras_distanta[i][j].first<<" aflat la distanta "<<a.oras_distanta[i][j].second<<"km | ";
        out<<"\n";
    }
    return out;
}
