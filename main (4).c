/*

Create the sentinel node at the beginning of main() and then implement functions
appendNumber( )  and deleteNumber( ).

The sentinel node should always be there at the beginning of the list,
with a data value of -1.  This sentinel Node should not be displayed whenever
you print the list.

 */
#include <stdio.h>  // For printf and scanf
#include <stdlib.h> // For malloc

typedef struct Node
    *NodePtr; // Make:  NodePtr to be a synonym for: struct Node *
struct Node {
  int data;      // The data stored at the node
  NodePtr pNext; // Pointer to the next node
};

//------------------------------------------------------------
// Display the list.  We've supplied this version so your output
// will match the expected test cases.
void displayList(NodePtr pHead) {
  printf("List is: ");
  while (pHead != NULL) {
    // Don't print the sentinel Node value
    if (pHead->data != -1) {
      printf("%d ", pHead->data);
    }
    pHead = pHead->pNext;
  }
  printf("\n");
} // end displayList()

///--------------------------------------------------------------
// Append number at the end of the list.  Add the parameters
// and the code needed to implement this function.
void appendNumber(NodePtr *pHead, NodePtr *pTail, int number) {
  // ... Your code here ...
  NodePtr pTemp = malloc(sizeof(struct Node)); // declare and initialize new
                                               // node
  pTemp->data = number;       // put the data into the new Node
  if ((*pTail)->data == -1) { // if it's the first element to be inserted
    *pTail = pTemp;
    (*pHead)->pNext = pTemp;
  } else {
    (*pTail)->pNext = pTemp;      // set the current tail's next node to be the new node
    *pTail = pTemp; // set tail equal to the new Node
  }

} // end appendNumber()

//--------------------------------------------------------------
// Delete the first (non-sentinel) Node on the list and return the
// number that was in it. Add the parameters and the code needed to
// implement this function.
int deleteNumber(NodePtr *pHead, NodePtr *pTail) {
  // Sanity check: Ensure there is at least one Node on the list
  //printf("pHead->pNext: %p\n pHead: %p\n pTail: %p\n", (*pHead)->pNext, *pHead, *pTail);
  if ((*pHead)->pNext == NULL) {
    printf("Sorry, can't delete from an empty list. \n");
    return -1;
  }

  // Point to node to be deleted
  NodePtr pNodeToDelete = (*pHead)->pNext; // Pointer to node to be deleted
  int value = (*pHead)->pNext->data; // Retrieve value from node to be deleted
  if ((*pHead)->pNext == *pTail) { 
    // if there's only 1 node and it's about to be deleted
    (*pHead)->pNext = NULL;
    *pTail = *pHead;
  }
  else{
    (*pHead)->pNext = pNodeToDelete->pNext;
  }
  free(pNodeToDelete); // Free up memory from old node

  return value;
  // ... Other code ...

} // end deleteNumber()

//--------------------------------------------------------------
// Consider: For input of 1 3 5 -1, what is the output?
int main() {
  // Create a sentinal Node at list beginning, initialize it, and make
  //   both head and tail point to it.
  // ...
  NodePtr sentinel = malloc(sizeof(struct Node));
  sentinel->data = -1;

  NodePtr pHead = sentinel;
  NodePtr pTail = sentinel;

  // ---------------------------------------------------
  // The code below this point should remain unchanged.
  int number = 0;        // Used to store numbers read in
  char menuOption = ' '; // Store user input menu option

  // Loop to allow adding and deleting list values.
  while (menuOption != 'x') {
    printf("Menu: \n");
    printf("  a n  to add value n to the list \n");
    printf("  d    to delete value from the list \n");
    printf("  x    to exit program \n");
    printf("Your choice: ");
    scanf(" %c", &menuOption);

    // Handle menu options
    switch (menuOption) {
    case 'x':
      return 0; // Exit program
      break;
    case 'a':
      scanf("%d", &number);                 // Read in the number to be added
      appendNumber(&pHead, &pTail, number); // Append to end of list
      break;
    case 'd':
      number = deleteNumber(&pHead, &pTail); // Delete from end of list
      if (number != -1) {
        printf("Deleted %d\n", number);
      }
      break;
    default:
      printf("Invalid menu option.  Retry. \n");
      continue;
    }

    printf("\n");
    //printf("displayList runs\n");
    displayList(pHead);
    //printf("displayList finishes\n");
  }

  return 0; // return value to keep C++ happy
} // end main()