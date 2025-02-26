#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

bool checkNTR(char ch) 
{
    vector<char> big = {'S', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    for (char c : big) 
    {
        if (ch == c)
            return true;
    }
    return false;
}

bool checkTR(char ch) 
{
    vector<char> small = {'a', 'b', 'c', 'd', 'e'};
    for (char c : small) 
    {
        if (ch == c)
            return true;
    }
    return false;
}

bool checkPR(const string& ch)
{
    if (ch.length() == 1) 
    {
        if (checkTR(ch[0])) 
        {
            return true;
        }
    } 
    else if (ch.length() == 2)
    {
        if (checkNTR(ch[0]) && checkNTR(ch[1])) 
        {
            return true;
        }
    }
    return false;
}

bool checkEle(const string& El, char ch)
{
    for (char c : El) 
    {
        if (ch == c) 
        {
            return true;
        }
    }
    return false;
}

int main() 
{

    int n_pr = 0, n_pr2 = 0, pr_cnt = 0;

    cout << "Simboluri permise: 'S','A','B','C','D','E','F','G','H' \n";
    cout << "Terminali permisi: 'a','b','c','d' and 'e':lambda\n";
    cout << "\n\nNr. de reguli de productii = ";
    cin >> n_pr;
    vector<char> ntr(n_pr);
    vector<string> pr(n_pr);
    vector<int> ntr_cnt(n_pr);

    cout << "\nIntroduceti simbolurile:\n\nContor simbol\n";
    cin.ignore();
    int i1 = 0;
    while (n_pr2 < n_pr) {
        cin >> ntr[i1] >> ntr_cnt[i1];
        cin.ignore();

        if (!checkNTR(ntr[i1])) {
            cout << "Input invalid. \n\nExit...\n";
            return -1;
        }
        n_pr2 += ntr_cnt[i1];
        i1++;
    }

    if (n_pr != n_pr2) {
        cout << "Input invalid. \n\nExit...\n";
        return -1;
    }

    cout << "\n\nIntroduceti reguli de productie : \n";
    cout << "\nNon- Terminal   -->   Productie\n";
    pr_cnt = 0;
    for (int i = 0; i < i1; i++) {
        for (int j = 0; j < ntr_cnt[i]; j++) {
            cout << ntr[i] << " --> ";
            getline(cin, pr[pr_cnt]);
            if (!checkPR(pr[pr_cnt])) {
                cout << "Input invalid. \n\nExit...\n";
                return -1;
            }
            pr_cnt++;
        }
    }

    pr_cnt = 0;
    for (int i = 0; i < i1; i++) {
        for (int j = 0; j < ntr_cnt[i]; j++) {
            cout << "\n" << ntr[i] << " --> " << pr[pr_cnt];
            pr_cnt++;
        }
    }

    ifstream inputFile("Cyk input.txt");
    string s1;
    // cout << "\n\nInput String: ";
    getline(inputFile, s1);
    int n = s1.length();
    string st = s1;
    vector<vector<string>> tb(n, vector<string>(n, string(10, '\0')));

    if (n == 0) {
        cout << "String Gol!\n";
        return -1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            tb[i][j].assign(10, '\0');
        }
    }

    for (int i = 0; i < n; i++) {
        pr_cnt = 0;
        int k2 = 0;
        for (int i2 = 0; i2 < i1; i2++) {
            for (int j2 = 0; j2 < ntr_cnt[i2]; j2++) {
                if (checkTR(pr[pr_cnt][0]) && pr[pr_cnt][0] == st[i]) {
                    tb[i][i][k2] = ntr[i2];
                    k2 += 1;
                }
                pr_cnt++;
            }
        }
    }

    for (int l = 1; l <= (n - 1); l++) {
        for (int i = 0, j = 0; i <= (n - l - 1); i++) {
            j = i + l;

            for (int k = i; k <= (j - 1); k++) {
                pr_cnt = 0;
                int k2 = 0;

                for (int i2 = 0; i2 < i1; i2++) {
                    for (int j2 = 0; j2 < ntr_cnt[i2]; j2++) {
                        if (checkNTR(pr[pr_cnt][0])) {
                            if (checkEle(tb[i][k], pr[pr_cnt][0]) && checkEle(tb[k + 1][j], pr[pr_cnt][1])) {
                                tb[i][j][k2] = ntr[i2];
                                k2 += 1;
                            }
                        }
                        pr_cnt++;
                    }
                }
            }
        }
    }


    for (int i = 0; i < n; i++) {
        cout << "|";
        for (int j = 0; j < n; j++) {
            cout << tb[i][j] << " |";
        }
        cout << "\n";
    }

    if (checkEle(tb[0][n - 1], 'S')) {
        cout << "\n\nString acceptat!\n\n";
    } else {
        cout << "\n\nString neacceptat!\n\n";
    }

    return 0;
}

