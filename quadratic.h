#ifndef HASH_H_
#define HASH_H_

#include <string>
#include <sstream>

template <class Key, class Value>
class Quadratic {
private:
    unsigned int (*func) (const Key); 
    int size;
    int count;
    Key *keys;
    Key initialValue;
    Value *values;
    int indexOf(const Key) const;

public:
    Quadratic(int, Key, unsigned int (*f) (const Key));
    bool full() const;
    bool put(Key, Value);
    bool contains(const Key) const;
    Value get(const Key);
    std::string toString() const;
};

template <class Key, class Value>
Quadratic<Key, Value>::Quadratic(int sze, Key init, unsigned int (*f) (const Key)) {
    size = sze;
    keys = new Key[size];
    initialValue = init;

    for (int i = 0; i < size; i++) {
        keys[i] = init;
    }

    values = new Value[size];
    for (int i = 0; i < size; i++) {
        values[i] = 0;
    }

    func = f;
    count = 0;
}

template <class Key, class Value>
bool Quadratic<Key, Value>::full() const {
	if (count == size) {
		return true;
	} else {
		return false;
	}
}

template <class Key, class Value>
int Quadratic<Key, Value>::indexOf(const Key k) const {
    int h = func(k) % size;

    for (int j = 0; j < size; j++) {
        int i = (h + j * j) % size;

        if (keys[i] == k) {
            return i;
        }

        if (keys[i] == initialValue) {
            return -1;
        }
    }
    return -1;
}

template <class Key, class Value>
bool Quadratic<Key, Value>::put(Key k, Value v) {
    if (full()) {
		return false;
	}

    int pos = indexOf(k);
    if (pos != -1) {
        values[pos] = v;
        return true;
    }

    int h = func(k) % size;

    for (int j = 0; j < size; j++) {
        int i = (h + j * j) % size;

        if (keys[i] == initialValue) {
            keys[i] = k;
            values[i] = v;
            count++;
            return true;
        }
    }
    return false;
}

template <class Key, class Value>
bool Quadratic<Key, Value>::contains(const Key k) const {
	if (index(k) != -1) {
		return true;
	} else {
		return false;
	}
}

template <class Key, class Value>
Value Quadratic<Key, Value>::get(const Key k) {
    int pos = indexOf(k);
    if (pos != -1) {
        return values[pos];
    }
    return -1; 
}

template <class Key, class Value>
std::string Quadratic<Key, Value>::toString() const {
	std::stringstream aux;
	for (int i = 0; i < size; i++){
			if (keys[i] != initialValue){
				aux << "(" << i << " ";
			  aux << keys[i] << " : " << values[i] << ") ";
			}
	}
	return aux.str();
}

#endif

