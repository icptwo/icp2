// CH16:shuffle2.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 13
typedef struct
{
  char cards[MAX_SIZE];
  int size;
} CardDeck;
void printDeck(CardDeck deck);   
void shuffle(CardDeck origDeck, int round); 
int main(int argc, char ** argv)
{
  if (argc != 3) { return EXIT_FAILURE; }
  int num   = (int) strtol(argv[1], NULL, 10); // number of cards
  int round = (int) strtol(argv[2], NULL, 10); // how many times
  if ((num < 2) || (num > MAX_SIZE))
    { return EXIT_FAILURE; }
  if (round < 1)
    { return EXIT_FAILURE; }
  char cards[MAX_SIZE] = // use 'T' for 10
    {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
  CardDeck origDeck;
  origDeck.size = num;
  memcpy(origDeck.cards, cards, MAX_SIZE * sizeof(char));
  shuffle(origDeck, round);
  return EXIT_SUCCESS;
}
void printDeck(CardDeck deck)
{
  int ind;
  for (ind = 0; ind < deck.size; ind ++)
    { printf("%c ", deck.cards[ind]); }
  printf("\n");
}
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
		      CardDeck newDeck, int leftind, int rightind,
		      int newind, int round)
{
  int ind;
  if (leftind == -1) 
    {
      for (ind = 0; ind <= rightind; ind ++)
	{ newDeck.cards[ind] = rightDeck.cards[ind]; }
      shuffle(newDeck, round - 1);
      return; 
    }
  if (rightind == -1) 
    {
      for (ind = 0; ind <= leftind; ind ++) 
	{ newDeck.cards[ind] = leftDeck.cards[ind]; }
      shuffle(newDeck, round - 1);
      return; 
    }
  newDeck.cards[newind] = leftDeck.cards[leftind];
  interleaveHelper(leftDeck, rightDeck, newDeck, leftind - 1,
		   rightind, newind - 1, round);
  newDeck.cards[newind] = rightDeck.cards[rightind];
  interleaveHelper(leftDeck, rightDeck, newDeck, leftind,
		   rightind - 1, newind - 1, round);
}
void interleave(CardDeck leftDeck, CardDeck rightDeck, int round)
{
  CardDeck newDeck;
  newDeck.size = leftDeck.size + rightDeck.size;
  interleaveHelper(leftDeck, rightDeck, newDeck,
		   leftDeck.size - 1, rightDeck.size - 1,
		   newDeck.size - 1, round);
}
void shuffle(CardDeck origDeck, int round)
{
  if (round == 0)
    {
      printDeck(origDeck);
      return;
    }
  int numpairs = origDeck.size - 1;
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
      interleave(leftDeck[ind], rightDeck[ind], round);
    }
  free (leftDeck);
  free (rightDeck);
}
