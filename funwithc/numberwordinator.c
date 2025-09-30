/** Number Wordinator
Use C to convert numbers to words

The number 1,147,483,647 can be written like this:

one billion, one hundred and forty-seven million, four hundred and eighty-three
thousand, six hundred and forty-seven

Write a program in C to convert numbers into words like the above. It should
work for the range 0 to 2 billion.
**/

#include <stdio.h>

char zero[4] = "zero";
char one[3] = "one";
char two[3] = "two";
char three[5] = "three";
char four[4] = "four";
char five[4] = "five";
char six[3] = "six";
char seven[5] = "seven";
char eight[5] = "eight";
char nine[4] = "nine";
char ten[3] = "ten";
char eleven[6] = "eleven";
char twelve[6] = "twelve";
char thirteen[8] = "thirteen";
char fourteen[8] = "fourteen";
char fifteen[7] = "fifteen";
char sixteen[7] = "sixteen";
char seventeen[9] = "seventeen";
char eighteen[8] = "eighteen";
char nineteen[8] = "nineteen";
char twenty[6] = "twenty";
char hundred [8] = "hundred";
char thousand[9] = "thousand";
char million [8] = "million";
char billion [8] = "billion";

int convertDigitsToWord (int numberToBeConverted, char *word, int wordlen)
{
  int status = 0;
  if (numberToBeConverted == 0) {snprintf(word, sizeof(zero) + 1, "%s", zero); status = 1;}
  else {

    }
  return status;
}

int main() {
  puts("wordinator!");
  int entry = 0, inputvalid = 0;
  char wordform[512] = {};
  do {
    inputvalid = scanf("%d", &entry);
    if (inputvalid != 1) {
      while (getchar() != '\n')
        ;
    }
  } while (inputvalid != 1);
  printf("Entered digits are:- %d\n", entry);
  if (convertDigitsToWord(entry, wordform, 512) == 1) { printf("Word form is %s\n", wordform); }
  else { puts ("error in conversion"); }
  return 0;
}
