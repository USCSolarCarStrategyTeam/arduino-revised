// Cache implementation in C
#ifndef CACHE_H
#define CACHE_H

#define CACHE_MAX 64
#define NULL_INT -1 // unused integer value for initialization
​
struct cache {
	int size;
	struct node* head;
	struct node* tail;
};
​
typedef struct node {
   int data;
   struct node* next;
   struct node* prev;
};
​
struct cache* cache_init();
​
struct node* node_init(int data);
​
// Returns 0 for false, 1 for true
int isEmpty(struct cache* c);
​
// Inserts one node at beginning of list, if size is >= 64, remove last element
void insert(struct cache* c, int data);
​
void printList(struct cache* c);
