#include "node.h"
#include <stdio.h>
#include "list.h"

void printList(List *list) {
  Node *head = list->head;
  Node *tail = list->tail;
  printf("Values for list are:\n");
  printf("Forward\t\t Backward\n");
  while(head && tail) {
    printf("%4d\t\t %4d\n", *(int *)head->item, *(int *)tail->item );
    head = head->next;
    tail = tail->prev;
  }
  printf("Current item is %d\n", *(int *)ListCurr(list));
}


int main () {
  int values[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
  printf("Creating two lists\n");
  List *list1 = ListCreate();
  List *list2 = ListCreate();

  printf("Testing list Add\n");
  ListAdd(list1, &values[11]);
  printList(list1);
  ListAdd(list1, &values[1]);
  printList(list1);

}
