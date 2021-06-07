#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "heap.h"

typedef struct nodo{
   void* data;
   int priority;
}heapElem;

typedef struct Heap{
  heapElem* heapArray;
  int size;
  int capac;
} Heap;


void* heap_top(Heap* pq){
  if(pq->size==0)return NULL;
    return pq->heapArray[0].data;;
}



void heap_push(Heap* pq, void* data, int priority){
  int k=0;
  int aux;
  pq->heapArray[pq->size].priority = priority;
  pq->heapArray[pq->size].data = data;
  /*
  for(k=0 ; k<pq->size ; k++)
  {
    printf("[%d] ",pq->heapArray[k].priority);
  } 
  printf("\n");*/
  k = pq->size;
  while(pq->heapArray[(k-1)/2].priority < priority)
  {
    aux = pq->heapArray[k].priority;
    pq->heapArray[k].priority = pq->heapArray[(k-1)/2].priority;
    pq->heapArray[(k-1)/2].priority = aux;
    data = pq->heapArray[k].data;
    pq->heapArray[k].data = pq->heapArray[(k-1)/2].data;
    pq->heapArray[(k-1)/2].data = data;
    k = (k-1)/2;
  }
  //printf("([%d]-[%d])\n",pq->size,pq->capac);
  pq->size++;
  //printf("[%d]-[%d]\n",pq->size,pq->capac);
  if(pq->size == pq->capac)
  {
     pq->heapArray = realloc(pq->heapArray, sizeof(heapElem)*((pq->capac*2)+1));
     pq->capac = (pq->capac*2)+1;
     //printf("ENTRA");
  }
}


void heap_pop(Heap* pq){
  pq->heapArray[0].data = 0;
  pq->heapArray[0].priority = 0;
  int i;
  int aux=0;
  int k=0;
  for(i=0 ; i<pq->size ; i++)
  {
    if(pq->heapArray[i].priority>aux)
    {
      aux = pq->heapArray[i].priority;
      k=i;
    }
  }
  //reemplazo del ultimo
  pq->heapArray[0].priority = pq->heapArray[pq->size].priority; 
  pq->heapArray[pq->size].priority = 0;
  pq->heapArray[k].priority = pq->heapArray[0].priority;
  pq->heapArray[0].priority = aux;
  pq->size--;
}

Heap* createHeap(){
  Heap *h = malloc(sizeof(Heap));
  h->capac = 3;
  h->size = 0;
  h->heapArray = malloc(sizeof(heapElem)*3);
   return h;
}
void mostrar(Heap *h)
{
  int i;
  for(i=0 ; i<h->size ; i++)
  {
    printf("%d",h->heapArray[i].priority);
  }
}