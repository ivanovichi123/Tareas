#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

class Graph {
private:
    vector<vector<int>> adjList;   
    vector<vector<int>> adjMat;
    int total; 

public:
    Graph();
    void loadGraphList(const string&, int);
    void loadGraphMat(const string&, int, int);
    string printAdjList();
    string printAdjMat();
    string DFS(int inicio, int destino);
    void DFS_Ayuda(int, int, vector<bool>&, vector<int>&, vector<int>&, bool&);
    string BFS(int inicio, int destino);
};

Graph::Graph() {
    total = 0;
}

void Graph::loadGraphList(const string &lista, int vertices) {
    total = vertices;
    adjList.clear();
    adjList.resize(total);

    stringstream laLista(lista);
    string nodo;

    while (laLista >> nodo) {
        for (char &c : nodo) {
            if (c == '(' || c == ')' || c == ',') {
                c = ' ';    
            }
        }

        stringstream Limpio(nodo);
        int n, m;
        Limpio >> n >> m;

        if (n >= 0 && n < total && m >= 0 && m < total) {
            adjList[n].push_back(m);
            adjList[m].push_back(n); 
        }
    }

    for (int i = 0; i < total; i++) {
        sort(adjList[i].begin(), adjList[i].end());
    }
}

void Graph::loadGraphMat(const string &lista, int fila, int columna) {
    total = fila;

    adjMat.clear();
    adjMat.resize(fila, vector<int>(columna, 0));

    stringstream laLista(lista);
    string nodo;

    while (laLista >> nodo) {
        for (char &c : nodo) {
            if (c == '(' || c == ')' || c == ',') {
                c = ' ';
            }
        }

        int n, m;
        stringstream Limpio(nodo);
        Limpio >> n >> m;

        if (n >= 0 && n < fila && m >= 0 && m < columna) {
            adjMat[n][m] = 1;
            adjMat[m][n] = 1;
        }
    }
}

string Graph::printAdjList() {
    string resultado = "";
    for (int i = 0; i < total; i++) {
        resultado += "vertex " + to_string(i) + " : ";
        for (int j = 0; j < adjList[i].size(); j++) {
            resultado += to_string(adjList[i][j]) + " ";
        }
        resultado += "";
    }
    return resultado;
}

string Graph::printAdjMat() {
    string resultado = "";
    for (int i = 0; i < adjMat.size(); i++) {
        for (int j = 0; j < adjMat[i].size(); j++) {
            resultado += to_string(adjMat[i][j]) + " ";
        }
    }

    return resultado;
}


string Graph::DFS(int inicio, int destino) {
    vector<bool> visitado(total, false);
    vector<int> padre(total, -1);
    vector<int> listaVisitada;
    bool encontrado = false;

    DFS_Ayuda(inicio, destino, visitado, padre, listaVisitada, encontrado);

    string resultado = "visited: ";
    for (int i = 0; i < listaVisitada.size(); i++) {
        resultado += to_string(listaVisitada[i]) + " ";
    }

    vector<int> camino;
    if (encontrado == true) {
        int actual = destino;
        while (actual != -1) {
            camino.push_back(actual);
            actual = padre[actual];
        }
        reverse(camino.begin(), camino.end());
    }

    resultado += "path: ";
    for (int i = 0; i < camino.size(); i++) {
        resultado += to_string(camino[i]) + " ";
    }

    if (resultado.empty() != true && resultado.back() == ' ')
    resultado.pop_back();


    return resultado;

}


void Graph::DFS_Ayuda(int nodo, int destino, vector<bool> &visitado, vector<int> &padre, vector<int> &listaVisitada, bool &encontrado)  {
    if (encontrado == true) {
        return;
    }
    
    visitado[nodo] = true;
    listaVisitada.push_back(nodo);

    if (nodo == destino) {
        encontrado = true;
        return;
    }

    for (int conectado = 0; conectado < adjList[nodo].size(); conectado++) {
        if (visitado[adjList[nodo][conectado]] != true) {
            padre[adjList[nodo][conectado]] = nodo;
            DFS_Ayuda(adjList[nodo][conectado], destino, visitado, padre, listaVisitada, encontrado);
        }
    }
}

string Graph::BFS(int inicio, int destino) {
    vector<bool> visitado(total, false);
    vector<int> padre(total, -1);
    vector<int> listaVisitada;
    vector<int> queue; 

    visitado[inicio] = true;
    queue.push_back(inicio);

    bool encontrado = false;

    while (queue.empty() != true && encontrado != true) {
        int actual = queue.front(); 
        queue.erase(queue.begin());  
        listaVisitada.push_back(actual);

        if (actual == destino) {
            encontrado = true;
            break;
        }

        for (int i = 0; i < adjList[actual].size(); i++) {
            int vecino = adjList[actual][i];
            if (visitado[vecino] != true) {
                visitado[vecino] = true;
                padre[vecino] = actual;
                queue.push_back(vecino);  
            }
        }
    }

    string resultado = "visited: ";
    for (int i = 0; i < listaVisitada.size(); i++) {
        resultado += to_string(listaVisitada[i]) + " ";
    }

    vector<int> camino;
    if (encontrado) {
        int actual = destino;
        while (actual != -1) {
            camino.push_back(actual);
            actual = padre[actual];
        }
        reverse(camino.begin(), camino.end());
    }

    resultado += "path: ";
    for (int i = 0; i < camino.size(); i++) {
        resultado += to_string(camino[i]) + " ";
    }

    if (resultado.empty() != true && resultado.back() == ' ')
    resultado.pop_back();

    return resultado;
}

#endif
