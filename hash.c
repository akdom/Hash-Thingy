#define TABLESIZE 16

/* Node struct */
typedef struct Node Node;
struct Node {
	int index;
	int *key;
	Node *next;
}

/* Read in a vector */
void read_vec(int* our_vec);

/* Hash function: Returns an index into the hash table (int) */
int hash_func(int* our_vec);

/* Returns pointer to "node" in hash table...
 * If NULL, there is nothing stored in at that key
 * Otherwise, the key must be checked for whether it is the key being looked up, if it isn't, then the key would normall be the "next."
 */
node *lookup(int* our_vec);

/* Insert function */
/* Looks up, checks if it is NULL, if so store
 * else check if it is the key we are looking for, if so return -1
 * else return index of newly stored value.
 */
int insert(int* our_vec);

/* Main */
int main() { return 0; }
