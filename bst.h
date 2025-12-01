#ifndef BST_H_
#define BST_H_

#include <string>
#include <iostream>
#include <sstream>

template <class T> class BST;

template<class T>
class Node {
    private:
    T value;
    Node *left;
    Node *right;

    public:
    Node(T);
    Node(T, Node<T>*, Node<T>*);
    void add(T);
    bool find(T);
    void preorder(std::stringstream&) const;
    void inorder(std::stringstream&, bool&) const;
    void postorder(std::stringstream&, bool&) const;
    int findHeight() const;
    void findAncestors(std::stringstream&, T, bool&) const;
    int findLevel(T,int);
    void printLevel(std::stringstream&,int, bool&) const;
    void levelorder(std::stringstream&) const;

    friend class BST<T>;
};

template <class T>
Node<T>::Node(T val) {
    value = val;
    left = 0;
    right = 0;
}

template <class T>
Node<T>::Node(T val, Node<T> *le, Node<T> *ri) {
    value = val;
    left = le;
    right = ri;
}

template <class T>
void Node<T>::add(T val) {
    if (val < value) {
        if (left != 0) {
            left -> add(val);
        } else {
            left = new Node<T>(val);
        }
    } else {
        if (right != 0) {
            right -> add(val);
        } else {
            right = new Node<T>(val);
        }
    }
}

template <class T>
bool Node<T>::find(T val) {
    if (val == value) {
        return true;
    } else if (val < value) {
        return(left != 0 && left -> find(val));
    }  else if (val > value) {
        return(right != 0 && right -> find(val));
    }
    return false;
}

template <class T>
void Node<T>::preorder(std::stringstream &stream) const {
    stream << value;
    if(left != 0) {
        stream << " ";
        left -> preorder(stream);
    }
    if (right != 0) {
        stream << " ";
        right -> preorder(stream);
    }
}

template <class T>
void Node<T>::inorder(std::stringstream &stream, bool &first) const {
    if(left != 0) {
        left -> inorder(stream, first);
    }
    if (first == false) {
	    stream << " ";
	}
    stream << value;
    first = false;
    if (right != 0) {
        right -> inorder(stream, first);
    }
}

template <class T>
void Node<T>::postorder(std::stringstream &stream, bool &first) const {
    if(left != 0) {
        left -> postorder(stream, first);
    }

    if (right != 0) {
        right -> postorder(stream, first);
    }

    if (first == false) {
	    stream << " ";
	}
    
    stream << value;
    first = false;
}

template <class T>
int Node<T>::findHeight() const {
    int leftPart = 0;
    int rightPart = 0;

    if (left != 0) {
        leftPart = left -> findHeight();
    }
    if (right != 0) {
        rightPart = right -> findHeight();
    }
    if (leftPart < rightPart) {
        return 1 + rightPart;
    } else {
        return 1 + leftPart;
    }    
}

template <class T>
void Node<T>::findAncestors(std::stringstream &stream, T val, bool &first) const {
    if (val == value) {
        return;
    } else if (val < value) {
        if(left != 0) {
            if (first == false) {
	            stream << " ";
	        }
            stream << value;
            first = false;
            left -> findAncestors(stream, val, first);
        }
    } else if (val > value) {
        if (right != 0) {
            if (first == false) {
	            stream << " ";
	        }
            stream << value;
            first = false;
            right -> findAncestors(stream, val, first);
        }
    }

}

template<class T>
int Node<T>::findLevel(T val, int counter) {
    counter += 1;
    if (val == value) {
        return counter;
    } else if (val < value && left != 0) {
        return left -> findLevel(val, counter);
    }  else if (val > value && right != 0) {
        return right -> findLevel(val, counter);
    }
    return 0;
}


template <class T>
void Node<T>::printLevel(std::stringstream &stream, int level, bool &first) const {
    if (level == 1) {
        if (first == false) {
            stream << " ";
        }
        stream << value;
        first = false;
    } else {
        if (left != 0) left->printLevel(stream, level - 1, first);
        if (right != 0) right->printLevel(stream, level - 1, first);
    }
}

template <class T>
void Node<T>::levelorder(std::stringstream &stream) const {
    bool first = true;
    int h = findHeight();
    for (int i = 1; i <= h; i++) {
        printLevel(stream, i, first);       
    }
}

template <class T>
class BST {
    private:
    Node<T> *root;

    public:
    BST();
    void add(T);
    std::string visit(); 
    int height();
    std::string ancestors(T);
    int whatlevelamI(T);
};

template <class T>
BST<T>::BST() {
    root = 0;
}

template <class T>
void BST<T>::add(T val) {
    if (root != 0) {
        if(!root -> find(val)) {
            root -> add(val);
        }
    } else {
        root = new Node<T>(val);
    }
}

template <class T>
std::string BST<T>::visit() {
    bool first = true;
    bool first2 = true;
    //Preorder
    std::stringstream stream;

    stream << "[";
    if (root != 0) {
        root -> preorder(stream);
    }
    stream << "]\n";

    //Inorder
    stream << "[";
    if (root != 0) {
        root -> inorder(stream, first);
    }
    stream << "]\n";

    //Postorder
    stream << "[";
    if (root != 0) {
        root -> postorder(stream, first2);
    }
    stream << "]\n";

    //Level order
    stream << "[";
    if (root != 0) {
        root -> levelorder(stream);
    }
    stream << "]";

    return stream.str();
}

template <class T>
int BST<T>::height() {
    if (root == 0) {
        return 0;
    } else {
        int result = root -> findHeight();
        return result;
    }
}

template <class T>
std::string BST<T>::ancestors(T val) {
    std::stringstream stream;
    bool first = true;

    stream << "[";
    if (root != 0) {
        if (root -> find(val) != false) {
            root -> findAncestors(stream, val, first);
        }
    }
    stream << "]";

    return stream.str();
}

template <class T>
int BST<T>::whatlevelamI(T val) {
    if (root == 0) {
        return 0;
    }
    return root -> findLevel(val, 0);
}


#endif