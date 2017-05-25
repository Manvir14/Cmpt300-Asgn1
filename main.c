#include "node.h"
#include <stdio.h>
#include "list.h"

int main () {
  int values[6] = {10,13,15,17,18,19};
  List *list1 = ListCreate();
  List *list2 = ListCreate();

  ListAppend(list1, &values[0]);
  ListAppend(list1, &values[1]);
  ListAppend(list1, &values[2]);
  ListAppend(list1, &values[3]);
  ListAppend(list1, &values[4]);
  //ListAppend(list2, &values[4]);
  //ListInsert(list2, &values[5]);

  //ListLast(list1);
  //ListTrim(list1);
  ListPrev(list1);
  ListRemove(list1);
  ListRemove(list1);
  ListAppend(list1, &values[5]);
  //ListConcat(list1, &list2);
  ListAppend(list1, &values[2]);
  //Printing the list
  Node* curr  = list1->head;
  while (curr){
    printf("List 1: Value is %d\t Count is %d\n", *(int *)curr->item, ListCount(list1));
    curr = curr->next;
  }
  printf("List 1: Current value is %d\n", *(int *)ListCurr(list1));

  Node* curr2  = list2->head;
  while (curr2 != NULL){
    printf("List 2: Value is %d\n", *(int *)curr2->item);
    printf("List 2: Current value is %d\n", *(int *)ListCurr(list2));
    curr2 = curr2->next;
  }
}
