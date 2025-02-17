#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "COADA.h"
#include "STIVA.h"
#include "FUNCTII.h"

int main()  
{
    ListaBanda list = createBanda();
    FILE *fp;
    FILE *ies;
    ies = fopen("tema1.out", "wt");
    Coada coada = initCoada();
    stivaUNDO* undo = initstiva();
    stivaUNDO* redo = initstiva();
    char numcom[60];
    int nrcom;
    char c;
    int i;
    CurrentNodeDeget *temp;
    //deschidere fisier pentru citire
    fp = fopen("tema1.in", "rt");
    fscanf(fp, "%d", &nrcom);
    fscanf(fp, "%c", &c);
    //parcurgere fisier
    for (i = 0; i < nrcom; i++) {
        fgets(numcom, 60, fp);
        // printf("%s", numcom);
        //MOVE_LEFT
        if (numcom[0] == 'M' && numcom[7] == 'F' && numcom[8] == 'T' && numcom[9] != '_') {
            coada = intcomenzi(coada,'1', 0);
        }
        //MOVE_RIGHT
        if (numcom[0] == 'M' && numcom[8] == 'H' && numcom[9] == 'T' && numcom[10] != '_') {
            coada = intcomenzi(coada,'2', 0);
        }
        //SHOW_CURRENT
        if (numcom[0] == 'S' && numcom[4] == '_') {
            SHOW_CURRENT(list, ies);
        }
        //SHOW
        if (numcom[0] == 'S' && numcom[4] != '_') {
            SHOW(list, ies);
        }
        //UNDO
        if (numcom[0] == 'U' && numcom[3] == 'O') {
            adaugare(redo, list->deget);
            list->deget = top(undo);
            pop(undo);
        }
        //REDO
        if (numcom[0] == 'R' && numcom[3] == 'O') {
            adaugare(undo, list->deget);
            list->deget = top(redo);
            pop(redo);
        }
        //INSERT_LEFT
        if (numcom[0] == 'I' && numcom[7] == 'L') {
            coada = intcomenzi(coada, '3', numcom[12]);
        }
        //INSERT_RIGHT
        if (numcom[0] == 'I' && numcom[7] == 'R') {
            coada = intcomenzi(coada, '4', numcom[13]);
        }
        //WRITE
        if (numcom[0] == 'W') {
            coada = intcomenzi(coada, '5', numcom[6]);
        }
        //MOVE_LEFT_CHAR
        if (numcom[0] == 'M' && numcom[5] == 'L' && numcom[9] == '_') {
            coada = intcomenzi(coada, '6', numcom[15]);
        }
        //MOVE_RIGHT_CHAR
        if (numcom[0] == 'M' && numcom[5] == 'R' && numcom[10] == '_') {
            coada = intcomenzi(coada, '7', numcom[16]);
        }
        if (numcom[0] == 'E' && numcom[6] == 'E') {
            switch(coada->head->nrcomanda) {
                case '1':
                    if (list->deget != list->first->right) {
                        temp = list->deget;
                        MOVE_LEFT(list);
                        adaugare(undo, temp);
                    } else {
                        MOVE_LEFT(list);
                    }
                    break;
                case '2':
                    temp = list->deget;
                    MOVE_RIGHT(list);
                    adaugare(undo, temp);
                    break;
                case '3':
                    list = INSERT_LEFT(coada->head->c, list, ies);
                    break;
                case '4':
                    list = INSERT_RIGHT(coada->head->c, list);
                    break;
                case '5':
                    list = WRITE(coada->head->c, list);
                    break;
                case '6':
                    MOVE_LEFT_CHAR(coada->head->c, list, ies);
                    break;
                case '7':
                    MOVE_RIGHT_CHAR(coada->head->c, list);
                    break;
                default:
                    printf("what\n");
                    break;
            }
            //printf("fghd\n\nn\n");
            coada = scoatecomenzi(coada);
        } 
    }
    fclose(fp);
   
    return 0;
}
