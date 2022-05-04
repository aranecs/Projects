#include <stdio.h>
#include <stdlib.h>
#include "episod.c"
#include "sezon.h"


SeasonQueue *createSeasonQueue()
{
    SeasonQueue *SQ = (SeasonQueue*)malloc(sizeof(SeasonQueue));

    if (SQ == NULL)
        return NULL;
    SQ->size = 0;
    SQ->time = 0;
    SQ->head = NULL;
    SQ->tail = NULL;
    return SQ;
}

SeasonNode *createSeasonNode(EpisodQueue *EQ)
{
    SeasonNode *node = (SeasonNode*)malloc(sizeof(SeasonNode));

    if (node == NULL)
        return NULL;
    node->EQ = EQ;
    node->next = NULL;
    return node;
}

void enqueueSQ(SeasonQueue *SQ, EpisodQueue *EQ)
{
    SeasonNode *node = createSeasonNode(EQ);

    if (SQ->head == NULL) {
        SQ->head = node;
        SQ->tail = node;
    } else {
        node->next = SQ->head;
        SQ->head = node;
    }
    SQ->size++;
    SQ->time += EQ->time;
}
