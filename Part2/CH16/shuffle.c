// CH16:shuffle.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 13
typedef struct // struct will be explained in Part III of the book
{
  char cards[MAX_SIZE];
  int size;
} CardDeck;
void shuffle(CardDeck origDeck); // Riffle shuffle once
void printDeck(CardDeck deck);   // print the cards
int main(int argc, char ** argv)
{
  if (argc != 2) { return EXIT_FAILURE; }
  int num = (int) strtol(argv[1], NULL, 10); // number of cards
  if ((num < 2) || (num > MAX_SIZE))  { return EXIT_FAILURE; }
  char cards[MAX_SIZE] = // use 'T' for 10
    {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
  CardDeck origDeck;
  origDeck.size = num;
  memcpy(origDeck.cards, cards, MAX_SIZE * sizeof(char));
  shuffle(origDeck);
  return EXIT_SUCCESS;
}
void printDeck(CardDeck deck)
{
  int ind;
  for (ind = 0; ind < deck.size; ind ++)
    { printf("%c ", deck.cards[ind]); }
  printf("\n");
}
// This function creates pairs of left and right decks.
// Each deck has at least one card.
// leftDeck and rightDeck are arrays of CardDeck
// Each pair divides the original deck into two non-overlapping decks and
// together they form the original deck. 
void divide(CardDeck origDeck, CardDeck * leftDeck, CardDeck * rightDeck)
{
  int ind;
  int leftSize;
  int rightSize;
  for (ind = 0; ind < origDeck.size - 1; ind ++)
  {
    leftSize = ind + 1;
    rightSize = origDeck.size - 1 - ind;
    memcpy(leftDeck[ind].cards, origDeck.cards,
	   leftSize * sizeof(origDeck.cards[0]));
    memcpy(rightDeck[ind].cards, & origDeck.cards[ind + 1],
	   rightSize * sizeof(origDeck.cards[0]));
    leftDeck[ind].size = leftSize;
    rightDeck[ind].size = rightSize;
  }
}
void interleaveHelper(CardDeck leftDeck, CardDeck rightDeck,
		      CardDeck newDeck,
		      int leftind, int rightind, int newind)
{
  int ind;
  if (leftind == -1) // no more card from left deck
    {
      for (ind = 0; ind <= rightind; ind ++)
	// put all cards from right deck
	{
	  newDeck.cards[ind] = rightDeck.cards[ind];
	}
      printDeck(newDeck);
      return; 
    }
  if (rightind == -1) // no more card from right deck
    {
      for (ind = 0; ind <= leftind; ind ++)
	// put all cards from left deck
	{
	  newDeck.cards[ind] = leftDeck.cards[ind];
	}
      printDeck(newDeck);
      return; 
    }
  // two options: pick one from left deck or one from right deck
  // from left deck
  newDeck.cards[newind] = leftDeck.cards[leftind];
  interleaveHelper(leftDeck, rightDeck, newDeck,
		   leftind - 1, rightind, newind - 1);
  // from right deck
  newDeck.cards[newind] = rightDeck.cards[rightind];
  interleaveHelper(leftDeck, rightDeck, newDeck,
		   leftind, rightind - 1, newind - 1);
}
// Interleave two decks to generate all possible results.
void interleave(CardDeck leftDeck, CardDeck rightDeck)
{
  CardDeck newDeck;
  newDeck.size = leftDeck.size + rightDeck.size;
  interleaveHelper(leftDeck, rightDeck, newDeck,
		   leftDeck.size - 1, rightDeck.size - 1,
		   newDeck.size - 1);
}
// The shuffle function has the following steps:
// 1. calculate the number of possible left and right decks. It is
//    the number of cards - 1 because the left deck may have 1, 2,...,
//    #cards - 1 cards.
// 2. allocate memory to store these possible pairs of left and right
//    decks.
// 3. send each pair to the interleave function
// 4. release allocated memory
void shuffle(CardDeck origDeck)
{
  int numpairs = origDeck.size - 1;
  // allocate memory
  CardDeck * leftDeck;
  CardDeck * rightDeck;
  leftDeck = malloc(numpairs * sizeof(CardDeck));
  if (leftDeck == NULL)  { return; } // malloc fail
  rightDeck = malloc(numpairs * sizeof(CardDeck));
  if (rightDeck == NULL) // malloc fail
    {
      free (leftDeck);
      return;
    }
  divide(origDeck, leftDeck, rightDeck);
  int ind;
  for (ind = 0; ind < numpairs; ind ++)
    {
      interleave(leftDeck[ind], rightDeck[ind]);
    }
  free (leftDeck);
  free (rightDeck);
}
