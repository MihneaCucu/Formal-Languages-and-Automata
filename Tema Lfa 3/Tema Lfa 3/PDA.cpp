/*#include <iostream>
 #include <fstream>
 #include <vector>
 #include <stack>
 #include <unordered_map>
 #include <unordered_set>
 #include <string>
 
 struct Transition {
 char input;
 char stackTop;
 string newStack;
 int nextState;
 };
 
 struct PDA {
 int startState;
 unordered_set<int> acceptStates;
 unordered_map<int, vector<Transition>> transitions;
 };
 
 bool isAccepted(PDA &pda, const string &word) {
 struct Configuration {
 int state;
 string remainingWord;
 stack<char> stack;
 };
 
 vector<Configuration> configurations;
 configurations.push_back({pda.startState, word, stack<char>()});
 configurations.back().stack.push('$'); // Start symbol
 
 while (!configurations.empty()) {
 Configuration config = configurations.back();
 configurations.pop_back();
 
 if (config.remainingWord.empty() && config.stack.top() == '$') {
 if (pda.acceptStates.find(config.state) != pda.acceptStates.end()) {
 return true;
 }
 continue;
 }
 
 char currentInput = config.remainingWord.empty() ? '\0' : config.remainingWord[0];
 char stackTop = config.stack.top();
 
 for (const auto &transition : pda.transitions[config.state]) {
 if ((transition.input == currentInput || transition.input == '\0') && transition.stackTop == stackTop) {
 Configuration newConfig = config;
 if (transition.input == currentInput) {
 newConfig.remainingWord = config.remainingWord.substr(1);
 }
 newConfig.stack.pop();
 for (auto it = transition.newStack.rbegin(); it != transition.newStack.rend(); ++it) {
 if (*it != '\0') {
 newConfig.stack.push(*it);
 }
 }
 newConfig.state = transition.nextState;
 configurations.push_back(newConfig);
 }
 }
 }
 
 return false;
 }
 
 
 int main() {
 ifstream infile("input.txt");
 PDA pda;
 string word;
 
 if (!infile) {
 cerr << "Cannot open input file!" << endl;
 return 1;
 }
 
 int numStates, numAcceptStates, numTransitions;
 infile >> numStates >> pda.startState >> numAcceptStates;
 
 for (int i = 0; i < numAcceptStates; ++i) {
 int state;
 infile >> state;
 pda.acceptStates.insert(state);
 }
 
 infile >> numTransitions;
 for (int i = 0; i < numTransitions; ++i) {
 int fromState, toState;
 char input, stackTop;
 string newStack;
 infile >> fromState >> input >> stackTop >> newStack >> toState;
 
 pda.transitions[fromState].push_back({input, stackTop, newStack, toState});
 }
 
 infile >> word;
 infile.close();
 
 if (isAccepted(pda, word)) {
 cout << "The word is accepted by the PDA." << endl;
 } else {
 cout << "The word is not accepted by the PDA." << endl;
 }
 
 return 0;
 }
 */
