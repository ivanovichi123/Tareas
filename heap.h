//Ivan Arturo Rosas Balderas
#ifndef HEAP_H_
#define HEAP_H_

#include <string>
#include <iostream>
#include <sstream>

template<class H>
class Heap {
    private:
    H *data;
    int tamano;
    int indice;
    
    public:
    Heap(int);
    void push(int);
    void pop();
    int top();
    bool empty();
    int size();
    bool full();
    std::string toString() const;
};

template <class H>
Heap<H>::Heap(int t) {
    tamano = t;
    data = new H[t + 1];
    indice = 0;
}

template<class H>
void Heap<H>::push(int valor) {
    if(full()) {
        return;
    }
    indice += 1;
    data[indice] = valor;
    if (indice > 1) {
        bool continuar = true;
        int indiceTemporal = indice;
        int indicePadre = indice/2;
        while(continuar && indicePadre > 0) {
            if(data[indicePadre] > data[indiceTemporal]) {
                int auxiliar = data[indicePadre];
                data[indicePadre] = data[indiceTemporal];
                data[indiceTemporal] = auxiliar;
                indiceTemporal = indicePadre;
                indicePadre = indicePadre/2;
            } else {
                continuar = false;
            }
        }
    }
}

template<class H>
void Heap<H>::pop() {
    if(empty()) {
        return;
    }
    data[1] = data[indice];
    indice -= 1;
    bool continuar = true;
    int indiceTemporal = 1;
    while(continuar) {
        int hijoIzquierdo =  indiceTemporal * 2;
        int hijoDerecho = (indiceTemporal * 2) + 1;
        int menor = indiceTemporal;
        if(hijoIzquierdo <= indice && data[hijoIzquierdo] < data[menor]) {
            menor = hijoIzquierdo;
        } 
        if (hijoDerecho <= indice && data[hijoDerecho] < data[menor]){
            menor = hijoDerecho;

        } 
        if(menor != indiceTemporal) {
            int auxiliar = data[indiceTemporal];
            data[indiceTemporal] = data[menor];
            data[menor] = auxiliar;
            indiceTemporal = menor; 
        } else {
            continuar = false;
        }
    }
}

template<class H>
int Heap<H>::top() {
    if(empty()) {
        return 0;
    }
    return data[1];
}

template<class H>
bool Heap<H>::empty() {
    if(indice == 0) {
        return true;
    } 
    return false;
}

template<class H>
bool Heap<H>::full() {
    if (indice == tamano) {
        return true;
    }
    return false;
}

template<class H>
int Heap<H>::size() {
    return indice;
}

template <class H>
std::string Heap<H>::toString() const {
	std::stringstream aux;
	aux << "[";	for (unsigned int i = 1; i <= indice; i++) {
		if (i != 1) {
			aux << " ";
		} aux << data[i];
	} aux << "]";
	return aux.str();
}

#endif