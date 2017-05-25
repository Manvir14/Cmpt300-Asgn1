#include "list.h"
#include <stddef.h>

#define NODEMAX 4
#define HEADMAX 10

Node nodes[NODEMAX];
List heads[HEADMAX];
Node *nodePool[NODEMAX];
List *headPool[HEADMAX];
int loaded = 0;
int nodeCurrent = 0;
int headCurrent = 0;


Node *ItemCreate(void *item) {
  if (nodeCurrent < NODEMAX) {
    Node *node = nodePool[nodeCurrent++];
    node->item = item;
    node->next = NULL;
    node->prev = NULL;
    return node;
  }
  return NULL;
}

//QA
List *ListCreate() {
  int i = 0;
  if (!loaded) {
    for (i=0; i<HEADMAX; i++) {
      headPool[i] = &heads[i];
    }
    for (i=0; i<NODEMAX; i++) {
      nodePool[i] = &nodes[i];
    }
  }
  if (headCurrent < HEADMAX){
    List* list = headPool[headCurrent++];
    list->count = 0;
    list->head = NULL;
    list->current = NULL;
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
    return list->head;
  }
  return NULL;
}

//QA
void *ListLast(List *list) {
  if(list->count > 0) {
    list->current = list->tail;
    return list->tail;
  }
  return NULL;
}

//QA
void *ListNext(List *list) {
  if(list->current->next != NULL) {
    list->current = list->current->next;
    return list->current->item;
  }
  return NULL;
}

//QA
void *ListPrev(List *list){
  if(list->current->prev != NULL) {
    list->current = list->current->prev;
    return list->current->item;
  }
  return NULL;
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
  if (!list || list->count == 0) {
    return NULL;
  }
  nodePool[--nodeCurrent] = list->current;
  if (list->count == 1) {
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
    list->count--;
    return NULL;
  }
  if (list->current->prev) {
    list->current->prev->next = list->current->next;
  }
  if (list->current->next) {
    list->current->next->prev = list->current->prev;
  }
  if (list->current == list->tail) {
    list->current = list->tail->prev;
    list->tail->prev->next = NULL;
    list->tail = list->current;
  }
  else if (list->current == list->head) {
    list->head->next->prev = NULL;
    list->head = list->head->next;
    list->current = list->head;
  }
  else {
    list->current = list->current->next;
  }
  list->count--;
  return list->current;
}

void ListConcat (List *list1, List **list2) {
  if (list1 && list2) {
    list1->tail->next = (*list2)->head;
    (*list2)->head->prev = list1->tail;
    list1->count += (*list2)->count;
    *list2 = NULL;
  }
}

// Needs to add node back to pool
void *ListTrim(List *list) {
  if (list->count == 0) {
    return NULL;
  }
  if (list->count == 1) {
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
    list->count--;
    return list->current;
  }
  else {
    list->tail = list->tail->prev;
    list->current = list->tail;
    list->current->next = NULL;
    list->count--;
    return list->current;
  }
}

void *ListSearch(List *list, int (*comparator)(void *item, void *comparisonArg), void *comparisonArg) {
  Node *curr = list->current;
  while (curr) {
    if ( (*comparator)(curr, comparisonArg )) {
      list->current = curr;
      return list->current;
    }
  }
}
