#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>

using namespace std;
int main()
{
    ifstream fin("Input");
    int n,m,start,k,finish[105];
    
    // v[x][c] = lista de noduri y cu proprietatea ca x->y cu caracterul c
    vector<int> v[105][35];

    fin >> n >> m >> start >> k;
    
    for(int i = 1; i <= m; i++)
    {
        int x,y;
        char c;
        fin >> x >> y >> c;

        // lambda e codificat cu '0'
        v[x][c - 'a'].push_back(y);
    }
    
    for(int i = 1; i <= k; i++)
    {
        fin >> finish[i];
    }

    // nodes[i] = multimea de noduri din NFA care reprezinta nodul i din DFA
    vector<unordered_set<int>> nodes;
    nodes.push_back(unordered_set<int>());

    unordered_set<int> start_node;
    start_node.insert(start);
    nodes.push_back(start_node);

    queue<int> que;
    que.push(1);

    int dfa[10005][35];
    while (!que.empty())
    {
        int index = que.front();
        unordered_set<int> node_dfa = nodes[index];
        que.pop();

        for (int c = 0; c < 26; ++c)
        {
            unordered_set<int> new_node_dfa;

            for (int node: node_dfa)
            {
                for (int i = 0; i < v[node][c].size(); ++i)
                {
                    new_node_dfa.insert(v[node][c][i]);
                }
            }

            // Daca nu am niciun vecin, atunci nu am tranzitie
            if (new_node_dfa.empty())
            {
                continue;
            }

            int new_index = nodes.size();

            // Verific daca in nodes exista deja o multime cu aceleasi noduri din nfa
            for (int i = 1; i < nodes.size(); ++i)
            {
                if (nodes[i].size() != new_node_dfa.size())
                {
                    continue;
                }

                bool equal = true;
                for (int val: new_node_dfa)
                {
                    if (nodes[i].find(val) == nodes[i].end())
                    {
                        equal = false;
                        break;
                    }
                }

                if (equal)
                {
                    new_index = i;
                    break;
                }
            }

            // Verific daca aceasta multime exista deja
            if (new_index == nodes.size())
            {
                nodes.push_back(new_node_dfa);
                que.push(new_index);
            }

            dfa[index][c] = new_index;
        }
    }

    for (int i = 1; i < nodes.size(); ++i)
    {
        cout << "Node " << i << ": ";
        for (int node: nodes[i])
        {
            cout << node << " ";
        }
        cout << "\n";
    }
    cout << "\n";

    for (int i = 1; i < nodes.size(); ++i)
    {
        for (int c = 0; c < 'z' - 'a'; ++c)
        {
            if (dfa[i][c] != 0)
            {
                cout << i << " " << dfa[i][c] << " " << char(c + 'a') << "\n";
            }
        }
    }

    return 0;
}

