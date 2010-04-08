/*TODO:
 * 1. Number of collisions
 * 2. Function to print out hash table
 */
#include <stdio.h>
#include <stdlib.h>
#define TABLESIZE 16

/* Key Index */
int index = 0;

/* Total collisions */
int collisions = 0;

/* Node struct */
typedef struct Node Node;
struct Node {
	int index;
	int *key;
	Node *next;
};

/* Hash Table */
Node *table[TABLESIZE];

/* Set up initial conditions (like cleaning hash table) */
void initialize();

/* Read in a vector */
int read_vec(int* our_vec, int length);

/* Compare values of two vectors */
/* returns 0 if equal, -<int> if our_vec is before their_vec
 * +<int> if their_vec is before our_vec.
 */
int vec_cmp(int* our_vec, int* their_vec, int length);


/* Print out the vector in clean form (e.g. <a, b, c, ..., z>) */
void vec_print(int* our_vec, int length);

/*Malloc space and fill out a new node */
Node *create_node(int index, int* our_vec, int length);

/* Hash function: Returns an index into the hash table (int) */
int hash_func(int* our_vec, int length);

/* Returns pointer to the pointer of a "node" in hash table...
 * If NULL, there is nothing stored at that key
 * Otherwise, the key must be checked for whether it is the key being looked up, if it isn't, then the key would normally be the "next."
 */
Node **lookup(int* our_vec, int length);

/* Insert function */
/* Looks up, checks if it is NULL, if so store
 * else check if it is the key we are looking for, if so return -1
 * else return index of newly stored value.
 */
int insert(int* our_vec, int length);

/* Traversal function */
void map_traverse(void *func(Node *my_node), int length);

/* Main */
int main() { 
	int length, result;
	
	initialize();
	result = scanf("%d", &length);
	
	int our_vec[length];
	read_vec(our_vec, length);
	
	while(read_vec(our_vec, length) == 0) {
		result = insert(our_vec, length);
		if(result == -1) {
			printf("Key ");
			vec_print(our_vec, length);
			printf(" has been ignored.\n");
		} else {
			printf("Key ");
			vec_print(our_vec, length);
			printf(" has been assigned the key %d.\n", result);
		}
	}
	printf("collisions: %d\n", collisions);
	
	return 0;
}

void initialize() {
	int i;
	for(i=0; i< TABLESIZE; i++) { table[i] = NULL; }
}

int read_vec(int* our_vec, int length) {
	int i, result;
	for(i=0; i<length; i++) {
		result = scanf("%d", &our_vec[i]);
		if (result != 1) { return result; }
		if (our_vec[i] == -911) { return -1; }
	}
	return 0;
}

void vec_print(int* our_vec, int length) {
	int i;
	
	printf("<");
	for(i=0; i<(length-1); i++) {
		printf("%d, ", our_vec[i]);
	}
	printf("%d>", our_vec[i]);
	
	return;
}

int vec_cmp(int* our_vec, int* their_vec, int length) {
	int i;
	for(i=0; i<length; i++) {
		if (our_vec[i] != their_vec[i]) {
			return our_vec[i] - their_vec[i];
		}
	}
	return 0;
}

Node *create_node(int index, int* our_vec, int length) {
	int i;
	Node *new_node = (Node *) malloc(sizeof(Node));
	if (new_node == NULL) {
		perror("Not enough space to malloc for a new node.");
		exit(EXIT_FAILURE);
	}
	
	new_node->key = (int *) malloc(sizeof(int)*length);
	if (new_node->key == NULL) {
		perror("Not enough space to malloc for a key.");
		exit(EXIT_FAILURE);
	}
	
	new_node->index = index;
	new_node->next = NULL;
	for(i=0; i<length; i++) {
		new_node->key[i] = our_vec[i];
	}
	return new_node;
}

int hash_func(int* our_vec, int length) {
	/* Here lies a stupid hash function for testing */
	int i, sum=0;
	for (i=0; i < length; i++) { sum += our_vec[i]; }
	return sum%TABLESIZE;
}

Node **lookup(int* our_vec, int length) {
	Node **curr_node = &table[hash_func(our_vec, length)];
	
	while(*curr_node != NULL) {
		if (vec_cmp(our_vec, (*curr_node)->key, length) >= 0) {
			return curr_node;
		} else {
			curr_node = &(*curr_node)->next;
		}
	}
	return curr_node;
}

int insert(int* our_vec, int length) {
	Node *temp_node;
	Node **node_ptr = lookup(our_vec, length);
	if (*node_ptr == NULL) {
		*node_ptr = create_node(index, our_vec, length);
		return index++;
	} else if (vec_cmp(our_vec, (*node_ptr)->key, length) == 0) {
		return -1;
	} else {
		/* insert before the node returned by lookup */
		collisions++;
		temp_node = *node_ptr;
		*node_ptr = create_node(index, our_vec, length);
		(*node_ptr)->next = temp_node;
		return index++;
	}
}
