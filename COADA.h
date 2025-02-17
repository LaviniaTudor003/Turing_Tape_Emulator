#ifndef COADA_H_
#define COADA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structura nodului pentru coada
typedef struct nodCoada {
    int nrcomanda;
    //c-pentru caracterul care trebuie adaugat in cadrul comenzilor de la coada din main;
    char c;
    struct nodCoada *next;
} NodCoada;
//alocare memorie nod
NodCoada *initNod(int nrcomanda, char c) {
    NodCoada *nod = (NodCoada*)calloc(1, sizeof(struct nodCoada));
    nod->nrcomanda = nrcomanda;
    nod->c = c;
    return nod; 
}
//structura cozii
typedef struct coada{
    NodCoada *head, *tail;
    int size;
} *Coada;
//alocare memorie coada
Coada initCoada() {
    Coada queue = (Coada)calloc(1, sizeof(struct coada));
    return queue;
}
int isEmpty(Coada coada) {
    return coada == NULL || coada->head == NULL || coada->size == 0;
}
//inserare comenzi in coada
Coada intcomenzi(Coada coada, int nrcomanda, char c) {
    NodCoada *nod;
    nod = initNod(nrcomanda, c);
    if (isEmpty(coada)) {
      coada->head = nod;
      coada->tail = nod;
      coada->size++;
      return coada;
    }
    coada->tail->next = nod;
    coada->tail = nod;
    coada->size++;
    return coada;
}
//scoaterea comenzilor din coada
Coada scoatecomenzi(Coada coada) {
    NodCoada *tmp;
    if (!isEmpty(coada)) {
        tmp = coada->head;
        coada->head = coada->head->next;
//de adaugat in locul lui free functia care dealoca memoria;
        free(tmp);
        coada->size--;
    }
    return coada;
}

#endif