/*SOLONARU MIHAELA 313CB*/
#ifndef SEZON_H_INCLUDED
#define SEZON_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "episod.h"

typedef struct seasonnode {
    EpisodQueue *EQ; // coada de episoade din sezon
    struct seasonnode *next; // legatura la urmatorul sezon
} SeasonNode;

typedef struct {
    int time; // durata totala a sezoanelor
    int size; // numarul de sezoane
    SeasonNode *head;
    SeasonNode *tail;
} SeasonQueue;

/*Functia creeaza o coada de sezoane vida*/
SeasonQueue *createSeasonQueue();

/*Functia creeaza un sezon cu coada de episoade necesara*/
SeasonNode *createSeasonNode(EpisodQueue *EQ);

/*Functia verifica daca coada de sezoane este goala*/
int isEmptySeasonQueue(SeasonQueue *SQ);

/*Functia creeaza un sezon nou si il insereaza
 *la inceputul cozii de sezoane (enqueue pe cozi)*/
void enqueueSQ(SeasonQueue *SQ, EpisodQueue *EQ);

#endif /* SEZON_H_INCLUDED */
