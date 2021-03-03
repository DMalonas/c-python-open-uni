#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define NUM 3
#define MOD 10
#define NAME_SIZE 20
#define ADDRESS_SIZE 20

struct student {
	int ar;
	char* forname;
	char* surname;
	char* midname;
	char* address;
	char* firstSemMod;
	int personalPhone;
	int homePhone;
};



void displayStudent(struct student stud);
struct student* getStudents(int numOfStudents);
int getNumOfStudents();
void printAllStudents(struct student* stud, int numOfStudents);
struct student* getCommonModStudents(struct student* st, int size, int* commonSize, char* module);

int main(void) {
	struct student* st;
	int numOfStudents = getNumOfStudents();
	st = getStudents(numOfStudents);
	printAllStudents(st, numOfStudents);

	printf("\nEnter common module: ");
	char mod[20];
	gets(mod);
	int cnt = 0;
	struct student* common_st = getCommonModStudents(st, numOfStudents, &cnt, mod);
	printAllStudents(common_st, cnt);
	free(common_st);
	free(st);
	return 0;
}

int getNumOfStudents() {
	int numOfStudents;
	printf("Enter number of students: ");
	scanf_s("%d", &numOfStudents);
	getchar();
	return numOfStudents;
}

//Να χρησιμοποιηθεί μια δομή δείκτη για την πρόσβαση σε όλους τους φοιτητές που έχουν επιλέξει ένα συγκεκριμένο μάθημα.
struct student* getCommonModStudents(struct student* st, int size, int *commonSize, char* module) {
	
	for (int i = 0; i < size; i++) {
		if (strcmp(st[i].firstSemMod, module) == 0) {
			(*commonSize)++;
		}
	}
	
	struct student* stCommon = (struct student*)malloc(sizeof(struct student) * (*commonSize));
	if (stCommon == NULL) {
		exit(1);
	}
	int k = 0;
	for (int i = 0; i < size; i++) {
		if (strcmp(st[i].firstSemMod, module) == 0) {
			stCommon[k].forname = (char*)malloc(sizeof(char) * NAME_SIZE);
			if (stCommon[k].forname == NULL) {
				exit(1);
			}
			strcpy_s(stCommon[k].forname, NAME_SIZE, st[i].forname);
			stCommon[k].midname = (char*)malloc(sizeof(char) * NAME_SIZE);
			if (stCommon[k].midname == NULL) {
				exit(1);
			}
			strcpy_s(stCommon[k].midname, NAME_SIZE, st[i].midname);
			stCommon[k].surname = (char*)malloc(sizeof(char) * NAME_SIZE);
			if (stCommon[k].surname == NULL) {
				exit(1);
			}
			strcpy_s(stCommon[k].surname, NAME_SIZE, st[i].surname);
			stCommon[k].address = (char*)malloc(sizeof(char) * NAME_SIZE);
			if (stCommon[k].address == NULL) {
				exit(1);
			}
			strcpy_s(stCommon[k].address, NAME_SIZE, st[i].address);
			stCommon[k].firstSemMod = (char*)malloc(sizeof(char) * MOD);
			if (stCommon[k].firstSemMod == NULL) {
				exit(1);
			}
			strcpy_s(stCommon[k].firstSemMod, MOD, st[i].firstSemMod);
			stCommon[k].ar = st[i].ar;
			stCommon[k].homePhone = st[i].homePhone;
			stCommon[k].personalPhone = st[i].personalPhone;
			k++;
		}
	}
	return stCommon;
}

//Να γραφεί κώδικας C για την αναπαράσταση του συνόλου των φοιτητών χρησιμοποιώντας έναν πίνακα εγγραφημάτων.
void printAllStudents(struct student* stud, int numOfStudents) {
	for (int i = 0; i < numOfStudents; i++) {
		displayStudent(stud[i]);
	}
}

// Να γραφεί κώδικας C για την αναπαράσταση ενός εγγραφήματος φοιτητή. 
void displayStudent(struct student stud) {
	printf("\nAr: %d, Forname: %s, Midname: %s, Surname: %s, address: %s, First semester module: %s, personal phone: %d, home phone: %d\n", 
		stud.ar, stud.forname, stud.midname, stud.surname, stud.address, stud.firstSemMod, stud.personalPhone, stud.homePhone);
}

struct student* getStudents(int numOfStudents) {
	struct student *st = (struct student*)malloc(sizeof(struct student) * numOfStudents);
	if (st == NULL) {
		exit(1);
	}
	for (int i = 0; i < numOfStudents; i++) {
		st[i].forname = (char*)malloc(sizeof(char) * NAME_SIZE);
		if (st[i].forname == NULL) {
			exit(1);
		}
		st[i].midname = (char*)malloc(sizeof(char) * NAME_SIZE);
		if (st[i].midname == NULL) {
			exit(1);
		}
		st[i].surname = (char*)malloc(sizeof(char) * NAME_SIZE);
		if (st[i].surname == NULL) {
			exit(1);
		}
		st[i].address = (char*)malloc(sizeof(char) * ADDRESS_SIZE);
		if (st[i].forname == NULL) {
			exit(1);
		}
		st[i].firstSemMod = (char*)malloc(sizeof(char) * MOD);
		if (st[i].firstSemMod == NULL) {
			exit(1);
		}
		printf("\nForname: ");
		gets(st[i].forname);
		printf("\nMidname: ");
		gets(st[i].midname);
		printf("\nSurname: ");
		gets(st[i].surname);
		printf("\nAddress: ");
		gets(st[i].address);
		printf("\nFirst semester module: ");
		gets(st[i].firstSemMod);
		printf("\nId number: ");
		scanf_s("%d", &st[i].ar);
		printf("\nHome number: ");
		getchar();
		scanf_s("%d", &st[i].homePhone);
		printf("\nPersonal number: ");
		getchar();
		scanf_s("%d", &st[i].personalPhone);
		getchar();

	}
	return st;
}