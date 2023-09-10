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

/* recomendable mantener referenciado el arreglo *actual/antiguo* de la tabla con un puntero auxiliar. Luego, los valores de la tabla se reinicializan con un nuevo arreglo con el **doble de capacidad**. Por último los elementos del arreglo antiguo se insertan en el mapa *vacío* con el método *insertMap*.
Cree una variable auxiliar de tipo Pair** para matener el arreglo map->buckets (*old_buckets*);
Duplique el valor de la variable capacity.
Asigne a map->buckets un nuevo arreglo con la nueva capacidad.
Inicialice size a 0.
Inserte los elementos del arreglo *old_buckets* en el mapa (use la función insertMap que ya implementó). */
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

/*  Para hacerlo debe buscar el dato y luego *marcarlo* para que no sea válido.
**No elimine el par**, sólo invalídelo asignando NULL a la clave (pair->key=NULL).
Recuerde actualizar la variable size. */
void eraseMap(HashMap * map,  char * key) {    
  long indice = hash(key, map->capacity);
  while(1) {
    if(map->buckets[indice] == NULL) {
      return;
    }
    if(map->buckets[indice]->key != NULL && strcmp(map->buckets[indice]->key, key) == 0) {
      map->buckets[indice]->key = NULL;
      map->size--;
      return;
    }
    indice = (indice + 1) % map->capacity;
  }
}

/* retorna el **Pair** asociado a la clave ingresada. 
Usar la función hash para obtener la posición donde puede encontrarse el par con la clave.
Si la clave no se encuentra avance hasta encontrarla (*método de resolución de colisiones*).
Si llega a una casilla nula, retorne NULL inmediatamente (no siga avanzando, la clave no está).
Recuerde actualizar el índice current a la posición encontrada.
Recuerde que el arreglo es **circular**. */
Pair * searchMap(HashMap * map,  char * key) {   
  long indice = hash(key, map->capacity);
  long primerIndice = indice; // como es circular, si llega al indice inicial entonces significa que no esta.

  while(1) {
    if(map->buckets[indice] == NULL) {
      return NULL;
    }
    if(map->buckets[indice]->key != NULL && strcmp(map->buckets[indice]->key,key) == 0) {
      map->current = indice;
      return map->buckets[indice];
    }
    indice = (indice + 1) % map->capacity; // metodo resulicion colisiones
    if(indice == primerIndice) {
      return NULL;
    }
  }
}

/* Pair * firstMap(HashMap * map) retorna el primer **Pair** válido del arreglo buckets. Pair * nextMap(HashMap * map) retorna el siguiente **Pair** del arreglo buckets a partir índice current. Recuerde actualizar el índice (CURRENT). */
Pair * firstMap(HashMap * map) {
  for(long i = 0; i < map->capacity; i ++) {
    if(map->buckets[i] != NULL && map->buckets[i]->key != NULL) {
      map->current = i;
      return map->buckets[i];
    }
  }
  map->current = -1;
  return NULL;
}

Pair * nextMap(HashMap * map) {
  if (map == NULL || map->buckets == NULL || map->size <= 0) {
    return NULL;
  }
  map->current++;
  while (map->current < map->size) {
    Pair *par = map->buckets[map->current];
    if (par != NULL) {
      return par;
    }
    map->current++;
  }
  return NULL;
}
