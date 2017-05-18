#include "list.h"
#include <stddef.h>

Node nodePool[100];
List listHeads[10];
int nodeCounter = 0;
int headCounter = 0;
//Think its fine
List *ListCreate() {
  List* list = &listHeads[headCounter++];
  list->count = 0;
  list->head = NULL;
  list->current = NULL;
  return list;
}
//Think its fine
int ListCount(List *list) {
  return list->count;
}
//Think its fine
void *ListFirst(List *list) {
  if (list->count > 0) {
    list->current = list->head;
    return list->head;
  }
}

//Think its fine
void *ListLast(List *list) {
  if(list->count > 0) {
    list->current = list->tail;
    return list->tail;
  }
}

//Think its fine
void *ListNext(List *list) {
  if(list->current->next != NULL) {
    list->current = list->current->next;
    return list->current->item;
  }
  return NULL;
}

//Think its fine
void *ListPrev(List *list){
  if(list->current->prev != NULL) {
    list->current = list->current->prev;
    return list->current->item;
  }
  return NULL;
}

//done
void *ListCurr(List *list){
  return list->current->item;
}


int ListAdd(List *list, void *item) {
  Node* node = &nodePool[nodeCounter++];
  node->item = item;
  if (list->current != NULL ) {
    node->next = list->current->next;
    node->prev = list->current;
    list->current = node;
  }
  else if (list->count == 0) {
    list->head = node;
    list->tail = node;
    list->current =node;
  }
  else {}
  return 0;
}

int ListInsert(List *list, void *item) {
  Node* node = &nodePool[nodeCounter++];
  node->item = item;
}

int ListAppend(List *list, void *item) {
  Node* node = &nodePool[nodeCounter++];
  node->item = item;
  list->tail->next = node;
  node->prev = list->tail;
  list->tail = node;
}

int ListPrepend(List *list, void *item) {\
  Node* node = &nodePool[nodeCounter++];
  node->item = item;
}

void *ListRemove(List *list) {

}

void ListConcat (List *list1, List *list2) {

}

void *ListTrim(List *list) {

}
