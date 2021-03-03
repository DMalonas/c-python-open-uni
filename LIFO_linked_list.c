
#include <stdio.h>
#include <stdlib.h>


struct node {
	int data;
	struct node* next;
};

typedef struct node* NODE;

NODE start = NULL;

void display();
NODE create_node();
void insert_beg();
void delete_beg();



int main() {

	int choice;

	do {
		// Menu
		printf("******   Choose from the options   ******\n\n");
		printf("1. Create a List\n ");
		printf("2. Display List\n ");
		printf("3. Add node at the begining\n ");
		printf("4 DELETE a node from the BEGINING\n ");
		printf("5. EXIT \n\n");

		scanf_s("%d", &choice);

		switch (choice) {
		case 1:	create_node();
			break;
		case 2:	display();
			break;
		case 3:	insert_beg();
			break;
		case 4: delete_beg();
			break;
		case 5:	
			exit(0);
			break;

		default:
			printf("Wrong input! Try again!!\n\n");
		}


	} while (choice != 10);

	return 0;
}

void display() {

	if (start == NULL) {
		printf("\n List is already empty...");
	}

	NODE temp = start;

	printf("\n Current Linked List: \n");
	while (temp != NULL) {
		printf(" %d ", temp->data);
		temp = temp->next;
	}
	printf("\n");
}

NODE create_node() {
	NODE new_node = (NODE)malloc(sizeof(struct node));
	return new_node;
}

void insert_beg() {
	NODE new_node;
	int data;
	new_node = create_node();

	printf("\n Enter the data to insert at begining: ");
	scanf_s("%d", &data);

	new_node->data = data;

	if (start == NULL) {
		new_node->next = NULL;
		start = new_node;
	}
	else {
		new_node->next = start;
		start = new_node;
	}

	display();
}



void delete_beg() {

	if (start == NULL) {
		printf("\n Error: The list is already empty!");
		return;
	}

	NODE temp;
	temp = start;

	start = temp->next;

	printf("\n The element with data %d deleted!", temp->data);

	free(temp);

	display();
}