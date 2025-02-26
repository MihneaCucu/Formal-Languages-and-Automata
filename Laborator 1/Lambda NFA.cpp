#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

const int stari_max = 101;
const int simboluri_max = 27;

bool tranzitii[stari_max][simboluri_max][stari_max] = {false};

void adauga_tranzitie(int x, int y, char c)
{
    if(c == '*')
    {
        tranzitii[x][simboluri_max - 1][y] = true;
        
    }
    else
    {
        tranzitii[x][c - 'a'][y] = true;
    }
}

void inchidere_lambda(bool inchidere[], int stare)
{
    if (inchidere[stare]) return;
    inchidere[stare] = true;
    
    for (int i = 0; i < stari_max; ++i)
    {
        if (tranzitii[stare][simboluri_max - 1][i])
        {
            inchidere_lambda(inchidere, i);
        }
    }
}

void copiaza_stare(bool destinatie[], const bool sursa[])
{
    for (int i = 0; i < stari_max; ++i)
    {
        destinatie[i] = sursa[i];
    }
}

int main() {
    ifstream fin("test.in");
    int n, m, i, x, y, stare_initiala, k;
    
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
        adauga_tranzitie(x, y, c);
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

        bool stare_curenta[stari_max] = {false};
        inchidere_lambda(stare_curenta, stare_initiala);

        for (int j = 0; j < strlen(cuvant); j++)
        {
            bool urmatoarea_stare[stari_max] = {false};
            for (int stare = 0; stare < stari_max; stare++)
            {
                if (stare_curenta[stare])
                {
                    for (int s = 0; s < n; s++)
                    {
                        if (tranzitii[stare][cuvant[j] - 'a'][stari[s]])
                        {
                            inchidere_lambda(urmatoarea_stare, stari[s]);
                        }
                    }
                }
            }
            copiaza_stare(stare_curenta, urmatoarea_stare);
        }

        bool acceptat = false;
        
        for (int stare = 0; stare < stari_max; stare++)
        {
            if (stare_curenta[stare])
            {
                for (int s = 0; s < k; s++)
                {
                    if (stare == stari_f[s])
                    {
                        acceptat = true;
                        break;
                    }
                }
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

