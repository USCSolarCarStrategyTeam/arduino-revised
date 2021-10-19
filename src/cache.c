#include <stdio.h>
#include <stdlib.h>
#include "cache.h"

cache* cache_init(){
	cache* c = malloc(sizeof(cache));
	c->head = NULL;
	c->tail= NULL;
	c->size = 0;
	return c;
}
​
node* node_init(){
	node* n  = malloc(sizeof(node));
	n->data = NULL_INT;
	n->next = NULL;
	n->prev = NULL;
	return n;
}
​
// Returns 0 for false, 1 for true
int isEmpty(cache* c) {
   return c->head == NULL;
}
​
// Inserts one node at beginning of list, if size is maxed out, remove last element
void insert(cache* c, int data) {
	// Remove end node if size is maxed out when new node inserted
	if(c->size == CACHE_MAX) {
		c->tail = c->tail->prev;
		free(c->tail->next);
		c->tail->next = NULL;
		c->size--;
	}
​
   //create a link, allocates memory with malloc function call
   node* newNode = node_init();
   newNode->data = data;

   if(isEmpty(c)) {
      // List is empty, make it the first and last link
      c->head = newNode;
      c->tail = newNode;
   }
   else {
      // newNode will be inserted at start of list
      c->head->prev = newNode;
      newNode->next = c->head;
      c->head = newNode;
   }
   c->size++;
}
​
void printList(cache* c){
    if(isEmpty()){
        return;
    }

    node* tempNode = c->head;
​
	while(tempNode->next != NULL){
		printf("%d \n", tempNode->data);
		tempNode = tempNode->next;
	}
	printf("%d \n", tempNode->data);
	return;
}
