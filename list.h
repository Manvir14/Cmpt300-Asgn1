#include "node.h"

typedef struct list {
  Node *head;
  Node *tail;
  Node *current;
  int count;
} List;


Node *ItemCreate(void *item);

List *ListCreate();

int ListCount(List *list);

void *ListFirst(List *list);

void *ListLast(List *list);

void *ListNext(List *list);

void *ListPrev(List *list);

void *ListCurr(List *list);

int ListAdd(List *list, void *item);

int ListInsert(List *list, void *item);

int ListAppend(List *list,void *item);

int ListPrepend(List *list, void *item);

void *ListRemove(List *list);

void ListConcat(List *list1, List **list2);

void ListFree(List *list, int itemFree);

void *ListTrim(List *list);

void ListPrint(List *list);

void *ListSearch(List *list, int (*comparator)(void *item, void *comparisonArg), void *comparisonArg);
