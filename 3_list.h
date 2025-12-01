//Ivan Arturo Rosas Balderas A01713176

#ifndef LIST_H_
#define LIST_H_

#include <string>
#include <sstream>

template <class L> class List;

template <class L>
class Link {
    private:
        Link(L);
        Link(L, Link<L>*);

        L valor;
        Link<L> *siguiente;

        friend class List<L>;
};

template <class L>
Link<L>::Link(L valors) {
    valor = valors;
    siguiente = 0;
}

template <class L>
Link<L>::Link(L valors, Link* siguientes) {
    valor = valors;
    siguiente = siguientes;
}

template <class L> 
class List {
    private:
        int tamano;
        Link<L> *cabeza;

    public:
        List();
        List(const List<L>&);
        void insertion(L);
        int search(L);
        void update(int, L);
        L deleteAt(int);
        std::string toString() const;
};

template <class L> 
List<L>::List() {
    tamano = 0;
    cabeza = 0;
}

template <class L>
List<L>::List(const List<L>& copia) {
    tamano = copia.tamano;
    cabeza = copia.cabeza;
} 

template <class L>
void List<L>::insertion(L valors) {
    Link<L> *nuevo;
    Link<L> *ptr;
    nuevo = new Link<L>(valors);
    if (cabeza == 0) {
        cabeza = nuevo;
    } else {
        ptr = cabeza;
        while (ptr -> siguiente != 0) {
            ptr = ptr -> siguiente;
        }
        ptr -> siguiente = nuevo;
    }
    tamano = tamano + 1;
}

template <class L>
int List<L>::search(L busqueda) {
    Link<L> *ptr;
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
void List<L>::update(int indice, L valorNuevo) {
    Link<L> *ptr;
    ptr = cabeza;

    for (int i = 0; i < indice; i++) {
        ptr = ptr -> siguiente;
    }
    ptr -> valor = valorNuevo;
}

template<class L>
L List<L>::deleteAt(int indice) {
    Link<L> *ptr;
    Link<L> *ptraux;
    L valor;
    ptr = cabeza;

    if (indice == 0) {
        ptraux = cabeza;
        cabeza = cabeza -> siguiente;
        valor = ptraux -> valor;
    } else {
        for (int i = 0; i < indice - 1; i++) {
            ptr = ptr -> siguiente;
        }

        ptraux = ptr -> siguiente;
        ptr -> siguiente = ptraux -> siguiente;
        valor = ptraux -> valor;
        ptraux -> valor = 0;
    }

    delete ptraux;
    tamano = tamano - 1;
    return valor;
}

template <class L>
std::string List<L>::toString() const {
	std::stringstream aux;
	Link<L> *p;

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

#endif