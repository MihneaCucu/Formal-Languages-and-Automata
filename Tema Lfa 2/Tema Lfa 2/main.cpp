/*#include <cstdio>
#include <fstream>
#include <iostream>
#include <bitset>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <set>
#define stari_nfa_max 10
#define alfabet_max 10
using namespace std;

class stareNFA
{
    public:
        int tranzitii[alfabet_max][stari_nfa_max];
    stareNFA()
        {
            for (int i = 0; i < alfabet_max; i++)
                for (int j = 0; j < stari_nfa_max; j++)
                    tranzitii[i][j] = -1;
        }
}*stariNFA;

struct stareDFA
{
        bool stare_finala;
        bitset<stari_nfa_max> stariNFAconstituente;
        bitset<stari_nfa_max> tranzitii[alfabet_max];
        int tranzitii_simbolice[alfabet_max];
};

void inchidere_lambda(int stare, bitset<stari_nfa_max> &inchidere, int N)
{
    for (int i = 0; i < N && stariNFA[stare].tranzitii[0][i] != -1; i++)
        if (inchidere[stariNFA[stare].tranzitii[0][i]] == 0)
        {
            inchidere[stariNFA[stare].tranzitii[0][i]] = 1;
            inchidere_lambda(stariNFA[stare].tranzitii[0][i], inchidere, N);
        }
}

void inchidere_lambda(bitset<stari_nfa_max> stare,
        bitset<stari_nfa_max> &inchidere, int N)
{
    for (int i = 0; i < N; i++)
        if (stare[i] == 1)
            inchidere_lambda(i, inchidere, N);
}

void NFAmove(int X, int A, bitset<stari_nfa_max> &Y, int N)
{
    for (int i = 0; i < N && stariNFA[X].tranzitii[A][i] != -1; i++)
        Y[stariNFA[X].tranzitii[A][i]] = 1;
}

void NFAmove(bitset<stari_nfa_max> X, int A, bitset<stari_nfa_max> &Y, int N)
{
    for (int i = 0; i < N; i++)
        if (X[i] == 1)
            NFAmove(i, A, Y, N);
}
int main()
{   set<int> NFAstari_finale = {};
    vector<int> DFAstari_finale = {};
    vector<stareDFA*> stariDFA = {};
    queue<int> DFAstari_incomplete = {};
    int N, M;
    int i, j, X, Y, A, T, F, D;
    ifstream fin("NFA.txt");
    fin >> N >> M;
    stariNFA = new stareNFA[N];
    fin >> F;
    for (i = 0; i < F; i++)
    {
        fin >> X;
        NFAstari_finale.insert(X);
    }
    fin >> T;
    while (T--)
    {
        fin >> X >> A >> Y;
        for (i = 0; i < Y; i++)
        {
            fin >> j;
            stariNFA[X].tranzitii[A][i] = j;
        }
    }
    fin.close();
    D = 1;
    stariDFA.push_back(new stareDFA);
    stariDFA[0]->stariNFAconstituente[0] = 1;
    inchidere_lambda(0, stariDFA[0]->stariNFAconstituente, N);
    for (j = 0; j < N; j++)
        if (stariDFA[0]->stariNFAconstituente[j] == 1 && NFAstari_finale.find(
                j) != NFAstari_finale.end())
        {
            stariDFA[0]->stare_finala = true;
            DFAstari_finale.push_back(0);
            break;
        }
    DFAstari_incomplete.push(0);
    while (!DFAstari_incomplete.empty())
    {
        X = DFAstari_incomplete.front();
        DFAstari_incomplete.pop();
        for (i = 1; i <= M; i++)
        {
            NFAmove(stariDFA[X]->stariNFAconstituente, i,
                    stariDFA[X]->tranzitii[i], N);
            inchidere_lambda(stariDFA[X]->tranzitii[i],
                              stariDFA[X]->tranzitii[i], N);
            for (j = 0; j < D; j++)
                if (stariDFA[X]->tranzitii[i]
                        == stariDFA[j]->stariNFAconstituente)
                {
                    stariDFA[X]->tranzitii_simbolice[i] = j;
                    break;
                }
            if (j == D)
            {
                stariDFA[X]->tranzitii_simbolice[i] = D;
                stariDFA.push_back(new stareDFA);
                stariDFA[D]->stariNFAconstituente
                        = stariDFA[X]->tranzitii[i];
                for (j = 0; j < N; j++)
                    if (stariDFA[D]->stariNFAconstituente[j] == 1
                            && NFAstari_finale.find(j) != NFAstari_finale.end())
                    {
                        stariDFA[D]->stare_finala = true;
                        DFAstari_finale.push_back(D);
                        break;
                    }
                DFAstari_incomplete.push(D);
                D++;
            }
        }
    }
    ofstream fout("DFA.txt");
    fout << D << " " << M << "\n" << DFAstari_finale.size();
    for (vector<int>::iterator it = DFAstari_finale.begin(); it
            != DFAstari_finale.end(); it++)
        fout << " " << *it;
    fout << "\n";
    for (i = 0; i < D; i++)
    {
        for (j = 1; j <= M; j++)
            fout << i << " " << j << " "
                    << stariDFA[i]->tranzitii_simbolice[j] << "\n";
    }
    fout.close();
    return 0;
}

*/
