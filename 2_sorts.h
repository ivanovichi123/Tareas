//Ivan Arturo Rosas Balderas A01713176
#ifndef SORTS_H_
#define SORTS_H_

template <class S>
class Sorts {
    private:
    void swap(std::vector<S>&, int, int);
    void separarMerge(std::vector<S>&, std::vector<S>&,int, int);
    void unirMerge(std::vector<S>&, std::vector<S>&, int, int, int);
    void copiarMerge(std::vector<S>&, std::vector<S>&, int, int);
    int binarioRecursion(std::vector<S>&, int, int, int);

    public:
    std::vector<S> ordenaSeleccion(std::vector<S>&);
    std::vector<S> ordenaBurbuja(std::vector<S>&);
    std::vector<S> ordenaMerge(std::vector<S>&);
    int busqSecuencial(std::vector<S>&, int);
    int busqBinaria(std::vector<S>&, int);
};

template <class S>
void Sorts<S>::swap(std::vector<S> &v, int a, int b) {
    S aux = v[a];
    v[a] = v[b];
    v[b] = aux;
}


template <class S>
std::vector<S> Sorts<S>::ordenaSeleccion(std::vector<S> &vector) {
    for (int i = 0; i <= vector.size() - 1; i++) {
        int min = i;
        for(int j = i; j <= vector.size() - 1; j++) {
            if (vector[min] > vector[j]) {
                min = j;
            }
        }
        swap(vector, i, min);
    }
    return vector;
}

template <class S>
std::vector<S> Sorts<S>::ordenaBurbuja(std::vector<S> &vector) {
    for(int i = vector.size() - 1; i >= 0; i-- ) {
        for (int j = 0; j < i; j++) {
            if(vector[j] > vector[j + 1]) {
                swap(vector, j, j + 1);
            }
        }
    }
    return vector;
}

template<class S>
void Sorts<S>::unirMerge(std::vector<S> &vector, std::vector<S> &ordenado,int min, int mid, int max) {
    int i = min;
    int j = mid + 1;
    int k = min;

    while (i <= mid && j <= max) {
        if(vector[i] < vector[j]) {
            ordenado[k] = vector[i];
            i++;
        } else {
            ordenado[k] = vector[j];
            j++;
        }
        k++;
    }

    if (i > mid) {
        for (int l = j; l <= max; l++) {
            ordenado[k] = vector[l];
            k++;
        }
    } else {
        for (int m = i; m <= mid; m++) {
            ordenado[k] = vector[m];
            k++;
        }
    }
}

template<class S>
void Sorts<S>::copiarMerge(std::vector<S> &vector, std::vector<S> &ordenado, int min, int max) {
    for (int i = min; i <= max; i++) {
        vector[i] = ordenado[i];
    }
}


template<class S>
void Sorts<S>::separarMerge(std::vector<S> &vector, std::vector<S> &ordenado, int min, int max) {
    if (max - min <= 0) {
        return;
    }
    int mid = (min + max)/2;
    separarMerge(vector, ordenado, min, mid);
    separarMerge(vector, ordenado, mid + 1, max);
    unirMerge(vector, ordenado, min, mid, max);
    copiarMerge(vector, ordenado, min, max);
}


template <class S>
std::vector<S> Sorts<S>::ordenaMerge(std::vector<S> &vector) {
    std::vector<S> ordenado(vector.size());
    separarMerge(vector, ordenado, 0, vector.size() - 1);
    return vector;
}

template <class S>
int Sorts<S>::busqSecuencial(std::vector<S> &vector, int a) {
    for(int i = 0; i < vector.size(); i++) {
        if(vector[i] == a) {
            return i;
        }
    }
    return -1;
}

template <class S>
int Sorts<S>::binarioRecursion(std::vector<S> &vector, int min, int max, int a) {
        if (min > max) {
        return -1;
    }

    int mid = (min + max) / 2;
    
    if (vector[mid] == a) {
        return mid;
    }
    if (vector[mid] < a) {
        return binarioRecursion(vector, mid + 1, max, a);
    } else {
        return binarioRecursion(vector, min, mid - 1, a);
    }
}

template <class S>
int Sorts<S>::busqBinaria(std::vector<S> &vector, int a) {
    return binarioRecursion(vector, 0, vector.size() - 1, a);
}

#endif