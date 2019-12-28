template<typename T>
string_map<T>::string_map() : raiz(new Nodo()), _size(0) {
}

template<typename T>
string_map<T>::string_map(const string_map<T> &aCopiar) : string_map() {
    *this = aCopiar;
} // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template<typename T>
string_map<T> &string_map<T>::operator=(const string_map<T> &d){
    for(string x : this->claves){
        this->erase(x);
    }
    for(string x : d.claves){
        this->insert(make_pair(x, d.at(x)));
    }
}

template<typename T>
string_map<T>::~string_map() {
    linear_set<string> clavesDefinidas = this->claves;
    for(string x : clavesDefinidas) {
        this->erase(x);
    }
    delete raiz;
}

template<typename T>
void string_map<T>::insert(const pair<string, T> &keyValue) {
    Nodo *actual = raiz;
    string clave = keyValue.first;
    for (char i : clave) {
        if (actual->siguientes[int(i)] != nullptr) {
            actual = actual->siguientes[int(i)];
        } else {
            Nodo *nuevo = new Nodo();
            actual->siguientes[int(i)] = nuevo;
            actual->definidos++;
            actual = nuevo;
        }
    }
    if (actual->definicion == nullptr) {
        actual->definicion = new T;
        this->_size += 1;
        this->claves.insert(keyValue.first); //Si el nodo no existia, agrego la clave a mi conjunto de claves definidas.
    }
    *actual->definicion = keyValue.second;
}

template<typename T>
T &string_map<T>::operator[](const string &key) {
    if(this->count(key) == 0){
        T nuevo;
        this->insert(make_pair(key, nuevo));
    }
    return this->at(key);
}


template<typename T>
int string_map<T>::count(const string &key) const {
    Nodo *actual = raiz;
    for (char i : key) {
        if (actual->siguientes[int(i)] == nullptr) {
            return 0;
        }
        actual = actual->siguientes[int(i)];
    }
    if(actual->definicion != nullptr){
        return 1;
    }else{
        return 0;
    }
}

template<typename T>
const T &string_map<T>::at(const string &key) const {
    Nodo *actual = raiz;
    for (char i : key) {
        actual = actual->siguientes[int(i)];
    }
    return *actual->definicion;
}

template<typename T>
T &string_map<T>::at(const string &key) {
    Nodo *actual = raiz;
    for(char i : key) {
        actual = actual->siguientes[int(i)];
    }
    return *actual->definicion;
}

template<typename T>
void string_map<T>::erase(const string &key) {
    Nodo *actual = raiz;
    Nodo *ultimo = raiz;
    int indiceUltimo = 0;
    for(int i = 0; i < key.size(); i++){ //Busco el elemento a borrar y me guardo cual es el ultimo nodo que no puedo borrar.
        if(actual->definidos > 1 || actual->definicion != nullptr){
            ultimo = actual;
            indiceUltimo = i;
        }
        actual = actual->siguientes[int(key[i])];
    }
    char ultimoChar = key[indiceUltimo];
    if(actual->definidos == 0) {
        Nodo *borrar = ultimo->siguientes[ultimoChar];
        ultimo->siguientes[int(ultimoChar)] = nullptr;
        for (int i = indiceUltimo + 1; i < key.size(); i++) {
            Nodo *temp = borrar;
            borrar = borrar->siguientes[int(key[i])];
            delete temp->definicion;
            delete temp;
        }
        delete borrar->definicion;
        delete borrar;
        ultimo->siguientes[int(ultimoChar)] = nullptr;
        ultimo->definidos--;
    }else{
        delete actual->definicion;
        actual->definicion = nullptr;
    }
    this->claves.erase(key);
    this->_size --;
}

template<typename T>
int string_map<T>::size() const {
    return this->_size;
}

template<typename T>
bool string_map<T>::empty() const {
    return _size == 0;
}

template<typename T>
linear_set<string> string_map<T>::clavesDef() const{
    return this->claves;
}