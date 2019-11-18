/** @file libpriqueue.c
 */

#include <stdlib.h>
#include <stdio.h>

#include "libpriqueue.h"

/**
  Initializes the priqueue_t data structure.

  Assumtions
    - You may assume this function will only be called once per instance of priqueue_t
    - You may assume this function will be the first function called using an instance of priqueue_t.
  @param q a pointer to an instance of the priqueue_t data structure
  @param comparer a function pointer that compares two elements.
  See also @ref comparer-page
 */
void priqueue_init(priqueue_t *q, int(*comparer)(const void *, const void *))
{
  q->root = NULL;
  q->tail = NULL;
  q->size = 0;
  q->comp = comparer;
	//q = malloc(sizeof(priqueue_t));
  //q->rootPtr = nullptr;
  // comparer(q->rootPtr->aTime, q->rootPtr->next->aTime);
}


/**
  Insert the specified element into this priority queue.

  @param q a pointer to an instance of the priqueue_t data structure
  @param ptr a pointer to the data to be inserted into the priority queue
  @return The zero-based index where ptr is stored in the priority queue, where 0 indicates that ptr was stored at the front of the priority queue.
 */
int priqueue_offer(priqueue_t *q, void *ptr)
{
 Node * temp = q->root;
 Node * newNode = malloc(sizeof(Node));

 newNode->job = ptr;
 q->size ++;

 for(int i = 0; i<=q->size; i++){
    //Empty List
    if(temp = NULL){
      newNode->left = NULL;
      newNode->right = NULL;
      q->root = newNode;
    }
		//Greater Priorty, Move Right
		if (q->comp(temp->job, ptr) >= 0){
			temp = temp->right;
		}
		//Less Priorty, Insert in between
		else {
      newNode->left = temp->left;
      newNode->right = temp;

      newNode->left->right = newNode;
      temp->left = newNode;
		}
  }
  //List Traversed Insert at the End
  newNode->left = temp;
  newNode->right = NULL;

  temp->right = newNode;
   
	return q->size;
}

void sort(Node * r){
  int swapped;
  Node *ptr1;
  Node *lptr = NULL;

  /* Checking for empty list */
  if (r == NULL)
      return;

  do
  {
      swapped = 0;
      ptr1 = r;

      while (ptr1->right != lptr)
      {
          if (ptr1->job > ptr1->right->job)
          {
              swap(ptr1, ptr1->right);
              swapped = 1;
          }
          ptr1 = ptr1->right;
      }
      lptr = ptr1;
  }
  while (swapped);
}

void swap(Node* a, Node* b){
   void * temp = a->job;
   a->job = b->job;
   b->job = temp;
}

/**
  Retrieves, but does not remove, the head of this queue, returning NULL if
  this queue is empty.

  @param q a pointer to an instance of the priqueue_t data structure
  @return pointer to element at the head of the queue
  @return NULL if the queue is empty
 */
void *priqueue_peek(priqueue_t *q)
{
	return q->root->job;
}


/**
  Retrieves and removes the head of this queue, or NULL if this queue
  is empty.

  @param q a pointer to an instance of the priqueue_t data structure
  @return the head of this queue
  @return NULL if this queue is empty
 */
void *priqueue_poll(priqueue_t *q)
{
	void * temp = q->root->job;
	Node * td = q->root;
	q->root = q->root->right;
	free(td);
	q->size --;
	return temp;
}


/**
  Returns the element at the specified position in this list, or NULL if
  the queue does not contain an index'th element.

  @param q a pointer to an instance of the priqueue_t data structure
  @param index position of retrieved element
  @return the index'th element in the queue
  @return NULL if the queue does not contain the index'th element
 */
void *priqueue_at(priqueue_t *q, int index)
{
	Node * temp = q->root;
	if(index > q->size){
		return NULL;
	}
	/*for(int lcv = 0; lcv < index; lcv++) {
		if(temp->index == index){
			temp = q->root->job;
			break;
		}
		else{
			temp = temp->right;
		}
	}*/
	for(int lcv = 0; lcv < index; lcv++) {
		temp = temp->right;
	}
	//temp = temp + (index)*sizeof(Node);
	return temp->job;
}


/**
  Removes all instances of ptr from the queue.

  This function should not use the comparer function, but check if the data contained in each element of the queue is equal (==) to ptr.

  @param q a pointer to an instance of the priqueue_t data structure
  @param ptr address of element to be removed
  @return the number of entries removed
 */
int priqueue_remove(priqueue_t *q, void *ptr)
{
	int c = 0;
	Node * temp = q->root;
	for(int i = 0; i <= q->size; i++){
		if(temp->job == ptr){
			c++;
			temp->left = temp->right;
			free(temp);
		}
		temp = temp->right;
	}
	q->size -= c;
	return c;
}


/**
  Removes the specified index from the queue, moving later elements up
  a spot in the queue to fill the gap.

  @param q a pointer to an instance of the priqueue_t data structure
  @param index position of element to be removed
  @return the element removed from the queue
  @return NULL if the specified index does not exist
 */
void *priqueue_remove_at(priqueue_t *q, int index)
{
	Node * temp = q->root;
	if(index > q->size){
		return NULL;
	}
	/*for(int lcv = 0; lcv < index; lcv++) {
		if(temp->index == index){
			temp = q->root->job;
			break;
		}
		else{
			temp = temp->right;
		}
	}*/
	for(int lcv = 0; lcv < index; lcv++) {
		temp = temp->right;
	}
	//temp = temp + (index)*sizeof(Node);
	void * j = temp->job;
	free(temp);
	q->size--;
	return j;
}


/**
  Return the number of elements in the queue.

  @param q a pointer to an instance of the priqueue_t data structure
  @return the number of elements in the queue
 */
int priqueue_size(priqueue_t *q)
{
	return q->size+1;
}


/**
  Destroys and frees all the memory associated with q.

  @param q a pointer to an instance of the priqueue_t data structure
 */
void priqueue_destroy(priqueue_t *q)
{
	for(int i = 0; i<= q->size; i++)
		priqueue_remove_at(q, i);
}
