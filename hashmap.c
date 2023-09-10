#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}

/* Una casilla disponible es una casilla nula, pero también una que tenga un par inválido (key==NULL).
No inserte claves repetidas. 
Recuerde que el arreglo es **circular**.
Recuerde actualizar la variable size.*/
void insertMap(HashMap * map, char * key, void * value) {
  for(long i = 0; i < map->capacity; i++) {
    if(map->buckets[i] != NULL && strcmp(map->buckets[i]->key, key) == 0) {
      return; // se encuentra una existencia (clave repetida)
    }
  }
  
  long indice = hash(key, map->capacity);
  while(map->buckets[indice] != NULL && map->buckets[indice]->key != NULL) { // metodo para  evitar colision
    indice = (indice + 1) % map->capacity;
  }
  Pair * par = (Pair *) malloc(sizeof(Pair));
  if(par == NULL) exit(EXIT_FAILURE);
  par->key = key;
  par->value = value;
  map->buckets[indice] = par;
  map->current = (long) index;
  map->size++;
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}

/* inicializa el arreglo de buckets con casillas nulas, inicializa el resto de variables y retorna el mapa. Inicialice el índice current a -1. */
HashMap * createMap(long capacity) {
  HashMap * MAP = (HashMap *) malloc(sizeof(HashMap));
  if(MAP == NULL) exit(EXIT_FAILURE);
  
  MAP->capacity = capacity;
  MAP->size = 0;
  MAP->current = -1;
  MAP->buckets = (Pair **) malloc(sizeof(Pair *) * capacity);
  if(MAP->buckets == NULL) exit(EXIT_FAILURE);
  
  for(long i = 0; i < capacity; i++) {
    MAP->buckets[i] = NULL;
  }
  
  return MAP;
}

void eraseMap(HashMap * map,  char * key) {    


}

Pair * searchMap(HashMap * map,  char * key) {   


    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
