// Cache implementation in C

#define CACHE_MAX 64
#define NULL_INT -1 // unused integer value for initialization
​
typedef struct cache {
	int size;
	struct node* head;
	struct node* tail;
} cache;
​
typedef struct node {
   int data;
   struct node* next;
   struct node* prev;
} node;
​
cache* cache_init();
​
node* node_init(int data);
​
// Returns 0 for false, 1 for true
int isEmpty(cache* c);
​
// Inserts one node at beginning of list, if size is >= 64, remove last element
void insert(cache* c, int data);
​
void printList(cache* c);
