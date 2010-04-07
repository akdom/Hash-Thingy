#define TABLESIZE 16

/* Node struct */
typedef struct Node Node;
struct Node {
	int index;
	int *key;
	Node *next;
}

/* Hash Table */
Node table[TABLESIZE];

/* Set up initial conditions (like cleaning hash table) */
void initialize();

/* Read in a vector */
int read_vec(int* our_vec, int length);

/* Compare values of two vectors */
/* returns 0 if equal, -<int> if our_vec is before their_vec
 * +<int> if their_vec is before our_vec.
 */
int vec_cmp(int* our_vec, int* their_vec, length);

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

/* Main */
int main() { 
	int length;
	initialize();
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

int vec_cmp(int* our_vec, int* their_vec, length) {
	int i;
	for(i=0; i<length; i++) {
		if (our_vec[i] != their_vec[i]) {
			return our_vec[i] - their_vec[i];
		}
	}
	return 0;
}

int hash_func(int* our_vec, int length) {
	/* Here lies a stupid hash function for testing */
	int i, sum=0;
	for (i=0; i < length; i++) { sum += our_vec[i]; }
	return sum%TABLESIZE;
}

node **lookup(int* our_vec, int length) {
	Node *curr_node = table[hash_func(our_vec, length)];
	
	while(curr_node != NULL) {
		if (vec_cmp(our_vec, curr_node->key, length) >= 0) {
			return &curr_node;
		} else {
			curr_node = curr_node->next;
		}
	}
	return &curr_node;
}

