#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

// Longitud máxima de una palabra
#define LENGTH 45

// Representa un nodo en una tabla hash
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Tamaño de la tabla hash
#define HASH_SIZE 1000000

// Función de hash
unsigned int hash(const char *word)
{
    unsigned int hashval = 0;

    // Calcula el valor hash sumando el valor ASCII de cada carácter de la palabra
    // y aplicando una operación de desplazamiento y resta
    for (int i = 0; word[i] != '\0'; i++)
    {
        hashval = tolower(word[i]) + (hashval << 5) - hashval;
    }

    // Retorna el valor hash ajustado al tamaño de la tabla
    return hashval % HASH_SIZE;
}

// Tabla hash
node *table[HASH_SIZE] = {NULL};

// Número de palabras cargadas en la tabla hash
unsigned int word_count = 0;

// Devuelve true si la palabra está en el diccionario, de lo contrario, false
bool check(const char *word)
{
    unsigned int hash_value = hash(word);

    // Recorre la lista enlazada en el valor hash y compara la palabra con cada nodo
    for (node *tmp = table[hash_value]; tmp != NULL; tmp = tmp->next)
    {
        if (strcasecmp(tmp->word, word) == 0)
        {
            return true; // La palabra está en el diccionario
        }
    }

    return false; // Palabra no encontrada en el diccionario
}

// Carga el diccionario en memoria, devuelve true si se carga correctamente, de lo contrario, false
bool load(const char *dictionary)
{
    // Abrir archivo de diccionario
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false; // No se pudo abrir el archivo
    }

    char word[LENGTH + 1];

    // Leer palabras del archivo y agregarlas a la tabla hash
    while (fscanf(file, "%s", word) != EOF)
    {
        // Asignar memoria para un nuevo nodo
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            fclose(file);
            return false; // No se pudo asignar memoria
        }

        // Copiar la palabra en el nodo
        strncpy(new_node->word, word, LENGTH);

        // Obtener un valor hash para la palabra
        unsigned int hash_value = hash(word);

        // Agregar el nodo al principio de la lista enlazada en el valor hash
        new_node->next = table[hash_value];
        table[hash_value] = new_node;

        // Incrementar el conteo de palabras
        word_count++;
    }

    // Cerrar archivo de diccionario
    fclose(file);

    return true; // Diccionario cargado correctamente
}

// Devuelve el número de palabras en el diccionario si se ha cargado, de lo contrario, 0
unsigned int size(void)
{
    return word_count;
}

// Libera la memoria utilizada por el diccionario, devuelve true si se descarga correctamente, de lo contrario, false
bool unload(void)
{
    // Recorre la tabla hash
    for (int i = 0; i < HASH_SIZE; i++)
    {
        node *tmp = table[i];
        while (tmp != NULL)
        {
            node *next = tmp->next;
            free(tmp);
            tmp = next;
        }

        table[i] = NULL;
    }

    return true;
}
