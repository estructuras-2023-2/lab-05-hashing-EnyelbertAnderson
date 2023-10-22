#include <iostream>
#include <vector>

class HashTable {
private:
    int size;
    std::vector<std::vector<int>> table;
    int (*hash_function)(int, int);

public:
    HashTable(int (*hash_func)(int, int), int table_size) : size(table_size), table(table_size), hash_function(hash_func) {}

    void insert(int x) {
        int hash_value = hash_function(x, size);
        table[hash_value].push_back(x);
    }

    void remove(int x) {
        int hash_value = hash_function(x, size);
        for (auto it = table[hash_value].begin(); it != table[hash_value].end(); ++it) {
            if (*it == x) {
                table[hash_value].erase(it);
                break;
            }
        }
    }

    bool find(int x) {
        int hash_value = hash_function(x, size);
        for (int num : table[hash_value]) {
            if (num == x) {
                return true;
            }
        }
        return false;
    }
};

int mi_Mod(int x, int n) {
    if (n == 0) {
        std::cerr << "Error: No se puede dividir por 0" << std::endl;
        return -1; // Devuelve un valor especial para indicar error
    }
    return x % n;
}

int main() {
    // Crear una instancia de HashTable con mi_Mod como la función de hash y un tamaño de 10
    HashTable HT(mi_Mod, 10);

    // Define los valores x e y
    int x = 1234567;
    int y = 76554334234;

    // Inserta el valor x en la tabla hash
    HT.insert(x);

    // Verifica si x está en la tabla hash
    std::cout << "¿Está x en la tabla hash? " << (HT.find(x) ? "Sí" : "No") << std::endl;

    // Verifica si y está en la tabla hash
    std::cout << "¿Está y en la tabla hash? " << (HT.find(y) ? "Sí" : "No") << std::endl;

    return 0;
}

