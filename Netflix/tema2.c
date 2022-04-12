/*SOLONARU MIHAELA 313CB*/
#include "serial.c"

int main(int argc, char const *argv[])
{
    /*
    * SLType[ID]
    * ID = 0 => categoria TOP10
    * ID = 1 => Tendinte
    * ID = 2 => Documentare
    * ID = 3 => Tutoriale
    * ID = 4 => coada watch_later
    * ID = 5 => stiva currently_watching
    * ID = 6 => stiva history
    */
    SerialList **SLType = (SerialList**)malloc(7*sizeof(SerialList*));
    for (int i = 0; i < 7; i++) {
        SLType[i] = createSerialList();
    }



    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "wr");
    char function[100];
    char name[100];
    char categorie[100];
    //char *function = malloc(100*sizeof(char));
    //char *name = malloc(100*sizeof(char));
    //char *categorie = malloc(100*sizeof(char));


    
    while (!feof(input)) {
        // citesc functia
        fscanf(input, "%s ", function);
        
        // daca e functia add
        if (strcmp(function, "add") == 0) {
            // citesc datele despre serial
            int ID; fscanf(input, "%d ", &ID);
            fscanf(input, "%s ", name);
            double rating; fscanf(input, "%lf ", &rating);
            int numSes; fscanf(input, "%d ", &numSes);
            // formez coada de sezoane
            SeasonQueue *SQ = createSeasonQueue();
            for (int i = 0; i < numSes; i++) {
                int numEps; fscanf(input, "%d ",&numEps);
                // formez coada de episoade
                EpisodQueue *EQ = createEpisodQueue();
                for (int j = 0; j < numEps; j++) {
                    int durata; fscanf(input, "%d ", &durata);
                    enqueueEQ(EQ, durata);
                }
                enqueueSQ(SQ, EQ);
            }
            // formez serialul, inserez in lista si printez rezultatul in out_file.txt
            fprintf(output, "Serialul %s a fost adaugat la pozitia %d.\n", name,
            	insert(SLType[ID], SQ, ID, 0, name, rating));
        }

        // daca e functia add_sez
        if(strcmp(function, "add_sez") == 0){
            fscanf(input, "%s ", name);
            int numEps; fscanf(input, "%d ",&numEps);
            // verific daca nu e in SLType[6] (history)
            if (getSerial(SLType[6], name) != NULL) {
                fprintf(output, "Serialul %s e in history\n", name);
            } else {
                // formez coada de episoade
                EpisodQueue *EQ = createEpisodQueue();
                for (int j = 0; j < numEps; j++) {
                    int durata; fscanf(input, "%d ", &durata);
                    enqueueEQ(EQ, durata);
                }
                // caut unde sa inserez noul sezon
                SerialNode *nodeSer = NULL; 
                for(int i = 0; i < 6; i++){
                    nodeSer = getSerial(SLType[i], name);
                    if(nodeSer != NULL){
                    	// inserez sezonul
                        enqueueSQ(nodeSer->SQ, EQ);
                        break;
                    }
                }
                fprintf(output, "Serialul %s are un sezon nou.\n", name);
            }    
        }

        // daca e add_top
        if (strcmp(function, "add_top") == 0) {
            int position; fscanf(input, "%d ", &position);
            fscanf(input, "%s ", name);
            double rating; fscanf(input, "%lf ", &rating);
            int numSes; fscanf(input, "%d ", &numSes);
            // formez coada de sezoane
            SeasonQueue *SQ = createSeasonQueue();
            for (int i = 0; i < numSes; i++) {
                int numEps; fscanf(input, "%d ",&numEps);
                // formez coada de episoade
                EpisodQueue *EQ = createEpisodQueue();
                for (int j = 0; j < numEps; j++) {
                    int durata; fscanf(input, "%d ", &durata);
                    enqueueEQ(EQ, durata);
                }
                enqueueSQ(SQ, EQ);
            }
            // inserez in lista top10 cu ID 0
            insertTOP10(SLType[0], SQ, 0, position, name, rating);
            fprintf(output, "Categoria top10: ");
            printSerialList(SLType[0], output);
        }

        // daca e functia later
        if (strcmp(function, "later") == 0) {
            fscanf(input, "%s\n", name);
            // caut Serialul dupa nume in cele 4 liste
            SerialNode *nodeSer = NULL; 
            for(int i = 0; i < 4; i++){
                nodeSer = getSerial(SLType[i], name);
                // cand gasesc serialul il adaug in coada watch_later
                if(nodeSer != NULL){
                    // inserez serialul in coada watch_later
                    insertFRONT(SLType[4], nodeSer->SQ, nodeSer->ID, nodeSer->pos, nodeSer->name, nodeSer->rating);
                    // elimin serialul din categorie
                    if (i == 0) {
                    	removeTOP10(SLType[i], name);
                    } else {
                    	removeL(SLType[i], name);
                    }
                    fprintf(output, "Serialul %s se afla in coada de asteptare pe pozitia %d.\n",nodeSer->name, SLType[4]->size);
                    break;
                }
            }

        }

        // daca e functia watch
        if (strcmp(function, "watch") == 0) {
            fscanf(input, "%s ", name);
            int durata; fscanf(input, "%d\n", &durata);

            // caut Serialul dupa nume in cele 4 categorii + watch_later + currently_watching
            SerialNode *nodeSer = NULL; 
            for(int i = 0; i < 6; i++){
                nodeSer = getSerial(SLType[i], name);
                // cand gasesc serialul
                if(nodeSer != NULL){
                    if (getSerial(SLType[5], name) != NULL) {
                        // daca se afla in stiva currently_watching
                        if (durata >= nodeSer->SQ->time) {
                            // daca pot privi serialul integral
                            // decrementez durata
                            nodeSer->SQ->time -= durata;
                            // elimin serialul din stiva currently_watching
                            removeL(SLType[5], name);
                            // adaug serialul in stiva history
                            insertFRONT(SLType[6], nodeSer->SQ, nodeSer->ID, nodeSer->pos, nodeSer->name, nodeSer->rating);
                            fprintf(output, "Serialul %s a fost vizionat integral.\n", name);
                            break;
                        } else {
                        	// altfel actualizez pozitia serialului in stiva currently_watching
                        	// elimin serialul din stiva
                        	removeL(SLType[5], name);
                            // decrementez durata
                            nodeSer->SQ->time -= durata;
                            // adaug serialul in fata stivei
                            insertFRONT(SLType[5], nodeSer->SQ, nodeSer->ID, nodeSer->pos, nodeSer->name, nodeSer->rating);
                            break;
                        }
                    } else {
                        // daca nu se afla in stiva currently_watching
                        // daca il pot viziona integral
                        if (durata >= nodeSer->SQ->time) {
                            // decrementez durata
                            nodeSer->SQ->time -= durata;
                            // adaug serialul in stiva history
                            insertFRONT(SLType[6], nodeSer->SQ, nodeSer->ID, nodeSer->pos, nodeSer->name, nodeSer->rating);
                            // sterg din celelalte liste
                            if (i == 0) {
                            	removeTOP10(SLType[i], name);
                            } else {
                            	removeL(SLType[i], name);
                            }
                            fprintf(output, "Serialul %s a fost vizionat integral.\n", name); 
                            break;
                        } else {
                            // decrementez durata
                            nodeSer->SQ->time -= durata;
                            // sterg din celelalte liste
                            if (i == 0) {
                                removeTOP10(SLType[i], name);
                            } else {
                                removeL(SLType[i], name);
                            }
                            // adaug in stiva currently_watching
                            insertFRONT(SLType[5], nodeSer->SQ, nodeSer->ID, nodeSer->pos, nodeSer->name, nodeSer->rating);
                            break;
                        }
                    }
                    break;
                }
            }
        }
        
        if (strcmp(function, "show") == 0) {
            fscanf(input, "%s\n", categorie);
            if (strcmp(categorie, "1") == 0) {
                fprintf(output, "Categoria %s: ", categorie);
                printSerialList(SLType[1], output);
            } else if (strcmp(categorie, "2") == 0) {
                fprintf(output, "Categoria %s: ", categorie);
                printSerialList(SLType[2], output);
            } else if (strcmp(categorie, "3") == 0) {
                fprintf(output, "Categoria %s: ", categorie);
                printSerialList(SLType[3], output);
            } else if (strcmp(categorie, "top10") == 0) {
                fprintf(output, "Categoria %s: ", categorie);
                printSerialList(SLType[0], output);
            } else if (strcmp(categorie, "later") == 0) {
                fprintf(output, "Categoria %s: [", categorie);
                if (SLType[4]->head != NULL) {
                	printSerialQueue(SLType[4]->head->next, output);
            		fprintf(output, "(%s, %.1f)",SLType[4]->head->name, SLType[4]->head->rating);
                	fprintf(output, "].\n");
                } else {
                	fprintf(output, "].\n");
                }
            } else if (strcmp(categorie, "watching") == 0) {
                fprintf(output, "Categoria %s: ", categorie);
                printSerialList(SLType[5], output);
            } else if (strcmp(categorie, "history") == 0) {
                fprintf(output, "Categoria %s: ", categorie);
                printSerialList(SLType[6], output);
            }
        }
    }
    return 0;
}