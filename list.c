#include "list.h"
#include <stddef.h>

#define NODEMAX 100
#define HEADMAX 10

Node nodePool[NODEMAX];
List listHeads[HEADMAX];
int nodeCounter = 0;
int headCounter = 0;


Node *ItemCreate(void *item) {
  if (nodeCounter < NODEMAX) {
    Node *node = &nodePool[nodeCounter++];
    node->item = item;
    node->next = NULL;
    node->prev = NULL;
    return node;
  }
  return NULL;
}

//QA
List *ListCreate() {
  if (headCounter < HEADMAX){
    List* list = &listHeads[headCounter++];
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

void *ListTrim(List *list) {

}
