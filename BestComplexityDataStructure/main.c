#include "sequence.c"

int main() {
	
	Sequence first_structure = init();
	Sequence second_structure = init();
	Sequence third_structure = init();
	Sequence fourth_structure = init();

	printf("\t\t\tCHECK INIT()\n\n");
	if (first_structure == NULL)
		printf("Prima structura este vida...\n\n");
	set(first_structure,0,0);

	printf("\t\t\tCHECK INSERT()\n\n");
	printf("Inseram 15 elemente in prima structura cu item = index^2...\n\n");
	// data (item) va fi generata dupa formula : index^2
	for (int i = 0; i < 15; i++)
		first_structure = insert(first_structure, i*i, i );


	printf("Afisare index(item) in preordine...\n");
	preorder_traversal(first_structure);
	printf("\n\n");
	printf("Afisare index(item) in inordine...\n");
	inorder_traversal(first_structure);
	printf("\n\n");

	printf("\t\t\tCHECK LOOKUP()\n\n");
	for (int i = 0; i < 15; i += 4)
		printf("Valoarea elementului de pe pozitia %d este %d\n", i, 
				lookup(first_structure, i) );
	printf("\n");

	printf("\t\t\tCHECK SET()\n\n");
	printf("Inlocuim valorile elementelor de pe pozitiile impare cu index*10...\n");
	for (int i = 1; i < 15; i += 2)
		first_structure = set(first_structure, i*10, i);
	printf("Afisare index(item) in preordine...\n");
	preorder_traversal(first_structure);
	printf("\n\n");
	printf("Afisare index(item) in inordine...\n");
	inorder_traversal(first_structure);
	printf("\n\n");	
	
	printf("\t\t\tCHECK SPLIT()\n\n");
	printf("Impart Prima structura in doua (2 si 3) (index = 7)\n");
	Sequence *sub_structure = split(first_structure, 7);
	second_structure = sub_structure[0];
	third_structure = sub_structure[1];
	printf("\nS-au format:\nStructura 2 : (preordine)\n");
	preorder_traversal(second_structure);
	printf("\nStructura 3 : (preordine)\n");
	preorder_traversal(third_structure);
	printf("\n\n");

	printf("\t\t\tCHECK CONCAT()\n\n");
	printf("Concatenez structura 4 (vida) cu structura 3\n");
	fourth_structure = concat(fourth_structure, third_structure);
	printf("Afisare index(item) in preordine...\n");
	preorder_traversal(fourth_structure);
	printf("\n");
	printf("\nConcatenez structura 4 cu structura 1\n");
	fourth_structure = concat(fourth_structure,first_structure);
	printf("Afisare index(item) in preordine...\n");
	preorder_traversal(fourth_structure);
	printf("\n\n");
	printf("Afisare index(item) in inordine...\n");
	inorder_traversal(fourth_structure);
	printf("\n\n");

	printf("\t\t\tCHECK SIZE() and DELETE()\n\n");
	printf("Dimensiunea structurii 1 dim = ( %d )\n", size(first_structure));
	printf("Dimensiunea structurii 2 dim = ( %d )\n", size(second_structure));
	printf("Dimensiunea structurii 3 dim = ( %d )\n", size(third_structure));
	printf("Dimensiunea structurii 4 dim = ( %d )\n", size(fourth_structure));
	int s;
	
	printf("\nSterg din structura 1 elementele de pe pozitii pare...\n");
	s = size(first_structure);
	for (int i = 0; i < s; i++)
		first_structure = delete(first_structure, i);
	printf("Afisare index(item) in preordine...\n");
	preorder_traversal(first_structure);
	printf("\n\n");
	
	s = size(third_structure);
	printf("Sterg toate elementele din structura 3...\n");
	for (int i = 0; i < s; i++)
		third_structure = delete(third_structure, 0);
	printf("Afisare index(item) in preordine...\n");
	preorder_traversal(third_structure);
	printf("\n\n");
	
	printf("Sterg din structura 4 ultimul element pana cand nu raman 5...\n");
	while(size(fourth_structure) > 5)
		fourth_structure = delete(fourth_structure, size(fourth_structure) - 1);
	printf("Afisare index(item) in preordine...\n");
	preorder_traversal(fourth_structure);
	printf("\n\n");

	printf("Dimensiunea structurii 1 dim = ( %d )\n", size(first_structure));
	printf("Dimensiunea structurii 2 dim = ( %d )\n", size(second_structure));
	printf("Dimensiunea structurii 3 dim = ( %d )\n", size(third_structure));
	printf("Dimensiunea structurii 4 dim = ( %d )\n", size(fourth_structure));

	printf("\nSFARSIT. MULTUMESC!\n");

	return 0;
}