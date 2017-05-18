#include "node.h"
#include <stdio.h>
#include "list.h"

int main () {
  int i = 0;
  int j = 4;
  int k = 5;
  List *testList = ListCreate();
  printf("The lenght of this list is: %d\n", ListCount(testList));
  ListAdd(testList, &j);
  printf("added value");
  Node* curr = testList->head;
  while (curr != NULL) {
    printf("Value is: %d\n", *(int *)curr->item);
    curr = curr->next;
  }
  return 0;

}
