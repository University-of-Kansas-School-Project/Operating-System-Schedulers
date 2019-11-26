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

void setSecondaryCompare (priqueue_t *q, int(*comparer)(const void *, const void *)){
  q->comp2 = comparer;
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
  q->size += 1;
  newNode->job = ptr;
  if(temp == NULL){
    q->root = newNode;
    q->tail = newNode;
    newNode->right = NULL;
    // newNode->left = NULL;
  }
  else{
    // if(q->comp(newNode->job, q->tail->job) >= 0){
    //   //newNode is large, add at the end
    //   q->tail->right = newNode;
    //   newNode->left = q->tail;
    //   q->tail = newNode;
    // }
    // else{
    //   //newNode is small, swap
    //   while(temp != NULL){
    //     if(q->comp(newNode->job, temp->job) >= 0){
    //       //location found insert
    //       if(temp->left == NULL){
    //         q->root = newNode;
    //         newNode->right = temp;
    //         break;
    //       }
    //     else{
    //       Node * mid = temp->left;
    //       temp->left = newNode;
    //       newNode->right = temp;
    //       newNode->left = mid;
    //       mid->right = newNode;
    //       break;
    //     }
    //     }
    //     else{
    //       //traverse
    //       temp = temp->right;
    //     }
    //   }
    // }

      q->tail->right = newNode;
      q->tail = newNode;
      newNode->right = NULL;
      listSort(q);
  }


  // Node* current = q->root;
  // Node * newNode = malloc(sizeof(Node));
  // newNode->job = ptr;
  // q->size +=1;
  //
  // // Case 1 of the above algo
  // if (current == NULL)
  // {
  //     newNode->right = newNode;
  //     q->root = newNode;
  // }
  //
  // // Case 2 of the above algo
  // else if (q->comp(current->job, newNode->job) > 0)
  // {
  //     /* If value is smaller than head's value then
  //     we need to change next of last node */
  //     swap(current->job, newNode->job);
  //
  //     newNode->right = q->root;
  //     q->root->right = newNode;
  // }
  //
  // // Case 3 of the above algo
  // else
  // {
  //     /* Locate the node before the point of insertion */
  //     while (current->right!= q->root &&
  //         q->comp(current->right->job, newNode->job) < 0)
  //     current = current->right;
  //
  //     newNode->right = current->right;
  //     current->right = newNode;
  // }
  // return q->size;
 // Node * temp = q->root;
 // if(q->root == NULL){
 // 	q->root = malloc(sizeof(Node));
	// q->root->job = ptr;
	// q->root->left = NULL;
	// q->root->right = NULL;
	// q->tail = q->root;
	// q->root->index = q->size;
 // }
 // else{
	// q->size += 1;
 //
 // // for(int i = 0; i<=q->size; i++){
	// 	//At end, insert into last spot
	// 	// if(temp == q->tail) {
	// 		q->tail->right = malloc(sizeof(Node));
 //      q->tail->right->left = q->tail;
	// 		q->tail = q->tail->right;
	// 		q->tail->job = ptr;
	// 		q->tail->index = q->size;
 //      //if(q->comp(q->tail->left->job, q->tail->job) > 0)
 //        sort(q);
	// 	}
		//Greater Priorty, Move Right
	// 	if (q->comp(temp->job, ptr) >= 0){
	// 		temp = temp->right;
	// 	}
	// 	//Less Priorty, Insert in between
	// 	else {
  //     Node * tr = temp->right;
	// 		temp->left = temp->right;
	// 		temp->right = ptr;
	// 		temp->right->index = q->size;
	// 		temp->right->right = tr;
  //     //sort(q->root);
	// 	}
  // }// if(q->comp(newNode->job, q->tail->job) >= 0){
    //   //newNode is large, add at the end
    //   q->tail->right = newNode;
    //   newNode->left = q->tail;
    //   q->tail = newNode;
    // }
    // else{
    //   //newNode is small, swap
    //   while(temp != NULL){
    //     if(q->comp(newNode->job, temp->job) >= 0){
    //       //location found insert
    //       if(temp->left == NULL){
    //         q->root = newNode;
    //         newNode->right = temp;
    //         break;
    //       }
    //     else{
    //       Node * mid = temp->left;
    //       temp->left = newNode;
    //       newNode->right = temp;
    //       newNode->left = mid;
    //       mid->right = newNode;
    //       break;
    //     }
    //     }
    //     else{
    //       //traverse
    //       temp = temp->right;
    //     }
    //   }
    // }

		/*printf("In If\n");
		printf("%d\n",q->comp(ptr,temp->job));
		temp->right = malloc(sizeof(Node));
		if(temp->right != NULL){
			Node * tr = temp->right;
			temp->left = temp->right;
			temp->right = ptr;
			temp->right->index = q->size;
			temp->right->right = tr;
		}*/
		//q->tail->index = q->size;

	//else{

	//}
	/*q->tail->right = malloc(sizeof(Node));
	q->tail = q->tail->right;
	q->tail->job = ptr;
	q->tail->index = q->size;*/
 // }
 listSort(q);
	return q->size;
}

void listSort(priqueue_t *q){
  // if(priqueue_size(q) == 0)
  //   return;
  Node* curr;// = m_front;
	Node* temp = NULL;
	Node* lptr = NULL;
	int swapped = 0;
	if(q->root == NULL)
		return;
	do{
		swapped = 0;
		curr = q->root;
		while(curr->right != lptr){
			temp = curr;
			curr = curr->right;
      //Case: When Priorties are not the same
			if(curr != NULL && q->comp(temp->job, curr->job) > 0 ){
				void * t = temp->job;
				void * c = curr->job;
				temp->job = c;
				curr->job = t;
				swapped = 1;
        break;
				//std::cout<<t;
			}
      //Case: When Priorities are the same
      else if(curr != NULL && q->comp2 != NULL) {
        if( q->comp(temp->job, curr->job) == 0) {
        //Temp Arrival greater then Curr Arrival
        // printf("Comparing 2 Jobs with equal priorty -> Checking Arrival Time now\n");
        if(q->comp2(temp->job, curr->job) > 0) {
          void * t = temp->job;
          void * c = curr->job;
          temp->job = c;
          curr->job = t;
          swapped = 1;
          break;
        }
        //Curr Arrival greater then Temp Arrival
        else {
          //Do Nothing, Keep the order
        }
      }
      }
		}
		lptr = curr;
	}while(swapped);
}

void sort(priqueue_t *q){
  int swapped;
  Node *ptr1;
  Node *lptr = NULL;

  /* Checking for empty list */
  if (q->root == NULL)
      return;

  do
  {
      swapped = 0;
      ptr1 = q->root;

      while (ptr1->right != lptr)
      {
          if (q->comp(ptr1->job, ptr1->right->job) > 0)
          {
              swap(ptr1, ptr1->right);
              swapped = 1;
              // return;
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
	// void * temp = q->root->job;
	// Node * td = q->root;
	// q->root = q->root->right;

	// free(td);
	// q->size --;
  // if(priqueue_size(q) == 0)
  //   return NULL;
  // else
	 return priqueue_remove_at(q,0);
  // else
  //   return NULL;
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
  int s = q->size;
  // Node * pTemp = q->root;
	for(int i = 0; i < s; i++){
		if(temp->job == ptr){
			c++;
      priqueue_remove_at(q,i);
      return priqueue_remove(q,ptr) + 1;
      // break;
      // // Node * t = temp;
      //
      // printf(" removing%d \n", *(int *)temp->job);
      // if(temp->right != NULL)
			//    pTemp->right = temp->right;
      // else
      //   pTemp->right = NULL;
      // printf("linking %d with %d\n", *(int *)pTemp->job, *(int *)temp->right->job);
			// free(temp);
		}
    else
      temp = temp->right;
    // pTemp = temp;
		// temp = temp->right;
	}
	// q->size -= c;
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
  Node * pTemp = q->root;
  if(priqueue_size(q) == 0)
    return NULL;
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
    pTemp = temp;
		temp = temp->right;
	}
	//temp = temp + (index)*sizeof(Node);
	void * j = temp->job;
  if(temp == q->root && temp->right != NULL){
    // printf("removing head case1\n");
    q->root = temp->right;
  }
  else if (temp == q->root && temp->right == NULL){
    // printf("case4\n");
    q->root = NULL;
    q->tail = NULL;
  }
  else if(temp == q->tail){
    // printf("case3\n");
    pTemp->right = NULL;
    q->tail = pTemp;
  }
  else{
    // printf("case2\n");
    pTemp->right = temp->right;
  }

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
	return q->size;
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
