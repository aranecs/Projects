#include <stdio.h>
#include <stdlib.h>

typedef int Type;

typedef struct sequence {
	// indexul structurii
	int index;
	// "continutul" structurii
	Type item;
	// pointer la fiul stang
	struct sequence *left;
	//pointer la fiul drept
	struct sequence *right;
	// inaltimea structurii (0 - daca structura e vida)
	int height;

} *Sequence;

// Returneaza structura vida;
Sequence init();

// Insereaza un element in structura pe pozitia index
Sequence insert(Sequence data_structure, Type item, int index);

// Sterge elementul de pe pozitia index din structura
Sequence delete(Sequence data_structure, int index);

// Returneaza valoarea elementului de pe pozitia index
Type lookup(Sequence data_structure, int index);

// Inlocuieste valoarea elementului de pe pozitia index
Sequence set(Sequence data_structure, Type item, int index);

// Returneaza dimensiunea structurii
int size(Sequence data_structure);

// Returneaza cele 2 structuri rezultate in urma divizarii
Sequence *split(Sequence data_structure, int index);

// Returneaza structura rezultata dupa concatenare
Sequence concat(Sequence data_structure1, Sequence data_structure2);