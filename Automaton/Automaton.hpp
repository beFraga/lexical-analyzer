#ifndef AUTOMATON_HPP
#define AUTOMATON_HPP
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
using namespace std;

// Implementação de um Autômato Finito

class Automaton {
private:
    int _initialState;
    set<int> _states;
    set<int> _acceptingStates;
    set<char> _alphabet;

    // Transições normais (estado_origem -> símbolo) -> conjunto de estados destino
    map<pair<int, char>, set<int>> _transitions;

    // Transições vaizas 
    map<int, set<int>> _epsilonTransitions;

    // Mapeamento estado_de_aceitação -> token (ex: "id", "num")
    map<int, string> _tokenPatterns;

public:
    Automaton();

    // getters e setters
    void setInitialState(int state);
    int getInitialState();
    
    const set<int>& getStates();
    const set<int>& getFinalStates();
    const set<char>& getAlphabet();

    // montar o autômato
    void addState(int state);
    void addFinalState(int state, const string& patternName = "");
    void addTransition(int from, char symbol, int to);
    void addEpsilonTransition(int from, int to);

    // consultar transições
    set<int> getTransitions(int from, char symbol);
    set<int> getEpsilonTransitions(int from);
    string getTokenPattern(int state);

    // visualizar tabela de transições
    void printTable();
};

#endif