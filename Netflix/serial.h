#ifndef SERIAL_H_INCLUDED
#define SERIAL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sezon.h"

typedef struct serialnode {
    /*ID = 0 => categoria top10 
     *ID = 1 => categoria tendindte
     *ID = 2 => categoria documentare
     *ID = 3 => categoria tutoriale
     *ID = 4 => coada watch_later
     *ID = 5 => stiva curently_watching
     *ID = 6 => stiva history
     */
    int ID;
    int pos; // doar pentru categoria top10
    char *name;
    double rating;
    SeasonQueue *SQ; // coada de sezoane din serial
    struct serialnode *next; // legatura la serialul urmator
} SerialNode;

typedef struct {
    int size; // numarul de seriale
    SerialNode *head;
    SerialNode *tail;
} SerialList;

/*Functia creeaza o lista de seriale goala*/
SerialList *createSerialList();

/*Functia creeaza un serial cu parametrii specificati*/
SerialNode *createSerialNode(SeasonQueue *SQ, int ID, int pos, char* name, double rating);

/*Functia verifica daca o lista de seriale este goala*/
int isEmptySerialList(SerialList *SL);

/*Functia creeaza si insereaza un serial in fata listei
 *(folosit pentru cozi(enqueue) si stive(push))*/
void insertFRONT(SerialList *SL, SeasonQueue *SQ, int ID, int pos, char *name, double rating);

/*Functia elibereaza memeoria ocupata de un serial*/
void destroySerialNode(SerialNode *node);

/*Functia creeaza un nod si il insereaza in categoria TOP10 dupa pozitie
 *In functie se duce contul ca dimensiunea maxima a listei va ramane mereu 10.
 *De asemenea la o inserare pe pozitia care e deja ocupata se face actualizarea
 *pozitiilor */
void insertTOP10(SerialList *SL, SeasonQueue *SQ, int ID, int pos, char *name, double rating);

/*Functia creeaza un nod si il insereaza in categoria TOP10 dupa rating
 *descrescator, daca ratingul este egal atunci inserez crescator dupa nume.*/
int insert(SerialList *SL, SeasonQueue *SQ, int ID, int pos, char *name, double rating);

/*Functia sterge un serial cu numele necesat din lista de seriale de la oricare pozitie*/
void removeL(SerialList *SL, char *name);

/*Functia sterge un serial din categoria top 10 de la oricare pozitie,
 * de asemenea duc contul de actualizarea pozitiilor pentru serialele
 *imediat urmatoare a serialului sters*/
void removeTOP10(SerialList *SL, char *name);

/*Functia imi returneaza adresa serialului cu numele necesar din lista
 *de seriale si NULL in cazul ca acesta nu exista in lista*/
SerialNode *getSerial(SerialList *SL, char* name);

/*Functia pentru a printa continutul listei*/
void printSerialList(SerialList *SL, FILE *output);

/*Functie recursiva pentru a printa continutul cozii
 *deoarece avem liste simplu inlantuite, pentru a parcurge de la
 *sfarsit la inceput ma folosesc de recursivitate*/
void printSerialQueue(SerialNode *serial, FILE *output);

#endif /* SERIAL_H_INCLUDED */
