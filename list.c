#include "list.h"
#include <stddef.h>
#include <stdio.h>

#define NODEMAX 100
#define HEADMAX 10

Node nodes[NODEMAX];
List heads[HEADMAX];
Node *nodeAvailable;
List *headAvailable;
int loaded = 0;

Node *ItemCreate(void *item) {
  if (nodeAvailable) {
    Node *node = nodeAvailable;
    nodeAvailable = nodeAvailable->next;
    node->item = item;
    node->next = NULL;
    node->prev = NULL;
    return node;
  }
  return NULL;
}

//QA
List *ListCreate() {
  int i;
  if (!loaded) {
    for (i=0; i<NODEMAX-1; i++) {
      nodes[i].next = &nodes[i+1];
    }
    for (i=0; i <HEADMAX-1; i++) {
      heads[i].next = &heads[i+1];
    }
    headAvailable = &heads[0];
    heads[HEADMAX-1].next = NULL;
    nodeAvailable = &nodes[0];
    nodes[NODEMAX-1].next = NULL;
    loaded = 1;
    printf("Node Count is: %d\n", nodePoolCount() );
  }
  if (headAvailable){
    List* list = headAvailable;
    headAvailable = headAvailable->next;
    list->count = 0;
    list->head = NULL;
    list->current = NULL;
    list->beyond = 0;
    list->before = 0;
    return list;
  }
  return NULL;
}

//QA
int ListCount(List *list) {
  return list->count;
}

//QA
void *ListFirst(List *list) {
  if (list->count > 0) {
    list->current = list->head;
    return list->head->item;
  }
  return NULL;
}

//QA
void *ListLast(List *list) {
  if(list->count > 0) {
    list->current = list->tail;
    if (list->current) {
      return list->tail->item;
    }
  }
  return NULL;
}

//QA
void *ListNext(List *list) {
  if (list->before) {
    list->current = list->head;
    list->before = 0;
  }
  else if(list->current) {
    list->current = list->current->next;
  }
  if (list->current == NULL) {
    list->beyond = 1;
  }
  return list->current ? list->current->item : NULL;

}

//QA
void *ListPrev(List *list){
  if (list->beyond) {
    list->current = list->tail;
    list->beyond = 0;
  }
  else if(list->current) {
    list->current = list->current->prev;
  }
  if (list->current == NULL) {
    list->before = 1;
  }
  return list->current ? list->current->item : NULL;
}

//QA
void *ListCurr(List *list){
  if (list->current != NULL) {
    return list->current->item;
  }
  return NULL;
}

//Done
int ListAdd(List *list, void *item) {
  Node *node = ItemCreate(item);
  if (!node || !list) {
    return -1;
  }
  if(list->count == 0) {
    list->head = node;
    list->tail = node;
    list->current = node;
    list->count++;
    return 0;
  }

  if (list->before) {
    list->head->prev = node;
    node->next = list->head;
    list->head = list->current = node;
    list->before = 0;
    list->count++;
    return 0;
  }

  if (list->beyond) {
    list->tail->next = node;
    node->prev = list->tail;
    list->tail = list->current = node;
    list->beyond = 0;
    list->count++;
    return 0;
  }

  node->prev = list->current;
  node->next = list->current->next;
  if (list->current->next) {
    list->current->next->prev = node;
  }
  list->current->next = node;

  if(list->current == list->tail) {
    list->tail = node;
  }
  list->current = node;
  list->count++;
  return 0;

}

//Done
int ListInsert(List *list, void *item) {
  Node *node = ItemCreate(item);
  if (!node || !list) {
    return -1;
  }
  if(list->count == 0) {
    list->head = node;
    list->tail = node;
    list->current = node;
    list->count++;
    return 0;
  }

  if (list->before) {
    list->head->prev = node;
    node->next = list->head;
    list->head = list->current = node;
    list->before = 0;
    list->count++;
    return 0;
  }

  if (list->beyond) {
    list->tail->next = node;
    node->prev = list->tail;
    list->tail = list->current = node;
    list->beyond = 0;
    list->count++;
    return 0;
  }

  node->prev = list->current->prev;
  node->next = list->current;

  if (list->current->prev) {
    list->current->prev->next = node;
  }
  list->current->prev = node;
  if (list->current == list->head) {
    list->head = node;
  }
  list->current = node;
  list->count++;
  return 0;


}

//Done
int ListAppend(List *list, void *item) {
  Node* node = ItemCreate(item);
  if (!node || !list) {
    return -1;
  }
  if (list->count == 0) {
    list->head = node;
    list->tail = node;
    list->current = node;
    list->count++;
    return 0;
  }
  else {
    list->tail->next = node;
    node->prev = list->tail;
    list->tail = node;
    list->current = node;
    list->count++;
    return 0;
  }
  return -1;
}

//Done
int ListPrepend(List *list, void *item) {\
  Node* node = ItemCreate(item);
  if (!node || !list) {
    return -1;
  }
  if (list->count == 0) {
    list->head = node;
    list->tail = node;
    list->current = node;
    list->count++;
    return 0;
  }
  else {
    node->next = list->head;
    list->head->prev = node;
    list->head = node;
    list->current = node;
    list->count++;
    return 0;
  }
  return -1;
}

// Works but needs to add node back to pool
void *ListRemove(List *list) {
  if (!list || list->count == 0 || !list->current) {
    return NULL;
  }
  Node *newAvailable = list->current;
  Node *tmp = list->current;
  if (list->count == 1) {
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
    list->count--;
    newAvailable->next = nodeAvailable;
    nodeAvailable = newAvailable;
    return tmp->item;
  }

  if (list->current->prev) {
    list->current->prev->next = list->current->next;
  }
  if (list->current->next) {
    list->current->next->prev = list->current->prev;
  }
  if (list->current == list->tail) {
    list->current = list->tail->prev;
    list->tail = list->current;
  }
  else if (list->current == list->head) {
    list->head = list->head->next;
    list->current = list->head;
  }
  else {
    list->current = list->current->next;
  }
  if (newAvailable) {
    newAvailable->next = nodeAvailable;
    nodeAvailable = newAvailable;
  }
  list->count--;
  return tmp->item;
}

void ListConcat (List *list1, List *list2) {
  list1->tail->next = list2->head;
  list2->head->prev = list1->tail;
  list1->tail = list2->tail;
  list1->count += list2->count;
  List *newHeadAvailable = list2;
  newHeadAvailable->next = headAvailable;
  headAvailable = newHeadAvailable;
  list2 = NULL;
}

// Needs to add node back to pool
void *ListTrim(List *list) {
  if (list->count == 0 || !list) {
    return NULL;
  }
  Node *newAvailable = list->tail;
  Node *tmp = list->tail;
  if (list->count == 1) {
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
  }
  else {
    list->tail = list->tail->prev;
    list->current = list->tail;
    list->current->next = NULL;
  }
  list->count--;
  if (newAvailable) {
    newAvailable->next = nodeAvailable;
    nodeAvailable = newAvailable;
  }
  return tmp->item;
}

void ListFree(List *list, void (*itemFree)(void *itemToBeFreed)) {
  Node *curr = list->tail;
  while (curr) {
    (*itemFree)(curr->item);
    ListTrim(list);
    curr = curr->prev;
  }
  List *newHeadAvailable = list;
  newHeadAvailable->next = headAvailable;
  headAvailable = newHeadAvailable;
}


void *ListSearch(List *list, int (*comparator)(void *item, void *comparisonArg), void *comparisonArg) {
  Node *curr = list->current;
  while (curr) {
    if ( (*comparator)(curr->item, comparisonArg )) {
      return list->current->item;
    }
    curr = curr->next;
    list->current = curr;
  }
  if (list->count > 0) {
    list->beyond = 1;
  }
  return curr;
}

int nodePoolCount () {
  int j = 0;
  Node *node = nodeAvailable;
  while (node) {
    j++;
    node = node->next;
  }
  return j;
}
