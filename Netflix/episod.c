/*SOLONARU MIHAELA 313CB*/
#include <stdio.h>
#include <stdlib.h>
#include "episod.h"

EpisodQueue *createEpisodQueue()
{
    EpisodQueue *EQ = (EpisodQueue*)malloc(sizeof(EpisodQueue));

    if (EQ == NULL)
        return NULL;
    EQ->size = 0;
    EQ->time = 0;
    EQ->head = NULL;
    EQ->tail = NULL;
    return EQ;
}

EpisodNode *createEpisodNode(int time)
{
    EpisodNode *node = (EpisodNode*)malloc(sizeof(EpisodNode));

    if (node == NULL)
        return NULL;
    node->time = time;
    node->next = NULL;
    return node;
}

void enqueueEQ(EpisodQueue *EQ, int time)
{
    EpisodNode *node = createEpisodNode(time);

    if (EQ->head == NULL) {
        EQ->head = node;
        EQ->tail = node;
    } else {
        node->next = EQ->head;
        EQ->head = node;
    }
    EQ->size++;
    EQ->time += time;
}
