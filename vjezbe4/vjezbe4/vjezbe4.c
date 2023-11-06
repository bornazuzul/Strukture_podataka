//4. Napisati program za zbrajanje i množenje polinoma.Koeficijenti i eksponenti se
//čitaju iz datoteke.
//Napomena: Eksponenti u datoteci nisu nužno sortirani.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct _polinom;
typedef struct _polinom* Position;
typedef struct _polinom {
	int koeficjent;
	int eksponent;
	Position next;
}polinom;

Position initalizationOfStructure(int koeficjent, int eksponent);
int readingPolinoms(Position HeadFirst, Position HeadSecond);
int intsertElement(Position head, int koeficjent, int eksponent);
int printPolinom(Position HeadNext);

int main() 
{
	polinom HeadFirst = { .koeficjent = 0, .eksponent = 0, .next = NULL };
	polinom HeadSecond = { .koeficjent = 0, .eksponent = 0, .next = NULL };
	readingPolinoms(&HeadFirst, &HeadSecond);
	printPolinom(HeadFirst.next);
	printPolinom(HeadSecond.next);
}

Position initalizationOfStructure(int koeficjent, int eksponent) {
	Position newElement = NULL;
	newElement = (Position)malloc(sizeof(polinom));
	newElement->eksponent = eksponent;
	newElement->koeficjent = koeficjent;

	if (newElement == NULL) {
		printf("Nije ispravno inicijalzan novi element\n");
		return 0;
	}
	return newElement;
}

int readingPolinoms(Position HeadFirst, Position HeadSecond) {
	FILE* filepointer;
	filepointer = fopen("polinomi.txt", "r");
	if (filepointer == NULL) {
		printf("Nije moguce otvoriti teksutalnu datoteku\n");
		return 0;
	}

	char nextCharacter = "";
	int koeficjent, eksponent = 0;
	while (fscanf(filepointer, "%dx%d%c", &koeficjent, &eksponent, &nextCharacter) == 3) {

		intsertElement(HeadFirst, koeficjent, eksponent);
		//printf("%dx^%d ", koeficjent, eksponent); //provjera ispisa prvog polinoma

		if (nextCharacter == '\n') {
			break;
		}
	}

	while (fscanf(filepointer, "%dx%d%c", &koeficjent, &eksponent, &nextCharacter) == 3) {

		intsertElement(HeadSecond, koeficjent, eksponent);
		//printf("%dx^%d ", koeficjent, eksponent); //provjera ispisa

		if (nextCharacter == '\n') {
			break;
		}
	}
	return 0;
}

int intsertElement(Position head, int koeficjent, int eksponent) {
	Position element = NULL;
	element = initalizationOfStructure(koeficjent, eksponent);

	while (head->next != NULL && head->next->eksponent > element->eksponent) {
		head = head->next;
	}

	element->next = head->next;
	head->next = element;
	return 0;
}

int printPolinom(Position HeadNext) {
	//printf("\n---------Ispis---------\n");
	for (; HeadNext != NULL; HeadNext = HeadNext->next) {
		printf("%dx^%d ", HeadNext->koeficjent, HeadNext->eksponent);
	}
	printf("\n");
	return 0;
}