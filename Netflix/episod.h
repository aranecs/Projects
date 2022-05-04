#ifndef EPISOD_H_INCLUDED
#define EPISOD_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct episodnode {
    int time; // durata episodului
    struct episodnode *next; // legatura la episodul urmator
} EpisodNode;

typedef struct {
    int time; // durata totala a epizoadelor
    int size; // numarul de episoade
    EpisodNode *head; // legatura la primul element din coada
    EpisodNode *tail; // legatura la ultimul element din coada
} EpisodQueue;

/*Functia creeaza o coada vida de episoade*/
EpisodQueue *createEpisodQueue();

/*Functia creeaza un episod cu durata indicata*/
EpisodNode *createEpisodNode(int time);

/*Functia verifica daca coada de episoade este goala*/
int isEmptyEpisodQueue(EpisodQueue *EQ);

/*Functia creeaza un episod si il adauga adauga in coada
 *de episoade la inceput (enqueue pe cozi)*/
void enqueueEQ(EpisodQueue *EQ, int time);

#endif /* EPISOD_H_INCLUDED */
