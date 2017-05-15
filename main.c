#include "node.h"
#include <stdio.h>
#include "list.h"

int main () {
  Node arr[3];
  int i = 0;
  int j = 4;
  int k = 5;
  arr[0].item = &j;
  arr[2].item = &k;
  List testList;
  testList.head = &arr[0];
  testList.head->next = &arr[2];
  testList.head->next->next = NULL;
  Node *curr = testList.head;
  while (curr != NULL) {
    printf("%d\n", *(int *)curr->item);
    curr = curr->next;
  }
  return 0;
}

