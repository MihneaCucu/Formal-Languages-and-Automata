#include <cstdio>
#include <fstream>
#include <iostream>
#include <bitset>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <set>
#define MAX_NFA_STATES 10
#define MAX_ALPHABET_SIZE 10
using namespace std;
// Representation of an NFA state
class NFAstate
{
    public:
        int transitions[MAX_ALPHABET_SIZE][MAX_NFA_STATES];
        NFAstate()
        {
            for (int i = 0; i < MAX_ALPHABET_SIZE; i++)
                for (int j = 0; j < MAX_NFA_STATES; j++)
                    transitions[i][j] = -1;
        }
}*NFAstates;
// Representation of a DFA state
struct DFAstate
{
        bool finalState;
        bitset<MAX_NFA_STATES> constituentNFAstates;
        bitset<MAX_NFA_STATES> transitions[MAX_ALPHABET_SIZE];
        int symbolicTransitions[MAX_ALPHABET_SIZE];
};
 // N -> No. of stattes, M -> Size of input alphabet
// finds the epsilon closure of the NFA state "state" and stores it into "closure"
void epsilonClosure(int state, bitset<MAX_NFA_STATES> &closure, int N)
{
    for (int i = 0; i < N && NFAstates[state].transitions[0][i] != -1; i++)
        if (closure[NFAstates[state].transitions[0][i]] == 0)
        {
            closure[NFAstates[state].transitions[0][i]] = 1;
            epsilonClosure(NFAstates[state].transitions[0][i], closure, N);
        }
}
// finds the epsilon closure of a set of NFA states "state" and stores it into "closure"
void epsilonClosure(bitset<MAX_NFA_STATES> state,
        bitset<MAX_NFA_STATES> &closure, int N)
{
    for (int i = 0; i < N; i++)
        if (state[i] == 1)
            epsilonClosure(i, closure, N);
}
// returns a bitset representing the set of states the NFA could be in after moving
// from state X on input symbol A
void NFAmove(int X, int A, bitset<MAX_NFA_STATES> &Y, int N)
{
    for (int i = 0; i < N && NFAstates[X].transitions[A][i] != -1; i++)
        Y[NFAstates[X].transitions[A][i]] = 1;
}
// returns a bitset representing the set of states the NFA could be in after moving
// from the set of states X on input symbol A
void NFAmove(bitset<MAX_NFA_STATES> X, int A, bitset<MAX_NFA_STATES> &Y, int N)
{
    for (int i = 0; i < N; i++)
        if (X[i] == 1)
            NFAmove(i, A, Y, N);
}
int main()
{   set<int> NFA_finalStates = {};
    vector<int> DFA_finalStates = {};
    vector<DFAstate*> DFAstates = {};
    queue<int> incompleteDFAstates = {};
    
    int N, M;
    
    
    int i, j, X, Y, A, T, F, D;
    // read in the underlying NFA
    ifstream fin("NFA.txt");
    fin >> N >> M;
    NFAstates = new NFAstate[N];
    fin >> F;
    for (i = 0; i < F; i++)
    {
        fin >> X;
        NFA_finalStates.insert(X);
    }
    fin >> T;
    while (T--)
    {
        fin >> X >> A >> Y;
        for (i = 0; i < Y; i++)
        {
            fin >> j;
            NFAstates[X].transitions[A][i] = j;
        }
    }
    fin.close();
    // construct the corresponding DFA
    D = 1;
    DFAstates.push_back(new DFAstate);
    DFAstates[0]->constituentNFAstates[0] = 1;
    epsilonClosure(0, DFAstates[0]->constituentNFAstates, N);
    for (j = 0; j < N; j++)
        if (DFAstates[0]->constituentNFAstates[j] == 1 && NFA_finalStates.find(
                j) != NFA_finalStates.end())
        {
            DFAstates[0]->finalState = true;
            DFA_finalStates.push_back(0);
            break;
        }
    incompleteDFAstates.push(0);
    while (!incompleteDFAstates.empty())
    {
        X = incompleteDFAstates.front();
        incompleteDFAstates.pop();
        for (i = 1; i <= M; i++)
        {
            NFAmove(DFAstates[X]->constituentNFAstates, i,
                    DFAstates[X]->transitions[i], N);
            epsilonClosure(DFAstates[X]->transitions[i],
                    DFAstates[X]->transitions[i], N);
            for (j = 0; j < D; j++)
                if (DFAstates[X]->transitions[i]
                        == DFAstates[j]->constituentNFAstates)
                {
                    DFAstates[X]->symbolicTransitions[i] = j;
                    break;
                }
            if (j == D)
            {
                DFAstates[X]->symbolicTransitions[i] = D;
                DFAstates.push_back(new DFAstate);
                DFAstates[D]->constituentNFAstates
                        = DFAstates[X]->transitions[i];
                for (j = 0; j < N; j++)
                    if (DFAstates[D]->constituentNFAstates[j] == 1
                            && NFA_finalStates.find(j) != NFA_finalStates.end())
                    {
                        DFAstates[D]->finalState = true;
                        DFA_finalStates.push_back(D);
                        break;
                    }
                incompleteDFAstates.push(D);
                D++;
            }
        }
    }
    // write out the corresponding DFA
    ofstream fout("DFA.txt");
    fout << D << " " << M << "\n" << DFA_finalStates.size();
    for (vector<int>::iterator it = DFA_finalStates.begin(); it
            != DFA_finalStates.end(); it++)
        fout << " " << *it;
    fout << "\n";
    for (i = 0; i < D; i++)
    {
        for (j = 1; j <= M; j++)
            fout << i << " " << j << " "
                    << DFAstates[i]->symbolicTransitions[j] << "\n";
    }
    fout.close();
    return 0;
}

/**

Analiză pas cu pas a algoritmului:

1. Citirea NFA-ului:
Programul începe prin citirea datelor despre NFA dintr-un fișier de intrare numit "NFA.txt".
Se citește numărul de stări ale NFA-ului (`N`), dimensiunea alfabetului de intrare (`M`), numărul de stări finale (`F`),
stările finale și tranzitiile NFA-ului.

2. Inițializarea DFA-ului:
Se construiește un DFA (automat finit determinist) corespunzător NFA-ului citit.
Se inițializează un vector de obiecte `DFAstate`, fiecare reprezentând o stare a DFA-ului. Se creează starea inițială a DFA-ului,
care este închiderea epsilon a stării inițiale a NFA-ului.

3. Transformarea NFA-ului în DFA: Pentru fiecare stare a DFA-ului care nu a fost încă procesată,
se determină tranzitiile posibile pe fiecare simbol din alfabet. Se calculează închiderea epsilon pentru fiecare stare
rezultată și se adaugă starea corespunzătoare DFA-ului dacă nu există deja.

4. Scrierea DFA-ului în fișier:
După ce toate stările DFA-ului au fost construite, programul scrie DFA-ul rezultat într-un fișier de ieșire numit "DFA.txt".

5. Finalizarea programului: Programul se încheie.


Sinteză a ideii din spatele algoritmului:

- Se pornește de la starea inițială a NFA-ului și se calculează închiderea epsilon,
adică mulțimea tuturor stărilor la care se poate ajunge folosind tranzitii cu epsilon.
- Pentru fiecare simbol din alfabet, se determină stările în care putem ajunge din starea
curentă a DFA-ului și se calculează închiderea epsilon pentru aceste stări.
- Se verifică dacă starea rezultată a fost deja adăugată în DFA; dacă nu, aceasta este adăugată.
- Procesul continuă până când nu mai există stări noi de explorat în DFA.
- La final, se scrie DFA-ul rezultat într-un fișier de ieșire.

Acest algoritm demonstrează o modalitate eficientă de a transforma un NFA într-un DFA, permițând o reprezentare mai simplă
și o execuție mai rapidă a operațiilor de căutare și verificare.




Acest program implementează un algoritm pentru transformarea unui NFA într-un DFA folosind
închiderea epsilon și explorarea tranzitiilor în DFA.
Explicarea fiecarei parti a codului și ce face fiecare subprogram:

1. Declararea și inițializarea structurilor și variabilelor:
La începutul programului, se declara și se inițializează variabilele și structurile necesare.
Acestea includ:
   - `NFAstate`: o clasă care reprezintă o stare a unui NFA. Are o matrice `transitions` care stochează tranzitiile
   către alte stări pe baza simbolurilor din alfabet. Constructorul acestei clase inițializează toate tranzitiile la -1.
   - `DFAstate`: o structură care reprezintă o stare a unui DFA. Are câmpurile `finalState`, `constituentNFAstates`,
   `transitions` și `symbolicTransitions`. `finalState` indică dacă starea este finală sau nu, `constituentNFAstates`
    reprezintă stările NFA corespunzătoare stării DFA, `transitions` stochează tranzitiile DFA pe baza alfabetului, iar
    `symbolicTransitions` stochează stările destinație ale tranzitiilor în DFA.
   - `N`, `M`: variabile care rețin numărul de stări și dimensiunea alfabetului din NFA.
   - `NFA_finalStates`: un set care conține stările finale ale NFA-ului.
   - `DFA_finalStates`: un vector care conține stările finale ale DFA-ului.
   - `DFAstates`: un vector de pointeri către structuri `DFAstate` care vor reprezenta stările DFA-ului.
   - `incompleteDFAstates`: o coadă care va stoca stările DFA care încă nu au fost procesate complet.
   
2. Funcția epsilonClosure(int state, bitset<MAX_NFA_STATES> &closure):
    Această funcție calculează închiderea epsilon a unei stări a NFA-ului. Primește ca argumente un număr întreg `state`,
    reprezentând starea pentru care trebuie calculată închiderea epsilon, și o referință la un `bitset` numit `closure`,
    care va stoca închiderea epsilon rezultată.

   - Funcția parcurge tranzitiile stării date cu simbolul epsilon și adaugă toate stările accesibile în `closure`.
   - Acest proces este recursiv, pentru a acoperi toate stările accesibile indirect prin tranzitiile epsilon.
   
3. Funcția `epsilonClosure(bitset<MAX_NFA_STATES> state, bitset<MAX_NFA_STATES> &closure)`:
    Această funcție calculează închiderea epsilon a unui set de stări ale NFA-ului.

   - Primește ca argumente un `bitset` numit `state`, reprezentând setul de stări pentru care trebuie calculată închiderea epsilon,
   și o referință la un `bitset` numit `closure`, care va stoca închiderea epsilon rezultată.
   - Pentru fiecare stare din `state`, se apelează funcția `epsilonClosure(int state, bitset<MAX_NFA_STATES> &closure)`
   pentru a calcula închiderea epsilon a fiecărei stări și se adaugă în `closure`.
   
4. Funcția `NFAmove(int X, int A, bitset<MAX_NFA_STATES> &Y)`:
    Această funcție calculează starea în care se poate ajunge dintr-o anumită stare a NFA pe baza unui simbol din alfabet.

   - Primește ca argumente un număr întreg `X`, reprezentând starea din care trebuie făcută mutarea, un număr întreg `A`,
   reprezentând simbolul din alfabet, și o referință la un `bitset` numit `Y`, care va stoca stările accesibile din starea de plecare.
   - Funcția parcurge tranzitiile stării `X` cu simbolul `A` și adaugă stările accesibile în `Y`.
   
5. Funcția `NFAmove(bitset<MAX_NFA_STATES> X, int A, bitset<MAX_NFA_STATES> &Y)`:
    Această funcție calculează stările în care se poate ajunge dintr-un set de stări al NFA pe baza unui simbol din alfabet.

   - Primește ca argumente un `bitset` numit `X`, reprezentând setul de stări din care trebuie făcută mutarea, un număr întreg `A`,
   reprezentând simbolul din alfabet, și o referință la un `bitset` numit `Y`, care va stoca stările accesibile din setul de stări de plecare.
   - Funcția parcurge fiecare stare din `X` și apelează funcția `NFAmove(int X, int A, bitset<MAX_NFA_STATES> &Y)` pentru a calcula stările
   Accesibile din fiecare stare.
   
6. Main()*: În funcția principală a programului:
   - Se deschide fișierul "NFA.txt" pentru citire și se citesc detaliile NFA-ului, inclusiv numărul de stări,
   dimensiunea alfabetului, stările finale și tranzitiile.
   - Se construiește DFA-ul corespunzător NFA-ului citit.
   - Se scrie DFA-ul rezultat în fișierul "DFA.txt".
   - Programul se încheie.






*/

