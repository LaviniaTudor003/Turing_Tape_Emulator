#ifndef STIVA_H_
#define STIVA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FUNCTII.h"

//structura pentru nodul stivei de la UNDO
typedef struct nodstivaU {
    CurrentNodeDeget *data;
    struct nodstivaU *next;
} nodstivaUNDO;
//structura pentru stiva de la UNDO
typedef struct stivaU {
    nodstivaUNDO* head; //varful stivei
    long size; //nr elem stiva
} stivaUNDO;
//alocare memorie stiva UNDO
stivaUNDO* initstiva() {
    stivaUNDO* s = (stivaUNDO*) calloc(1, sizeof(struct stivaU));
    return s;
}
//verificare stiva goala
int isEmptysu(stivaUNDO* s) {
    if (s == NULL || s->head == NULL) {
        return 1;
    }
    return 0;
}
//functie de adaugare in stiva respectand regula LIFO
void adaugare(stivaUNDO* stiva, CurrentNodeDeget *data){
   nodstivaUNDO* top = (nodstivaUNDO*)calloc(1, sizeof(struct  nodstivaU));
   if (isEmptysu(stiva) == 1) {
       if (stiva == NULL) {
           return;
       }
       top->data = data;
       top->next = NULL;
       stiva->head = top;
       stiva->size++;
       return;
   }
   top->data = data;
   top->next = stiva->head;
   stiva->head = top;
   stiva->size++;
}
//functie care returneaza elementul din varful stivei fara a-l extrage
CurrentNodeDeget* top(stivaUNDO* stack) {	
	return stack->head->data;
}
//functie care extrage un element din stiva dupa regula LIFO
void pop(stivaUNDO* s) {
    nodstivaUNDO* tmp;
    // if (isEmptysu(s)) {
    //     if(s == NULL) {
    //         return;
    //     }
    //     free(s->head);
    //     s->size = 0;
    //     return;
    // }
    tmp = s->head;
    s->head = s->head->next;
    s->size--;
    free(tmp);
}

#endif