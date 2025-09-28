/** Number Wordinator
Use C to convert numbers to words

The number 1,147,483,647 can be written like this:

one billion, one hundred and forty-seven million, four hundred and eighty-three
thousand, six hundred and forty-seven

Write a program in C to convert numbers into words like the above. It should
work for the range 0 to 2 billion.
**/

#include <stdio.h>

int convertDigitsToWord (char *word, int wordlen)
{
  return 0;
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
  convertDigitsToWord(wordform, 512);
  printf("Word form is %s\n", wordform);
  return 0;
}
