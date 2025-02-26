#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

const int stari_max = 101;
const int simboluri_max = 26;

int main()
{
    ifstream fin("test.in");
    int n, m, i, x, y, stare_initiala, k;
    bool tranzitii[stari_max][simboluri_max][stari_max] = {false};

    fin >> n;
    int stari[stari_max];
    
    for (i = 0; i < n; i++)
    {
        fin >> stari[i];
    }

    fin >> m;
    
    for (i = 0; i < m; i++)
    {
        char c;
        fin >> x >> y >> c;
        tranzitii[x][c - 'a'][y] = true;
    }

    fin >> stare_initiala;

    fin >> k;
    int stari_f[stari_max];
    
    for (i = 0; i < k; i++)
    {
        fin >> stari_f[i];
    }

    fin >> k;
    for (i = 0; i < k; i++)
    {
        char cuvant[101];
        fin >> cuvant;

        int stare_curenta = stare_initiala;

        for (int j = 0; j < strlen(cuvant); j++)
        {
            int urmatoarea_stare = -1;
            
            for (int s = 0; s < n; s++)
            {
                if (tranzitii[stare_curenta][cuvant[j] - 'a'][stari[s]])
                {
                    urmatoarea_stare = stari[s];
                    break;
                }
            }
            
            if (urmatoarea_stare == -1)
            {
                stare_curenta = -1;
                break;
            }
            stare_curenta = urmatoarea_stare;
        }

        bool acceptat = false;
        
        for (int s = 0; s < k; s++)
        {
            if (stare_curenta == stari_f[s])
            {
                acceptat = true;
                break;
            }
        }

        if (acceptat)
            cout << "DA" << endl;
        else
            cout << "NU" << endl;
    }

    fin.close();
    return 0;
}



