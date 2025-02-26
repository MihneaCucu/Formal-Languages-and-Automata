#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class DFA {
private:
    int nr_stari;
    int nr_simboluri;
    vector<vector<int>> tabel_tranzitii;
    vector<bool> stari_finale;

public:
    DFA() {
        cout << "Introduceti nr de stari: ";
        cin >> nr_stari;
        cout << "Introduceti nr de simboluri: ";
        cin >> nr_simboluri;

        tabel_tranzitii.assign(nr_stari, vector<int>(nr_simboluri));
        stari_finale.assign(nr_stari, false);
    }

    void setTranzitie(int from, int to, int simbol) {
        tabel_tranzitii[from][simbol] = to;
    }

    void setStareFinala(int stare) {
        stari_finale[stare] = true;
    }

    void minimizare() {
        vector<vector<int>> partitii;

        vector<int> nonFinale, finale;
        for (int i = 0; i < nr_stari; i++) {
            if (stari_finale[i]) {
                finale.push_back(i);
            } else {
                nonFinale.push_back(i);
            }
        }
        partitii.push_back(nonFinale);
        partitii.push_back(finale);

        bool schimbat = true;
        while (schimbat) {
            schimbat = false;

            vector<vector<int>> partitiiNoi;
            for (auto partitie : partitii) {
                vector<vector<int>> splits;
                for (int stare : partitie) {
                    bool ales = false;
                    for (auto parteNoua : splits) {
                        if (esteCompatibil(stare, parteNoua[0])) {
                            parteNoua.push_back(stare);
                            ales = true;
                            break;
                        }
                    }
                    if (!ales) {
                        vector<int> parteNoua { stare };
                        splits.push_back(parteNoua);
                    }
                }

                if (splits.size() > 1) {
                    schimbat = true;
                }

                for (auto split : splits) {
                    partitiiNoi.push_back(split);
                }
            }
            partitii = move(partitiiNoi);
        }

        minimizareDFA(partitii);
    }

    void minimizareDFA(const vector<vector<int>>& partitii) {
        int nr_stari = partitii.size();

        vector<vector<int>> tabelNou(nr_stari, vector<int>(nr_simboluri, -1));
        vector<bool> newFinals(nr_stari, false);

        for (int i = 0; i < partitii.size(); i++) {
            if (stari_finale[partitii[i][0]]) {
                newFinals[i] = true;
            }
        }

        for (int from = 0; from < nr_stari; from++) {
            for (int simbol = 0; simbol < nr_simboluri; simbol++) {
                int to = tabel_tranzitii[partitii[from][0]][simbol];
                for (int i = 0; i < nr_stari; i++) {
                    if (find(partitii[i].begin(), partitii[i].end(), to) != partitii[i].end()) {
                        tabelNou[from][simbol] = i;
                        break;
                    }
                }
            }
        }

        tabel_tranzitii = move(tabelNou);
        stari_finale = move(newFinals);
        nr_stari = partitii.size();
    }

    bool esteCompatibil(int q1, int q2) {
        for (int simbol = 0; simbol < nr_simboluri; simbol++) {
            if (tabel_tranzitii[q1][simbol] != tabel_tranzitii[q2][simbol]) {
                return false;
            }
        }
        return true;
    }

    void afisareDFA() {
        cout << "Transition table:" << endl;
        for (auto row : tabel_tranzitii) {
            for (int col : row) {
                cout << col << " ";
            }
            cout << endl;
        }

        cout << "Stari finale: ";
        for (int i = 0; i < nr_stari; i++) {
            if (stari_finale[i]) cout << i << " ";
        }
        cout << endl;
    }
};

int main() {

    DFA dfa;

    int tranzitii;
    cout << "Introduceti nr de tranzitii: ";
    cin >> tranzitii;

    for (int i = 0; i < tranzitii; i++) {
        int from, to, simbol;
        cout << "Tranzitie " << i + 1 << ":" << endl;
        cout << "From: ";
        cin >> from;
        cout << "To: ";
        cin >> to;
        cout << "Pe simbol: ";
        cin >> simbol;

        dfa.setTranzitie(from, to, simbol);
    }

    int stari_finale;
    cout << "Introduceti nr de stari finale: ";
    cin >> stari_finale;

    for (int i = 0; i < stari_finale; i++) {
        int stare;
        cout << "Final state " << i + 1 << ": ";
        cin >> stare;
        dfa.setStareFinala(stare);
    }

    dfa.minimizare();
    dfa.afisareDFA();

    return 0;
}
