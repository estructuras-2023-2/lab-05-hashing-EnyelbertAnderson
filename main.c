#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct RandomGenerator {
    int (*randomFn)(struct RandomGenerator*);
    int value;
};

struct HashTable {
    int size;
    struct Node** table;
    int (*hash_function)(int, int);
    struct RandomGenerator* generator;
};

int generateRandomValue(struct RandomGenerator* generator) {
    return rand() % 100; 
}

struct RandomGenerator* createRandomGenerator() {
    struct RandomGenerator* generator = malloc(sizeof(struct RandomGenerator));
    generator->randomFn = generateRandomValue;
    generator->value = 0; 
    return generator;
}

struct HashTable* createHashTable(int (*hash_func)(int, int), int table_size, struct RandomGenerator* generator) {
    struct HashTable* ht = malloc(sizeof(struct HashTable));
    ht->size = table_size;
    ht->table = malloc(table_size * sizeof(struct Node*));
    ht->hash_function = hash_func;
    ht->generator = generator;
    for (int i = 0; i < table_size; ++i) {
        ht->table[i] = NULL;
    }

    return ht;
}

void insert(struct HashTable* ht, int x) {
    int hash_value = ht->hash_function(x, ht->size);

    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->data = x;
    newNode->next = NULL;

    if (ht->table[hash_value] == NULL) {
        ht->table[hash_value] = newNode;
    } else {
        struct Node* current = ht->table[hash_value];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

bool find(struct HashTable* ht, int x) {
    int hash_value = ht->hash_function(x, ht->size);
    struct Node* current = ht->table[hash_value];

    while (current != NULL) {
        if (current->data == x) {
            return true;
        }
        current = current->next;
    }

    return false;
}

void destroyHashTable(struct HashTable* ht) {
 
    for (int i = 0; i < ht->size; ++i) {
        struct Node* current = ht->table[i];
        while (current != NULL) {
            struct Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(ht->table);
    free(ht->generator);
    free(ht);
}

int mi_Mod(int x, int n) {
    if (n == 0) {
        fprintf(stderr, "Error: No se puede dividir por 0\n");
        return -1; 
    }
    return x % n;
}

int randomFn(struct RandomGenerator* generator) {
    int randomValue = generator->randomFn(generator);
    printf("Número aleatorio generado: %d\n", randomValue);
    generator->value = randomValue;
    return randomValue;
}

int main() {

    struct RandomGenerator* generator = createRandomGenerator();


    struct HashTable* HT = createHashTable(mi_Mod, 100, generator);


    int x = 1234567;
    long long int y = 76554334234;

   
    insert(HT, x);

    printf("¿Está x en la tabla hash? %s\n", (find(HT, x) ? "Sí" : "No"));

    printf("¿Está y en la tabla hash? %s\n", (find(HT, y) ? "Sí" : "No"));

  
    destroyHashTable(HT);
    free(generator);

    return 0;
}

