#include <bits/stdc++.h>
#include "Graf.h"
#include "Arbore.h"
#include "Complet.h"
#include "Exceptii.h"
using namespace std;
int main()
{
    try
    {
        int n;
        cin>>n;
        if(n<=0)
            throw Exception("Valoarea trebuie sa fie macar 1");
        vector  <Arbore> obiecte_arbore;
        vector <Graf> obiecte_graf;
        vector <Graf_Complet> obiecte_graf_complet;
        for(int i=0;i<n;i++)
        {
            string nume;
            cout<<"Dati tipul regiunii: ";
            cin>>nume;
            if(nume!="ARBORE" && nume!="GRAF" && nume!= "GRAF_COMPLET")
                throw Exception("Ati introdus o regiune neexistenta");
            if(nume=="ARBORE")
            {
                Arbore a;
                cin>>a;
                obiecte_arbore.push_back(a);
            }
            else if(nume=="GRAF")
            {
                Graf g;
                cin >> g;
                obiecte_graf.push_back(g);
            }
            else if(nume=="GRAF_COMPLET")
            {
                Graf_Complet g;
                cin >> g;
                obiecte_graf_complet.push_back(g);
            }
        }
        for(unsigned i=0;i<obiecte_graf.size();++i)
            {
                cout<<obiecte_graf[i]<<"\n";
                cout<<"Distanta de la orasul 1 la orasul 3 este "<<obiecte_graf[i].dist(1,3)<<" km\n\n";
            }
        for(unsigned i=0;i<obiecte_arbore.size();++i)
            {
                cout<<obiecte_arbore[i]<<"\n";
                cout<<"Distanta de la orasul 1 la orasul 3 este "<<obiecte_arbore[i].dist(1,3)<<" km\n\n";
            }
        for(unsigned i=0;i<obiecte_graf_complet.size();++i)
            {
                cout<<obiecte_graf_complet[i]<<"\n";
                cout<<"Distanta de la orasul 1 la orasul 3 este "<<obiecte_graf_complet[i].dist(1,3)<<" km\n\n";
            }
    }
    catch(Exception &exception)
    {
        cout << "A aparut o exceptie : (" << exception.what() << ")\n";
    }
    catch(std::exception &exception)
    {
        cout << "Alta exceptie din clasa std::exception a aparut (" << exception.what() << ")\n";
    }
    return 0;
}
