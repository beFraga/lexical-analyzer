#include "Automaton.h"
#include <iomanip>
using namespace std;

Automaton::Automaton() : _initialState(0) {}

void Automaton::setInitialState(int state) {
    _initialState = state;
    addState(state);
}

int Automaton::getInitialState() {
    return _initialState;
}

const set<int>& Automaton::getStates() {
    return _states;
}

const set<int>& Automaton::getFinalStates() {
    return _acceptingStates;
}

const set<char>& Automaton::getAlphabet() {
    return _alphabet;
}

void Automaton::addState(int state) {
    _states.insert(state);
}

void Automaton::addFinalState(int state, const string& patternName) {
    addState(state);
    _acceptingStates.insert(state);
    if (!patternName.empty()) {
        _tokenPatterns[state] = patternName;
    }
}

void Automaton::addTransition(int from, char symbol, int to) {
    addState(from);
    addState(to);
    _alphabet.insert(symbol);
    _transitions[{from, symbol}].insert(to);
}

void Automaton::addEpsilonTransition(int from, int to) {
    addState(from);
    addState(to);
    _epsilonTransitions[from].insert(to);
}

set<int> Automaton::getTransitions(int from, char symbol) {
    auto it = _transitions.find({from, symbol});
    if (it != _transitions.end()) {
        return it->second;
    }
    return {};
}

set<int> Automaton::getEpsilonTransitions(int from) {
    auto it = _epsilonTransitions.find(from);
    if (it != _epsilonTransitions.end()) {
        return it->second;
    }
    return {};
}

string Automaton::getTokenPattern(int state) {
    auto it = _tokenPatterns.find(state);
    if (it != _tokenPatterns.end()) {
        return it->second;
    }
    return "";
}

void Automaton::printTable() {
    cout << "\n=== TABELA DE TRANSIÇÕES DO AUTÔMATO ===" << endl;
    cout << "Estado Inicial: q" << _initialState << endl;
    cout << "Estados de Aceitação: ";
    for (int f : _acceptingStates) {
        cout << "q" << f << " ";
    }
    cout << "\n\n";

    // Cabeçalho da tabela
    cout << setw(10) << "Estado" << setw(9);
    for (char c : _alphabet) {
        cout << c << setw(10);
    }
    cout << setw(12) << "&" << endl;
    cout << string(30 + _alphabet.size() * 10, '-') << endl;

    // Linhas dos estados
    for (int state : _states) {
        string label = "q" + to_string(state);
        if (state == _initialState) label = "->" + label;
        if (_acceptingStates.count(state)) label += "*";

        cout << setw(10) << label;

        for (char c : _alphabet) {
            set<int> dest = getTransitions(state, c);
            string destStr = "";
            for (int d : dest) destStr += "q" + to_string(d) + " ";
            cout << setw(10) << (destStr.empty() ? "- " : destStr);
        }

        set<int> epsDest = getEpsilonTransitions(state);
        string epsStr = "";
        for (int d : epsDest) epsStr += "q" + to_string(d) + " ";
        cout << setw(12) << (epsStr.empty() ? "- " : epsStr) << endl;
    }
    cout << endl;
}
