#include "node.h"
#include <stdio.h>
#include "list.h"
#include <assert.h>

void printList(LIST *list) {
  Node *head = list->head;
  Node *tail = list->tail;
  printf("Values for list are:\n");
  printf("Forward\t\t Backward\n");
  while(head && tail) {
    printf("%4d\t\t %4d\n", *(int *)head->item, *(int *)tail->item );
    head = head->next;
    tail = tail->prev;
  }
  printf("Number of items is %d\n", ListCount(list));
  if (ListCurr(list)) {
    printf("Current item is %d\n\n", *(int *)ListCurr(list));
  }
  else {
    printf("Current item is NULL\n\n");
  }
}

int comparator(void *item, void *comparisonArg) {
  if (*(int *)item == *(int *)comparisonArg) {
    return 1;
  }
  return 0;
}

void itemFree (void *itemToBeFreed) {
  itemToBeFreed = NULL;
}


int main () {
  int values[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
  int i;
  int *returned;
  LIST *list1 = ListCreate();
  LIST *list3 = ListCreate();
  LIST *list4 = ListCreate();
  for (i=0; i<6; i++) {
    ListAdd(list1, &values[i]);
    if (i<3) {
      ListAdd(list3, &values[i]);
    }
    if (i>2) {
      ListAdd(list4, &values[i]);
    }
  }
  printList(list1);

  printf("Testing listFirst: Current should be 1, Returned should be 1\n");
  returned = ListFirst(list1);
  printf("Returned item is %d\n", *returned);
  printf("Current item is %d\n\n", *(int *)ListCurr(list1));

  printf("Testing ListPrev going before beginning of list: Current should be NULL, Returned should be NULL\n");
  if(!ListPrev(list1)){
    printf("NULL was returned\n" );
  }
  else {
    printf("NULL was not returned\n");
  }
  if(!ListCurr(list1)) {
    printf("Current is before beginning and NULL\n\n" );
  }

  printf("Testing ListNext from before beginning: Current should be 1, Returned should be 1\n");
  returned = ListNext(list1);
  printf("Returned item is %d\n", *returned);
  printf("Current item is %d\n\n", *(int *)ListCurr(list1));

  printf("Testing ListNext: Current should be 2, Returned should be 2\n");
  returned = ListNext(list1);
  printf("Returned item is %d\n", *returned);
  printf("Current item is %d\n\n", *(int *)ListCurr(list1));

  printf("Testing listLast: Current should be 6, Returned should be 6\n");
  returned = ListLast(list1);
  printf("Returned item is %d\n", *returned);
  printf("Current item is %d\n\n", *(int *)ListCurr(list1));

  printf("Testing ListNext past the end of the list: Current should be NULL, Returned should be NULL\n");
  if(!ListNext(list1)){
    printf("NULL was returned\n" );
  }
  else {
    printf("NULL was not returned\n");
  }
  if(!ListCurr(list1)) {
    printf("Current is beyond end and NULL\n\n" );
  }

  printf("Testing ListPrev from past end of list: Current should be 6, Returned should be 6\n");
  returned = ListPrev(list1);
  printf("Returned item is %d\n", *returned);
  printf("Current item is %d\n\n", *(int *)ListCurr(list1));

  printf("Testing ListPrev: Current should be 5, Returned should be 5\n");
  returned = ListPrev(list1);
  printf("Returned item is %d\n", *returned);
  printf("Current item is %d\n\n", *(int *)ListCurr(list1));

  ListPrev(list1);
  ListPrev(list1);

  printf("Testing Add and Insert in middle of list\n");
  printf("10 should be added after 3:\n");
  ListAdd(list1, &values[9]);
  printList(list1);
  printf("12 should be inserted before 10\n");
  ListInsert(list1, &values[11]);
  printList(list1);

  ListFirst(list1);
  ListPrev(list1);

  printf("Testing Add and Insert with current before beginning\n");
  printf("Current is before beginning of list: Inserting 5\n");
  ListInsert(list1, &values[4]);
  printList(list1);
  printf("Current is before beginning of list: Adding 7\n");
  ListPrev(list1);
  ListAdd(list1, &values[6]);
  printList(list1);

  printf("Testing Add and Insert with current after end\n");
  ListLast(list1);
  ListNext(list1);
  printf("Current is beyond end of list: Inserting 11\n");
  ListInsert(list1, &values[10]);
  printList(list1);
  printf("Current is beyond end of list: Adding 4\n");
  ListNext(list1);
  ListAdd(list1, &values[3]);
  printList(list1);


  printf("Creating new list\n\n");
  LIST *list2 = ListCreate();
  for (i=0; i<6; i++) {
    ListAdd(list2, &values[i]);
  }

  printf("Testing listAppend: Current should be 3\n");
  ListAppend(list2, &values[2]);
  printList(list2);

  printf("Testing listPrepend: Current should be 11\n");
  ListPrepend(list2, &values[10]);
  printList(list2);

  ListNext(list2);
  printf("Testing listRemove:\n");
  printf("Removal in middle: Current is 1, after removal should be 2, Returned should be 1:\n");
  returned = ListRemove(list2);
  printf("Returned item is %d\n", *returned);
  printList(list2);

  ListFirst(list2);
  printf("Removal at beginning: Current is 11, after removal should be 2, Returned should be 11:\n");
  returned = ListRemove(list2);
  printf("Returned item is %d\n", *returned);
  printList(list2);

  ListLast(list2);
  printf("Removal at end: Current is 3, after removal should be 6, Returned should be 3:\n");
  returned = ListRemove(list2);
  printf("Returned item is %d\n", *returned);
  printList(list2);

  printf("Testing ListConcat: Concatenating list: {1,2,3} to end of list2:{4,5,6}\n");
  printf("List 1 before concatenating:\n");
  printList(list4);
  printf("List 2 before concatenating:\n");
  printList(list3);
  ListConcat(list4,list3);
  printf("After concatenating list should be {4,5,6,1,2,3}, Current should be 6:\n");
  printList(list4);


  ListFirst(list4);
  printf("Testing ListTrim: Current is 6, after removal should be 2, Returned should be 3:\n");
  returned = ListTrim(list4);
  printf("Returned item is %d\n", *returned);
  printList(list4);

  ListFirst(list4);
  printf("Testing ListSearch: Searching for 2, 2 is in list and should be returned\n");
  returned = ListSearch(list4, comparator, &values[1]);
  printf("Returned item is %d\n", *returned);
  printList(list4);

  ListFirst(list4);
  printf("Testing ListSearch: Searching for 10, 10 is not in list and NULL should be returned\n");
  returned = ListSearch(list4, comparator, &values[9]);
  if (!returned) {
    printf("NULL was returned\n");
  }
  else {
    printf("NULL was not returned\n");
  }
  printList(list2);

  printf("Testing ListFree: Head, tail and current of list should be NULL with all nodes back in pool\n");
  ListFree(list2, itemFree);
  printList(list2);

  LIST *list5 = ListCreate();
  LIST *list6 = ListCreate();
  LIST *list7 = ListCreate();
  LIST *list8 = ListCreate();
  LIST *list9 = ListCreate();
  LIST *list10 = ListCreate();
  LIST *list11 = ListCreate();
  LIST *list12 = ListCreate();
  LIST *list13 = ListCreate();
  printf("Testing ListCreate: NULL should be returned as limit is reached\n");
  if(!list13) {
    printf("NUll was returned\n\n");
  }
  else {
    printf("NULL was not returned\n\n");
  }

  printf("Testing reuse of list heads: List should be created after one is freed, 5 will be added after creation:\n");
  ListFree(list12, itemFree);
  LIST* list14 = ListCreate();
  ListAppend(list14, &values[4]);
  printList(list14);

  printf("Testing reuse of list node: All nodes should be added to list\n");
  while (!ListAppend(list14, &values[2]));
  printf("All nodes currently in use: Adding should return -1\n");
  int nodesAllUsed = ListAdd(list14, &values[6]);
  if (nodesAllUsed) {
    printf("Adding Failed, returned %d\n\n", nodesAllUsed);
  }
  else {
    printf("Should not have been added, returned %d\n\n", nodesAllUsed);
  }
  printf("Nodes all in use then removing a node from list, reusing it in different list, 10 should be added to list:\n");
  ListRemove(list14);
  ListAdd(list10, &values[9]);
  printList(list10);
}
