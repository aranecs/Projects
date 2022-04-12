/*SOLONARU MIHAELA 313CB*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sezon.c"
#include "serial.h"

SerialList *createSerialList()
{
    SerialList *SL = (SerialList*)malloc(sizeof(SerialList));

    if (SL == NULL)
        return NULL;
    SL->size = 0;
    SL->head = NULL;
    SL->tail = NULL;
    return SL;
}

SerialNode *createSerialNode(SeasonQueue *SQ, int ID, int pos, char *name, double rating)
{
    SerialNode *node = (SerialNode*)malloc(sizeof(SerialNode));

    if (node == NULL)
        return NULL;
    node->SQ = SQ;
    node->ID = ID;
    node->pos = pos;
    node->name = calloc(100,sizeof(char));
    strcpy(node->name, name);
    node->rating = rating;
    node->next = NULL;
    return node;
}

void insertFRONT(SerialList *SL, SeasonQueue *SQ, int ID, int pos, char *name, double rating)
{
    SerialNode *node = createSerialNode(SQ, ID, pos, name, rating);

    if (SL->head == NULL) {
        SL->head = node;
        SL->tail = node;                                
    } else {                                                
        node->next = SL->head;
        SL->head = node;
    }
    SL->size++;
    return;
}

void insertTOP10(SerialList *SL, SeasonQueue *SQ, int ID, int pos, char *name, double rating)
{
    SerialNode *node = createSerialNode(SQ, ID, pos, name, rating);
    
    // daca lista e vida
    if (SL->head == NULL) {
        SL->head = node;
        SL->tail = node;
        SL->size += 1;
        return;
    }

    SerialNode *curr = SL->head;
    SerialNode *prev = SL->head;

    // inserez la inceput
    if (pos <= SL->head->pos) {
        // 2 cazuri :
        if (SL->head->pos == pos) {
        	// inserez in fata
            node->next = prev;
            SL->head = node;
            SL->size += 1;
            // actualizez locurile
            prev = node;
            if (curr->pos == prev->pos){
            	curr->pos += 1;
            }
            while(curr->next != NULL) {
            	prev = curr;
            	curr = curr->next;
            	if (curr->pos == prev->pos) {
            		curr->pos += 1;
            	}
        	}
        	// daca am depasit dimensiunea => elimin ultimul element
        	if (SL->size == 11) {
        		prev->next = NULL;
        		SL->tail = prev;
        		SL->size = 10;
        	}
        	return;
        } else {
            // inserez in fata primului element fara actualizare
            node->next = prev;
            SL->head = node;
            SL->size += 1;
            return;
        }
    }

    // inserez la sfarsit
    if (pos >= SL->tail->pos) {
        // aflu pozitiile astfel ca curr sa fie ultimul nod
        while(curr->next != NULL) {
            prev = curr;
            curr = curr->next;
        }
        // 2 cazuri :
        if (SL->tail->pos == pos) {
        	// inserez in fata ultimului nod
        	node->next = curr;
        	prev->next = node;
            SL->size += 1;
            // actualizez pozitia
            curr->pos += 1;
            // daca am depasit
            if (SL->size == 11) {
            	node->next = NULL;
            	SL->tail = node;
            	SL->size = 10;
            }
            return;
        } else {
            // inserez dupa ultimul element
            curr->next = node;
            SL->tail = node;
            SL->size += 1;
            return;
        }
    }

    // altfel inserez intre prima si ultima pozitie
    while (curr->next != NULL) {
        prev = curr;
        curr = curr->next;
        if (pos <= curr->pos) {
            // 2 cazuri :
            if (pos == curr->pos) {
            	// inserez in fata nodului curent
            	node->next = curr;
            	prev->next = node;
            	SL->size += 1;

            	// actualizez pozitiile
            	prev = node;
            	if (curr->pos == prev->pos) {

            	curr->pos += 1;
            	}
            	while(curr->next != NULL) {
            		prev = curr;
            		curr = curr->next;
            		if (curr->pos == prev->pos) {
         		   		curr->pos += 1;
            		}
            	}

            	// verific daca nu am depasit limita
            	if (SL->size == 11) {
            		prev->next = NULL;
            		SL->tail = prev;
            		SL->size = 10;
            	}
            	return;
            } else {
                // inserez in fata nodului curent 
                node->next = curr;
                prev->next = node;
                SL->size += 1;
                return;
            }
        }
    }
}

int insert(SerialList *SL, SeasonQueue *SQ, int ID, int pos, char *name, double rating)
{
    SerialNode *node = createSerialNode(SQ, ID, pos, name, rating);
    // daca lista e vida
    if (SL->head == NULL) {
        SL->head = node;
        SL->tail = node;
        SL->size += 1;
        return 1;
    }

    // daca trebuie sa inseram la inceput
    if (node->rating > SL->head->rating) {
        node->next = SL->head;
        SL->head = node;
        SL->size += 1;
        return 1;
    } else if (node->rating == SL->head->rating) {
        if (strcmp(node->name, SL->head->name) < 0) {
            node->next = SL->head;
            SL->head = node;
            SL->size += 1;
            return 1;
          }
    }

    // daca trebuie sa inseram la sfarsit
    if (node->rating < SL->tail->rating) {
        SL->tail->next = node;
        SL->tail = node;
        SL->size += 1;
        return SL->size;
    } else if (node->rating == SL->tail->rating) {
        if (strcmp(node->name, SL->tail->name) > 0) {
            SL->tail->next = node;
            SL->tail = node;
            SL->size += 1;
            return SL->size;
        }
    }

    // altfel trebuie sa inseram intre inceputul si sfarsitul listei
    SerialNode *curr = SL->head->next;
    SerialNode *prev = SL->head;
    int position = 2;

    while(curr != NULL) {
        if (node->rating > curr->rating) {
            // adaug intre prev si curr
            node->next = curr;
            prev->next = node;
            SL->size += 1;
            return position;
        } else if (node->rating == curr->rating) {
            if (strcmp(node->name, curr->name) < 0) {
                // adaug intre prev si curr
                node->next = curr;
                prev->next = node;
                SL->size += 1;
                return position;
             }
        }
        prev = curr;
        curr = curr->next;
        position++;
    }

    return -1;
}

void removeL(SerialList *SL, char *name)
{
	if(SL->head == NULL) {
        return;
    }

    SerialNode *curr = SL->head;
    SerialNode *prev = SL->head;

    // sterg la inceput
    if (strcmp(SL->head->name, name) == 0){
        SL->head = curr->next;
        SL->size -= 1;
        return;
    }
    // sterg la sfarsit
    if(strcmp(SL->tail->name, name) == 0) {
        while(curr->next != NULL) {
            prev = curr;
            curr = curr->next;
        }
        prev->next = NULL;
        SL->tail = prev;
        SL->size -= 1;
        return;
    }
    // sterg intre
    curr = SL->head->next;
    prev = SL->head;
    while (curr->next != NULL) {
        if(strcmp(curr->name, name) == 0) {
            prev->next = curr->next;
            SL->size -= 1;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void removeTOP10(SerialList *SL, char *name)
{
    if(SL->head == NULL) {
        return;
    }

    SerialNode *curr = SL->head;
    SerialNode *prev = SL->head;
    SerialNode *node = NULL;

    // sterg la inceput
    if (strcmp(SL->head->name, name) == 0){
        SL->head = curr->next;
        // actualizez pozitiile
        node = SL->head;
            while(node != NULL) {
            node->pos -= 1;
            node = node->next;
        }
        SL->size -= 1;
        return;
    }
    // sterg la sfarsit
    if(strcmp(SL->tail->name, name) == 0) {
        while(curr->next != NULL) {
            prev = curr;
            curr = curr->next;
        }
        prev->next = NULL;
        SL->tail = prev;
        SL->size -= 1;
        return;
    }
    // sterg intre
    curr = SL->head->next;
    prev = SL->head;
    while (curr->next != NULL) {
        if(strcmp(curr->name, name) == 0) {
            prev->next = curr->next;
            // actualizez pozitiile
            node = prev->next;
            while(node != NULL) {
                node->pos -= 1;
                node = node->next;
            }
            SL->size -= 1;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

SerialNode *getSerial(SerialList *SL, char* name)
{
    SerialNode *node = SL->head;
    while(node != NULL){
        if(strcmp(node->name, name) == 0){
            return node;
        }
        node = node->next;

    }
    return NULL;
}

void printSerialList(SerialList *SL, FILE *output)
{
    fprintf(output, "[");
    SerialNode *nodeSer = SL->head;
    while(nodeSer != NULL) {
        if (nodeSer->next != NULL) {
            fprintf(output, "(%s, %.1f), ",nodeSer->name, nodeSer->rating);
        } else {
            fprintf(output, "(%s, %.1f)",nodeSer->name, nodeSer->rating);
        }
        nodeSer = nodeSer->next;
    }
    fprintf(output, "].\n");
}

void printSerialQueue(SerialNode *serial, FILE *output)
{
	if (serial == NULL) {
		return;
	}

	if (serial->next == NULL) {
            fprintf(output, "(%s, %.1f), ",serial->name, serial->rating);
            return;
	} else {
		printSerialQueue(serial->next, output);
		fprintf(output, "(%s, %.1f), ",serial->name, serial->rating);
		return;
	}
}