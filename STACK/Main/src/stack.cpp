#include "headers/stack.h"
#pragma warning (disable:4996)

// pointer to first element
static STACK *first = NULL; 
// size of stack
static int capacity = 0;	


void *STACK_push(void *pdat){
	STACK *current = (STACK *)malloc(sizeof(STACK));

	// empty list
	if (first == NULL) {
		current->next = NULL;
		first = current;
	}
	else {
		current->next = first;
		first = current;
	}
	current->data = pdat;
	capacity++;
	return current;
}
void STACK_pop(DATA_FREE clear){
	// empty list
	if (first == NULL) {
		printf("\n\Stack is empty"); //communicate
		return;
	}
	// list with 1 element
	else if (first->next == NULL) {
		clear(first->data);
		first = NULL;
		capacity--;
		printf("\n\tElement removed from stack\n"); //communicate
	}
	else {
		STACK *temp = first->next;
		clear(first->data);
		free(first);
		first = temp;
		capacity--;
		printf("\n\tElement removed from stack\n"); //communicate
	}
}
bool STACK_free(DATA_FREE clear) {
	// empty list
	if (first == NULL) 
		return true;
	// one element in list
	else if (first->next == NULL) {
		clear(first->data);
		free(first);
		capacity--;
		return true;
	}
	else {
		STACK *new_current = first->next;
		while (first->next != NULL) {
			clear(first->data);
			free(first);
			first = new_current;
			new_current = new_current->next;
			capacity--;
		}
		clear(first->data);
		free(first);
		capacity--;
		first = NULL;
	}
	return true;
}
void STACK_show_top(DATA_SHOW show) {
	if (first != NULL) {
		show(first->data);
	}
	else {
		printf("\tStack is empty"); //comm
	};
}
void STACK_show_stack(DATA_SHOW show) {
	if (first == NULL) {
		printf("\n\tStack is empty"); //comm
		return;
	}
	else {
		STACK *current = first;
		int i = 1;
		while (current->next != NULL) {
			printf("\n\t%d.\n", i);
			show(current->data);
			printf("\n");
			current = current->next;
			i++;
		}
		printf("\n\t%d.\n", i);
		show(current->data);
		printf("\n");
	}
}
void STACK_find_surname(char *surname, DATA_COMP_SURNAME comp_surname, DATA_SHOW show) {
	if (first == NULL) {
		printf("\n\tStack is empty");
		return;
	}
	STACK *current = first;
	int k = 0;
	int i = 1;
	while (current != NULL) {
		if (comp_surname(surname, current->data)) {
			printf("\n");
			printf("\t%d.\n", i);
			show(current->data);
			current = current->next;
			i++;
			k++;
		}
		else {
			current = current->next;
			i++;
		}
	}
	if (k == 0) printf("\n\tNo results");
}
void STACK_save(FILE *f, DATA_SAVE save) {
	STACK *temp = first;
	while (temp != NULL) {
		save(f, temp->data);
		temp = temp->next;
	}
}
void STACK_load(FILE *f, DATA_LOAD load) {
	reverse_file(f);

	char buffer[255];
	while (fscanf(f, "%s", buffer) != EOF) 
		STACK_push(load(f, buffer));
	fseek(f, 0, SEEK_SET);

	reverse_file(f);
}
void *STACK_ret_first() {
	return (void*)first;
}

void reverse_file(FILE *f) {
	int j = 0;
	int num = num_lines(f);

	// init buffers
	char **temp = (char**)malloc(num * sizeof(char*));
	for (int i = 0; i < num; i++) 
		temp[i] = (char*)malloc(255 * sizeof(char));


	// get data from file
	while (fscanf(f, "%s", temp[j]) != EOF) 
		j++;

	// go back to the start of a file
	fseek(f, 0, SEEK_SET);

	// overwrite file with data in reversed order
	for (j = j-1; j >= 0; j--) {
		fwrite(temp[j], sizeof(char), strlen(temp[j]), f);
		fwrite("\n", sizeof(char), 1, f);
	}

	// free buffers memory
	for (j = 0; j < num; j++) {
		free(temp[j]);
	}
	free(temp);

	// go back to the start of a file
	fseek(f, 0, SEEK_SET);
}
int  num_lines(FILE *f) {
	int num = 0;
	char buffer[1024];

	while (fscanf(f, "%s", buffer) != EOF) 
		num++;
	fseek(f, 0, SEEK_SET);

	return num;
}
int  STACK_capacity() {
	return capacity;
}
