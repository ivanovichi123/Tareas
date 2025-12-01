//Ivan Arturo Rosas Balderas A01713176

#ifndef DLIST_H_
#define DLIST_H_

#include <string>
#include <sstream>

template <class L> class dList;

template <class L>
class dLink {
    private:
        dLink(L);
        dLink(L, dLink<L>*, dLink<L>*);

        L valor;
        dLink<L> *siguiente;
        dLink<L> *anterior;

        friend class dList<L>;
};

template <class L>
dLink<L>::dLink(L valors) {
    valor = valors;
    siguiente = 0;
    anterior = 0;
}

template <class L>
dLink<L>::dLink(L valors, dLink* siguientes, dLink* anteriores) {
    valor = valors;
    siguiente = siguientes;
    anterior = anteriores;
}

template <class L> 
class dList {
    private:
        int tamano;
        dLink<L> *cabeza;
        dLink<L> *cola;

    public:
        dList();
        dList(const dList<L>&);
        void insertion(L);
        int search(L);
        void update(int, L);
        L deleteAt(int);
        std::string toStringForward() const;
        std::string toStringBackward() const;
};

template <class L> 
dList<L>::dList() {
    tamano = 0;
    cabeza = 0;
    cola = 0;
}

template <class L>
dList<L>::dList(const dList<L>& copia) {
    tamano = copia.tamano;
    cabeza = copia.cabeza;
    cola = copia.cola;
} 

template <class L>
void dList<L>::insertion(L valors) {
    dLink<L> *nuevo;
    dLink<L> *ptr;
    nuevo = new dLink<L>(valors);
    if (cabeza == 0) {
        cabeza = nuevo;
        cola = nuevo;
    } else {
        ptr = cabeza;
        while (ptr -> siguiente != 0) {
            ptr = ptr -> siguiente;
        }
        ptr -> siguiente = nuevo;
        nuevo -> anterior = ptr;
        cola = nuevo;
    }
    tamano = tamano + 1;
}

template <class L>
int dList<L>::search(L busqueda) {
    dLink<L> *ptr;
    ptr = cabeza;
    for (int i = 0; i < tamano; i++) {
        if (ptr -> valor == busqueda) {
            return i;
        }
        ptr = ptr -> siguiente;
    }
    return -1;
}


template <class L>
void dList<L>::update(int indice, L valorNuevo) {
    dLink<L> *ptr;
    ptr = cabeza;

    for (int i = 0; i < indice; i++) {
        ptr = ptr -> siguiente;
    }
    ptr -> valor = valorNuevo;
}

template<class L>
L dList<L>::deleteAt(int indice) {
    dLink<L> *ptr;
    dLink<L> *ptraux;
    dLink<L> *ptrauxAtras;
    L valor;
    ptr = cabeza;

    if (indice == 0) {
        ptraux = cabeza;
        cabeza = cabeza -> siguiente;
        if (cabeza != 0) {
            cabeza->anterior = 0;
        } else {
            cola = 0;
        }
        valor = ptraux -> valor;
    } else {
        for (int i = 0; i < indice - 1; i++) {
            ptr = ptr -> siguiente;
        }
        ptraux = ptr -> siguiente;
        ptr -> siguiente = ptraux -> siguiente;
        if (ptraux->siguiente != 0) {
            ptrauxAtras = ptraux -> siguiente;
            ptrauxAtras -> anterior = ptr;
        } else {
            cola = ptr;
        }

        valor = ptraux -> valor;
        ptraux -> valor = 0;
    }

    delete ptraux;
    tamano = tamano - 1;
    return valor;
}

template <class L>
std::string dList<L>::toStringForward() const {
	std::stringstream aux;
	dLink<L> *p;

	p = cabeza;
	aux << "[";
	while (p != 0) {
		aux << p->valor;
		if (p->siguiente != 0) {
			aux << ", ";
		}
		p = p->siguiente;
	}
	aux << "]";
	return aux.str();
}

template <class L>
std::string dList<L>::toStringBackward() const {
	std::stringstream aux;
	dLink<L> *p;

	p = cola;
	aux << "[";
	while (p != 0) {
		aux << p->valor;
		if (p->anterior != 0) {
			aux << ", ";
		}
		p = p->anterior;
	}
	aux << "]";
	return aux.str();
}

#endif