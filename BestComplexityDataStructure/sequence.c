#include "sequence.h"

Sequence init() {
	// returnez structura vida
	Sequence data_structure = NULL;
	return data_structure;
}

/*
*		Functia creaza un nou nod de structura
*/
Sequence create_node(Type item, int index) {
	// aloc memorie si initializez nodul de structura
	Sequence data_structure = malloc(sizeof(struct sequence));
	data_structure->index = index;
	data_structure->item = item;
	data_structure->left = NULL;
	data_structure->right = NULL;
	data_structure->height = 1;
	// returnez nodul de structura format
	return data_structure;
}

/*
*		Returneaza maximul intre x si y
*/
int maximum(int x, int y) {
	if (x > y)
		return x;
	return y;
}

/*
*		Returneaza inaltimea nodului de structura de date
*/
int height(Sequence data_structure) {
	// daca nodul este vid
	if (data_structure == NULL)
		return 0;
	// returnez inaltimea nodului
	return data_structure->height;
}

/*
*		Functia executa rotatia la dreapta a unui nod din strucutra
*/
Sequence right_rotate(Sequence data_structure) {
	// fiul stang a nodului (unde nodul este parinte)
	Sequence left_child = data_structure->left;
	// subarborele drept a fiului stang
	Sequence right_subtree = left_child->right;

	// rotatia :
	// fiul stang devine parinte pentru nod
	left_child->right = data_structure;
	// subarborele stang a nodului devine subarborele drept a fiului stang
	data_structure->left = right_subtree;

	// actualizarea inaltimilor
	data_structure->height = maximum(height(data_structure->left), 
						height(data_structure->right)) + 1;
	left_child->height = maximum(height(left_child->left), 
						height(left_child->right)) + 1;
	
	// returnez noul parinte
	return left_child;
}

/*
*		Functia executa rotatia la stanga a unui nod din strucutra
*/
Sequence left_rotate(Sequence data_structure) {
	// fiul drept a nodului (unde nodul este parinte)
	Sequence right_child = data_structure->right;
	// subarborele stang a fiului drept
	Sequence left_subtree = right_child->left;

	// rotatia :
	// fiul drept devine parinte pentru nod
	right_child->left = data_structure;
	// subarborele drept a nodului devine subarborele stang a fiului drept
	data_structure->right = left_subtree;

	// actualizarea inaltimilor
	data_structure->height = maximum(height(data_structure->left), 
						height(data_structure->right)) + 1;
	right_child->height = maximum(height(right_child->left), 
						height(right_child->right)) + 1;
	
	// returnez noul parinte
	return right_child;
}

/*
*		Functia retuneaza factorul da echilibrare = (-1, 0, 1) a unui nod
*/
int BalanceFactor(Sequence data_structure) {
	// daca nodul e vid factorul de echilibrare este 0
	if (data_structure == NULL)
		return 0;
	// factorul = diferenta inaltimilor a subarborelui drept cu cel stang
	return height(data_structure->right) - height(data_structure->left);
}

Sequence insert(Sequence data_structure, Type item, int index) {
	
	// daca structura este vida => inseram nodul
	if (data_structure == NULL)
		return create_node(item, index);

	// daca deja exista elementul cu indexul dat
	if (data_structure->index == index)
		// nu modific structura
		return data_structure;

	// altfel caut pozitia pentru inserare si inserez 
	if (data_structure->index > index)
		// plec recursiv pe ramura din stanga
		data_structure->left = insert(data_structure->left, item, index);
	else
		// plec recursiv pe ramura din dreapta
		data_structure->right = insert(data_structure->right, item, index);

	// actualizez inaltimea deoarece am adaugat un element
	data_structure->height = 1 + maximum(height(data_structure->left), 
							height(data_structure->right));

	// verific daca arborele este echilibrat :

	/*
	----------------------------ATENTIE!!!---------------------------------

	Daca inserarea elementelor s-ar produce in ordinea crescatoare (dupa indexi)
	si consecutiv (0,1,2,3,4, ... , size(data_structure) - 1) =>
	atunci vom avea doar cazul in care inseram in subarborele drept a fiului
	drept. Eu am tinut cont si de inserarea neordonata (Daca vrem sa inseram N
	elemente, le putem insera in orice ordine dorim).
	*/

	// Inserarea in subarborele stang a fiului stang => rotatie dreapta nod
	if (BalanceFactor(data_structure) < -1 &&
	 	data_structure->left->index > index)
		return right_rotate(data_structure);

	// Inserarea in subarborele drept a fiului drept => rotatie stanga nod
	if (BalanceFactor(data_structure) > 1 && 
		data_structure->right->index < index)
		return left_rotate(data_structure);

	// Inserarea in subarborele drept a fiului stang =>
	// rotatie stanga a fiului stang + rotatie dreapta a nodului
	if (BalanceFactor(data_structure) < -1 && 
		data_structure->left->index < index) {
		data_structure->left = left_rotate(data_structure->left);
		return right_rotate(data_structure);
	}

	// Inserarea in subarborele stang a fiului drept =>
	// rotatie dreapta a fiului drept + rotatie stanga a nodului
	if (BalanceFactor(data_structure) > 1 && 
		data_structure->right->index > index) {
		data_structure->right = right_rotate(data_structure->right);
		return left_rotate(data_structure);
	}

	// daca arborele era echilibrat returnez nodul nemodificat
	return data_structure;
}

/*
*		Functia returneaza nodul cu indexul minimal (cel mai din stanga nod)
*/
Sequence minimum_node(Sequence data_structure) {
    // nod folosit pentru parcurgerea structurii 
    Sequence node = data_structure; 
  	
  	// parcurg ramura stanga a structurii
    while (node->left != NULL) 
        node = node->left; 
  	// returnez nodul cu indexul minimal din structura
    return node; 
}

/*
*		Functia actualizeaza indexii la structura. Este folosita in functia
*		delete(). Daca stergem elementul de la indexul x, idexul elementelor
*		de la indexul (x+1) pana la size(struct) - 1 il decrementez.
*		Prin urmare daca am avut elementele 0 1 2 3 4 si sterg elementul 2 =>
*		voi obtine 0 1 2(fost 3) 3(fost 4).
*/
void update_index(Sequence data_structure) { 
	
	// traversare in inordine a structurii    
    if(data_structure != NULL) {
        update_index(data_structure->left);
        update_index(data_structure->right);
        //decrementarea indexului
        if (data_structure->index > 0)
			data_structure->index = data_structure->index - 1;
		return;
    }
}

Sequence delete(Sequence data_structure, int index) {
	
	// daca structura este vida nu avem ce sterge
	if (data_structure == NULL)
		return data_structure;

	// caut nodul pe care trebuie sa il sterg 
	if (data_structure->index > index){
		// plec recursiv pe ramura din stanga
		data_structure->left = delete(data_structure->left,index);
		//printf("%d-------\n",data_structure->index );

	}
	else if (data_structure->index < index){
		// plec recursiv pe ramura din dreapta
		data_structure->right = delete(data_structure->right, index);
		//printf("%d-------\n",data_structure->index );
		}
	// in caz contrar am gasit nodul pe care trebuie sa il sterg
	else {
		// daca nodul are cel mult un copil
		if (data_structure->right == NULL || data_structure->left == NULL) {

			// nod auxiliar pentru a efectua stergerea
			Sequence tmp = NULL;
			// daca nu are fiu stang
			if (data_structure->left == NULL) {
				tmp = data_structure->right;
			}
			// daca nu are fiu drept
			if (data_structure->right == NULL) {
				tmp = data_structure->left;
			}
			// daca nodul nu are fii
			if (tmp == NULL) {
				tmp = data_structure;
				data_structure = NULL;
			} else {
				// altfel are 1 fiu si copiez in nod continutul fiului
				*data_structure = *tmp;
			}

			// eliberez memoria alocata nodului sters
			free(tmp);

		} else {
			// deoarece e mai usor sa sterg un nod terminal:
			// daca are 2 fii => inlocuiesc nodul parinte cu succesorul sau 
			// nodul cu indexul minim din subarborele drept este succesorul
			Sequence tmp = minimum_node(data_structure->right); 
            // inlocuiesc datele a nodului gasit cu nodul parinte
            data_structure->index = tmp->index; 
            data_structure->item = tmp->item;
            data_structure->height = tmp->height;
            // sterg nodul gasit care e un nod terminal
            data_structure->right = delete(data_structure->right, tmp->index);

		}
	}

	// daca dupa ce am sters elementul nodul este vid
	if (data_structure == NULL)
		return data_structure;

	// fac actualizarea la index a nodurilor care au un index mai mare
	// decat indexul elementului sters
	if (data_structure->index > index){
		// updata la subarborele drep (elementele cu index mai  mare)
		update_index(data_structure->right);
		if(data_structure->index > 0)
			data_structure->index = data_structure->index - 1;
	}

	// actualizez inaltimea deoarece am sters un element
	data_structure->height = 1 + maximum(height(data_structure->left), 
							height(data_structure->right));

	// verific daca arborele este echilibrat :

	/*
	Daca factorul de echilibru este mai mic ca -1 => atunci nodul data_structure
	este neechilibrat spre stanga. Daca in acest caz factorul de echilibrare
	a fiului stang este negativ ori egal cu 0 => inseamna ca inaltimea 
	subarborelui stang a fiului stang este mai mare decat a subarborelui drept
	=> rotatie dreapta. Altfel executam o ratatie stanga a fiului stang pentru
	a ajunge in primul caz.  
	*/
	if (BalanceFactor(data_structure) < -1 && 
		BalanceFactor(data_structure->left) <= 0)
		return right_rotate(data_structure);

	if (BalanceFactor(data_structure) < -1 && 
		BalanceFactor(data_structure->left) > 0) {
		data_structure->left = left_rotate(data_structure->left);
		return right_rotate(data_structure);
	}

	/*
	Daca factorul de echilibru este mai mare ca 1 => atunci nodul data_structure
	este neechilibrat spre dreapta. Daca in acest caz factorul de echilibrare
	a fiului drept este pozitiv => inseamna ca inaltimea subarborelui drept a 
	fiului drept este mai mare decat a subarborelui stang => rotatie stanga. 
	Altfel executam o ratatie dreapta a fiului drept pentru a primi primul caz.  
	*/

	if (BalanceFactor(data_structure) > 1 && 
		BalanceFactor(data_structure->right) >= 0)
		return left_rotate(data_structure);

	if (BalanceFactor(data_structure) > 1 && 
		BalanceFactor(data_structure->right) < 0) {
		data_structure->right = right_rotate(data_structure->right);
		return left_rotate(data_structure);
	}
	
	// daca arborele era echilibrat returnez nodul nemodificat
	return data_structure;
}

Type lookup(Sequence data_structure, int index) {
	// daca structura este vida => returnez -1
	if (data_structure == NULL)
		return -1;

	// daca am gasit nodul necesar
	if (data_structure->index == index)
		// returnez valoarea sa
		return data_structure->item;

	// altfel continui sa caut recursiv 
	if (data_structure->index > index)
		// plec recursiv pe ramura din stanga
		return lookup(data_structure->left, index);
	else
		// plec recursiv pe ramura din dreapta
		return lookup(data_structure->right, index);
}

Sequence set(Sequence data_structure, Type item, int index) {
	// daca structura este vida => nu am ce inlocui
	if (data_structure == NULL)
		return data_structure;

	// daca am gasit nodul necesar
	if (data_structure->index == index) {
		// inlocuiesc valoarea 
		data_structure->item = item;
		// returnez nodul
		return data_structure;
	}

	// altfel continui sa caut recursiv 
	if (data_structure->index > index)
		// plec recursiv pe ramura din stanga
		data_structure->left = set(data_structure->left, item, index);
	else
		// plec recursiv pe ramura din dreapta
		data_structure->right =  set(data_structure->right, item, index);
}
/*
*		Luand in considerarea ca indexarea va fi mereu de la 0 la numarul de
*		elemente din structura - 1 => si faptul ca structura (AVL tree) o
*		formez prin comparare de index la elemente => as putea obtine size()
*		ca valoarea index-ului celui mai din dreapta element + 1 => O(logN).
		Insa eu voi lua in calcul ca utilizatorul ar vrea sa obtina dimensiunea
		substructurilor structurii, de aceea voi parcurge toate elementele;
*/
int size(Sequence data_structure) {
	// daca structura este vida => returnez 0
	if (data_structure == NULL)
		return 0;

	// parcurg recursiv toate elementele
	return size(data_structure->left) + size(data_structure->right) + 1;
}	


Sequence *split(Sequence data_structure, int index) {
	/*
	Pentru a imparti structura in 2 substructuri voi efectua urmatorii pasi:
	1. Formez un vector de 2 elemente de tip Sequence (pe care il voi returna)
	2. Parcurg toate elementele din "data_structure" si inserez elementele de
	la 0 la index in prima substructura, si cele de la index+1 la size(struct)
	in a doua substructura
	*/

	// am alocat un "vector" de 2 elemente de tip Sequence;
	Sequence *sub_data_structure = (Sequence*)malloc(2*sizeof(Sequence));

	// daca structura e vida => nu am ce imparti
	if (data_structure == NULL)
		return NULL;

	Type item;
	// inserez elementele din structura de la 0 la index 
	// in substructura 1 de la 0 la index
	for (int i = 0; i <= index; i++) {
		item = lookup(data_structure, i);
		sub_data_structure[0] = insert(sub_data_structure[0], item, i);
	}
	// inserez elementele din structura de la index+1 la size() 
	// in substructura 2 de la 0 la size() - (index+1)
	for (int i = 0; i < size(data_structure) - (index + 1); i++) {
		item = lookup(data_structure, i + (index + 1));
		sub_data_structure[1] = insert(sub_data_structure[1], item, i);
	}

	// returnez vectorul de substructuri
	return sub_data_structure;
}

Sequence concat(Sequence data_structure1, Sequence data_structure2) {
	/*
	Pentru a concatena 2 structuri, voi efectua urmatorii pasi:
	1. Declar o variabila de tip Sequence care va reprezenta structura
	concatenata.
	2. Initializez structura declarata cu data_structure1 si inserez in ea
	elementele din structura 2 => astfel voi obtine structura concatenata
	*/

	Sequence concat_data_structure = data_structure1;

	Type item;

	int index = size(data_structure1);

	// inserez elementele din structura 2
	for (int i = 0; i < size(data_structure2); i++) {
		// valoarea i-ului element din structura 2
		item = lookup(data_structure2, i);
		// inserez in structura rezultata (la urma)
		concat_data_structure = insert(concat_data_structure, 
								item, index );
		index++;
	}

	// returnez structura rezultata din cocatenarea
	return concat_data_structure;
}

/*
*		Functia utila care poate fi folosita pentru afisarea indexilor
*		structurii in preordine (radacina, fiul stang, fiul drept). Aceasta
*		afisare arata daca structura este echilibrata => complexitatea O(logn)
*/
void preorder_traversal(Sequence data_structure) { 
    // va afisa "index(item)"
    if(data_structure != NULL) { 
        printf("%d(%d) ", data_structure->index, data_structure->item); 
        preorder_traversal(data_structure->left); 
        preorder_traversal(data_structure->right); 
    } 
}

/*
*		Functia utila care poate fi folosita pentru afisarea structurii
*		in inordine (fiul stang, radacina, fiul drept). Aceasta arata daca
*		indexarea in structura este corecta  de la 0 la (size(struct) - 1)
*/
void inorder_traversal(Sequence data_structure) { 
    // va afisa "index(item)"
    if(data_structure != NULL) { 
        inorder_traversal(data_structure->left); 
        printf("%d(%d) ", data_structure->index, data_structure->item); 
        inorder_traversal(data_structure->right); 
    }
}