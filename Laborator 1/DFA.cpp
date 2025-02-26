#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main() 
{
    ifstream fin("test.in");
    int n, m, i, stari[101], x, y, stari_f[101], stare_initiala, k;
    char c, tranzitii[101][101], cuvant[101];

    fin >> n;
    
    for (i = 1; i <= n; i++)
        fin >> stari[i];
    
    fin >> m;
    
    for (i = 1; i <= m; i++)
    {
        fin >> x >> y >> c;
        tranzitii[x][y] = c;
    }
    
    fin >> stare_initiala;
    fin >> k;
    
    for (i = 1; i <= k; i++)
        fin >> stari_f[i];
    
    fin >> k;
    
    for (i = 1; i <= k; i++)
    {
        fin >> cuvant;
        int stare_curenta = stare_initiala;
        int ok = 1;
        
        for (int j = 0; j < strlen(cuvant); j++)
        {
            int gasit = 0;
            
            for (int l = 1; l <= n; l++)
            {
                if (tranzitii[stare_curenta][l] == cuvant[j])
                {
                    stare_curenta = l;
                    gasit = 1;
                    break;
                }
            }
            
            if (gasit == 0)
            {
                ok = 0;
                break;
            }
        }
        
        if (ok)
        {
            int acceptat = 0;
            
            for (int j = 1; j <= k; j++)
            {
                if (stare_curenta == stari_f[j])
                {
                    acceptat = 1;
                    break;
                }
            }
            
            if (acceptat)
                cout << "DA" << endl;
            else
                cout << "NU" << endl;
        }
        
        else
        {
            cout << "NU" << endl;
        }
    }
    fin.close();
    return 0;
}
