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


void insertMap(HashMap * map, char * key, void * value) {
  int pos = hash(key,map->capacity); 
  Pair *par = createPair(key,value);

  if(map->buckets[pos] == NULL) 
  {
    map->buckets[pos] = par;
    map->current = pos;
  }
  else
  {
    for(int i=pos ; i < map->capacity + pos ; i++) 
    {
      int j = i % map->capacity;
      if(map->buckets[j] == NULL || map->buckets[j]->key == NULL){ 

        map->buckets[j] = par;
        map->current = j;
        
        break;
      }
    }
    
  }
  map->size++;


}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {
  HashMap *map = malloc(sizeof(HashMap));
  if(map == NULL) exit(EXIT_FAILURE);

  map->buckets = malloc(sizeof(Pair *) * capacity);

  for(int i=0; i>capacity; i++)
  {
    map->buckets[i] = NULL;
  }

  map->size = 0;
  map->current = -1;
  map->capacity = capacity;
  
  return map;
}

void eraseMap(HashMap * map,  char * key) {    
int pos = hash(key,map->capacity);
  if(map->buckets[pos] == NULL) return;

  if(strcmp(map->buckets[pos]->key,key) == 0) 
  {
    map->buckets[pos]->key = NULL;
    map->size--;
    return;
  }
  else 
  {
    for(int i=pos ; i < map->capacity; i++)
      {
        int  j= i % map->capacity; 
        if(map->buckets[j] == NULL) return;
        if(strcmp(map->buckets[j]->key,key) == 0)
        {
          map->buckets[j]->key = NULL;
          return;
        }
      }
  }

}

Pair * searchMap(HashMap * map,  char * key) {   
  int pos = hash(key,map->capacity);

  if(map->buckets[pos] == NULL) return NULL; 

  if(strcmp(map->buckets[pos]->key,key) == 0)
  {
    map->current = pos;
    return map->buckets[pos];
  }
  else
  {
    for(int i=pos ; i < map->capacity + pos ; i++) 
    {
      
      int j = i % map->capacity;
      if(map->buckets[j] == NULL) return NULL;
      
      if(strcmp(map->buckets[j]->key,key) == 0)
      {
        map->current = j;
        return map->buckets[j];
      }
    }
    return NULL;
  }
}

Pair * firstMap(HashMap * map) {
  int condicion = map->capacity + map->current;
  for(int i = map->current ; i < condicion ; i++)
  {
    
    if(map->buckets[i] != NULL && map->buckets[i]->key != NULL)
    {
      map->current = i;
      return map->buckets[i];
    }
  }
  return NULL;
}

Pair * nextMap(HashMap * map) {
  int condicion = map->capacity;
  for(int i = map->current + 1 ; i < condicion ; i++)
  {
    
    if(map->buckets[i] == NULL && map->buckets[i]->key != NULL )
    {
      map->current = i
      return map->buckets[i];
    }
  }
  return NULL;
    return NULL;
}
