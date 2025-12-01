// Ivan Arturo Rosas Balderas A01713176
#ifndef FUNCIONES_H_
#define FUNCIONES_H_

class Funciones {
    private:
    int numero;

    public:
    int sumaIterativa(int);  
    int sumaRecursiva(int);
    int sumaDirecta(int);

};

int Funciones::sumaIterativa(int n) {
    int resul = 0;
    for(int i = 1; i <= n; i++) {
        resul += i;
    }
    return resul;
}

int Funciones::sumaRecursiva(int n) {
    if (n <= 0) {
        return 0;
    }
    return sumaRecursiva(n - 1) + n;
}

int Funciones::sumaDirecta(int n) {
    int resul = (n * (n + 1)) / 2;
    return resul;
}

#endif