#ifndef FUNCTII_H_
#define FUNCTII_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct CurrentNodeDeget{
    char elem;
    struct CurrentNodeDeget* left;
    struct CurrentNodeDeget* right;
} CurrentNodeDeget;

typedef struct ListaBanda{
    CurrentNodeDeget* first ; // pointer catre primul nod din lista
    CurrentNodeDeget* last;
    CurrentNodeDeget* deget;
} *ListaBanda;

//alocare memorie nod si banda
CurrentNodeDeget *createNode(char elem) {
    CurrentNodeDeget *node = (CurrentNodeDeget *)calloc(1, sizeof(CurrentNodeDeget));
    node->elem = elem;
    return node;
}
ListaBanda createBanda(void) {
    ListaBanda list = (ListaBanda)calloc(1, sizeof(ListaBanda));
    CurrentNodeDeget *sentinel;
    sentinel = createNode(0);
    CurrentNodeDeget *nod;
    nod = createNode('#');
    //fac legaturi intre santinela si nod
    sentinel->right = nod;
    nod->left = sentinel;
    //fac legaturi intre lista, santinela si nod ptr a-mi crea banda initiala;
    list->first = sentinel;
    list->last = nod;
    list->deget = nod;
    return list;
}

//operatiile de tip UPDATE
//scriere a nodului curent;
//parcurgere banda;
//inserare dreapta, inserare stanga;
void MOVE_LEFT(ListaBanda list) {
   //verificare daca sunt pozitionata pe primul element din banda
    if (list->deget->left == list->first) {
        return ;
    }
    //verificare daca sunt pozitionata cu degetul in interiorul unei benzi mai mari
    if (list->deget->left != NULL) {
        list->deget = list->deget->left;
        return ;
    }
}
void MOVE_RIGHT(ListaBanda list) {
    //verificare daca sunt pozitionata la sfarsitul listei
    if (list->deget->right == NULL) {
        //creez un nod;
        CurrentNodeDeget *node = createNode('#');
        //refac legaturile;
        list->deget->right = node;
        node->left = list->deget;
        //mut degetul pe noua pozitie;
        list->deget = node;
        list->last = node;
        return;
    }
    //verificare daca ma aflu in interiorul listei 
    else {
        list->deget = list->deget->right;
        return;
    }
}
//operatiile de tip QUERY
//afisare caracter curent(un singur caracter);
void SHOW_CURRENT(ListaBanda list, FILE* out) {
    if (list->deget->left == list->first && list->deget->right == list->last) {
        fprintf(out,"%c\n", list->deget->elem);
    } else fprintf(out,"%c\n", list->deget->elem);
}
//afisare elementele continute de banda;
void SHOW(ListaBanda list, FILE* out) {
//trebuie sa parcurg toata lista si doar verific daca elementul aflat pe pozitia curenta este cea indicata de deget
//caz in care afisez elementul intre doua " | ". 
//celelate elemente vor fi afisate simplu, toate pe aceeasi linie.
CurrentNodeDeget *iter = list->first->right;
while (iter != NULL) {
    //cand gasesc elementul indicat de deget, il afisez.
    if (iter == list->deget) {
        fprintf(out,"|%c|", list->deget->elem);
    } else fprintf (out,"%c", iter->elem);
    //ma mut cu o pozitie la dreapta la fiecare parcurgere;
    iter = iter->right;
  }fprintf(out,"\n");
}
void MOVE_LEFT_CHAR(char c, ListaBanda list, FILE* out) {
    int k = 0;
    CurrentNodeDeget *iter = list->deget;
    //caz in care elementul pe care il caut se afla deja pe pozitia indicata de deget
    if (iter->elem == c) {
        return;
    }
    //caz in care elementul pe care il caut se afla in stanga 
    while (iter->left != list->first) {
        //caut pana ajung pe ultima pozitie din stanga;
        if (iter->left->elem == c) {
        //daca gasesc elementul ma mut cu degetul pe aceasta pozitie;
            iter = iter->left;
        //folosesc un contor ptr a verifica daca am gasit sau nu elementul cautat;
            list->deget = iter;
            k++;
            return;
        }
        iter = iter->left;
    }
    //daca nu am gasit elementul cautat, afisez ERROR;
    if (k == 0) {
        fprintf(out,"ERROR\n");
    }
}
void MOVE_RIGHT_CHAR(char c, ListaBanda list) {
    int k = 0;
    CurrentNodeDeget *iter = list->deget;
    //caz in care elementul pe care il caut se afla deja pe pozitia indicata de deget
    if (iter->elem == c) {
        return;
    }
    //parcurg banda
    while (iter->right != NULL) {
        //daca gasesc elementul cautat, ma mut cu degetul pe aceasta pozitie;
        if (iter->right->elem == c) {
            iter = iter->right;
            list->deget = iter;
            k++;
            return;
        }
        iter = iter->right;
    }
    //caz in care elementul meu se afla fix pe ultima pozitie
    if (list->last->elem == c) {
        iter = list->last;
        list->deget = iter;
        k++;
        return;
    }
    //caz in care elementul cautat nu se afla in dreapta si adaug un nou nod
    if (iter->right == NULL && k == 0) {
        CurrentNodeDeget *nod = createNode('#');
        nod->left = list->last;
        list->last->right = nod;
        list->last = nod;
        //ma mut cu degetul pe nodul inserat.
        iter = nod;
        list->deget = iter;
        return;
    }
   
}
ListaBanda WRITE(char c, ListaBanda list) {
    list->deget->elem = c;
    return list;
}
ListaBanda INSERT_LEFT(char c, ListaBanda list, FILE* out) {
    if (list->deget->left == list->first) {
        fprintf(out,"ERROR\n");
        return list;
    } else {
        CurrentNodeDeget *nod = createNode(c);
        nod->right = list->deget;
        nod->left = list->deget->left;
        list->deget->left->right = nod;
        list->deget->left = nod;
        list->deget = nod;
        return list;
    }
}
ListaBanda INSERT_RIGHT(char c, ListaBanda list) {
    CurrentNodeDeget *nod = createNode(c);
    if (list->deget->right == NULL) {
        nod->left = list->deget;
        list->deget->right = nod;
        list->deget = nod;
        list->last = nod;
        return list;
    } else {
        nod->left = list->deget;
        nod->right = list->deget->right;
        list->deget->right->left = nod;
        list->deget->right = nod;
        list->deget = nod;
        return list;
    }
}

#endif